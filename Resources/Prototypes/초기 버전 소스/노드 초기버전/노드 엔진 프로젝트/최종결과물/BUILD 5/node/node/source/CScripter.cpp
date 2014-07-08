#include "CScripter.hpp"

CScripter::CScripter(CEngine* engine)
: _engine(engine)
{
	/*	
		#작업# 나중에 제대로 초기화 하자..
		// 임시로 카메라 초기화
		//_camera[0]._x = 100; _camera[0]._y = 100;
		_camera[1]._angle = 0;	
	*/
	_camera[1]._argb.setAlpha(100);
	_camera[1]._argb.setRed(0);
	_camera[1]._argb.setBlue(0);
	//_camera[3]._angle = timeGetTime() / 2000.0f;
	_camera[4]._argb.setAlpha(20);
	_camera[3].setRenderState(DEFAULT_CENGINE_RENDERSTATE_ALPHABLENDING);
}
CScripter::~CScripter() 
{}
//	자신이 담당하고 있는 기능을 수행: 한 프레임 계산 및 출력하기
void	CScripter::excute()
{
	// vectoring();
	rendering();
}

void	CScripter::rendering()
{
	//	#작업# 일단 테스트용으로 이렇게 때운다..
	static float	angle1;
	static float	zoom = 1.0;
	static int		sign = 1;
	

	zoom += 1.0f * sign;	
	if(zoom > 600)
		sign = -1;
	else if (zoom < -600)
		sign = 1;
	_camera[0]._x = zoom;
	_camera[0]._y = zoom;

	_camera[1]._angle = timeGetTime() / 2000.0f;
	//	키체크
	//	블러: F1~F3
	//	F1 : 블러 키고 / 끄기
	//	F2 : 더 흐리게
	//	F3 : 덜 흐리게
	static	int	camera_index = 0;
	if ( GetAsyncKeyState(VK_ESCAPE) & 0x0001 ) // 키를 누른순간
	{
		if (_camera[camera_index]._enable)
			_camera[camera_index]._enable = false;
		else
			_camera[camera_index]._enable = true;
	}
	if ( GetAsyncKeyState(VK_F1) & 0x0001 ) // 키를 누른순간
	{
		if (_camera[camera_index]._filter_data[DEFAULT_CSHADER_BLURFILTER]->_enable)
			_camera[camera_index]._filter_data[DEFAULT_CSHADER_BLURFILTER]->_enable = false;
		else
			_camera[camera_index]._filter_data[DEFAULT_CSHADER_BLURFILTER]->_enable = true;

	}
	if ( GetAsyncKeyState(VK_F2) & 0x0001 ) // 키를 누른순간
	{				
		CBlurFilterData* blur_data = static_cast<CBlurFilterData*> (_camera[camera_index]._filter_data[DEFAULT_CSHADER_BLURFILTER]);
		float blur_level = blur_data->getBlurLevelHeight();

		blur_level -= 0.5f;
		blur_data->setBlurLevelHeight(blur_level);
	}
	if ( GetAsyncKeyState(VK_F3) & 0x0001 ) // 키를 누른순간
	{				
		CBlurFilterData* blur_data = static_cast<CBlurFilterData*> (_camera[camera_index]._filter_data[DEFAULT_CSHADER_BLURFILTER]);
		float blur_level = blur_data->getBlurLevelHeight();

		blur_level += 0.5f;
		blur_data->setBlurLevelHeight(blur_level);
	}

	//	노이즈:	F4~F8
	//	F5:노이즈 키고 / 끄기
	//	F6:MAX을 높이기
	//	F7:MAX를 낮추기
	//	F8:딜레이를 느리게 하기
	if ( GetAsyncKeyState(VK_F5) & 0x0001 ) // 키를 누른순간
	{
		if (_camera[camera_index]._filter_data[DEFAULT_CSHADER_NOISEFILTER]->_enable)
			_camera[camera_index]._filter_data[DEFAULT_CSHADER_NOISEFILTER]->_enable = false;
		else
			_camera[camera_index]._filter_data[DEFAULT_CSHADER_NOISEFILTER]->_enable = true;

	}
	if ( GetAsyncKeyState(VK_F6) & 0x0001 ) // 키를 누른순간
	{				
		CNoiseFilterData* noise_data = static_cast<CNoiseFilterData*> (_camera[camera_index]._filter_data[DEFAULT_CSHADER_NOISEFILTER]);
		int noise_max = noise_data->getNoiseMaxLevel();
		int noise_min = noise_data->getNoiseMinLevel();
		
		noise_max = noise_max + 15;
		noise_min = noise_min + 15;
		noise_data->setNoiseMaxLevel(noise_max);
		noise_data->setNoiseMinLevel(noise_min);
	}
	if ( GetAsyncKeyState(VK_F7) & 0x0001 ) // 키를 누른순간
	{				
		CNoiseFilterData* noise_data = static_cast<CNoiseFilterData*> (_camera[camera_index]._filter_data[DEFAULT_CSHADER_NOISEFILTER]);
		int noise_max = noise_data->getNoiseMaxLevel();
		int noise_min = noise_data->getNoiseMinLevel();


		noise_min = noise_min - 15;		
		noise_max = noise_max - 15;
		noise_data->setNoiseMaxLevel(noise_max);
		noise_data->setNoiseMaxLevel(noise_min);
	}
	if ( GetAsyncKeyState(VK_F8) & 0x0001 ) // 키를 누른순간
	{				
		CNoiseFilterData* noise_data = static_cast<CNoiseFilterData*> (_camera[camera_index]._filter_data[DEFAULT_CSHADER_NOISEFILTER]);
		int noise_delay = noise_data->getDelay();

		noise_delay += 1;
		noise_data->setDelay(noise_delay);
	}


	//	블룸: F9, F11~F12
	//	F9:블룸 키고 / 끄기
	//	F11:블룸 더 심하게
	//	F12:블룸 더 약하게
	
	if ( GetAsyncKeyState(VK_F9) & 0x0001 ) // 키를 누른순간
	{
		if (_camera[camera_index]._filter_data[DEFAULT_CSHADER_BLOOMFILTER]->_enable)
			_camera[camera_index]._filter_data[DEFAULT_CSHADER_BLOOMFILTER]->_enable = false;
		else
			_camera[camera_index]._filter_data[DEFAULT_CSHADER_BLOOMFILTER]->_enable = true;

	}	
	if ( GetAsyncKeyState(VK_F11) & 0x0001 ) // 키를 누른순간
	{				
		CBloomFilterData* bloom_data = static_cast<CBloomFilterData*> (_camera[camera_index]._filter_data[DEFAULT_CSHADER_BLOOMFILTER]);
		float bloom_level = bloom_data->getBloomLevel();

		bloom_data->setBloomLevel(bloom_level + 0.005f);						
	}
	if ( GetAsyncKeyState(VK_F12) & 0x0001 ) // 키를 누른순간
	{				
		CBloomFilterData* bloom_data = static_cast<CBloomFilterData*> (_camera[camera_index]._filter_data[DEFAULT_CSHADER_BLOOMFILTER]);
		float bloom_level = bloom_data->getBloomLevel();

		bloom_data->setBloomLevel(bloom_level - 0.005f);						
	}

	if ( GetAsyncKeyState('1') &0x0001)
	{
		camera_index = 1;
	}
	if ( GetAsyncKeyState('2') &0x0001)
	{
		camera_index = 2;
	}
	if ( GetAsyncKeyState('3') &0x0001)
	{
		camera_index = 3;
	}
	if ( GetAsyncKeyState('4') &0x0001)
	{
		camera_index = 4;
	}
	if ( GetAsyncKeyState('5') &0x0001)
	{
		camera_index = 5;
	}
	if ( GetAsyncKeyState('0') &0x0001)
	{
		camera_index = 0;
	}

	//	카메라 렌더스테이트:
	//	insert: linear
	//	home:	alphablending
	//	delete:	negative
	//	end:	darken
	if ( GetAsyncKeyState(VK_INSERT) & 0x0001 ) // 키를 누른순간
	{
		_camera[camera_index].setRenderState(DEFAULT_CENGINE_RENDERSTATE_LINEAR);
	}	
	if ( GetAsyncKeyState(VK_HOME) & 0x0001 ) // 키를 누른순간
	{
		_camera[camera_index].setRenderState(DEFAULT_CENGINE_RENDERSTATE_ALPHABLENDING);
	}	
	if ( GetAsyncKeyState(VK_DELETE) & 0x0001 ) // 키를 누른순간
	{
		_camera[camera_index].setRenderState(DEFAULT_CENGINE_RENDERSTATE_NEGATIVE);
	}	
	if ( GetAsyncKeyState(VK_END) & 0x0001 ) // 키를 누른순간
	{
		_camera[camera_index].setRenderState(DEFAULT_CENGINE_RENDERSTATE_DARKEN);
	}	
	//	카메라 색상변경:
	//	numpad 7, 4: ALPHA +, -
	//	numpad 8, 5: RED +, -
	//	numpad 9, 6: GREEN +, -
	//	numpad -, +: BLUE +, -
	//	numpad 0: 초기화
	if ( GetAsyncKeyState(VK_NUMPAD7) & 0x0001 ) // 키를 누른순간
	{
		int alpha = _camera[camera_index]._argb.getAlpha();
		alpha++;	
		_camera[camera_index]._argb.setAlpha(alpha);
	}	
	if ( GetAsyncKeyState(VK_NUMPAD4) & 0x0001 ) // 키를 누른순간
	{
		int alpha = _camera[camera_index]._argb.getAlpha();
		alpha--;
		_camera[camera_index]._argb.setAlpha(alpha);
	}	
	if ( GetAsyncKeyState(VK_NUMPAD8) & 0x0001 ) // 키를 누른순간
	{
		int red = _camera[camera_index]._argb.getRed();
		if (red < 255) 
			red++;	
		_camera[camera_index]._argb.setRed(red);
	}	
	if ( GetAsyncKeyState(VK_NUMPAD5) & 0x0001 ) // 키를 누른순간
	{
		int red = _camera[camera_index]._argb.getRed();
		red--;	
		_camera[camera_index]._argb.setRed(red);
	}	
	if ( GetAsyncKeyState(VK_NUMPAD9) & 0x0001 ) // 키를 누른순간
	{
		int blue = _camera[camera_index]._argb.getBlue();
		blue++;	
		_camera[camera_index]._argb.setBlue(blue);
	}	
	if ( GetAsyncKeyState(VK_NUMPAD6) & 0x0001 ) // 키를 누른순간
	{
		int blue = _camera[camera_index]._argb.getBlue();
		blue--;	
		_camera[camera_index]._argb.setBlue(blue);
	}	
	if ( GetAsyncKeyState(VK_ADD) & 0x0001 ) // 키를 누른순간
	{
		int green = _camera[camera_index]._argb.getGreen();
		green++;	
		_camera[camera_index]._argb.setGreen(green);
	}	
	if ( GetAsyncKeyState(VK_SUBTRACT) & 0x0001 ) // 키를 누른순간
	{
		int green = _camera[camera_index]._argb.getGreen();
		green--;
		_camera[camera_index]._argb.setGreen(green);
	}	
	if ( GetAsyncKeyState(VK_NUMPAD0) & 0x0001 ) // 키를 누른순간
	{
		_camera[camera_index]._argb.initialize();
	}	

	//	카메라 preserve
	//	backspace:
	if ( GetAsyncKeyState(VK_BACK) & 0x0001 ) // 키를 누른순간
	{
		if (_camera[camera_index]._preserve)
			_camera[camera_index]._preserve = false;
		else
			_camera[camera_index]._preserve = true;
	}	


	_camera[1]._scale_x = 0.8f;
	_camera[1]._scale_y = 0.8f;
	_camera[2]._x = -400.0f;
	_camera[2]._y = -400.0f;

	_camera[3]._x = 100.0f;
	_camera[3]._y = -150.0f;

	_camera[4]._x = +350.0f;
	_camera[4]._y = +350.0f;



	// 배경을 검게칠한다
	preRender();

	for( int n=0; n < TEMP_CAMERA_NUMBER ;n++)
	{
		if (_camera[n]._enable)
			_engine->rendering(&_camera[n], n);
	}

	if ( postRender() == D3DERR_DEVICELOST ) // 디바이스 복구
		_engine->restore();				
}
//	한프레임 렌더링을 하기전에 수행하는 작업들. 한프레임에 한번만 수행된다.
void	CScripter::preRender()
{	
	_engine->clearBuffer(DEFAULT_CENGINE_MAINFRAME_BACKGROUND); // 버퍼 비우기: 이미, 메인프레임으로 타겟팅 되어 있음		
	searchLastPreserveCamera(); // 카메라 탐색
}
//	카메라들 중에서, 제일 마지막에 찍는 PRESERVE를 탐색한다. (선형탐색)
void	CScripter::searchLastPreserveCamera() // 카메라배열을 다 탐색함
{
	// 실제로는, 배열이 아니라 C대상자를 사용함
	for (int n=TEMP_CAMERA_NUMBER-1; n >= 0 ;n--) // !거꾸로 탐색!
	{
		if (_camera[n].isPreserved()) // preserved 필터를 사용중인가
		{
			_engine->_shader.setLastPreserveCamera(&_camera[n]);
			_engine->_shader.swapToRecentTarget();
			_engine->clearBuffer(DEFAULT_CENGINE_RENDERTARGET_BACKGROUND);
			return ;
		}
	}	
}
//	한프레임에 필요한 모든 렌더링 작업이 끝나고 수행되는 작업.
HRESULT	CScripter::postRender()
{
	return _engine->present();
}