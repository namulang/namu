//	---------------------------------------------------------------------------------
//	클래스명:	NETArray
//	설명	:	Array의 형태로 데이터를 관리하는 클래스.
//	관계	:	기반클래스.			NETReservedCollector
//	특성	:	배열의 특성을 그대로 구현한다. 각 엘리먼트는 추가/삽입/삭제의
//				부하가 큰 반면, "검색"에 강하다.//				
//	알고리즘:	만약 포인터를 삽입했을 경우, 해당 포인터로부터 가상복사생성자인 clone
//				을 호출해서 DeepCopy 한다.
//	사용방법:	정의 방법
//					:	템플릿 인자 InsideType의 조건
//							조건 1.	NEObject를 상속해야한다. 
//									NEObject::clone()를 사용하기 때문이다.
//							조건 2. 
//				bool pointerUseNewInstance란?
//					:	false일때 InsideType가 포인터일 경우, 포인터가 새로운 인스턴스를 가리키도록
//						하지않고, shallowcopy만을 사용하겠다는 의미다.
//						true일때는 NEPointerList.hpp를 참고하라.
//				기본적으로 NETReservedCollector의 함수를 모두 사용가능하다. (참조 할 것)
//				기본 인터페이스
//					1. push(InsideType*)			:	포인터의 형태로 삽입이 가능하다.
//					2. pushFront(InsideType*)	:	포인터의 형태로 삽입이 가능하다.
//					3. push(NETList&)	:	리스트 전부를 통째로 삽입한다.
//					4. pushFront(NETList&)
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once

namespace NE
{
	template <typename InsideType>
	class NETArray<InsideType*, false, InsideType*> : public NETReservedCollector<InsideType*>, public NESpecifiedInsertable<InsideType*>
	{
		typedef NETArray<InsideType*, false, InsideType*> _This;

		NE_DECLARE_CLASS(_This, NETReservedCollector<InsideType*>)
	public:
		using Super::push;
		using Super::find;
		using Super::setElement;

		//	생성자:
	public:
		NETArray();
		NETArray(type_count size);
		NETArray(const This& source);

		//	소멸자:
	public:
		virtual ~NETArray();

		//	연산자 중첩:
	public:
		const This& operator=(const This& source);
		bool operator==(const This& source) const;
		bool operator!=(const This& source) const;
		This operator+(const This& source) const;
		const This& operator+=(const This& source);

		//	인터페이스:
		//		상속:
		//			NESpecifiedInsertable:
	public:
		virtual type_index insert(type_index index, const InsideType* const source);
		virtual type_index remove(type_index index);
		//			NETReservedCollector:
	public:
		virtual type_result resize(type_index new_size);
		virtual type_result create(type_count new_size);
		//			NETCollector:
	public:
		virtual const InsideType& getElement(type_index index) const; 
		virtual InsideType& getElement(type_index index);
		virtual type_result setElement(type_index index, const InsideType* const source);		
		virtual type_index push(const InsideType* const source);
		using NETCollector::push;
		virtual type_index pop();
		virtual type_index find(const InsideType* const source) const;
		//			NEObject:
	public:
		virtual type_result isValid() const; 
		virtual void release(); 
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

		//		고유 인터페이스:
	public:
		type_index insert(type_index index, const InsideType& source);
		type_index popFront();
		type_index pushFront(const InsideType* const source);
		type_index pushFront(const InsideType& source);
		type_result push(const This& source); // pushArrayFront는 필요가 없음. source쪽에서 push를 호출하면 되니까
		type_result pushFront(const This& source); // pushArrayFront는 필요가 없음. source쪽에서 push를 호출하면 되니까
		bool isEqualSizeAndElement(const This& source) const;
		bool isEqualElement(const This& source) const;		

		//	내부함수:
	private:
		const This& _assign(const This& source);
		void _release();

		//	멤버변수:
	protected:
		InsideType**	_data;
	};
}

#include "NETPointerArrayWithSameTyped.inl"
