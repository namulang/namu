//	---------------------------------------------------------------------------------
//	클래스명:	NESwitchableUnit
//	설명	:	인터페이스 나타낸다.
//				다른 모듈과 교류가 존재하는 객체는 인터페이스를 상속해야 한다.
//	관계	:	기반 클래스.	NEUnit
//	특성	:	추상클래스
//	알고리즘:	
//	사용방법:	execute()로 클래스가 담당하고 있는 메인 기능을 실행시킨다.
//				enable(), disable()로 인터페이스의 기능을 ON / OFF 할 수 있다.
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	2011-06-05	이태훈	개발 완료.
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../NEUnit/NEUnit.hpp"

namespace NE
{
	class NE_DLL NESwitchableUnit : public NEUnit
	{
		NE_DECLARE_INTERFACE(NESwitchableUnit, NEUnit)

		//	생성자:
	public:
		NESwitchableUnit();
		NESwitchableUnit(const NESwitchableUnit& source);

		//	소멸자:
	public:
		virtual ~NESwitchableUnit();

		//	연산자 중첩:
	public:
		const NESwitchableUnit& operator=(const NESwitchableUnit& source);
		bool operator==(const NESwitchableUnit& source) const;
		bool operator!=(const NESwitchableUnit& source) const;

		//	접근자:
	public:
		bool isEnable() const;
		void setEnable(bool enable);

		//	인터페이스:
		//		상속:
		//			NEUnit:
	public:
		virtual void release();
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

		//	내부함수:
	private:
		void _release();
		const NESwitchableUnit& _assign(const NESwitchableUnit& source);

		//	멤버변수:
	private:
		bool _enable;
	};
}