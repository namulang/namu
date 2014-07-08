#include "CEngine.hpp"

//	생성자
CEngine::CEngine(CINI* ini) : _ini(ini), _direct(NULL), _device(NULL),
_texture(NULL), _texture_capacity(0), _texture_size(0),
_playable_display_mode_number(0), _playable_display_modes(NULL), _selected_display_mode(),
_isHardwareVertexProcessingEnable(D3DCREATE_SOFTWARE_VERTEXPROCESSING), _caps()
{	
	initializeDirectx();
	initializeDisplayMode();	
	initializeDevice();	
	initializeCapabilities();
	initializeVertexBuffer();
	initializeShader();
	initializeMatrix();
	initializeRenderState();	
	//	#작업#	나중에 CTexture를 CScripter에서 초기화시키자	
	initializeTextureCapacity(5);
	loadTexture(_T("..\\resource\\graphic\\background2.jpg"));
	loadTexture(_T("..\\resource\\graphic\\background.png"));	
	loadTexture(_T("..\\resource\\graphic\\car.bmp"));
	loadTexture(_T("..\\resource\\graphic\\logo.bmp"));
	loadTexture(_T("..\\resource\\graphic\\game.bmp"));
}
//	소멸자
CEngine::~CEngine()
{
	releaseShader();
	//	버텍스버퍼:
	if (_vertex_buffer)
		_vertex_buffer->Release();
	//	디바이스:
	if (_device)
		_device->Release();		
	//	다이렉트X:
	if (_direct)
		_direct->Release();	
}
//	넘겨받은 카메라가 보는 시각으로 렌더링한다
void	CEngine::render(CCamera* camera, int index)
{	
	DWORD	color = 0;
	//	카메라 적용:
	//		렌더스테이트:
	if (camera->_render_state_setted)
		setRenderState(camera->getRenderState());
	else
		setRenderState(DEFAULT_CENGINE_RENDERSTATE_DEFAULT);
	//		색상:
	if ( camera->_argb.isSetted() )
		color = camera->_argb.toD3DCOLOR();
	else	
		color = D3DCOLOR_ARGB(255,255,255,255);
	//		카메라 위치:
	getWorldMatrix(camera);
	

	_device->BeginScene();

	if (index == 0)
	{	
		// #작업# 추가할 내용은 이곳에	

		setVertex(	CArea(	-_texture[1]._halfwidth,
			-_texture[1]._halfheight,
			_texture[1]._halfwidth,
			_texture[1]._halfheight),
			color );	
		_texture[1].setTexture(_device); // 배경
		drawVertex();
	}
	else if (index == 1)
	{
		setVertex(	CArea(	-_texture[2]._halfwidth,
			-_texture[2]._halfheight,
			_texture[2]._halfwidth,
			_texture[2]._halfheight),
			color );
		_texture[2].setTexture(_device); // 캐릭터
		drawVertex();

		setVertex(	CArea(100-_texture[2]._halfwidth,
			100-_texture[2]._halfheight,
			100+_texture[2]._halfwidth,
			100+_texture[2]._halfheight),
			color );
		_texture[2].setTexture(_device); // 캐릭터
		drawVertex();
	}
	else if (index == 2)
	{		
		setVertex(	CArea(	-_texture[0]._halfwidth,
			-_texture[0]._halfheight,
			_texture[0]._halfwidth,
			_texture[0]._halfheight),
			color );
		_texture[0].setTexture(_device); // 배경2
		drawVertex();
	}
	else if (index == 3)
	{
		
		setVertex(	CArea(	-_texture[3]._halfwidth,
			-_texture[3]._halfheight,
			_texture[3]._halfwidth,
			_texture[3]._halfheight),
			color );
		_texture[3].setTexture(_device); // 배경2
		drawVertex();
	}
	else if (index == 4)
	{
		setVertex(	CArea(	-_texture[4]._halfwidth,
			-_texture[4]._halfheight,
			_texture[4]._halfwidth,
			_texture[4]._halfheight),
			color );
		_texture[4].setTexture(_device); // 배경2
		drawVertex();
	}

	_device->EndScene(); 
}
//	다이렉트9를 생성한다.
void	CEngine::initializeDirectx()
{
	_direct = Direct3DCreate9(D3D_SDK_VERSION);
	if ( !_direct)
	{
		// 심각한 오류. 메세지박스를 출력시키기 위해서 throw함
		throw CError 
		(	
			_T("에러01:\t다이렉트X9 생성 실패"), 
			_T("해결방법"),
			_T(__FUNCTION__)
		);
	}
}
//	현재 디스플레이 모드를 조사한다
void CEngine::getCurrentDisplayMode(D3DDISPLAYMODE* display)
{	
	if( FAILED( _direct->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, display)))
	{
		// 심각한 오류. 메세지박스를 출력시키기 위해서 throw함
		CError e
		(	
			_T("에러02:\t현재 사용하고 있는 디스플레이모드를 확인하지 못했습니다."), 
			_T("해결방법"),
			_T(__FUNCTION__)
		);
		e.log();

		throw e;
	}
}
//	텍스쳐를 담을 배열의 용량을 정한다 (초기화도 겸함)
void	CEngine::initializeTextureCapacity(int texture_capacity)
{	
	//	초기화:
	if ( _texture )
	{
		delete [] _texture;
		_texture = NULL;
	}
	_texture_capacity = texture_capacity;
	_texture_size = 0;
	//	할당:
	_texture = new CTexture[_texture_capacity];
}
//	디바이스 초기화
void	CEngine::initializeDevice()
{
	//	Direct 3D 디바이스 생성:
	//		변수 채우기:
	//			전체화면 && 윈도우창 공통:
	ZeroMemory( &_present_parameter, sizeof(_present_parameter) );		
	_present_parameter.SwapEffect = DEFAULT_CENGINE_CREATEDEVICE_SWAPEFFECT; // 화면전환 방법	
	_present_parameter.Windowed = _ini->_graphic_window_mode; // 전체화면 or 윈도우	
	_present_parameter.BackBufferFormat = _selected_display_mode.Format; // 찾아낸 포맷 사용
	if ( _ini->_graphic_vertical_synchronize == true ) // 수직동기화는 전체화면에서만 사용자에 의해서 on이 된다
		_present_parameter.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	else
		_present_parameter.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	//			전체화면 모드:	
	if (_present_parameter.Windowed == FALSE)
	{	
		_present_parameter.BackBufferCount = DEFAULT_CENGINE_CREATEDEVICE_BACKBUFFERCOUNT;
		_present_parameter.BackBufferHeight = _selected_display_mode.Height;
		_present_parameter.BackBufferWidth = _selected_display_mode.Width;		
		_present_parameter.EnableAutoDepthStencil = false;
		_present_parameter.FullScreen_RefreshRateInHz = _selected_display_mode.RefreshRate;
		if ( _ini->_graphic_vertical_synchronize == true ) // 수직동기화는 전체화면에서만 사용자에 의해서 on이 된다
			_present_parameter.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
		else
			_present_parameter.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	else
		_present_parameter.FullScreen_RefreshRateInHz = 0; // 윈도우 모드에서는 0이어야 한다		
	

	//		디바이스 생성:
	if( FAILED(_direct->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		CWindow::_hWnd, _isHardwareVertexProcessingEnable, &_present_parameter, &_device)) ) // 스태틱변수(HWND)를 사용하고있다
	{
		// 심각한 오류. 메세지박스를 출력시키기 위해서 throw함
		throw CError
		(	
			_T("에러03:\t디바이스 생성 실패"), 
			_T("해결방법"),
			_T(__FUNCTION__)
		);
	}
}
//	버텍스버퍼 초기화
void	CEngine::initializeVertexBuffer()
{
	//	버텍스 생성:
	if ( FAILED(_device->CreateVertexBuffer(	
		4 * sizeof(MYVERTEX), 0, DEFAULT_CENGINE_D3DFVF_MYVERTEX, D3DPOOL_DEFAULT, &_vertex_buffer,	NULL)))
	{
		// 심각한 오류.
		throw CError
		(	
			_T("에러04:\t버텍스버퍼 생성 실패"), 
			_T("해결방법"),
			_T(__FUNCTION__)
		);
	}				
	//	버텍스 초기화:		
	_device->SetFVF(DEFAULT_CENGINE_D3DFVF_MYVERTEX);
	_device->SetStreamSource(0, _vertex_buffer, 0, sizeof(MYVERTEX));
}
//	사용하지 않는, 렌더링 합성 방식을 지정한다. (게임내에서, 두번다시 건드릴 필요없음)
void	CEngine::initializeRenderState()
{
	//	렌더스테이트:
	//		3D와 관계된 항목: OFF로 함
	_device->SetRenderState(D3DRS_LIGHTING, FALSE);
	_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	_device->SetRenderState(D3DRS_ZENABLE, FALSE);
	_device->SetRenderState(D3DRS_DITHERENABLE, FALSE);
	_device->SetRenderState(D3DRS_SPECULARENABLE, FALSE);
	_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	_device->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
	_device->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);	
	_device->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ONE);	
	//	텍스쳐스테이지스테이트:
	_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE); // COLOR인수(ARG)1과 2의 값을 곱한것을 최종색으로 렌더링함
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE); // 인수(ARG)1은 텍스쳐의 색
	_device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE); // 인수2는 버텍스의 색		
	//	칼라 스테이지:
	_device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	_device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	_device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
}
//	매트릭스를 초기화한다
void	CEngine::initializeMatrix()
{
	//	뷰행렬:
	D3DXMATRIXA16	viewer_matrix,
					projection_matrix;
	D3DXMatrixIdentity(&viewer_matrix);		
	_device->SetTransform(D3DTS_VIEW, &viewer_matrix);		
	//	프로젝션 행렬:	윈도우 크기에 맞게 설정 (절대크기) 2차원 텍스쳐를 찍을때는, 텍셀이 -0.5f만큼 이동해야 제대로 찍힌다.
	//					그것을 보정하기 위해서 행렬을 만들어, 투영행렬에 곱해줌
	//	텍스쳐 보정:
	D3DXMATRIXA16	texture_correction_matrix;
	D3DXMatrixTranslation(&texture_correction_matrix,-0.5f,-0.5f,0);
	//	투영 행렬:
	D3DXMatrixOrthoLH(	&projection_matrix, 
						(float) _ini->getScreenWidth(),
						(float) _ini->getScreenHeight(),
						DEFAULT_CENGINE_MATRIXTRANSFORM_MAX_Z, DEFAULT_CENGINE_MATRIXTRANSFORM_MIN_Z );		
	_device->SetTransform(D3DTS_PROJECTION, &(texture_correction_matrix * projection_matrix));		
}
//	버텍스를 설정한다.
void	CEngine::setVertex(CArea vertex_area, DWORD color, CArea texture_area)
{	
	//	버퍼 잠구기:
	MYVERTEX*	vertex;
	_vertex_buffer->Lock(	0, 4 * sizeof(MYVERTEX), (void**) &vertex, NULL);	
	//	버텍스 설정:
	//		좌하:
	vertex[0].x = vertex_area._x1;		vertex[0].y = vertex_area._y2;
	vertex[0].tu = texture_area._x1;	vertex[0].tv = texture_area._y1;
	vertex[0].z = 1.0f;					vertex[0].color = color;
	//		좌상:
	vertex[1].x = vertex_area._x1;		vertex[1].y = vertex_area._y1;
	vertex[1].tu = texture_area._x1;	vertex[1].tv = texture_area._y2;
	vertex[1].z = 1.0f;					vertex[1].color = color;
	//		우하:
	vertex[2].x =vertex_area._x2;		vertex[2].y = vertex_area._y2;
	vertex[2].tu = texture_area._x2;	vertex[2].tv = texture_area._y1;
	vertex[2].z = 1.0f;					vertex[2].color = color;
	//		우상:
	vertex[3].x = vertex_area._x2;		vertex[3].y = vertex_area._y1;
	vertex[3].tu = texture_area._x2;	vertex[3].tv = texture_area._y2;
	vertex[3].z = 1.0f;					vertex[3].color = color;
	//	버퍼 풀기:
	_vertex_buffer->Unlock();
	
}
//	버텍스버퍼를 그린다
void	CEngine::drawVertex()
{		
	_device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2); // D3DPT_TRIANGLESTRIP표시방식, 버퍼의 시작인덱스, 표시할 삼각형의 갯수) 			
}
//	카메라가 비추고있는 공간을 설정한다
void	CEngine::getWorldMatrix(CCamera* camera)
{
	//	초기화:
	D3DXMATRIXA16	translation_matrix,
					rotation_matrix,
					scaling_matrix;
	//	행렬 구하기:
	D3DXMatrixTranslation(&translation_matrix, camera->_x, camera->_y, camera->_z ); // 평행이동	
	D3DXMatrixRotationZ(&rotation_matrix, camera->_angle );// 회전	
	D3DXMatrixScaling(&scaling_matrix, camera->_scale_x, camera->_scale_y, 1.0f);// 크기조절
	//	구한 행렬을 적용하여 변환:
	_device->SetTransform(D3DTS_WORLD, &(translation_matrix * rotation_matrix * scaling_matrix));
}
//	파일경로에 존재하는 그림 파일을 읽어서 현재 담야할 위치에 텍스쳐를 담는다
void	CEngine::loadTexture(CString filename)
{
	if (_texture_size < _texture_capacity ) // _texture_capacity-1 : 최대 허용가능한 인덱스
	{
		_texture[_texture_size].setFileName(filename);
		_texture[_texture_size].loadTexture(_device, _ini->_grpahic_32bit_texture);
		_texture_size++;		
	}
	else
	{
		//	약한 에러. 에러 정보만 기록한다
		CError e
		(	
			_T("경고02:\t텍스쳐의 허용량을 넘었습니다. 스크립트파일이 잘못되지 않았나 의심됩니다."), 
			_T("해결방법:\t"),
			_T(__FUNCTION__)
		);
		e.log();	
	}	
}
//	디바이스를 복구함
void	CEngine::restore()
{
	HRESULT	results = _device->TestCooperativeLevel();
	while(results == D3DERR_DEVICELOST)
	{
		while(results != D3DERR_DEVICENOTRESET)
		{
			Sleep(1000);
			MSG	message;
			PeekMessage(&message, NULL, 0, 0, PM_REMOVE);
			TranslateMessage(&message);
			DispatchMessage(&message);

			results = _device->TestCooperativeLevel();
		}		
		releaseResource(); // 리스토어를 실시함
		if ( FAILED(releaseDevice()) )
		{
			results = D3DERR_DEVICELOST;
		}
		else
		{			
			restoreDevice(); // 장치를 먼저 복구한다
			restoreResource();
			results = _device->TestCooperativeLevel();
		}		
	}
}
//	리소스를 풀어준다
void	CEngine::releaseResource()
{
	//	텍스쳐:
	for (int n = 0; n < _texture_capacity ;n++)
		_texture[n].UnloadTexture();
	//	버텍스:
	if (_vertex_buffer)
	{
		_vertex_buffer->Release();
		_vertex_buffer = NULL;
	}
	//	셰이더관련을 전부 해제: 필터값은 그대로 보존된다.
	releaseShader();
}	
//	디바이스를 다시 설정한다
HRESULT	CEngine::releaseDevice()
{		
	return _device->Reset(&_present_parameter);
}
//	디바이스를 복구한다
void	CEngine::restoreDevice()
{
	initializeVertexBuffer();
	initializeShader();
	initializeMatrix();
	initializeRenderState();
}
//	리소스를 다시 올려놓는다
void	CEngine::restoreResource()
{		
	for (int n = 0; n < _texture_capacity ;n++)
		_texture[n].loadTexture(_device, _ini->_grpahic_32bit_texture);
}
// _select_display_mode를 만드는 과정
void	CEngine::initializeDisplayMode() 
{
	//	예외상황 체크:
	//		윈도우모드: 윈도우모드는 16/32비트, 헤르츠, 포맷이 필요없기때문에 바로 정할 수 있다.
	if (_ini->_graphic_window_mode)
	{
		getCurrentDisplayMode(&_selected_display_mode); // 윈도우모드는, 현재 바탕화면FORMAT으로 해야한다.
		return ;
	}


	//	메인 코드:
	//		초기화:
	_playable_display_mode_number = 0;
	if (_playable_display_modes)
		delete [] _playable_display_modes;
	//		사용가능한 모드의 개수를 수집:
	_playable_display_mode_number = getEnumerateDisplayModeCount(_ini->_graphic_32colorbit);
	if ( !_playable_display_mode_number) // 모두 조사했는데 없었다면
	{
		getCurrentDisplayMode(&_selected_display_mode); // 윈도우모드는, 현재 바탕화면FORMAT으로 해야한다.
		return ;
	}

	//		배열생성:			
	_playable_display_modes = new D3DDISPLAYMODE[_playable_display_mode_number];
	//		배열에 값 넣음:
	getEnumerateDisplayMode(_ini->_graphic_32colorbit);	
	selectModeInEnumeratedMode(); // //	넣은 배열값 중에서 해상도를 찾는데 실패할경우, 내부에서 안전모드(윈도우 모드)로 세팅된다.		
}
//	그래픽 하드웨어의 기능 및 성능을 조사한다
void	CEngine::initializeCapabilities()
{
	_direct->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &_caps);	

	//	하드웨어 버텍스를 지원하는가?
	if (_caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		_isHardwareVertexProcessingEnable = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else	
		_isHardwareVertexProcessingEnable = D3DCREATE_SOFTWARE_VERTEXPROCESSING;	

	//	쉐이더를 지원하는 가
	//		SEPERATE_ALPHA가 가능한가: 불가능시, 끈다
	if (_ini->_graphic_isShaderOn)
	{
		if (_caps.PrimitiveMiscCaps & D3DPMISCCAPS_SEPARATEALPHABLEND)
		{
			if (	_caps.VertexShaderVersion < DEFAULT_CENGINE_VERTEXSHADER_VERSION ||
					_caps.PixelShaderVersion < DEFAULT_CENGINE_PIXELSHADER_VERSION )
			{
				_ini->_info_hardware_shader_support = false;
				_ini->_graphic_isShaderOn = false;
				CError	e
				(
					_T("경고07:\t그래픽 카드가 사용하려는 쉐이더 버전을 지원하지 못합니다."), 
					_T("해결방법"),
					_T(__FUNCTION__)
				);
				e.log();
			}
			else
				_ini->_info_hardware_shader_support = true; // 성공
		}	
		else
		{
			_ini->_info_hardware_shader_support = false;
			_ini->_graphic_isShaderOn = false;
			CError	e
			(
				_T("경고19:\t그래픽 카드가 SEPARATEALPHABLEND 를 지원하지 않습니다. 셰이더 기능을 강제로 끕니다."), 
				_T("해결방법"),
				_T(__FUNCTION__)
			);
			e.log();
		}
	}
}
//	조사한 디스플레이모드중에서, 유저가 원하는 모드를 찾는다
void	CEngine::selectModeInEnumeratedMode()
{
	for (int n = 0; n < _playable_display_mode_number ;n++)
	{
		if (	_playable_display_modes[n].Width == _ini->_graphic_width &&
				_playable_display_modes[n].Height == _ini->_graphic_height ) // 일단 해상도, 모드만 맞으면, refresh는 그냥 대입
		{
			_selected_display_mode = _playable_display_modes[n];
			return ;
		}
	}

	//	한개도 없다면, 안전모드로 들어간다.
	//	안전모드는, 윈도우모드에서 작동하므로, 현재 바탕화면의 모드를 가져온다.
	//	약한 오류.
	CError e
	(	
		_T("경고05:\t현재, 이전에 실행되었던 그래픽옵션으로 실행에 실패했습니다. 첫 실행이거나, 다른 컴퓨터의 높은 옵션으로 설정된 걸(ini파일) 그대로 복사하지는 않으셨습니까?"),
		_T("가장 낮은 그래픽 옵션(안전모드)으로 동작합니다."),
		_T(__FUNCTION__)
	);
	e.log();
	_ini->setDefaultVeryLow();
	getCurrentDisplayMode(&_selected_display_mode);
}
//	그래픽하드웨어가 지원하는 모든 모드를 조사한다
void	CEngine::getEnumerateDisplayMode(bool is32bitcolor)
{	
	int	count = 0,
		iter = 0;

	if (is32bitcolor)
	{
		count = _direct->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_X8R8G8B8); // D3DFMT_R5G6B5의 갯수
		enumerateOneDisplayMode(D3DFMT_X8R8G8B8,iter, count); // iter부터 count만큼.
		iter += count;
		count = _direct->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_X8B8G8R8); // D3DFMT_R5G6B5의 갯수
		enumerateOneDisplayMode(D3DFMT_X8B8G8R8,iter, count); // iter부터 count만큼.
		iter += count;
		count = _direct->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_A8R8G8B8); // D3DFMT_R5G6B5의 갯수
		enumerateOneDisplayMode(D3DFMT_A8R8G8B8,iter, count); // iter부터 count만큼.
		iter += count;
		count = _direct->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_A8B8G8R8); // D3DFMT_R5G6B5의 갯수
		enumerateOneDisplayMode(D3DFMT_A8B8G8R8,iter, count); // iter부터 count만큼.			
	}
	else
	{
		count = _direct->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_R5G6B5); // D3DFMT_R5G6B5의 갯수
		enumerateOneDisplayMode(D3DFMT_R5G6B5,iter, count); // iter부터 count만큼.
		iter += count;
		count = _direct->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_A1R5G5B5); // D3DFMT_R5G6B5의 갯수
		enumerateOneDisplayMode(D3DFMT_A1R5G5B5,iter, count); // iter부터 count만큼.
		iter += count;
		count = _direct->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_A4R4G4B4); // D3DFMT_R5G6B5의 갯수
		enumerateOneDisplayMode(D3DFMT_A4R4G4B4,iter, count); // iter부터 count만큼.
		iter += count;
		count = _direct->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_X1R5G5B5); // D3DFMT_R5G6B5의 갯수
		enumerateOneDisplayMode(D3DFMT_X1R5G5B5,iter, count); // iter부터 count만큼.
		iter += count;
		count = _direct->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_X4R4G4B4); // D3DFMT_R5G6B5의 갯수
		enumerateOneDisplayMode(D3DFMT_X4R4G4B4,iter, count); // iter부터 count만큼.			
	}

}
//	하나의 모드를 조사한다
void	CEngine::enumerateOneDisplayMode(D3DFORMAT format, int start_index, int count)
{
	for (int n = 0; n < count ;n++)
		_direct->EnumAdapterModes(D3DADAPTER_DEFAULT, format, n, &(_playable_display_modes[start_index + n]) );		
}
//	그래픽 하드웨어가 지원하는 모드의 갯수를 구한다
int		CEngine::getEnumerateDisplayModeCount(bool is32bitcolor)
{
	int	count = 0;
	
	if ( is32bitcolor )
	{
		count += _direct->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_X8R8G8B8);
		count += _direct->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_X8B8G8R8);
		count += _direct->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_A8R8G8B8);
		count += _direct->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_A8B8G8R8);
	}
	else
	{
		count += _direct->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_R5G6B5);
		count += _direct->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_A1R5G5B5);
		count += _direct->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_A4R4G4B4);
		count += _direct->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_X1R5G5B5);
		count += _direct->GetAdapterModeCount(D3DADAPTER_DEFAULT, D3DFMT_X4R4G4B4);
	}

	return count;	
}
//	포스트 이펙트를 초기화에 필요한 모든과정이 수행된다.
void	CEngine::initializeShader()
{		
	_shader.initialize(_device, _ini);
}

//	포스트 이펙트 해제에 필요한 모든 과정이 수행된다.
void	CEngine::releaseShader()
{
	_shader.release();
}


//	렌더스테이트를 설정함
void	CEngine::setRenderState(char mode)
{
	if (mode == DEFAULT_CENGINE_RENDERSTATE_LINEAR)
	{
		_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	}
	else if (mode == DEFAULT_CENGINE_RENDERSTATE_ALPHABLENDING)
	{
		_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	}
	else if (mode == DEFAULT_CENGINE_RENDERSTATE_DARKEN)
	{
		_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
		_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
	}
	else if (mode == DEFAULT_CENGINE_RENDERSTATE_NEGATIVE)
	{
		_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);
	}			 
}
//	하나의 카메라를 렌더링한다.
void	CEngine::rendering(CCamera* camera, int index)
{
	_shader.preFiltering(camera);	
	render(camera, index);	
	_shader.postFiltering(camera, _vertex_buffer);	
}
//	모든 렌더링 작업이 끝나고 한 프레임을 찍는다.
HRESULT	CEngine::present()
{
	return _device->Present(NULL, NULL, NULL, NULL);
}
//	화면을 비운다.
void	CEngine::clearBuffer(D3DCOLOR color)
{
	_device->Clear( 0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0 );
}
