#pragma once
#include "Dshow.h"
#include "Vmr9.h"

class CDXGraphVMR9
{
private:
	IGraphBuilder*                g_graph;        //FILTER������
	IBaseFilter*                  g_filter;         //���ڴ���VMR9
	IBaseFilter*                  g_source;        //������ý�����ݴ���
	IEnumPins*                    g_enumpins;     //���ڻ�ȡPIN
	IFilterGraph2*                g_Graph2;             //������Ƶ����Ⱦ����
	IMediaControl*                g_mediaControl;   //ý�����
	IVMRFilterConfig9*            g_filterConfig;     //VMR9����
	IVMRWindowlessControl9*       g_VMR;         //VMR9��WINDOWEDģʽ����
	HWND                          hWnd;           //���������ھ��
public:
	CDXGraphVMR9(void);
	~CDXGraphVMR9(void);
	bool Create(HWND hWnd);
	IPin* GetPin(IBaseFilter * pFilter, PIN_DIRECTION PinDir);
	void play(void);
};

