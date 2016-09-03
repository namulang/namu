//	---------------------------------------------------------------------------------
//	클래스명:	NETIndexedArray<Type>
//	설명	:	템플릿 인자로 포인터를 사용하고, 그 포인터가 각각 독립된 인스턴스를
//				가리키는, Array를 원할때 구현되는 클래스.
//				즉, 템플릿 인자가 포인터라고 할지라도 단순히 포인터를 가지고 있는
//				Array라면 NETIndexedArray<Type>가 사용될 것이다.
//				이는, 2번째 템플릿인자인
//	관계	:	기반클래스.			NETReservedCollector
//				일반 템플릿 클래스.	Array<Type>
//	특성	:	2번째 템플릿 인자인 type_bool pointerUseNewInstance가 true란?
//					:	포인터를 deepcopy한다는 것을 말한다.
//						예를들어, NENode a; 의 주소인 &a를 놓고 pointerUseNewInstance
//						가 true일때와 false일때의 동작의 차이를 살펴보자.
//							1. NETIndexedArray<Type*, false> 일 때 
//								: 포인터가 복사되어 엘리먼트로 들어간다. 단지 그 뿐이다.
//							2. This 일 때
//								: 포인터가 가리키는 인스턴스까지 복사되어 들어간다.
//								포인터로부터 복사된 엘리먼트는 포인터와는 별도의 인스
//								턴스를 가진다.
//						This의 이와 같은 동작은 Type* 다형성을 구현하고자 할때
//						제대로 사용된다. 
//	알고리즘:	NETIndexedArray<Type>와 동일하다. 해당 헤더파일을 참고할 것.
//	사용방법:	NETIndexedArray<Type>와 동일하다. 해당 헤더파일을 참고할 것.
//	메모	:	
//	히스토리:	2013-01-10	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once

namespace NE
{
	template <typename Type>
	class NETIndexedArray<Type*, true> : public NETReservedCollector<Type*>, public NESpecifiedInsertable<Type*> // Type = NEKey
	{
		typedef NETIndexedArray<Type*, true> _This;

		NE_DECLARE_CLASS(_This, NETReservedCollector<Type*>)

	public:
		using Super::push;
		using Super::match;
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
		type_bool operator==(const This& source) const;
		type_bool operator!=(const This& source) const;
		const This& operator+=(const This& source);

		//	인터페이스:
		//		접근자:
	public:
		const NEOccupiedSet& getOccupiedSet() const;

		//		상속:
		//			NESpecifiedInsertable:
	public:
		virtual type_result insert(type_index index, const Type* const source);
		virtual type_index remove(type_index index);
		//			NETReservedCollector:
	public:
		virtual type_result resize(type_index new_size);
		virtual type_result create(type_count new_size);
		//			NETCollector:
	public:
		virtual const Type& getElement(type_index index) const; 
		virtual Type& getElement(type_index index); 
		virtual type_result setElement(type_index index, const Type* const source); 
		virtual type_index match(const Type* const source) const;
		virtual type_index push(const Type* const source);
		virtual type_index pop();
		//			NEObject:
	public:
		virtual type_result isValid() const; 
		virtual void release();
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;

		//		고유 인터페이스:
	public:
		type_index popFront();
		type_index pushFront(const Type* const source);
		type_index pushFront(const Type& source);
		type_index insert(type_index index, const Type& source);
		type_result push(const This& source); // pushArrayFront는 필요가 없음. source쪽에서 push를 호출하면 되니까
		type_result pushFront(const This& source); // pushArrayFront는 필요가 없음. source쪽에서 push를 호출하면 되니까
		type_bool isEqualSizeAndElement(const This& source) const;
		type_bool isEqualElement(const This& source) const;		

		//	내부함수:
	private:
		const This& _assign(const This& source);
		void _release();
		type_result _returnHeapMemory(type_index index);
		type_index _searchIndex(type_bool by_descreasing, type_bool target_is_occupied) const;

		//	멤버변수:
	protected:
		Type**	_data;
		NEOccupiedSet _occupiedset;
	};
}