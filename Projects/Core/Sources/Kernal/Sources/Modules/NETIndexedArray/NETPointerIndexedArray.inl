//	---------------------------------------------------------------------------------
//	클래스명:	NETIndexedArray
//	설명	:	Array의 형태로 데이터를 관리하는 클래스.
//	관계	:	기반클래스.			NETReservedCollector
//	특성	:	배열의 특성을 그대로 구현한다. 각 엘리먼트는 추가/삽입/삭제의
//				부하가 큰 반면, "검색"에 강하다.//				
//	알고리즘:	만약 포인터를 삽입했을 경우, 해당 포인터로부터 가상복사생성자인 clone
//				을 호출해서 DeepCopy 한다.
//	사용방법:	정의 방법
//					:	템플릿 인자 Type의 조건
//							조건 1.	NEObject를 상속해야한다. 
//									NEObject::clone()를 사용하기 때문이다.
//							조건 2. 
//				bool pointerUseNewInstance란?
//					:	false일때 Type가 포인터일 경우, 포인터가 새로운 인스턴스를 가리키도록
//						하지않고, shallowcopy만을 사용하겠다는 의미다.
//						true일때는 NEPointerList.hpp를 참고하라.
//				기본적으로 NETCollector의 함수를 모두 사용가능하다. (참조 할 것)
//				기본 인터페이스
//					1. push(Type*)			:	포인터의 형태로 삽입이 가능하다.
//					2. pushFront(Type*)	:	포인터의 형태로 삽입이 가능하다.
//					3. push(NETList&)	:	리스트 전부를 통째로 삽입한다.
//					4. pushFront(NETList&)
/*
				외향(Outside)과 내향(Inside) 타입이 서로 다른 Collector 생성 방법:
					1. 타입이 다른 경우, NETIndexedArray은 추상클래스로서 선언된다.
					2. 다음의 함수들은 파생클래스에서 채워야한다.
						1. 복사생성자
						2. virtual release
						3. virtual insert
						3. virtual remove
						4. virtual getElement(index) const
						5. virtual getElement(index)
						6. virtual setElement
						7. virtual clone
						8. virtual find
*/
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once

namespace NE
{
	template <typename Type>
	class NETIndexedArray<Type*, false> : public NETReservedCollector<Type*>, public NESpecifiedInsertable<Type*>
	{	
		typedef NETIndexedArray<Type*, false> _This;

		NE_DECLARE_CLASS(_This, NETReservedCollector<Type*>)		

	public:
		using Super::push;
		using Super::find;
		using Super::setElement;
		//	생성자:
	public:
		NETIndexedArray();
		NETIndexedArray(type_count size);
		NETIndexedArray(const This& source);

		//	소멸자:
	public:
		virtual ~NETIndexedArray();

		//	연산자 중첩:
	public:
		const This& operator=(const This& source); 
		This operator+(const This& source) const;
		bool operator==(const This& source) const;
		bool operator!=(const This& source) const;
		const This& operator+=(const This& source);

		//	인터페이스:
		//		접근자:
	public:
		const NEOccupiedSet& getOccupiedSet() const;

		//		상속:
		//			NESpecifiedInsertable:
	public:
		virtual type_index insert(type_index index, const Type* const source);
		virtual type_index remove(type_index index);
		//			NETReservedCollector:
	public:
		virtual type_result resize(type_index new_size);
		virtual type_result create(type_count new_size);
		//			NETCollector:
	public:		
		virtual Type& getElement(type_index index);
		virtual const Type& getElement(type_index index) const;
		virtual type_result setElement(type_index index, const Type* const source);
		virtual type_index push(const Type* const source);
		virtual type_index pop();		
		virtual type_index find(const Type* const source) const;
		//			NEObject:
	public:		
		virtual type_result isValid() const;
		virtual void release();
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		
		//		고유 인터페이스:
	public:
		type_index pushFront(const Type* source);
		type_index popFront();
		type_result push(const This& source);
		type_result pushFront(const This& source);
		bool isEqualSizeAndElement(const This& source) const;
		bool isEqualElement(const This& source) const;
		type_index insert(type_index index, const Type& source);
		type_index pushFront(const Type& source);;

	protected:
		type_index _searchIndex(bool by_decreasing, bool target_is_occupied) const;

		//	내부함수:
	private:
		const This& _assign(const This& source);
		void _release();

		//	멤버변수:
	protected:
		Type**	_data;
		NEOccupiedSet _occupiedset;
	};
}