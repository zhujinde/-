#include "StdAfx.h"
#include "DXGraphVMR9.h"


CDXGraphVMR9::CDXGraphVMR9(void)
{
}


CDXGraphVMR9::~CDXGraphVMR9()
{
}


bool CDXGraphVMR9::Create(HWND hWnd)
{
	if(FAILED(CoCreateInstance(CLSID_FilterGraph,NULL,CLSCTX_INPROC_SERVER,IID_IGraphBuilder,(void **)&g_graph)))
	{
       return false;
	}

	if(FAILED(CoCreateInstance(CLSID_VideoMixingRenderer9,NULL,CLSCTX_INPROC_SERVER,IID_IBaseFilter,(void **)&g_filter)))
	{
        return false;
	}

	//add the VMR-9 to the filter graph
	if(FAILED(g_graph->AddFilter(g_filter, L"VMR9")))
	{
		return false;
	}

	//����VMRFilterConfig9
	if(FAILED(g_filter->QueryInterface(IID_IVMRFilterConfig9, reinterpret_cast<void**>(&g_filterConfig))))
	{
         return false;
	}

	g_filterConfig->SetRenderingMode(VMR9Mode_Windowless);  //��������ΪWINDOWLESSģʽ

	//����VMRWindowlessControl9
	if(FAILED(g_filter->QueryInterface(IID_IVMRWindowlessControl9, reinterpret_cast<void**>(&g_VMR))))
	{
         return false;
	}

	g_VMR->SetVideoClippingWindow(hWnd);    //ָ��Ҫ��Ⱦ�Ĵ���Ϊ���ǵ�Ӧ�ó���
                                                                      //������
	//����������������ǵ���Ⱦ����Ϊ����Ӧ�ó���ͻ������������ù��������ڴ���ģ//ʽ��ȫ��ģʽ��
	RECT *clientRect = new RECT;
	::GetClientRect(hWnd, clientRect );
	g_VMR->SetVideoPosition( NULL, clientRect );

	g_graph->AddSourceFilter(L"C:\\MyProject\\CircleofLife.mpg", L"source", &g_source);  //����Դ����

	//����IFilterGrahp2����ý����
	if(FAILED(g_graph->QueryInterface(IID_IFilterGraph2,reinterpret_cast<void**>(&g_Graph2))))
	{
		return false;
	}

	
	//ָ��RENDER��Ⱦ�豸�������豸�����ݽ��д���
	g_Graph2->RenderEx(GetPin(g_source,PINDIR_OUTPUT),AM_RENDEREX_RENDERTOEXISTINGRENDERERS,NULL);

	//����MediaControl���Ʋ���
	if(FAILED(g_graph->QueryInterface(IID_IMediaControl,reinterpret_cast<void**>(&g_mediaControl))))
	{
		return false;
	}

	return false;
}


IPin* CDXGraphVMR9::GetPin(IBaseFilter * pFilter, PIN_DIRECTION PinDir)
{
    BOOL       bFound = FALSE;
    IEnumPins  *pEnum;
    IPin       *pPin;
    HRESULT hr = pFilter->EnumPins(&pEnum);  //���������豸��PIN
    if (FAILED(hr))
    {
        return NULL;
    }
    while(pEnum->Next(1, &pPin, 0) == S_OK)
    {
        PIN_DIRECTION PinDirThis;
        pPin->QueryDirection(&PinDirThis);
        if (bFound = (PinDir == PinDirThis))   //�ҵ������豸�����PIN
            break;
        pPin->Release();
    }
    pEnum->Release();
    
	if(!bFound)MessageBox(NULL,L"Pin����ʧ��",L"PowerVideo",MB_OK);
    return (bFound ? pPin : NULL); 
}
//�÷�����Ҫ���ǰ���g_Graph2->RenderEx�����������豸��ý�����PIN���ж���
//�Ա㽫�����豸������ý����Ϣ������RENDER��Ӧ�ó��򴴽�����Ⱦ����


void CDXGraphVMR9::play(void)
{
	g_mediaControl->Run();   //����
}
