
// CCDgraphEPDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CCDgraphEP.h"
#include "CCDgraphEPDlg.h"
#include "afxdialogex.h"
#include "D3DShower.h"
#ifdef __cplusplus
extern "C" {
#endif
#include "libavutil/pixdesc.h"
#include "libavutil/imgutils.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#ifdef __cplusplus
} // endof extern "C"
#endif
//#include "SDL/SDL.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCCDgraphEPDlg �Ի���

//����PreTranslateMessage()����ʵ���˳�ȫ��
BOOL CCCDgraphEPDlg::PreTranslateMessage(MSG* pMsg)
{
  if (pMsg->message == WM_KEYDOWN)  
    {  
         if(pMsg->wParam == VK_ESCAPE)
			 pDXGraph->SetFullScreen(0);
		 return true;
		/*
        switch(pMsg->wParam)  
        {  
            case VK_ESCAPE: //Esc�����¼�  
			 {
                pDXGraph->SetFullScreen(0);     
                return true; 
			 }
            case VK_RETURN: //Enter�����¼�  
                return true;  
            default:  
                ;  
        }  
		*/
    }  
      
    return CDialogEx::PreTranslateMessage(pMsg);  
}


CCCDgraphEPDlg::CCCDgraphEPDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCCDgraphEPDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	pDXGraph = new CDXGraph();
}

//�ؼ��Ͷ�Ӧ���������ݽ���
void CCCDgraphEPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICT, m_PICT);
	DDX_Control(pDX, IDC_WEBOFFICECTRL1, m_office);
	DDX_Control(pDX, IDC_PICT1, m_PICT1);
}

//��Ϣӳ���
BEGIN_MESSAGE_MAP(CCCDgraphEPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SHOWPICTURE, &CCCDgraphEPDlg::OnBnClickedShowpicture)
	ON_BN_CLICKED(IDC_PLAYVIDEO, &CCCDgraphEPDlg::OnBnClickedPlayvideo)
	ON_STN_CLICKED(IDC_PICT, &CCCDgraphEPDlg::OnStnClickedPict)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_VIDEO_STOP, &CCCDgraphEPDlg::OnBnClickedVideoStop)
	ON_BN_CLICKED(IDCANCEL, &CCCDgraphEPDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CCCDgraphEPDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_VOLUME_SUB, &CCCDgraphEPDlg::OnBnClickedVolumeSub)
	ON_BN_CLICKED(IDC_VOLUME_ADD, &CCCDgraphEPDlg::OnBnClickedVolumeAdd)
	ON_BN_CLICKED(IDC_FULL_SCREEN, &CCCDgraphEPDlg::OnBnClickedFullScreen)
END_MESSAGE_MAP()

// ʱ����ϢID
static UINT indicators[] =

{

     IDS_INDICATOR_MESSAGE,

     IDS_INDICATOR_TIME

};


// CCCDgraphEPDlg ��Ϣ�������

BOOL CCCDgraphEPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// ��������...���˵�����ӵ�ϵͳ�˵��С�
	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//ʱ�ӳ�ʼ��
    SetTimer(1, 1000, NULL);
    m_bar.Create(this); //We create the status bar
    m_bar.SetIndicators(indicators, 2); //Set the number of panes
    CRect rect;
    GetClientRect(&rect);
//Size the two panes
    m_bar.SetPaneInfo(0, IDS_INDICATOR_MESSAGE,
    SBPS_NORMAL, rect.Width() - 220);
    m_bar.SetPaneInfo(1, IDS_INDICATOR_TIME, SBPS_STRETCH, 0);
//This is where we actually draw it on the screen
   RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST,
   IDS_INDICATOR_TIME);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCCDgraphEPDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCCDgraphEPDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
	//	CDialogEx::OnPaint();

     CPaintDC dc(this); // device context for painting  
     // CPaintDC  dc(this);    
     CRect  rect;    
     GetClientRect(&rect);    
     CDC  dcMem;   //����һ�������䣨�豸�����ģ�  
     dcMem.CreateCompatibleDC(&dc);///��������DC   
     CBitmap  bmpBackground;   //λͼ����  
     bmpBackground.LoadBitmap(IDB_BITMAP1);   //IDB_BITMAP�����Լ���ͼ��Ӧ��ID    
     BITMAP  bitmap;    
     bmpBackground.GetBitmap(&bitmap);  //�����󶨹�ϵ  
     CBitmap  *pbmpOld=dcMem.SelectObject(&bmpBackground);   //����ԭ��CDC���󣬲�ѡ����CDC������DC  
     dc.SetStretchBltMode(COLORONCOLOR);//��ֹbmpͼƬʧ��  
     dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,  bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);   
     // �����˽����,rect.Width(),rect.Height()���������� �������ͼƬ�Ĵ�С��ǰ����ͼƬ�㹻������ͼƬ������ʧ�档����ͼƬʧ�棬�ο���http://       blog.csdn.net/abidepan/article/details/7963929 ��  
     dcMem.SelectObject(pbmpOld);  
     bmpBackground.DeleteObject();  
     dcMem.DeleteDC();  
	}
	
	//��ʼ��ʱ�Զ�����Ĭ�Ͻ���
	ShowPicture_1();
    ShowPicture_2();
}


//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��

HCURSOR CCCDgraphEPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//��ȡ��ʾͼƬ
void CCCDgraphEPDlg::OnBnClickedShowpicture()
{
	if(pDXGraph->IsRunning()){
		pDXGraph->Stop();
		pDXGraph->Release();
	}
//�ļ�ѡ��Ի���ѡȡ�ļ�
	ShowPicture_1();
	CString FilePathName;
    CFileDialog dlg(TRUE, //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
        NULL, 
        NULL,
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        (LPCTSTR)_TEXT("JPG Files (*.jpg)|*.jpg|BMP Files (*.bmp)|*.bmp|PNG Files (*.png)|*.png|All Files (*.*)|*.*||"),
        NULL);
    if(dlg.DoModal()==IDOK)
    {
        FilePathName=dlg.GetPathName(); //�ļ�����������FilePathName��
    }
    else
    {
         return;
    }
// ��Ctringת��Ϊchar[]
   CString fileinfo = FilePathName;  
   int len =WideCharToMultiByte(CP_ACP,0,fileinfo,-1,NULL,0,NULL,NULL);    
   char *szFileName =new char[len +1];    
   WideCharToMultiByte(CP_ACP,0,fileinfo,-1,szFileName,len,NULL,NULL );  

   LoadPicture(szFileName,m_PICT1);
}



//��Ƶ���źͿ���
void CCCDgraphEPDlg::OnBnClickedPlayvideo()
{
	// TODO:
	//pDXGraph = new CDXGraph();
	//�ļ��Ի���ѡ����Ƶ�ļ�
	pDXGraph->Release();
	CString FilePathName;
    CFileDialog dlg(TRUE, //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
        NULL, 
        NULL,
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        (LPCTSTR)_TEXT("MPEG file (*.mpg;*.mpeg)|*.mpg;*.mpeg|AVI file (*.avi)|*.avi|wmv file (*.wmv)|*.wmv|Audio file (*.mp3;*.aac)|*.mp3;*.aac|All Files (*.*)|*.*||"),NULL);   //�ļ���ʽ
    if(dlg.DoModal()==IDOK)
    {
        FilePathName=dlg.GetPathName(); //�ļ�����������FilePathName��
    }
    else
    {
         return;
    }

	if(IsMp3(FilePathName))
		ShowPicture_3();

    CString fileinfo = FilePathName;
    int len =WideCharToMultiByte(CP_ACP,0,fileinfo,-1,NULL,0,NULL,NULL);    
    char *buf =new char[len +1];    
    WideCharToMultiByte(CP_ACP,0,fileinfo,-1,buf,len,NULL,NULL ); 


	if(pDXGraph->Create())
	{
//		char buf[100] = "D:\\Multimedia_files\\kungfu.mpg";
//		char buf[100] = "C:\\MyProject\\Hero.mpg";
		char * pf = buf;
		pDXGraph->RenderFile(pf);
		pDXGraph->SetDisplayWindow(m_PICT.GetSafeHwnd());
		pDXGraph->Pause();
		pDXGraph->Run();
//		ShowPicture_1();
	}
}
void CCCDgraphEPDlg::OnBnClickedVideoStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
   if(pDXGraph->IsRunning())
		pDXGraph->Pause();
   else if(pDXGraph->IsPaused())
	   pDXGraph->Run();
   else
	   ;
}
void CCCDgraphEPDlg::OnBnClickedVolumeSub()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	long volume = 0;
	volume = pDXGraph->GetAudioVolume();
	pDXGraph->SetAudioVolume(volume-1000);

}
void CCCDgraphEPDlg::OnBnClickedVolumeAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	long volume = 0;
	volume = pDXGraph->GetAudioVolume();
	pDXGraph->SetAudioVolume(volume+1000);
}
void CCCDgraphEPDlg::OnBnClickedFullScreen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		//	bool GetFullScreen(void);
	//  bool SetFullScreen(bool inEnabled);
	if(pDXGraph->GetFullScreen())
		pDXGraph->SetFullScreen(0);
//	if(pDXGraph->GetFullScreen() == 0)
//		pDXGraph->SetFullScreen(1);
	else
		pDXGraph->SetFullScreen(1);
}


void CCCDgraphEPDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CTime t = CTime::GetCurrentTime();
    m_bar.SetPaneText(1, t.Format(_T("%Y��%m��%d�� ����%w %H:%M:%S")));
    CDialog::OnTimer(nIDEvent);
    CDialogEx::OnTimer(nIDEvent);
}

bool CCCDgraphEPDlg::IsMp3(CString FilePath)
{
    CString  object;
	object=FilePath.Right(4);
	if(object == ".mp3" )
		return true;
	else
		return false;
}



//��Ƶ������Ĭ�ϱ���ͼƬ
void CCCDgraphEPDlg::ShowPicture_1()
{
	// TODO:
    char szFileName[128] = "D:\\Multimedia_files\\��Ƶ������.jpg";
    LoadPicture(szFileName,m_PICT);

}
//ͼƬ������Ĭ�ϱ���ͼƬ
void CCCDgraphEPDlg::ShowPicture_2()
{

    char szFileName[128] = "D:\\Multimedia_files\\ͼƬ������.jpg";
    LoadPicture(szFileName,m_PICT1);

}
//��Ƶ������������Ƶ�ļ�ʱ����ͼƬ
void CCCDgraphEPDlg::ShowPicture_3()
{

    char szFileName[128] = "D:\\Multimedia_files\\���ֲ���.jpg";
	LoadPicture(szFileName,m_PICT);

}

void CCCDgraphEPDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}

void CCCDgraphEPDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}

void CCCDgraphEPDlg::OnStnClickedPict()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//ͼƬ���غ���
void CCCDgraphEPDlg::LoadPicture(char szFileName[],CStatic kongjian)
{
	AVCodecContext *pCodecCtx = NULL;
	AVFrame *pFrame = NULL;
	AVFrame *pFrameYUV = NULL;
	AVCodec *pCodec = NULL;
	AVFormatContext *pFormatCtx = NULL;
	struct SwsContext *img_convert_ctx;
	unsigned char *out_buffer;                                  //ffmpga��ȡ����Ƶ�ļ����ɸ����ļ������Զ�ʶ��
	int ret;

	int decLen = 0;
	int frame = 0;
//    char szFileName[128] = "D:\\Multimedia_files\\���ֲ���.jpg";

	av_register_all();
	avformat_network_init();
	pFormatCtx = avformat_alloc_context();

	/* Open input video file */
	if (avformat_open_input(&pFormatCtx,szFileName, NULL, NULL) != 0)
		return ;

	/* Retrieve stream information */
	if (avformat_find_stream_info(pFormatCtx,NULL) < 0)
		return;

	/* Find the first video stream */
	int videoStream = -1;
	for (int i = 0; i < (int)pFormatCtx->nb_streams; i++) 
	{
		if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) 
		{
			videoStream = i;
			break;
		}
	}

	if (videoStream == -1)
		return ;
	// Didn't find a video stream
	/* Get a pointer to the codec context for the video stream */
    
	pCodecCtx = avcodec_alloc_context3(NULL);
    if (!pCodecCtx)
        return ;

    ret = avcodec_parameters_to_context(pCodecCtx, pFormatCtx->streams[videoStream]->codecpar);
    if (ret < 0)
        return ;

    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if (pCodec == NULL) 
	{
		return ;
	}
	/* Open codec */
	if (avcodec_open2(pCodecCtx, pCodec,NULL)<0)
		return ; // Could not open codec

		//Set up screen
	CRect cr;
	GetClientRect(&cr);
	int w = cr.Width();
	int h = cr.Height();

	pFrame = av_frame_alloc();
	pFrameYUV = av_frame_alloc();

    out_buffer=(unsigned char *)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_YUV420P,w,h,1));  
    av_image_fill_arrays(pFrameYUV->data, pFrameYUV->linesize,out_buffer,  
        AV_PIX_FMT_YUV420P,w,h,1);  

	img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
		w, h, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);

	/* flag whether we get a decoded yuv frame */
	int packetno = 0;

	AVPacket packet;
	av_init_packet(&packet);
	
	while (av_read_frame(pFormatCtx, &packet) >= 0) 
	{
		/* Is this a packet from the video stream? */
		if (packet.stream_index == videoStream) 
		{
			ret = avcodec_send_packet(pCodecCtx, &packet);
			if (ret != 0)
			{
				break;
			}
			while( avcodec_receive_frame(pCodecCtx, pFrame) != 0);
//			ret = avcodec_receive_frame(pCodecCtx, pFrame);

			img_convert_ctx = sws_getCachedContext(img_convert_ctx,
				pFrame->width, pFrame->height, (AVPixelFormat)(pFrame->format),
				w, h,
				AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
			if (img_convert_ctx == NULL)
			{
				exit(1);
			}
			ret = sws_scale(img_convert_ctx, pFrame->data, pFrame->linesize,
				0, pFrame->height, pFrameYUV->data, pFrameYUV->linesize);

			hvframe frame;
			CD3DShower dd;
//			pFrameYUV->height = h;

			frame.h = h;                                //pFrame->height;
			frame.y = pFrameYUV->data[0];
			frame.u = pFrameYUV->data[1];
			frame.v = pFrameYUV->data[2];
			frame.ypitch = pFrameYUV->linesize[0];
			frame.uvpitch = pFrameYUV->linesize[1];

			dd.InitD3D(kongjian.GetSafeHwnd(),w,h);        //m_PICTΪ�ؼ�
			dd.Render(&frame/* pFrameYUV*/);
		}
	}

	/* Free the YUV frame */
	av_free(pFrame);

	av_free(out_buffer);

	av_free(pFrameYUV);

	/* Close the codec */
	avcodec_close(pCodecCtx);

	/* Close the video file */
	avformat_close_input(&pFormatCtx);
}



/*   //���ÿؼ�����͸��
HBRUSH CCCDgraphEPDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)   
{  
 HBRUSH hbr = CCCDgraphEPDlg::OnCtlColor(pDC, pWnd, nCtlColor);  
  
 if( nCtlColor == CTLCOLOR_STATIC)        
 {      
  pDC->SetBkMode(TRANSPARENT);   //���ñ���͸��   
  return   HBRUSH(GetStockObject(HOLLOW_BRUSH));  
 }   
 return hbr;  
}
*/