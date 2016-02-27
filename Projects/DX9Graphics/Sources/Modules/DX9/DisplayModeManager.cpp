#include "DX9.hpp"
#include "define.hpp"

namespace DX9Graphics
{
	DX9::DisplayModeManager::DisplayModeManager()
		: NETList<DisplayMode>()
	{

	}
	type_index DX9::DisplayModeManager::findCorrespondingDisplayWithoutFormat(const DisplayMode& source)
	{
		int index_count = 0;
		for(NETList<DisplayMode>::Iterator* iterator=getIterator(0); iterator ;iterator=iterator->getNext())
		{
			DisplayMode& displaymode = iterator->getValue();
			if(	displaymode.Width == source.Width				&&
				displaymode.Height == source.Height				&&
				displaymode.isWindowed() == source.isWindowed() &&
				displaymode.RefreshRate == source.RefreshRate	)
				return index_count;

			index_count++;
		}

		return NE_INDEX_ERROR;
	}
	type_result DX9::DisplayModeManager::makeDisplayModeAvailable(DisplayMode& target, LPDIRECT3D9 direct)
	{
		/*
			개요:
				외부에서 선호하는 디스플레이가 세팅되는 순간 해당하는 디스플레이를
				실제 하드웨어가 지원 가능여부를 판단후 알맞게 세팅해줘야 한다.
				만약, 하드웨어정보가 읽어지지 않았을 경우에는 하드웨어 정보 초기화를 수행한다.
		*/
		//	pre:
		//		parameter가 Window 모드 인가: 윈도우 모드라면 바로 값을 할당한다
		if(target.isWindowed())
		{
			target.Format = D3DFMT_UNKNOWN;
			target.RefreshRate = 0;	//	윈도우 모드에서는 RefreshRate를 지정해서는 안된다.
			return RESULT_SUCCESS;
		}
		//		parameter Valid 체크:
		if(NEResult::hasError(target.isValid())) return RESULT_TYPE_ERROR;
		//		하드웨어 정보가 한번 초기화 되었는가:
		if(getLength() <= 0) // : 그래픽 하드웨어라면 최소한 1개 이상은 모드를 지원하고 있을 것이므로 이걸 사용해서 "한번 읽었는지" 여부를 판단할 수 있다.
			initialize(direct); // : 하드웨어 정보 읽기



		//	main:
		//		에러가 있을때만 변경한다.
		//		하드웨어 정보에 주어진 display 모드가 없다면:
		if(find(target) == NE_INDEX_ERROR)
		{
			int index = findCorrespondingDisplayWithoutFormat(target);

			if(index == NE_INDEX_ERROR)
			{
				ALERT_WARNING_IN_SPECIFIED_MODULE(NEExportable::Identifier(NETString(_NAME), NETString(_DEVELOPER), _REVISION), "해상도 %dx%d %dhz를 지원하는 그 어떤 포맷도 발견하지 못했습니다. 이전에 입력된 세팅이 유지될겁니다.", target.Width, target.Height, target.RefreshRate)

				target.Format = D3DFMT_UNKNOWN;

				return RESULT_TYPE_ERROR;
			}
			else
			{
				ALERT_INFORMATION_IN_SPECIFIED_MODULE(NEExportable::Identifier(NETString(_NAME), NETString(_DEVELOPER), _REVISION), "선택한 모드 %dx%d %dhz Format=%d 가 존재하지 않습니다. format을 제외하고 일치하는 모드로 검색합니다.", target.Width, target.Height, target.RefreshRate, target.Format);

				target.Format = getElement(index).Format;
			}
		}
		
		return RESULT_SUCCESS;	
	}

	type_result DX9::DisplayModeManager::initialize(LPDIRECT3D9 direct)
	{
		release();

		return _pushAvailableDisplayMode(direct);
	}

	//	그래픽 하드웨어가 지원하는 모드의 갯수를 구한다
	type_result DX9::DisplayModeManager::_pushAvailableDisplayMode(LPDIRECT3D9 direct)
	{
		if( ! direct) return RESULT_TYPE_ERROR;

		
		
		//	main:
		int	count = 0,
			iter = 0;

		for(int n=D3DFMT_R8G8B8; n <= D3DFMT_X8B8G8R8 ;n++)
			__enumerateOneDisplayMode(direct, D3DFORMAT(n)); 



		//	post:
		return RESULT_SUCCESS;
	}
	type_result DX9::DisplayModeManager::__enumerateOneDisplayMode(LPDIRECT3D9 direct, D3DFORMAT format)
	{
		int count = direct->GetAdapterModeCount(D3DADAPTER_DEFAULT, format); // D3DFMT_R5G6B5의 갯수
		
		for (int n = 0; n < count ;n++)
		{
			DisplayMode buffer;
			buffer.setWindowed(false);

			direct->EnumAdapterModes(D3DADAPTER_DEFAULT, format, n, &(buffer));

			push(buffer);
		}

		return RESULT_SUCCESS;
	}
}