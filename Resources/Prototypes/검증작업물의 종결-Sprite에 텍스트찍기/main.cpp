// main.cpp : Defines the entry point for the application.
//
#include <windows.h>
#include <WindowsX.h>
#include <d3dx9.h>
#include "resource.h"
#include <MMSystem.h>
#include <atlstr.h>
#pragma comment(lib, "winmm.lib")

char sen[256] = {0 ,};
int len = 0;

//-----------------------------------------------------------------------------
// GLOBALS
//-----------------------------------------------------------------------------
HWND						g_hWnd					= NULL;
LPDIRECT3D9					g_pD3D					= NULL;
LPDIRECT3DDEVICE9			g_pD3DDevice			= NULL;
ID3DXSprite *				g_pD3DXSprite			= NULL;
LPDIRECT3DTEXTURE9			g_pTexture				= NULL;
const int					SCREEN_WIDTH			= 800;

const int					SCREEN_HEIGHT			= 600;
LPD3DXFONT font;
POINT cs;
double	width_correction = 0.L,
		height_correction = 0.0l;
//-----------------------------------------------------------------------------
// PROTOTYPES
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT	InitializeD3D		( );
void RenderFrame			( );


//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR     lpCmdLine,
                    int       nCmdShow )
{
	WNDCLASSEX	winClass;
	MSG			uMsg;
	HRESULT		hr;

    memset(&uMsg,0,sizeof(uMsg));

	winClass.lpszClassName = "MY_WINDOWS_CLASS";
	winClass.cbSize        = sizeof(WNDCLASSEX);
	winClass.style         = CS_HREDRAW | CS_VREDRAW;
	winClass.lpfnWndProc   = WindowProc;
	winClass.hInstance     = hInstance;
	winClass.hIcon	       = LoadIcon(hInstance, (LPCTSTR)IDC_DXSPRITE);
    winClass.hIconSm	   = LoadIcon(hInstance, (LPCTSTR)IDC_DXSPRITE);
	winClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winClass.lpszMenuName  = NULL;
	winClass.cbClsExtra    = 0;
	winClass.cbWndExtra    = 0;

	if( !RegisterClassEx(&winClass) )
		return E_FAIL;

	g_hWnd = CreateWindowEx( NULL, "MY_WINDOWS_CLASS", 
                             "Direct3D 9 - ID3DXSprite Example",
						     WS_OVERLAPPEDWINDOW | WS_VISIBLE,
					         0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, NULL, NULL, hInstance, NULL );

	if( g_hWnd == NULL )
		return E_FAIL;

    ShowWindow( g_hWnd, nCmdShow );
    UpdateWindow( g_hWnd );

	//----------------------------------------------------------------
	// Create the DirectX device
	//----------------------------------------------------------------
	if (FAILED( InitializeD3D()))
		return 0;


	//----------------------------------------------------------------
	// CREATE THE ID3DXSprite
	//----------------------------------------------------------------

	// Create the ID3DXSprite interface object
	hr = D3DXCreateSprite(g_pD3DDevice, &g_pD3DXSprite );
	if( FAILED(hr) )
		return hr;


	//----------------------------------------------------------------
	// LOAD THE TEXTURE FOR THE SPRITE
	//----------------------------------------------------------------
		
	// --------------------------------------------------------
	// Load the texture.  I decided to use the extended
	// version of the texture loading function just to show what 
	// it would look like.
	// The texture was created with Photoshop with a transparent 
	// background to start with.  Then line cross hairs were added.
	//
	// Note - If you don't use a texture image that has a power of 
	// 2 size for the width or height then the image may not load 
	// properly.  This image is 256x256.
	//

	D3DSURFACE_DESC desc;

    hr = D3DXCreateTextureFromFileEx(
		g_pD3DDevice,
		"1.png",				// Our texture image!
		D3DX_DEFAULT_NONPOW2,				// width
		D3DX_DEFAULT_NONPOW2,				// height
		1			,				// MIP levels
		0			,				// usage
		D3DFMT_DXT1,				// texture format
		D3DPOOL_MANAGED,			// mem pool
		D3DX_DEFAULT,				// filter
		D3DX_DEFAULT,				// MIP filter
		0,							// transparent color key
		0,							// image info struct
		NULL,						// palette
		&g_pTexture);				// the returned texture, if success

	if ( FAILED(hr) )
		return hr;

	g_pTexture->GetLevelDesc(0, &desc);
	
	D3DXFONT_DESC font_desc;
	font_desc.CharSet = DEFAULT_CHARSET;
	strcpy(font_desc.FaceName, "Techno Hideo");
	font_desc.Width = 7;
	font_desc.Height = 13;
	font_desc.Weight = FW_NORMAL;
	font_desc.Quality = DEFAULT_QUALITY;
	font_desc.MipLevels = 1;
	font_desc.Italic = 0;
	font_desc.OutputPrecision = OUT_DEFAULT_PRECIS;
	font_desc.PitchAndFamily = FF_DONTCARE;

	D3DXCreateFontIndirect(g_pD3DDevice, &font_desc, &font);

	// ---------
	// Main Loop
	// ---------
	while( uMsg.message != WM_QUIT )
	{
		if( PeekMessage( &uMsg, NULL, 0, 0, PM_REMOVE ) )
		{ 
			TranslateMessage( &uMsg );
			DispatchMessage( &uMsg );
		}
        else
		{
			// Render the current frame
		    RenderFrame();
		}
	}

	// -------------------------
	// Release directx resources
	// -------------------------
	if (g_pD3DXSprite)
	{
		g_pD3DXSprite->Release();
		g_pD3DXSprite = NULL;
	}
	
	if (g_pTexture)
	{
		g_pTexture->Release();
		g_pTexture = NULL;
	}

	if (g_pD3DDevice)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}




    UnregisterClass( "MY_WINDOWS_CLASS", winClass.hInstance );

	return (int)uMsg.wParam;
}

bool DRAW_SPRITE = true;
bool MOUSE_IS_MOVING = false;
bool USE_QUATERNION = false;
D3DXVECTOR3	eye(0.2,0,-2),
			at(0,0,0);

//-----------------------------------------------------------------------------
// Name: WindowProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT CALLBACK WindowProc( HWND   hWnd, 
							 UINT   msg, 
							 WPARAM wParam, 
							 LPARAM lParam )
{
	static float step = 0.01f;

	switch( msg )
	{
        case WM_KEYDOWN:
		{
			switch( wParam )
			{
			case '1':	DRAW_SPRITE = !DRAW_SPRITE;		break;
			case 'W':	eye.z += step; at.z += step;	break;
			case 'A':	eye.x -= step; at.x -= step;	break;
			case 'S':	eye.z -= step; at.z -= step;	break;
			case 'D':	eye.x += step; at.x += step;	break;
			case 'Q':	eye.y -= step; at.y -= step;	break;
			case 'E':	eye.y += step; at.y += step;	break;

			case VK_ESCAPE:
				PostQuitMessage(0);
				break;

			}
		}
        break;

		case WM_LBUTTONDOWN:
			MOUSE_IS_MOVING = true;
			break;
		case WM_LBUTTONUP:
			MOUSE_IS_MOVING = false;
			break;

		case WM_RBUTTONDOWN:
			USE_QUATERNION = true;
			break;

		case WM_RBUTTONUP:
			USE_QUATERNION = false;
			break;

		case WM_MOUSEMOVE:
		{
			RECT rect;
			GetClientRect(g_hWnd, &rect);

			static int f_x = (rect.right - rect.left) / 2;
			static int f_y = (rect.bottom - rect.top) / 2;			

			int x = GET_X_LPARAM(lParam) - f_x,
				y = GET_Y_LPARAM(lParam) - f_y;
			at.x = x * 0.01;
			at.y = y * 0.01;
			if(MOUSE_IS_MOVING)
				GetCursorPos(&cs);
		}
		break;

		case WM_CLOSE:
		{
			PostQuitMessage(0);
		}
		
        case WM_DESTROY:
		{
            PostQuitMessage(0);
		}
        break;

		case WM_CHAR:
			switch((CHAR)wParam)
			{
			case VK_BACK:
			case VK_DELETE:
				if(len > 0)
					sen[--len] = 0;
				break;

			default:				
				if(len < 254) {
					sen[len++] = (CHAR) wParam;
					sen[len] = 0;
				}
				break;
			}
			

		default:
		{
			return DefWindowProc( hWnd, msg, wParam, lParam );
		}
		break;
	}

	return 0;
}

//-----------------------------------------------------------------------------
// Name: InitializeD3D()
// Desc: Create DirectX interface objects
//		 Initialize the view matrix.
//		 Setup render states that will not need changing throughout
//		 the life of the application.
//-----------------------------------------------------------------------------
HRESULT InitializeD3D( )
{
	HRESULT hr;

	// Create a direct 3D interface object
    g_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

	if( g_pD3D == NULL )
	{
		// TO DO: Respond to failure of Direct3DCreate9
		return E_FAIL;
	}

    D3DDISPLAYMODE d3ddm;

    if( FAILED( hr = g_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )
	{
		// TO DO: Respond to failure of GetAdapterDisplayMode
		return hr;
	}
	

	// 
	if( FAILED( hr = g_pD3D->CheckDeviceFormat( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 
												d3ddm.Format, D3DUSAGE_DEPTHSTENCIL,
												D3DRTYPE_SURFACE, D3DFMT_D16 ) ) )
	{
		if( hr == D3DERR_NOTAVAILABLE )
			// POTENTIAL PROBLEM: We need at least a 16-bit z-buffer!
			return hr;
	}

	//
	// Do we support hardware vertex processing? If so, use it. 
	// If not, downgrade to software.
	//

	D3DCAPS9 d3dCaps;

	if( FAILED( hr = g_pD3D->GetDeviceCaps( D3DADAPTER_DEFAULT, 
		                               D3DDEVTYPE_HAL, &d3dCaps ) ) )
	{
		// TO DO: Respond to failure of GetDeviceCaps
		return hr;
	}

	DWORD dwBehaviorFlags = 0;

	if( d3dCaps.VertexProcessingCaps != 0 )
		dwBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		dwBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	//
	// Everything checks out - create a simple, windowed device.
	//

	D3DPRESENT_PARAMETERS d3dpp;
	memset(&d3dpp, 0, sizeof(d3dpp));

    d3dpp.BackBufferFormat       = d3ddm.Format;
	d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed               = TRUE;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE;

	// Attempt to create a HAL device, end app on failure just to keep things
	// simple.  In other words we are not trying to create a REF device if the
	// HAL fails.
    if( FAILED( hr = g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd,
                                      dwBehaviorFlags, &d3dpp, &g_pD3DDevice ) ) )
	{
		// Should respond to failure of creating the hardware device.
		return hr;
	}


		
	// If we get here everything worked!
	return S_OK;
}


//-----------------------------------------------------------------------------
// Name: RenderFrame()
// Desc: Draw the image to the framebuffer.
//-----------------------------------------------------------------------------
bool isEqual(float lhs, float rhs)
{
	const float EPSILON = 0.0001f;
	if(	lhs > rhs - EPSILON &&
		lhs < rhs + EPSILON	)
		return true;
	return false;
}

void calculate(float& a_x, float& a_y, const D3DXVECTOR3& look)
{
	a_x = asinf(-look.y);
	//	시도 1
	float cosx = cosf(a_x);
	//		시도 1-1:
	a_y = asinf(look.x / cosx);
	float is_z = cosx*cosf(a_y);	
	if(isEqual(is_z, look.z))
		return;
	//		시도 1-2:
	a_y = D3DX_PI - a_y;
	is_z = cosx*cosf(a_y);
	if(isEqual(is_z, look.z))
		return;
		
	//	시도 2
	a_x = D3DX_PI - a_x;
	cosx = cosf(a_x);
	//		시도 2-1:
	a_y = asinf(look.x / cosx);
	is_z = cosx*cosf(a_y);
	if(isEqual(is_z, look.z))
		return;
	//		시도 2-2:
	a_y = D3DX_PI - a_y;
	is_z = cosx * cosf(a_y);
	if(isEqual(is_z, look.z))
		return;

	a_y++;
	return;
}
void RenderFrame( )
{
	if (!g_pD3DDevice && !g_pD3DXSprite && !g_pTexture)
		return;

	D3DXVECTOR3 normal(0, 0, -1);	//	스프라이트가 Rotate(0,0,0)일때 시자를 바라보므로.

	D3DXMATRIX v, p;
	D3DXMatrixPerspectiveFovLH(&p, 90, 1, 0.001f, 1000.0f);
	//D3DXMatrixOrthoLH(&p, 10, 10, 0.001, 1000);

	static float x_angle = 0.0f;
	static float y_angle = 0.0f;
	static float z_angle = D3DX_PI / 2.0f;
	//x_angle += 0.01f;
// 	y_angle += 0.01f;
// 	x_angle += 0.02f;
	if(y_angle > 2 * D3DX_PI)
		y_angle -= 2 * D3DX_PI;
	if(x_angle > 2 * D3DX_PI)
		x_angle -= 2 * D3DX_PI;

	D3DXVECTOR3 look;
	float	a_x, a_y = 0.0f, a_z;
	/*
		위의 Matrix와 기준벡터(0,0,1)로 다음과 같은 공식을 세운다:
			(0,0,1) * VR행렬 = (x,y,z)
			따라서 VR행렬의 1,2행이 삭제되고 3행만 남게 되며 
			알다시피 Roll인 Z각은 쓰지 않으므로 cosz = 1, sinz=0 으로
			또한번 줄일 수 있다. 최종적으로 다음과 같다
			
			x = cosx * siny
			y = -sinx
			z = cosx * cosy		
	*/
	//	Euler Angle로 Look 벡터 생성:
	D3DXVECTOR3 alook;
	float	cosx = cosf(x_angle);
	look.x = cosx * sinf(y_angle);
	look.y = -sinf(x_angle);
	look.z = cosx * cosf(y_angle);

	//	look벡터로 선을 그리는데, 제대로 법선벡터처럼 그려진다면 굳이
	//	look -> Euler를 테스트할 필요가 없다. 저거야 그냥 arcsin 하면 되는 거니까.
	//	그래도 해봅시다!

	{	
		calculate(a_x, a_y, look);
		
		float	cosx = cosf(a_x);
		look.x = cosx * sinf(a_y);
		look.y = -sinf(a_x);
		look.z = cosx * cosf(a_y);
	}
	
	D3DXMatrixLookAtLH(&v, &D3DXVECTOR3(eye.x, eye.y, -2), &at, &D3DXVECTOR3(0, 1, 0));	
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &v);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &p);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, 5);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, 6);

    g_pD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,  0x000000FF, 1.0f, 0 );
	g_pD3DDevice->BeginScene();
	{
		//-------------------------
		// Render the sprite
		//
		//	월드행렬 계산:
		D3DXMATRIX wy, wr, wz, s, w, t, r, e, wx;
		D3DXMatrixIdentity(&e);		
		static float d = D3DX_PI, d1 = 0.0f, dt = 0.0f;
		
		D3DXMatrixTranslation(&t, 1, -1.2, eye.z);
		D3DXMatrixIdentity(&s);
		D3DXMatrixRotationY(&r, d1);		
		D3DXMatrixScaling(&s, 0.02, 0.02, 0.02);
		/*
			수학적으로는 w = t * wr * s.
			코딩시 다이렉트에서는 w = s * wr * t;

			다이렉트에서는 operator*(a,b)가 내부적으로는 b * a가 되는 것 같다.
		*/
		w = s * r * t;
		D3DXVECTOR3 vecPos = D3DXVECTOR3(0,0,0);
		static float i=0;
		i+=-0.001f;
		RECT	rect = {0, 0, 500, 300},
				rect_source = {100, 100, 500, 500};

		//	노멀벡터 그리기:
		static float vs[] = {
			0, 0, 0, 0xffff0000,
			0, 0, -100, 0xffff0000,
		};

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &e);

		float LOOKAT[] = {
			0,		0,		0,		D3DCOLOR_ARGB(255,255,255,255),
			0 + look.x * 5,	0 + look.y * 5,	0 + look.z * 5,	D3DCOLOR_ARGB(255,255,255,255),			
		};
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, LOOKAT, sizeof(float) * 4);

		/*
			g_pD3DXSprite를 찍을 때는 디바이스의 setTransform을 항상 E(항등행렬)로 만들어야 한다.
		*/
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &e);


		D3DXMATRIX b1, b2, b, n_w, n_w2;
		D3DXMatrixRotationX(&b1, 3.141592);		
		n_w2 = w * b1 * e;

		if (g_pD3DXSprite && g_pTexture)
		{
			g_pD3DXSprite->Begin(D3DXSPRITE_DONOTMODIFY_RENDERSTATE | D3DXSPRITE_OBJECTSPACE);
			g_pD3DXSprite->SetTransform(&n_w2);
			g_pD3DXSprite->Draw(g_pTexture, &rect_source, &D3DXVECTOR3(50, 50, 0.5), &D3DXVECTOR3(n_w2._41, n_w2._42, n_w2._43), D3DCOLOR_ARGB(255, 255, 255, 255));
			font->DrawTextA(g_pD3DXSprite, 
				sen, -1, &rect, DT_WORDBREAK, D3DCOLOR_XRGB(0,0,0));
			g_pD3DXSprite->End();
			
		}
		
	}
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present( NULL, NULL, NULL, NULL );

}

