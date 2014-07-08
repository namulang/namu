#include "CShader.hpp"
//	생성자
CShader::CShader() : _iniShaderOn(false), _rendertarget_width(0), _rendertarget_height(0), _recent_index(0),
_device(NULL), _mainframe_surface(NULL), 
_last_preserve_index(NULL)
{
	//	필터 널:
	for (int n=0; n < DEFAULT_CSHADER_FILTER_NUMBER ;n++)
		_filter[n] = 0;	
	//	임시 타겟 널:
	for (int n=0; n < 2 ;n++)
	{
		_temp_texture[n] = NULL;
		_temp_surface[n] = NULL;
		_nested_filter_texture[n] = NULL;
		_nested_filter_surface[n] = NULL;
	}
}
//	셰이더와 관련된 모든 것을 일괄적으로 초기화한다.
void	CShader::initialize(LPDIRECT3DDEVICE9 device, CINI* ini)//	모든 초기화가 여기서 일어남
{
	_iniShaderOn = ini->_graphic_isShaderOn; // ini에서 셰이더를 껐나?
	//	예외상황처리: ini에서 셰이더를 껐다면 초기화를 생략한다.
	if (!_iniShaderOn)	
		return ;
	
	//	메인코드:
	//		초기화:
	initializeValue(ini, device); // 셰이더를 킨 경우, 각각 필터에서 셰이더가 되는지 체크한다. 그래서 잘 되는 필터는 enable = true가 되고, 안되는 필터는 false.
	initializeRenderTargetTexture();		
	initializeFilter();
}		
//	소멸자
CShader::~CShader()
{
	release();
}
//	셰이더와 관련된 모든것을 일괄적으로 해제한다. 여러번 중복 실행되어도 오작동하지 않게끔 해야한다.
void	CShader::release() 
{
	//	예외상황처리:		
	if (!_iniShaderOn) // ini을 끈경우는 바로 나가고... ini을 켰지만, 셰이더 초기화에 실패한 경우는, 각각의 필터를 순회하면서 _enable이 true인지 확인한다.
		return ;		
	
	//	메인코드:
	//		해제:
	releaseRenderTargetTexture();
	releaseFilter();
}
//	CScripter::searchLastPreserveCamera가 찾아낸 마지막 preserve의 주소를 가져와서 저장한다. 두가지로 사용된다.
//	1. preserve가 존재하는가.
//	2. 렌더링하려는 카메라가 마지막 preserve 카메라인가
void	CShader::setLastPreserveCamera(CCamera* camera)
{
	_last_preserve_index = camera; // 주소값이 들어감. preserve가 존재하는가. 혹은, 이 카메라가 last인가를 체크함
}
//	렌더링 타겟의 인덱스를 최신과 비최신을 바꾼다.
void	CShader::swapOldToRecentIndex()
{
	_recent_index = 1 - _recent_index; // 0 또는 1
}
//	최신 렌더링 타겟의 인덱스를 넘긴다.
int		CShader::getRecentIndex() // 변경하지 않음
{
	return _recent_index;
}
//	비최신 렌더링 타겟의 인덱스를 넘긴다.
int		CShader::getOldIndex()
{
	return (1 - _recent_index);
}
//	렌더링 타겟을 메인프레임으로 변경한다.
//	#주의# _mainframe_surface는 다른 렌더링타겟을 대입하게되면, d3d객체 리킹되어서, 
//			디바이스손실 됬을때, restore가 불가능하게 된다.
void	CShader::swapToMainFrame()
{
	_device->SetRenderTarget(0, _mainframe_surface);
}
//	최신 렌더링 타겟으로 변경한다.
void	CShader::swapToRecentTarget()
{
	_device->SetRenderTarget(0, _temp_surface[ getRecentIndex() ]);
}
//	비최신 렌더링 타겟으로 변경한다.
void	CShader::swapToOldTarget()
{
	_device->SetRenderTarget(0, _temp_surface[ getOldIndex() ]);
}	
//	카메라 1개를 렌더링 하기전에 실행해야할 필터링작업을 수행한다.
void	CShader::preFiltering(CCamera* camera)
{
	if ( _iniShaderOn)
	{
		if (_last_preserve_index) // last preserve가 존재하는가?
		{
			if (	!camera->_preserve &&
					camera->isThereEnabledFilter()	) // 필터가 존재하는가
			{
				// preserve가 있는 상황에서 개별 필터
				//	swap 비최신, 버퍼클리어
				swapToOldTarget();
				clearBuffer(DEFAULT_CENGINE_RENDERTARGET_BACKGROUND);
			}
		}
		else
		{
			if (camera->isThereEnabledFilter()) // 필터가 존재하는가
			{
				// preserve가 없고, 개별 필터
				swapToOldTarget();
				clearBuffer(DEFAULT_CENGINE_RENDERTARGET_BACKGROUND);
			}
		}
	}
}
//	렌더링 후, 필터링을 하기 위한 마무리작업
void	CShader::postFiltering(CCamera* camera, LPDIRECT3DVERTEXBUFFER9 vertex_buffer)
{
	if ( _iniShaderOn)
	{
		if (_last_preserve_index) // last preserve가 존재하는가?
		{
			if (camera->isPreserved()) // 이카메라는 preserve를 사용하는가
			{
				if (camera == _last_preserve_index) // 만약 이 카메라가 마지막 preserve인가?
				{
					// preserve가 있는 상황에서 마지막 preserve 필터
					//	메인프레임으로 타겟 변경 (처음 메인프레임에 그리는 시점. 이미 버퍼클리어가 되어있음)
					//	텍스쳐는 최신
					swapToMainFrame();
					filtering(camera, _temp_texture[getRecentIndex()], vertex_buffer);
					initializeLastPreserveCamera();
				}
				else
				{
					// preserve가 있는 상황에서 중간 preserve 필터
					//	타겟: 비최신 -> 버퍼클리어.
					//	텍스쳐: 최신
					//	그리고, 최신을 갱신함
					swapToOldTarget();
					clearBuffer(DEFAULT_CENGINE_RENDERTARGET_BACKGROUND);
					filtering(camera, _temp_texture[getRecentIndex()], vertex_buffer);
					swapOldToRecentIndex();
				}
			}
			else 
			{
				if (camera->isThereEnabledFilter()) // 필터가 존재하는가
				{
					// preserve가 있는 상황에서 개별 필터
					//	타겟: 최신
					//	텍스쳐: 비최신
					swapToRecentTarget();
					filtering(camera, _temp_texture[getOldIndex()], vertex_buffer);
				}
			}
		}
		else
		{
			if (camera->isThereEnabledFilter()) // 필터가 존재하는가
			{
				// preserve가 없고, 개별 필터
				//	버퍼:
				swapToMainFrame();
				filtering(camera, _temp_texture[getOldIndex()], vertex_buffer);					
			}
		}
	}
	else // 셰이더가 꺼져있음
	{
		// 오직 그냥 렌더링			
		//	X (메인프레임)
	}
}	
//	CScripter::searchLastPreserveCamera로부터 받은 주소값을 널로 초기화한다.
void	CShader::initializeLastPreserveCamera()
{
	_last_preserve_index = NULL; 
}
//	현재 렌더링 타겟의 버퍼를 비운다.
void	CShader::clearBuffer(D3DCOLOR color)
{
	_device->Clear( 0, NULL, D3DCLEAR_TARGET, color, 1.0f, 0 );
}
//	실제로 필터링이 일어난다.
//	몇개의 필터가 enable인지를 조사하고, 마지막 필터의 인덱스를 저장한다.
//	만약 필터가 1개일 경우, singleFiltering을 호출하고, 2개 이상이면, nestedFiltering을 호출한다.
void	CShader::filtering(CCamera* camera, LPDIRECT3DTEXTURE9 texture, LPDIRECT3DVERTEXBUFFER9 vertex_buffer)
{
	//	초기화:
	char	last_filter_index	= 0; 
	char	filter_count		= 0;

	//	탐색 시작:
	for(int n=0; n < DEFAULT_CSHADER_FILTER_NUMBER ;n++)
	{
		if (camera->_filter_data[n]->_enable)
		{
			filter_count++;
			last_filter_index = n;
		}
	}

	//	결과 분석:
	if (filter_count > 1)
		nestedFiltering(camera, texture, vertex_buffer, last_filter_index);
	else
		singleFiltering(camera, texture, vertex_buffer);
}
//	필터를 초기화한다.
void	CShader::initializeFilter() // #필터#추가#
{
	_filter[DEFAULT_CSHADER_BLURFILTER] = new CBlurFilter(_device, _rendertarget_width, _rendertarget_height);
	_filter[DEFAULT_CSHADER_NOISEFILTER] = new CNoiseFilter(_device, _rendertarget_width, _rendertarget_height);
	_filter[DEFAULT_CSHADER_BLOOMFILTER] = new CBloomFilter(_device, _rendertarget_width, _rendertarget_height);
}
//	렌더링타겟과 관련된 리소를 모두 초기화한다.
void	CShader::initializeRenderTargetTexture()
{
	//	temp 타겟 초기화:
	_device->CreateTexture( _rendertarget_width, _rendertarget_height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &_temp_texture[0], NULL);
	_temp_texture[0]->GetSurfaceLevel(0, &_temp_surface[0]);
	_device->CreateTexture( _rendertarget_width, _rendertarget_height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &_temp_texture[1], NULL);
	_temp_texture[1]->GetSurfaceLevel(0, &_temp_surface[1]);
	//	mainFrame 타겟 초기화:
	_device->GetRenderTarget(0, &_mainframe_surface);
	//	중첩필터링을 위한 임시 텍스쳐 초기화:
	_device->CreateTexture( _rendertarget_width, _rendertarget_height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &_nested_filter_texture[0], NULL);
	_nested_filter_texture[0]->GetSurfaceLevel(0, &_nested_filter_surface[0]);
	_device->CreateTexture( _rendertarget_width, _rendertarget_height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &_nested_filter_texture[1], NULL);
	_nested_filter_texture[1]->GetSurfaceLevel(0, &_nested_filter_surface[1]);
}
//	일반 변수들을 초기화한다.
void	CShader::initializeValue(CINI* ini, LPDIRECT3DDEVICE9 device)
{
	//	디바이스:
	_device = device;
	//	셰이더 크기(=퀄리티)
	_rendertarget_width = static_cast<UINT> (ini->getShaderWidth());
	_rendertarget_height = static_cast<UINT> (ini->getShaderHeight());
}
//	필터를 릴리즈한다.
void	CShader::releaseFilter()
{
	for (int n=0; n < DEFAULT_CSHADER_FILTER_NUMBER ;n++)
	{
		if (_filter[n])
		{
			delete _filter[n];
			_filter[n] = NULL;
		}			
	}
}
//	렌더링타겟과 관련된 리소스를 전부 릴리즈한다.
void	CShader::releaseRenderTargetTexture()
{
	//	메인프레임 타겟:
	if (_mainframe_surface)
	{
		_mainframe_surface->Release();
		_mainframe_surface = NULL;
	}
	//	임시 타겟:
	if (_temp_texture[0])
	{
		_temp_texture[0]->Release();
		_temp_texture[0] = NULL;
	}
	if (_temp_surface[0])
	{
		_temp_surface[0]->Release();
		_temp_surface[0] = NULL;
	}
	if (_temp_texture[1])
	{
		_temp_texture[1]->Release();
		_temp_texture[1] = NULL;
	}
	if (_temp_surface[1])
	{
		_temp_surface[1]->Release();
		_temp_surface[1] = NULL;
	}
	if (_nested_filter_texture[0])
	{
		_nested_filter_texture[0]->Release();
		_nested_filter_texture[0] = NULL;
	}
	if (_nested_filter_surface[0])
	{
		_nested_filter_surface[0]->Release();
		_nested_filter_surface[0] = NULL;
	}
	if (_nested_filter_texture[1])
	{
		_nested_filter_texture[1]->Release();
		_nested_filter_texture[1] = NULL;
	}
	if (_nested_filter_surface[1])
	{
		_nested_filter_surface[1]->Release();
		_nested_filter_surface[1] = NULL;
	}
}
//	한 카메라의 필터가 한개만 켜진 경우
void	CShader::singleFiltering(CCamera* camera, LPDIRECT3DTEXTURE9 texture, LPDIRECT3DVERTEXBUFFER9 vertex_buffer)
{
	for (int n=0; n < DEFAULT_CSHADER_FILTER_NUMBER ;n++)
	{
		if (camera->_filter_data[n]->_enable)
		{
			_filter[n]->excute(_device, texture, vertex_buffer, camera);
			return;
		}				
	}
}
//		중첩필터링: 하나의 카메라의 여러개의 필터가 동시에 켜진경우
void	CShader::nestedFiltering(CCamera* camera, LPDIRECT3DTEXTURE9 texture, LPDIRECT3DVERTEXBUFFER9 vertex_buffer, char last_filter_index)
{
	//	복잡함. 중첩 카메라 preserve와 원리가 비슷함. 축소판임.
	//	알고리즘.
	//		처음일때, oldtarget 보존 -> target = recent_temp -> 버퍼클리어 texture = 인자
	//		중간단계, target = old_temp -> 버퍼클리어 -> tex = recent_temp
	//		마지막,	  target = oldtarget -> tex = recent

	//	중첩필터링 준비:
	//		이전 렌더타겟 보존:
	LPDIRECT3DSURFACE9	old_buffer = NULL;		
	int					nested_filter_recent_index = 0;
	_device->GetRenderTarget(0, &old_buffer);

	//	루프 시작:		
	bool	first_filtering = true;
	for (int n=0; n < DEFAULT_CSHADER_FILTER_NUMBER ;n++)
	{
		if (camera->_filter_data[n]->_enable)
		{
			if (first_filtering)
			{
				//	처음단계:
				//	target = 최근 타겟
				//	texture = 인자 텍스쳐
				_device->SetRenderTarget(0, _nested_filter_surface[nested_filter_recent_index]);
				clearBuffer(DEFAULT_CENGINE_RENDERTARGET_BACKGROUND);				
				first_filtering = false;
				_filter[n]->excute(_device, texture, vertex_buffer, camera);
			}				
			else if (n == last_filter_index) // 이게 마지막 필터라면
			{
				//	마지막:
				//	target = 원래 찍을려던 타겟(old_buffer)
				//	texture = 최근 텍스쳐
				_device->SetRenderTarget(0, old_buffer);						
				_filter[n]->excute(_device, _nested_filter_texture[nested_filter_recent_index], vertex_buffer, camera);
				break;
			}
			else 
			{
				//	중간:
				//	target = 비최근 타겟
				//	texture = 최근 텍스쳐
				_device->SetRenderTarget(0, _nested_filter_surface[1-nested_filter_recent_index]);						
				clearBuffer(DEFAULT_CENGINE_RENDERTARGET_BACKGROUND);
				_filter[n]->excute(_device, _nested_filter_texture[nested_filter_recent_index], vertex_buffer, camera);
				nested_filter_recent_index = 1 - nested_filter_recent_index; // 최근 인덱스 갱신
			}				
		}				
	}

	//	복구:
	//		버퍼 릴리즈:
	old_buffer->Release();
	old_buffer = NULL;
}