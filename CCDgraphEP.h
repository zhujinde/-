
// CCDgraphEP.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCCDgraphEPApp:
// �йش����ʵ�֣������ CCDgraphEP.cpp
//

class CCCDgraphEPApp : public CWinApp
{
public:
	CCCDgraphEPApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCCDgraphEPApp theApp;