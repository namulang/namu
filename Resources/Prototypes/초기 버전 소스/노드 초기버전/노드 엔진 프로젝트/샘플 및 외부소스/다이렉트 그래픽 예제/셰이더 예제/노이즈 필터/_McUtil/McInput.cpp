// Implementation of the CMcInput class.
//
////////////////////////////////////////////////////////////////////////////////


#include "../_StdAFX.h"


CMcInput::CMcInput()
{
	m_hWnd		= NULL; // for Mouse

	memset(m_KeyOld, 0, sizeof(m_KeyOld));
	memset(m_KeyCur, 0, sizeof(m_KeyCur));
	memset(m_KeyMap, 0, sizeof(m_KeyMap));

	memset(m_BtnCur, 0, sizeof(m_BtnCur));
	memset(m_BtnOld, 0, sizeof(m_BtnOld));
	memset(m_BtnMap, 0, sizeof(m_BtnMap));

	m_vcCur = D3DXVECTOR3( 0, 0, 0);
	m_vcOld = D3DXVECTOR3( 0, 0, 0);
	m_vcEps = D3DXVECTOR3( 0, 0, 0);


	m_dTimeDC	= 0;
	memset(m_dBtnBgn, 0, sizeof(m_dBtnBgn));
	memset(m_dBtnCnt, 0, sizeof(m_dBtnCnt));
}

CMcInput::~CMcInput()
{

}

INT	CMcInput::Create(HWND hWnd)
{
	m_hWnd		= hWnd;

	memset(m_KeyOld, 0, sizeof(m_KeyOld));
	memset(m_KeyCur, 0, sizeof(m_KeyCur));
	memset(m_KeyMap, 0, sizeof(m_KeyMap));

	memset(m_BtnCur, 0, sizeof(m_BtnCur));
	memset(m_BtnOld, 0, sizeof(m_BtnOld));
	memset(m_BtnMap, 0, sizeof(m_BtnMap));

	m_vcCur = D3DXVECTOR3( 0, 0, 0);
	m_vcOld = D3DXVECTOR3( 0, 0, 0);
	m_vcEps = D3DXVECTOR3( 0, 0, 0);


	m_dTimeDC	= GetDoubleClickTime();

	memset(m_dBtnBgn, 0, sizeof(m_dBtnBgn));
	memset(m_dBtnCnt, 0, sizeof(m_dBtnCnt));

	m_dBtnBgn[0]	= GetTickCount();

	for(int i=1; i<MAX_INPUT_BTN; ++i)
	{
		m_dBtnBgn[i]	= m_dBtnBgn[0];
	}

	memset(m_dBtnCnt, 0, sizeof(m_dBtnCnt));

	//UINT ucNumLines=3;  // 3 is the default
	UINT ucNumLines=0;  // 3 is the default
	SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &ucNumLines, 0);

	return 0;
}


INT CMcInput::FrameMove()	// Mouse
{
	INT i	= 0;

	// 1. current 값을 old에 복사, 이전 상태를 저장한다.
	memcpy(m_KeyOld, m_KeyCur, sizeof(m_KeyOld));
	memcpy(m_BtnOld, m_BtnCur, sizeof(m_BtnOld));		// Mouse


	// 2. Current 와 Map의 값을 0으로 초기화
	memset(m_KeyCur, 0, sizeof(m_KeyCur));
	memset(m_KeyMap, 0, sizeof(m_KeyMap));

	memset(m_BtnCur, 0, sizeof(m_BtnCur));				// Mouse
	memset(m_BtnMap, 0, sizeof(m_BtnMap));
	

	// 3. current 이벤트를 가져옴.
	GetKeyboardState(m_KeyCur);

	
	m_BtnCur[0] = (GetAsyncKeyState(VK_LBUTTON) & 0x8000)? 1: 0;	// Left Button
	m_BtnCur[1] = (GetAsyncKeyState(VK_RBUTTON) & 0x8000)? 1: 0;	// Right Button
	m_BtnCur[2] = (GetAsyncKeyState(VK_MBUTTON) & 0x8000)? 1: 0;	// Middle Button


	// Keyboard
	for(i=0; i<MAX_INPUT_KEY; ++i)
	{
		//		SHORT	vKey = GetKeyboardState(nKey) & 0x8000;		// 현재의 키보드 상태를 읽어온다.
		BYTE	vKey = m_KeyCur[i] & 0x80;

		m_KeyCur[i] = (vKey)? 1: 0;

		INT nOld = m_KeyOld[i];
		INT nCur = m_KeyCur[i];

		if		(0 == nOld && 1 ==nCur) m_KeyMap[i] = EINPUT_DOWN;	// Down
		else if (1 == nOld && 0 ==nCur) m_KeyMap[i] = EINPUT_UP;	// UP
		else if (1 == nOld && 1 ==nCur) m_KeyMap[i] = EINPUT_PRESS;	// PRESS
		else							m_KeyMap[i] = EINPUT_NONE;	// NONE
	}
	
	
	// Mouse
	for(i=0; i<MAX_INPUT_BTN; ++i)
	{
		INT nOld = m_BtnOld[i];
		INT nCur = m_BtnCur[i];

		if		(0 == nOld && 1 ==nCur) m_BtnMap[i] = EINPUT_DOWN;
		else if (1 == nOld && 0 ==nCur) m_BtnMap[i] = EINPUT_UP;
		else if (1 == nOld && 1 ==nCur) m_BtnMap[i] = EINPUT_PRESS;
		else							m_BtnMap[i] = EINPUT_NONE;	// NONE
	}



	// 2. Update Mouse
	POINT pt;
	::GetCursorPos(&pt);
	::ScreenToClient(m_hWnd, &pt);

	m_vcOld.x = m_vcCur.x;
	m_vcOld.y = m_vcCur.y;

	m_vcCur.x = FLOAT(pt.x);
	m_vcCur.y = FLOAT(pt.y);

	m_vcEps = m_vcCur - m_vcOld;
	m_vcOld.z = m_vcCur.z;



	//3. Double Check
	DWORD dBtnCur = GetTickCount();

	for(i=0; i<MAX_INPUT_BTN; ++i)
	{
		if(EINPUT_DOWN == m_BtnMap[i])
		{
			if( 1== m_dBtnCnt[i])
			{
				if( (dBtnCur - m_dBtnBgn[i]) >= m_dTimeDC)
				{
					m_dBtnCnt[i] = 0;
				}
			}


			++m_dBtnCnt[i];

			if(1 == m_dBtnCnt[i])
			{
				m_dBtnBgn[i]	= dBtnCur;
			}
		}


		if(EINPUT_UP == m_BtnMap[i])
		{
			if( 1== m_dBtnCnt[i])
			{
				if( (dBtnCur - m_dBtnBgn[i]) >= m_dTimeDC)
				{
					m_dBtnCnt[i] = 0;
				}
			}

			else if( 2 == m_dBtnCnt[i])
			{
				if( (dBtnCur- m_dBtnBgn[i]) <= m_dTimeDC)
				{
					m_BtnMap[i] = EINPUT_DBCLC;
				}

				m_dBtnCnt[i] =0;
			}
		}

	}

//
//	mouse_event(MOUSEEVENTF_MOVE, -1, 0, 0,0);//	mouse_event(MOUSEEVENTF_MOVE, -1, 0, 0,0);


	return 0;
}


BOOL CMcInput::KeyDown(INT nKey)
{
	return m_KeyMap[nKey] == EINPUT_DOWN;
}

BOOL CMcInput::KeyUp(INT nKey)
{
	return m_KeyMap[nKey] == EINPUT_UP;
}

BOOL CMcInput::KeyPress(INT nKey)
{
	return m_KeyMap[nKey] == EINPUT_PRESS;
}

INT CMcInput::KeyState(INT nKey)
{
	return m_KeyMap[nKey];
}

// Mouse

BOOL CMcInput::BtnDown(INT nBtn)
{
	return m_BtnMap[nBtn] == EINPUT_DOWN;
}

BOOL CMcInput::BtnUp(INT nBtn)
{
	return m_BtnMap[nBtn] == EINPUT_UP;
}

BOOL CMcInput::BtnPress(INT nBtn)
{
	return m_BtnMap[nBtn] == EINPUT_PRESS;
}

INT CMcInput::BtnState(INT nBtn)
{
	return m_BtnMap[nBtn];
}

D3DXVECTOR3 CMcInput::GetMousePos()
{
	return m_vcCur;
}


D3DXVECTOR3 CMcInput::GetMouseEps()
{
	return m_vcEps;
}



void CMcInput::AddZ(INT d)
{
	m_vcOld.z = m_vcCur.z;
	m_vcCur.z += FLOAT(d);
}


LRESULT CMcInput::MsgProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	if( WM_MOUSEWHEEL == msg )
	{
		INT c= HIWORD(wParam);
		INT d= LOWORD(wParam);

		AddZ( short( HIWORD(wParam) ) );
	}

	return TRUE;
}
