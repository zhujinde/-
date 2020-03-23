#pragma once

#include "Dshow.h"  

class CDXGraphNew
{
private:
    //DirectShow��ؽӿڳ�Ա  
    IGraphBuilder   *pGraph;        //�˲������������  
    IMediaControl   *pMediaControl; //ý����ƽӿڣ���run��stop��pause  
    IMediaEventEx   *pMediaEvent;   //ý���¼��ӿ�  
    IBasicVideo     *pBasicVideo;   //��Ƶ�����ӿ�  
    IBasicAudio     *pBasicAudio;   //��Ƶ�����ӿ�  
    IVideoWindow    *pVideoWindow;  //��Ƶ���ڽӿ�  
  
    DWORD           m_dwGraphRegister;  
	IBaseFilter     *m_pLavSplitterSource;
	IBaseFilter     *m_pFileSourceFilter;
	IBaseFilter     *m_pLavVideoDecoder;
	IBaseFilter     *m_pLavAudioDecoder;
	IBaseFilter     *m_pVideoRenderer;
	IBaseFilter     *m_pAudioRender;

public:
	CDXGraphNew(void);
	~CDXGraphNew(void);
	void Release(void);
	bool Create(void);
	bool AddFile(CString FileName);
	bool QueryInterfaces(void);
	HRESULT AddToRot(IUnknown * pUnkGraph, DWORD * pdwRegister);
	void RemoveFromRot(DWORD pdwRegister);
	HRESULT AddFilterByCLSID(IGraphBuilder * pGraph, const GUID& clsid , LPCWCHAR wszName , IBaseFilter ** ppF);
	HRESULT GetUnconectedPin(IBaseFilter * pFilter, PIN_DIRECTION PinDir , IPin ** ppPin);
	HRESULT ConnectFilters(IGraphBuilder * pGraph, IPin * pOut, IBaseFilter * pDest);
	HRESULT ConnectFilters(IGraphBuilder * pGraph, IBaseFilter * pSrc, IBaseFilter * pDest);
	bool RenderFile(CString fileName);
	bool Run(void);
	bool IsRunning(void);
	bool SetDisplayWindow(HWND inWindow);
	bool Stop(void);
	bool IsStopped(void);
	bool IsPaused(void);
};

