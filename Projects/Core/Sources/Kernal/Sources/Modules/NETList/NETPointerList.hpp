#pragma once

namespace NE
{
	NE_DEFINE_CLASS_ONLY_2(NE_MACRO_FUNNEL(NETList<T*, false>), template <typename T>)

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	NETList<T*, false>::NETList()
		: Super(), _head(NE_NULL)
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	NETList<T*, false>::NETList(const This& source)
		: Super(source), _head(NE_NULL)
	{
		_assign(source);
	}	



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	NETList<T*, false>::~NETList()
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	const NETList<T*, false>&
		NETList<T*, false>::operator=
		(
		const This& source
		) 
	{
		Super::operator=(source);			
		return _assign(source);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	NETList<T*, false>  NETList<T*, false>::operator+(const This& source) const
	{
		//	pre:
		if(source._length <= 0)	return This(*this);

		//	main:
		//		버퍼 생성:
		This buffer(*this);
		//		버퍼에 값 축적:
		buffer.push(source);



		// post:
		return buffer;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	type_bool  NETList<T*, false>::operator==(const This& source) const
	{
		if(this == &source) return true;
		if(Super::operator==(source) == false) return false;



		//	main:
		const Iterator* iterator = getIterator(0);
		const Iterator* source_iterator	= source.getIterator(0);
		while(iterator)
		{
			if( ! (iterator->getValue() == source_iterator->getValue()))
				return false;

			iterator = iterator->getNext();
			source_iterator = source_iterator->getNext();
		}



		//	post:
		return true;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	type_bool  NETList<T*, false>::operator!=(const This& source) const
	{	
		return ! (operator==(source));
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//				2011-11-20	이태훈	버그 수정	source가 *this일 때 발생하게될 오류 대처 추가
	//	---------------------------------------------------------------------------------
	template <typename T>
	const NETList<T*, false>  &NETList<T*, false>::operator+=(const This& source)
	{
		//	pre:
		//		파라메터 검사:
		if(source._length == NE_NULL) return *this;




		//	main:
		if(this == &source)
		{
			This buffer(*this);
			push(buffer);
		}
		else
			push(source);



		//	post:
		return *this;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	const T& NETList<T*, false>::getElement(type_index index) const 
	{			
		//	pre:
		//		널 레퍼런스:
		T* null_pointer = NE_NULL;
		//		파라메터 검사:
		if(index < 0) return *null_pointer;		
		if(index > getLengthLastIndex()) return *null_pointer;
		//		관련 멤버변수 검사:
		if(!_head) return *null_pointer;
		if(_length <= 0) return *null_pointer;



		//	main:
		Iterator* pointer = _head;

		for(type_index n=0; n < index ;n++)
		{
			pointer = pointer->_next;

			if(!pointer) return *null_pointer;
		}



		//	post:
		return pointer->getValue();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	T& NETList<T*, false>::getElement(type_index index) 
	{	
		//	pre:
		//		널 레퍼런스:
		T* null_pointer = NE_NULL;
		//		파라메터 검사:
		if(index < 0) return *null_pointer;
		if(index > getLengthLastIndex()) return *null_pointer;
		//		관련 멤버변수 검사:
		if(_length <= 0) return *null_pointer;
		if(!_head) return *null_pointer;



		//	main:
		Iterator* pointer = _head;

		for(type_index n=0; n < index ;n++)
		{
			pointer = pointer->_next;

			if(!pointer) return *null_pointer;
		}



		//	post:
		return pointer->getValue();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	type_result NETList<T*, false>::setElement(type_index index, const T* const source)  
	{	
		//	pre:
		//		파라메터 감서:
		if( !(&source) ) return RESULT_TYPE_WARNING;
		if(index < 0) return RESULT_TYPE_WARNING;
		if(index > getLengthLastIndex()) return RESULT_TYPE_WARNING;
		//		관련 멤버변수 검사:
		if(_length <= 0) return RESULT_TYPE_WARNING;
		if(!_head) return RESULT_TYPE_WARNING;



		//	main:
		Iterator* target = getIterator(index);
		if(!target) return RESULT_TYPE_WARNING;
		T* const_casted_source = const_cast<T*>(source);

		target->_value = const_casted_source;

		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	type_result  NETList<T*, false>::push(const This& source)
	{
		//	per:
		//		파라메터 검사:
		if(!source._length)	return RESULT_TYPE_INFORMATION | RESULT_ABORT_ACTION;
		if(&source == this) return RESULT_TYPE_WARNING | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION;



		//	main:
		for(type_index index=0; index < source._length ;index++) // length는 index보다 1크므로 <= 대신 <를 사용한다
			insert(_length, &(source.getElement(index)) );



		//	post:
		return RESULT_SUCCESS;			
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	type_result NETList<T*, false>::pushFront(const This& source)
	{
		//	pre:
		//		파라메터 검사:
		if(!source._length)	return RESULT_TYPE_INFORMATION | RESULT_ABORT_ACTION;
		if(&source == this) return RESULT_TYPE_WARNING | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION;



		//	main:
		const This::Iterator* source_iterator = source.getIterator(0);
		type_index index = 0;
		while(source_iterator)
		{
			insert(index, &(source_iterator->getValue()));

			index++;

			source_iterator = source_iterator->getNext();
		}



		//	post:
		return RESULT_SUCCESS;			
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	데이터를 임의의 인덱스에 삽입한다.	
	//	동작조건:	중간에 값을 삽입. 길이 == 크기 일경우, 전체 크기가 + 1 증가한다.
	//	메모	:	만약 5에 데이터를 삽입하면, 5에 있던 데이터는 6으로 밀려난다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	//	중간에 값을 삽입. 길이 == 크기 일경우, 전체 크기가 + 1 증가한다.
	template <typename T>
	type_index NETList<T*, false>::insert(type_index index, const T* const source) 
	{
		//	pre:
		//		파라메터 검사:
		if(index < 0) return NE_INDEX_ERROR;
		if(index > _length) return NE_INDEX_ERROR;



		//	main:
		//		조건1:	제일 앞에있는 인덱스(= _head )를 선택했다면
		if(index == 0)
		{	//		_head에 새로운 인스턴스 생성:
			Iterator* temp = new Iterator(source, _head);

			_head = temp;
		}
		else
		{	//		새로운 인스턴스 추가:	추가할 위치의 전 Iterator의 next를 이용한다
			//			인덱스 변수 생성:	추가할 위치의 전 Iterator을 가리킬 인덱스
			type_index _index = 0;
			//			위치 검색:
			for(Iterator* iterator=_head; iterator ;iterator=iterator->_next)
			{	//			조건1-1:	목표Iterator을 next로 가리키고 있는 유닛을 찾았다면
				if(_index == (index - 1)) // 리스트는 한발 뒤에서 조작한다				
				{	//			추가:
					Iterator* temp = new Iterator(source, iterator->_next);

					iterator->_next = temp;
					break;
				}

				_index++;
			}
		}



		//	post:
		//		길이 수정:	유닛을 추가했으므로, 길이 정보도 동기화 시킨다
		_length++;
		return index;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	임의의 인덱스에 위치한 데이터를 하나 삭제한다.
	//	동작조건:	지정한 인덱스가 최대 인덱스보다 작고, 0 이상이다.
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	type_index NETList<T*, false>::remove(type_index index) 
	{
		//	pre:
		//		파라메터 검사:
		if(index < 0) return NE_INDEX_ERROR;
		if(index >= _length) return NE_INDEX_ERROR;



		//	main:
		//		조건1:	처음 유닛을 삭제하려 한다면
		if(index == 0)
		{	//		_head의 next를 이용:
			Iterator* temp = _head;

			_head = _head->_next;

			delete temp;
		}
		else
		{	//		중간 유닛 삭제:	삭제할 위치의 전 Iterator의 next를 이용한다
			//			인덱스 변수 생성:
			type_index _index = 0;
			//			인덱스 검색:
			for(Iterator* iterator=_head; iterator ;iterator=iterator->_next)
			{	//		조건1-1:	인덱스를 찾았다면 (= 리스트는 한발 뒤에서 조작한다 )
				if(_index == (index - 1)) // 리스트는 한발 뒤에서 조작한다				
				{	//		삭제:
					Iterator* temp = iterator->_next;

					iterator->_next = iterator->_next->_next;

					delete temp;
					break;
				}
				_index++;
			}
		}



		//	post:
		//		길이 수정:	유닛은 이미 삭제되었으므로, 길이정보만 수정한다
		_length--;
		return index;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	주어진 데이터와 일치하는 엘리먼트가 존재하는지 검색후, 인덱스를 전달
	//				한다.
	//	동작조건:	템플릿 인자 T가 operator==가 정의되어 있어야 한다.
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>	 
	type_index NETList<T*, false>::find(const T* const source) const
	{
		//	pre:
		//		관련멤버변수 검사:
		if(_length <= 0) return NE_INDEX_ERROR;



		//	main:
		//		검색:
		type_index index = 0;

		for(Iterator* iterator=_head; iterator ;iterator=iterator->_next)
		{
			if(iterator->_value == source) return index; // 포인터 자체를 비교한다

			index++;
		}



		//	post:
		return NE_INDEX_ERROR; // 발견 못함
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	type_result NETList<T*, false>::isValid() const  
	{	//	pre:
		//		상위 클래스의 VALID 체크:
		type_result result = Super::isValid();
		if(NEResult::hasError(result) == true) return result;		
		//		멤버변수의 VALID 체크:
		if(_length != _getUnitCount()) return RESULT_TYPE_WARNING | RESULT_WRONG_BOUNDARY;



		//	post:
		return RESULT_SUCCESS;
	}			



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	void  NETList<T*, false>::release()  
	{			
		_release();

		return Super::release();
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	NETList의 중첩 클래스인, Iterator을 외부에 내보낸다. Iterator에는 다음 데이터를
	//				가리키는 next가 존재한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	typename NETList<T*, false>::Iterator*
		NETList<T*, false>::getIterator(type_index index)
	{
		//	pre:
		//		파라메터 검사:
		if(index < 0) return NE_NULL;			
		if(index > getLengthLastIndex()) return NE_NULL;
		//		관련 멤버변수 검사:
		if(!_head) return NE_NULL;
		if(_length <= 0) return NE_NULL;



		//	main:
		Iterator* pointer = _head;

		for(type_index n=0; n < index ;n++)
		{
			pointer = pointer->_next;

			if(!pointer) return NE_NULL;
		}



		//	post:
		return pointer;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	NETList의 중첩 클래스인, Iterator을 외부에 내보낸다. Iterator에는 다음 데이터를
	//				가리키는 next가 존재한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	const typename NETList<T*, false>::Iterator*
		NETList<T*, false>::getIterator(type_index index) const
	{
		//	pre:
		//		파라메터 검사:
		if(index < 0) return NE_NULL;
		if(index > getLengthLastIndex()) return NE_NULL;
		//		관련 멤버변수 검사:
		if(!_head) return NE_NULL;
		if(_length <= 0) return NE_NULL;



		//	main:
		Iterator* pointer = _head;

		for(type_index n=0; n < index ;n++)
		{
			pointer = pointer->_next;

			if(!pointer) return NE_NULL;		
		}



		//	post:
		return pointer;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	const NETList<T*, false>  &NETList<T*, false>::_assign(const This& source)
	{	//	pre:
		release();
		//	main:
		push(source);
		//	post:
		return *this;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	void  NETList<T*, false>::_release() 
	{	//	pre:	
		if(!_head) return;



		//	main:
		type_index length = getLength(); // pop을 하면 _length가 하나씩 줄어들므로, for문 조건식에서 오작동을 일으킨다. 그러므로 미리 size를 가져옴

		for(type_index n=0; n < length ;n++)
			pop();
	}		



	//	---------------------------------------------------------------------------------
	//	설명	:	몇 개의 유닛이 존재하는지 셈한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>	 
	type_count NETList<T*, false>::_getUnitCount() const
	{
		//	main:
		type_count count = 0;

		for(Iterator* iterator = _head; iterator ;iterator = iterator->_next)
			count++;				



		//	main:
		return count;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	맨 마지막 바로 앞의 Iterator에 접근한다.
	//	동작조건:
	//	메모	:	LinkedList의 특성상, 바로 앞의 Iterator이 삭제/삽입을 할 수 있기 때문이다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	typename NETList<T*, false>::Iterator* NETList<T*, false>::_getBeforeTail()
	{
		//	pre:
		if(_length <= 0) return NE_NULL;
		if(_length == 1) return NE_NULL;



		//	post:
		return getIterator(getLengthLastIndex() - 1);		
	}



	template <typename T>
	type_index NETList<T*, false>::pushFront(const T* const source)
	{
		return insert(0, source);
	}



	template <typename T>
	type_index NETList<T*, false>::pushFront(const T& source)
	{
		return insert(0, &source);
	}



	template <typename T>
	type_index NETList<T*, false>::insert(type_index index, const T& source)
	{
		return insert(index, &source);
	}



	template <typename T>
	type_index NETList<T*, false>::popFront()
	{
		return remove(0);
	}



	template <typename T>
	type_index NETList<T*, false>::push(const T* const source)
	{
		return insert(getLength(), source);
	}

	template <typename T>
	type_index NETList<T*, false>::pop()
	{
		return remove(getLengthLastIndex());
	}
}