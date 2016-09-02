#pragma once

//	headers:
#pragma message("NETArray.hpp - 1")
#include "../NETClass/NETClass.hpp"
#pragma message("NETArray.hpp - 2")
#include "../NETReservedCollector/NETReservedCollector.hpp"
#pragma message("NETArray.hpp - 3")
//		this includes all related headers. please refer NETCollector.hpp about 
//		this issue.
#include "NETArray.inl"	
#pragma message("NETArray.hpp - 4")
//	implements:
#include "NETPointerArray.hpp"
#pragma message("NETArray.hpp - 5")
#include "NETPointerArrayUsingPolyMorphism.hpp"
#pragma message("NETArray.hpp - 6")
#include "NETArrayWithSameTyped.hpp"
#pragma message("NETArray.hpp - 7")
#include "NETPointerArrayWithSameTyped.hpp"
#pragma message("NETArray.hpp - 8")
#include "NETPointerArrayUsingPolyMorphismWithSameTyped.hpp"
#pragma message("NETArray.hpp - 9")

namespace NE
{
#define _TEMPLATE	template <typename InsideType, type_bool pointerUseNewInstance, typename OutsideType>
#define _NAME		NETArray<InsideType, pointerUseNewInstance, OutsideType>
	
	NE_DEFINE_INTERFACE_ONLY_2(NE_MACRO_FUNNEL(_NAME), NE_MACRO_FUNNEL(_TEMPLATE))

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	_NAME::NETArray()
		: Super(), _data(NE_NULL)
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	_NAME::NETArray(type_count size)
		: Super(size), _data(NE_NULL)
	{
		create(size);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	_NAME::NETArray(const _NAME& source)
		: Super(), _data(NE_NULL)
	{
		/*
			여기서는 어떠한 동작도 할 수없다:
				만약 insert를 상속받아서 사용한다면, 해당 위치에서 다시 _assign을 호출해야 한다.
				_assign내부적으로 가상함수인 insert를 쓰기 때문이다.
				복사생성자는 한단계 상위에서 구현해야만 한다.
		*/
	}	



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	_NAME::~NETArray()
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	const _NAME&
		_NAME::operator=(const This& source)
	{
		return _assign(source);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	원소만 같으 m면 true인건지, 사이즈까지 같아야 하는지에 대한 모호성이 
	//				있기때문에 그다지 추천하지 않는다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------	
	_TEMPLATE
	type_bool  _NAME::operator==(const This& source) const
	{
		if(this == &source) return true;
		if(Super::operator==(source) == false) return false;

		return isEqualElement(source);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	type_bool  _NAME::operator!=(const This& source) const
	{
		return !(operator==(source));
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	InsideType& _NAME::_getElement(type_index index) 
	{	
		//	pre:
		//		널 레퍼런스:
		InsideType* null_pointer = NE_NULL;
		//		파라메터 검사:
		if(index < 0) return *null_pointer;
		if(index > getLengthLastIndex()) return *null_pointer;
		//		관련멤버변수 검사:
		if(_size <= 0) return *null_pointer;



		//	post:
		return _data[index];
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	const InsideType& _NAME::_getElement(type_index index) const 
	{	
		//	pre:
		//		널 레퍼런스:
		InsideType* null_pointer = NE_NULL;
		//		파라메터검사: 
		if(index < 0) return *null_pointer;
		if(index > getLengthLastIndex()) return *null_pointer;
		//		관련멤버변수 검사:
		if(_size <= 0) return *null_pointer;



		//	post:
		return _data[index];
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	type_result _NAME::_setElement(type_index index, const InsideType& source)
	{
		//	pre:
		//		파라메터검사:
		if(index < 0) return RESULT_TYPE_WARNING;
		if(index > getLengthLastIndex()) return RESULT_TYPE_WARNING; // setElement는 추가된 데이터의 수정만 가능하다. 만약, 데이터 추가를 원한다면 push를 사용하라.
		//		관련멤버변수 검사:
		if(_size <= 0) return RESULT_TYPE_WARNING; 


		*(_data + index) = source;

		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	안의 데이터를 최대한 유지한 채 배열의 크기를 조절한다.
	//				당연히, 크기가 줄어들면 뒤의 데이터 일부분은 사라지게 된다.
	//	동작조건:
	//	메모	:	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	type_result _NAME::resize(type_count size) // 가지고있는 데이터는 보존한채 크기만 변경한다.
	{
		//	pre:
		if(size < 0) return RESULT_TYPE_INFORMATION | RESULT_ABORT_ACTION;



		//	main:
		This& copied_in_heap = static_cast<This&>(clone()); // use operator=
		create(size); // size도 내부에서 세팅됨.
		push(copied_in_heap); // temp 자동 소멸



		//	post:
		delete &copied_in_heap;
		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	 배열 자체를 push한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	type_result  _NAME::push(const This& source)
	{
		//	pre:
		//		파라메터검사:
		if( ! source.getLength())	return RESULT_TYPE_WARNING | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION;
		if( ! source.getSize()) return RESULT_TYPE_WARNING | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION;
		if(&source == this) return RESULT_TYPE_WARNING | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION; // 가능은하지만, assign계열에서 자기자신은 에러처리하는게 원칙이므로 형평성을 위해서 에러처리를 한다.



		//	main:
		for(type_index index=0; index < source.getLength() ;index++) // length는 index보다 1크므로 <= 대신 <를 사용한다
		{
			if(_length == _size) break;
			insert(_length, source.getElement(index));	
		}



		//	post:
		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	type_result _NAME::pushFront(const This& source)
	{
		//	pre:
		//		파라메터 검사:
		if( ! source.getLength() )	return RESULT_TYPE_WARNING | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION;
		if( ! source.getSize() ) return RESULT_TYPE_WARNING | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION;
		if(&source == this) return RESULT_TYPE_WARNING | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION; // 가능은하지만, assign계열에서 자기자신은 에러처리하는게 원칙이므로 형평성을 위해서 에러처리를 한다.



		//	main:
		for(type_index index=0; index < source._length ;index++) // length는 index보다 1크므로 <= 대신 <를 사용한다
		{
			if(_length == _size) break;

			insert(index, source.getElement(index));
		}



		//	post:
		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	데이터를 임의의 인덱스에 삽입한다.	
	//	동작조건:	길이가 크기보다 작아야 한다. 데이터의 공간이 존재해야 한다.
	//	메모	:	만약 5에 데이터를 삽입하면, 5에 있던 데이터는 6으로 밀려난다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------

	_TEMPLATE
	type_index _NAME::_insert(type_index index, const InsideType& source) 
	{
		//	pre:
		//		파라메터검사:
		if(index < 0) return NE_INDEX_ERROR;
		if( ! &source) return NE_INDEX_ERROR;
		if(index > _length) return NE_INDEX_ERROR;
		//		관련멤버변수 검사:
		if(_length >= _size) resize(_size * 2 + 1);



		//	main:
		//		OutType의 데이터를 실제로 삽입:
		
		//		삽입될 공간생성:	데이터를 한칸씩 옆으로 옮긴다
		for(type_index n = getLengthLastIndex(); n >= index ;n--)
			_data[n + 1] = _data[n];



		//	post:
		//		데이터삽입:
		//			데이터 변환:	파생클래스에서 정의할 _convert를 사용한다
		_data[index] = source;
		//		길이 증가:
		_length++;

		return index;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	임의의 인덱스에 위치한 데이터를 하나 삭제한다.
	//	동작조건:	지정한 인덱스가 최대 인덱스보다 작고, 0 이상이다.
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	type_index _NAME::_remove(type_index index) 
	{
		//	pre:
		//		파라메터검사:
		if(index < 0) return NE_INDEX_ERROR;
		if(index > getLengthLastIndex()) return NE_INDEX_ERROR;



		//	main:
		//		데이터 이동:	한칸씩 앞으로 옮긴다. 이 과정에서 삭제가 동시에 일어난다
		for(type_index n = index; n < getLengthLastIndex() ;n++)
			_data[n] = _data[n + 1];



		//	post:
		//		길이 감소:
		_length--;
		return index;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	주어진 배열이 같은 배열인지 확인한다.
	//	동작조건:	같은 배열로 판정되기 위해서는 2가지 조건이 필요하다.
	//					조건 1.	같은 크기와 길이를 가지고 있어야 함.
	//					조건 2. 원소가 같아야 함.
	//					조건 3. 템플릿 인자 InsideType가 operator==를 정의했을 것.
	//	메모	:	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	type_bool  _NAME::isEqualSizeAndElement(const This& source) const
	{
		//	pre:
		if(_size != source._size) return false;
		if(_length != source._length) return false;
		if(!isEqualElement(source)) return false;		

		return true;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	크기와 길이를 고려하지 않고, 같은 원소를 가지고 있는지 만을 따진다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	type_bool  _NAME::isEqualElement(const This& source) const
	{
		if(getLengthLastIndex() != source.getLengthLastIndex()) return false;

		for(type_index index=0; index < _length ;index++)
		{				
			if(getElement(index) != source.getElement(index))
				return false;
		}

		return true;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE 
	type_result _NAME::isValid() const  
	{
		//	상위 클래스의 valid 체크:
		type_result result = NETReservedCollector<OutsideType>::isValid();
		if(NEResult::hasError(result) == true) return result;
		//	멤버변수의 valid 체크:
		if(	_size > 0 && ! _data) return RESULT_TYPE_WARNING | RESULT_OUT_OF_MEMORY;

		return RESULT_SUCCESS;
	}			



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	void  _NAME::release()  
	{		
		_release();
		/*
			의도적인 역순 처리:
				여기에서는 _release와 상위클래스의 release를 호출하는 순서가 뒤바뀌어야 한다.
		*/

		return NETReservedCollector<OutsideType>::release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	NEBinaryFileSaver  &_NAME::serialize(NEBinaryFileSaver& saver) const 
	{			
		//	pre:		
		Super::serialize(saver);


		//	main:
		//		실제 데이터 저장:
		for(type_index n=0; n < _length ;n++)
			saver << _data[n];


		//	post:
		return saver;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	NEBinaryFileLoader& _NAME::serialize(NEBinaryFileLoader& loader)
	{
		//	pre:
		//		길이를 0으로 만드는 이유:
		//			create에서 release를 호출하고, NETArray<T, Q> 는 release에서 
		//			while(getLength()) pop()을 호출해야 하기 때문이다.
		//			create에서 release를 호출하는 것은 정당하고, release에서는 NETArray<T, Q>
		//			의 특성상 하위 클래스의 remove가 자동으로 호출되어야 하므로 역시 정당하다.
		//			serialize에서는 상위클래스의 serialize를 호출하지 않는 방법도 존재하나, 호환성을 
		//			위해서 생각해보면 상위클래스의 serialize함수에는 차후 길이 정보이외에도 다른 정보가
		//			있을 수 있다.
		//			따라서 release에서 영향을 받는 length 함수를 사전에 0으로 초기화 하는 것으로
		//			대처하는 것이 가장 효과적이라 볼 수 있다.
		type_index previous_length = getLength();
		Super::serialize(loader);
		

		//	main:
		//		메모리 버퍼공간 생성:
		//			길이 정보 저장:	create에서 초기화가 되버린다.
		type_index new_length = getLength();
		//			길이정보를 serialize 이전으로 되돌리기:
		//				create에서 호출하는 release와의 충돌을 막기 위해서다.
		_length = previous_length;
		create(getSize());
		//		데이터 로드:
		for(type_index n=0; n < new_length ;n++)
		{
			InsideType buffer;
			loader >> buffer;
			_insert(getLength(), buffer);
		}



		//	post:
		return loader;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	지정한 크기만큼의 메모리 공간을 할당한다.
	//				이전에 존재하던 데이터는 모두 초기화되어서 메모리에서 해제 된다.
	//	동작조건:
	//	메모	:	만약 데이터를 유지한 채 크기를 조절하고 싶다면 resize를 사용하라.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	type_result _NAME::create(type_count size)
	{
		release();

		if(size > 0)
		{
			//	보통, InsideType가 primitive일경우에, 0으로 대입을 해야한다. 이걸 배열로 표현하면
			//		new InsideType[size] = {0, }; 
			//	가 된다는 건 알고있다.
			//	그러나 InsideType가 클래스일경우에는, 위의 코드에서 int 생성자가 호출된다. 즉, 쓸데없는 int생성자를 만들지 않으면
			//	클래스를 이 템플릿클래스에 넣을 수 없다.
			//	그러나, new int(); 가 0으로 초기화가 된다는 사실에서 착안,
			//	밑의 코드는, InsideType가 클래스이건, primitive이건 같은 생성자를 호출하게 만들어주는 단 하나의 코드다.			
			_data = new InsideType[size](); // **주의**	InsideType가 클래스의 경우, 기본생성자()가 필요하다.		

			_size = size;
			_length = 0;
		}

		return RESULT_SUCCESS;
	}	



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	const _NAME& _NAME::_assign(const _NAME& source)
	{	
		if(this == &source) return *this;

		create(source._size);
		push(source);
		return *this;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	void  _NAME::_release() 
	{	
		if(_data)
			delete [] _data;
		_data = NE_NULL;
	}



	_TEMPLATE
	type_index _NAME::push(const OutsideType& source)
	{
		return insert(getLength(), source);
	}



	_TEMPLATE
	type_index _NAME::pop()
	{
		return remove(getLengthLastIndex());
	}


	
	_TEMPLATE
	type_index _NAME::pushFront(const OutsideType& source)
	{
		return insert(0, source);
	}



	_TEMPLATE
	type_index _NAME::popFront()
	{
		return remove(0);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	주어진 데이터와 일치하는 엘리먼트가 존재하는지 검색후, 인덱스를 전달
	//				한다.
	//	동작조건:	템플릿 인자 InsideType가 operator==가 정의되어 있어야 한다.
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//     	---------------------------------------------------------------------------------
	_TEMPLATE
	type_index _NAME::_find(const InsideType& source) const
	{
		//	pre:
		//		관련멤버변수 검사:
		if(_length <= 0) return NE_INDEX_ERROR;



		//	main:
		//		검색:
		for(type_index index=0; index < _length ;index++)
			if(_data[index] == source) // 포인터 자체를 비교한다
				return index;



		//	post:
		//		에러반환:	찾지 못했음
		return NE_INDEX_ERROR; // -1
	}


	_TEMPLATE
	const InsideType& _NAME::getInnerElement(type_index index) const
	{
		return _getElement(index);
	}

#undef _NAME
#undef _TEMPLATE
}