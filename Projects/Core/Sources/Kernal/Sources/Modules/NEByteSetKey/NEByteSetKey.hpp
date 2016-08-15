//	설명	:	NETKey를 사용한 명시적 템플릿 인스턴스화.
//				Kernal에 NETKey의 인스턴스를 미리 만들어 놓고, 외부에서 이를
//				include 해서 사용한다.
//				만약 외부에서 각각 NETKey를 인스턴스를 만들어 사용하게 구현하게
//				한다면, 각 모듈마다 NETKey들의 인스턴스가 들어가게 되므로 전체적
//				으로 모듈의 크기가 늘어나게 될것이다.
//	메모	:
//	히스토리:	2011-06-04	이태훈	개발 완료
//	---------------------------------------------------------------------------------
#pragma once
#pragma warning(push)
#pragma warning(disable : 4800)
#pragma warning(disable : 4804)

//	include:
#include "../NETKey/NETKey.hpp"
#include "../NEByteSet/NEByteSet.hpp"

namespace NE
{
	template
	class NE_DLL NETKey<NEByteSet>;
	typedef NETKey<NEByteSet> NEByteSetKey;
}

#pragma warning(pop)