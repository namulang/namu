//	---------------------------------------------------------------------------------
//	클래스명:	NETArray<InsideType>
//	설명	:	템플릿 인자로 포인터를 사용하고, 그 포인터가 각각 독립된 인스턴스를
//				가리키는, Array를 원할때 구현되는 클래스.
//				즉, 템플릿 인자가 포인터라고 할지라도 단순히 포인터를 가지고 있는
//				Array라면 NETArray<InsideType>가 사용될 것이다.
//				이는, 2번째 템플릿인자인
//	관계	:	기반클래스.			NETReservedCollector
//				일반 템플릿 클래스.	Array<InsideType>
//	특성	:	2번째 템플릿 인자인 bool pointerUseNewInstance가 true란?
//					:	포인터를 deepcopy한다는 것을 말한다.
//						예를들어, NENode a; 의 주소인 &a를 놓고 pointerUseNewInstance
//						가 true일때와 false일때의 동작의 차이를 살펴보자.
//							1. NETArray<InsideType*, false> 일 때 
//								: 포인터가 복사되어 엘리먼트로 들어간다. 단지 그 뿐이다.
//							2. This 일 때
//								: 포인터가 가리키는 인스턴스까지 복사되어 들어간다.
//								포인터로부터 복사된 엘리먼트는 포인터와는 별도의 인스
//								턴스를 가진다.
//						This의 이와 같은 동작은 InsideType* 다형성을 구현하고자 할때
//						제대로 사용된다. 
//	알고리즘:	NETArray<InsideType>와 동일하다. 해당 헤더파일을 참고할 것.
//	사용방법:	NETArray<InsideType>와 동일하다. 해당 헤더파일을 참고할 것.
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once

namespace NE
{
	template <typename InsideType>
	class NETArray<InsideType*, true, InsideType*> : public NETReservedCollector<InsideType*>, public NESpecifiedInsertable<InsideType*> // InsideType = NEKey
	{
		typedef NETArray<InsideType*, true, InsideType*> _This;

		NE_DECLARE_CLASS(_This, NETReservedCollector<InsideType*>)
	public:
		using Super::push;
		using Super::find;
		using Super::setElement;
		using Super::serialize;

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
		const This& operator+=(const This& source);
		This operator+(const This& source) const;

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
		virtual type_index find(const InsideType* const source) const;
		virtual type_index push(const InsideType* const source);
		virtual type_index pop();
		//			NEObject:
	public:
		virtual type_result isValid() const; 
		virtual void release(); 
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

		//		고유 인터페이스:
	public:
		type_index find(const InsideType& source) const;
		type_index popFront();
		type_index pushFront(const InsideType* const source);
		type_index pushFront(const InsideType& source);
		type_index insert(type_index index, const InsideType& source);
		type_result push(const This& source); // pushArrayFront는 필요가 없음. source쪽에서 push를 호출하면 되니까
		type_result pushFront(const This& source); // pushArrayFront는 필요가 없음. source쪽에서 push를 호출하면 되니까
		bool isEqualSizeAndElement(const This& source) const;
		bool isEqualElement(const This& source) const;		

		//	내부함수:
	private:
		const This& _assign(const This& source);
		void _release();
		type_result _returnHeapMemory(type_index index);

		//	멤버변수:
	protected:
		InsideType**	_data;
	};
}