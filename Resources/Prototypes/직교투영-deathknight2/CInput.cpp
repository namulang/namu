#include "CInput.h"
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia.07 - 10 - 10 생성자
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━.
CInputDevice::CInputDevice()
{
    m_pDevice = NULL;
    m_x = m_y = 0;
    ZeroMemory( m_keyLock, sizeof( BOOL ) * 256 );
    ZeroMemory( &m_mouseState, sizeof( DIMOUSESTATE ) );
    ZeroMemory( m_keyboardState, 256 );
    ZeroMemory( m_pressedKeys, 256 );
    ZeroMemory( m_pressedButtons, 4 );
}


//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia.07 - 10 - 10 초기화
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━.
BOOL CInputDevice::Initialize( LPDIRECTINPUT8 pDI, HWND hWnd, DIRECTINPUTTYPE type )
{
    // Check for a valid parent DIRECTINPUT8 interface
    if ( pDI == NULL || type == DIT_FORCE_DWORD )
    {
        return FALSE;
    }
    Release();

    DIDATAFORMAT* pDataFormat;
    m_hWnd = hWnd;
    m_type = type;
    
    // Create the device
    switch( type )
    {
    case DIT_KEYBOARD:
        if ( FAILED( pDI->CreateDevice( GUID_SysKeyboard, &m_pDevice, NULL ) ) )
        {
			MessageBox(g_hWnd, "Direct Input Create Error", "에러", MB_OK);
            return FALSE;
        }
        pDataFormat = (DIDATAFORMAT*)&c_dfDIKeyboard;
        break;
    case DIT_MOUSE:
        if ( FAILED( pDI->CreateDevice( GUID_SysMouse, &m_pDevice, NULL ) ) )
        {
			MessageBox(g_hWnd, "Direct Input Create Error", "에러", MB_OK);
            return FALSE;
        }
        pDataFormat = (DIDATAFORMAT*)&c_dfDIMouse;
        break;
    default: 
        return FALSE;
    }

    // Set the data format
    if( FAILED( m_pDevice->SetDataFormat( pDataFormat ) ) )
    {
		MessageBox(hWnd, "데이터 타입 설정 실패", "에러", MB_OK);
        return FALSE;
    }

    // Set the cooperative level
    if( FAILED( m_pDevice->SetCooperativeLevel( hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE ) ) )
    {
		MessageBox(hWnd, "협력 모드 설정 실패", "에러", MB_OK);
        return FALSE;
    }

    // Acquire the device
    if( FAILED( m_pDevice->Acquire() ) )
    {
        MessageBox(hWnd, "접근 권한 획득 실패", "에러", MB_OK);
        return FALSE;
    }

    return TRUE;
}


//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
// Narusia.07 - 10 - 10 현재 장치 상태
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━.
void CInputDevice::Read()
{
    if ( !m_pDevice )
    {
        return;
    }
    
    // Grab the data 
    if ( m_type == DIT_MOUSE )
    {
        HRESULT hr = m_pDevice->GetDeviceState( sizeof( DIMOUSESTATE ), (LPVOID)&m_mouseState );
        if ( FAILED( hr )  )
        {
            if ( hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED )
            {
                // Device is lost, try to reaquire it
                m_pDevice->Acquire();
            }
            return;
        }
        // Store cursor position
        POINT pt;
        GetCursorPos( &pt );
        ScreenToClient( m_hWnd, &pt );
        m_x = pt.x;
        m_y = pt.y;
        // Get pressed keys
        for ( int i = 0; i < 4; i++ )
        {
            if ( m_mouseState.rgbButtons[i] & 0x80 )
            {
                m_pressedButtons[i] = TRUE;
            }
            else
            {
                m_pressedButtons[i] = FALSE;
            }
        }
    }
    else if ( m_type == DIT_KEYBOARD )
    {
        HRESULT hr = m_pDevice->GetDeviceState( 256, (LPVOID)&m_keyboardState );
        if ( FAILED( hr )  )
        {
            if ( hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED )
            {
                // Device is lost, try to reaquire it
                m_pDevice->Acquire();
            }
            return;
        }
        // Get pressed keys and release locks on key up
        for ( int i = 0; i < 256; i++ )
        {
            if ( !(m_keyboardState[i] & 0x80) )
            {
                // Key is up so release lock
                m_keyLock[i] = FALSE;
                m_pressedKeys[i] = FALSE;
            }
            else
            {
                // Key is pressed if it isn't locked
                m_pressedKeys[i] = !(m_keyLock[i]);
            }
        }
    }
}

void CInputDevice::LockKey( DWORD key )
{
    m_keyLock[key] = TRUE;
}

void CInputDevice::Release()
{
    if( m_pDevice )
    {
        m_pDevice->Unacquire();
        SAFE_RELEASE( m_pDevice );
    }
}