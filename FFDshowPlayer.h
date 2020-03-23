#pragma once
#include "Dshow.h"

class CFFDshowPlayer
{
public:
	IGraphBuilder *pGB; //Graph Manager����
	IVideoWindow *pVW; //������Ƶ��ʾ���ڶ���
	IMediaControl *pMC; //��Ƶ���ſ��ƶ���
	IBasicAudio *pBA; //��Ƶ���ƶ���
	IBasicVideo *pBV; //��Ƶ���ƶ���
	IMediaEvent *pME; //Dshow�¼���������

	 IBaseFilter * pF_source;

public:
	CFFDshowPlayer(void);
	~CFFDshowPlayer(void);
	void Release(void);
	bool Create(void);
	bool QueryInterfaces(void);
	bool LoadFile(CString FileName);
};

