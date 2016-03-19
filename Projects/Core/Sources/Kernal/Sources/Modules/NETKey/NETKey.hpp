//	---------------------------------------------------------------------------------
//	클래스명:	NETKey<typename T>
//	설명	:	주어진 템플릿parameter T를 관리하는 클래스.
//				NEType::Type은 NEKeyTamplate의 타입이 된다. getType() 호출시 NEType::Type을 반환
//				한다.
//	관계	:	기반클래스.	NEKey
//	특성	:	외부에 공개되었다. 외부에서 상속 및 인스턴스 생성 가능하다.
//	알고리즘:	연산자 및 함수 호출시, operand의 타입을 확인후, 일치 할 경우 연산을 
//				수행한다.
//	사용방법:	public인 value를 바로 사용한다.
//	메모	:	
//	히스토리:	2011-06-05	이태훈	개발 완료
//	---------------------------------------------------------------------------------
#pragma once

#include "../NETKeyBase/NETKeyBase.hpp"

namespace NE
{
	template <typename T>
	class NETKey : public NETKeyBase
	{
		NE_DECLARE_CLASS(NETKey<T>, NETKeyBase)

	public:
		typedef T Trait;

		//	생성자:
	public:
		NETKey(const T& source = T(), const NETString& keyname = "");
		NETKey(const This& source);		
		NETKey(const NEKey& source);

		//	소멸자:
	public:
		virtual ~NETKey();

		//	연산자 중첩:
	public:
		const NETKey<T>& operator=(const NETKey<T>& source);

		//	인터페이스:
		//		접근자:
	public:
		T& getValue();
		const T& getValue() const;

	public:
		virtual void releaseValue();

		//			NEObject:
	public:
		virtual void release();
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual	NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

		//	멤버변수:
	protected:
		T _value;
	};
}

#include "NETKey.inl"