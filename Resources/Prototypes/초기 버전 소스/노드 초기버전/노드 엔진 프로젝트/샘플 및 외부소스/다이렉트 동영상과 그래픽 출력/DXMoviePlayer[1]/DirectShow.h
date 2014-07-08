#ifndef __DIRECT_SHOW_H__
#define __DIRECT_SHOW_H__


#include <dshow.h>

#define STREAM_TYPE_MUSIC			1
#define STREAM_TYPE_MOVIE			2


#define STREAM_STATE_PLAY			1
#define STREAM_STATE_STOP			2
#define STREAM_STATE_PAUSE			3

#define VOLUME_FULL					0L
#define VOLUME_SILENCE				-10000L
enum PLAYSTATE {STOP, PAUSE, RUNNING, INIT};
#define WM_GRAPHNOTIFY  WM_USER+13

/////////////////////////////////////////////////////////////////////////////////////////////////////
// 다이렉트쇼 클래스
/////////////////////////////////////////////////////////////////////////////////////////////////////
class CDirectShow
{
protected:
	IGraphBuilder*		m_pGB;
	IMediaControl*		m_pMC;
	IMediaEventEx*		m_pME;
	IVideoWindow*		m_pVW;
	IBasicAudio*		m_pBA;
	IBasicVideo*		m_pBV;
	IMediaSeeking*		m_pMS;
	IMediaPosition*		m_pMP;
	IVideoFrameStep*	m_pFS;
	DWORD				m_dwStream;
protected:
	HWND				m_hWnd;
	LONG				m_lVolume;	/* play volume */
	PLAYSTATE			m_CPState;	/* clip play state */
	BOOL				m_bReady;	/* clip play ready */

public:
	CDirectShow();
	virtual ~CDirectShow();
	CDirectShow(DWORD dwStream);

public:
	void Initial(void);
	void Release(void);
	BOOL PlayClip(HWND hWnd, LPTSTR szFile);	/* open clip and play */
	HRESULT InitVideoWindow(int nMultiplier, int nDivider);
	BOOL GetFrameStepInterface(void);


	void StopClip(void);
	void PauseClip(void);
	BOOL PlayClip(void);	/* play clip */
	//void RemoveGraphFromRot(DWORD pdwRegister);
	BOOL IS_FINISHED(void);	/* is finished */
	IVideoWindow* GetVideoWindow(void) { return m_pVW; }
	

public:
	inline PLAYSTATE GetState(void) { return m_CPState; }	/* get state */
	inline void SetState(PLAYSTATE CPState) { m_CPState = CPState; }	/* set state */
	//HRESULT AddGraphToRot(IUnknown *pUnkGraph, DWORD *pdwRegister);	
	HRESULT HandleGraphEvent(void);

};
void RemoveGraphFromRot(DWORD pdwRegister);
HRESULT AddGraphToRot(IUnknown *pUnkGraph, DWORD *pdwRegister);	
#endif
