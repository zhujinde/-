
// CCDgraphEPDlg.h : ͷ�ļ�
//

#pragma once

#include "DXGraph.h"
#include "afxwin.h"
#include "webofficectrl1.h"

// CCCDgraphEPDlg �Ի���
class CCCDgraphEPDlg : public CDialogEx
{
//	CBrush m_brush;   //������ˢ
// ����
public:
	CCCDgraphEPDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CCDGRAPHEP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CStatusBar m_bar; //״̬��ʱ��

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	CString GetFileTitleFromFileName(CString FileName , bool Ext);
//	void CreateGraph(void);
//	void DestroyGraph(void);
	void ShowPicture_1();
	void ShowPicture_2();
	void ShowPicture_3();
	bool IsMp3(CString FilePath);
	void LoadPicture(char szFileName[],CStatic kongjian);
public:
	CDXGraph* pDXGraph;
	CStatic m_PICT;
	CWebofficectrl1 m_office;
	CStatic m_PICT1;
	//���ظú���
	BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedShowpicture();
	afx_msg void OnStnClickedPict();
	afx_msg void OnBnClickedPlayvideo();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedVideoStop();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);  //���ÿؼ�����͸��
	afx_msg void OnBnClickedVolumeSub();
	afx_msg void OnBnClickedVolumeAdd();
	afx_msg void OnBnClickedFullScreen();
};
