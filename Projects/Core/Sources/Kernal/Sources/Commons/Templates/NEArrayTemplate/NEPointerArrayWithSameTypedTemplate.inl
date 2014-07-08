namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename InsideType, NEType::Type type>
	NEArrayTemplate<InsideType*, false, InsideType*, type>::NEArrayTemplate()
		: SuperClass(0), _data(NE_NULL)
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename InsideType, NEType::Type type>
	NEArrayTemplate<InsideType*, false, InsideType*, type>::NEArrayTemplate(type_count size)
		: SuperClass(size), _data(NE_NULL)
	{
		create(size);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename InsideType, NEType::Type type>
	NEArrayTemplate<InsideType*, false, InsideType*, type>::NEArrayTemplate(typename const ThisClass& source)
		: SuperClass(source), _data(NE_NULL)
	{
		_assign(source);
	}	



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename InsideType, NEType::Type type>
	NEArrayTemplate<InsideType*, false, InsideType*, type>::~NEArrayTemplate()
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename InsideType, NEType::Type type>
	const NEArrayTemplate<InsideType*, false, InsideType*, type>&
		NEArrayTemplate<InsideType*, false, InsideType*, type>::operator=
		(
		const ThisClass& source
		)
	{
		NEReservedCollectorTemplate<InsideType*>::operator=(source);

		return _assign(source);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	원소만 같으면 true인건지, 사이즈까지 같아야 하는지에 대한 모호성이 
	//				있기때문에 그다지 추천하지 않는다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------	
	template <typename InsideType, NEType::Type type>
	bool  NEArrayTemplate<InsideType*, false, InsideType*, type>::operator==(const ThisClass& source) const
	{
		if(this == &source) return true;
		if(NEReservedCollectorTemplate<InsideType*>::operator==(source) == false) return false;

		return isEqualElement(source);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename InsideType, NEType::Type type>
	bool  NEArrayTemplate<InsideType*, false, InsideType*, type>::operator!=(const ThisClass& source) const
	{
		return !(operator==(source));
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//				2011-11-20	이태훈	버그 수정	source가 *this일 때 발생하게될 오류 대처 추가
	//	---------------------------------------------------------------------------------
	template <typename InsideType, NEType::Type type>
	NEArrayTemplate<InsideType*, false, InsideType*, type>
		NEArrayTemplate<InsideType*, false, InsideType*, type>::operator+(const ThisClass& source) const
	{
		//	pre:
		//		파라메터 검사:
		if(source._length <= 0)	return ThisClass(*this);



		//	main:
		ThisClass buffer(source._length + _length);
		buffer.push(*this);
		buffer.push(source);



		//	post:
		return buffer;
	}



	template <typename InsideType, NEType::Type type>
	NEObject& NEArrayTemplate<InsideType*, false, InsideType*, type>::clone() const
	{
		return *(new ThisClass(*this));
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//				2011-11-20	이태훈	버그 수정	source가 *this일 때 발생하게될 오류 대처 추가
	//	---------------------------------------------------------------------------------
	template <typename InsideType, NEType::Type type>
	const NEArrayTemplate<InsideType*, false, InsideType*, type>&
		NEArrayTemplate<InsideType*, false, InsideType*, type>::operator+=
		(
		const ThisClass& source
		)
	{
		if(this == &source)
		{
			ThisClass& copyied_in_heap = static_cast<ThisClass&>(clone());
			resize(_length + copyied_in_heap._length);
			push(copyied_in_heap);
			delete &copyied_in_heap;
		}
		else 
		{
			resize(_length + source._length);		
			push(source);
		}

		return *this;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename InsideType, NEType::Type type>
	InsideType& NEArrayTemplate<InsideType*, false, InsideType*, type>::getElement(type_index index) 
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
		return *(_data[index]);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename InsideType, NEType::Type type>
	const InsideType& NEArrayTemplate<InsideType*, false, InsideType*, type>::getElement(type_index index) const 
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
		return *(_data[index]);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename InsideType, NEType::Type type>
	type_result NEArrayTemplate<InsideType*, false, InsideType*, type>::setElement(type_index index, const InsideType* const source)  
	{
		//	pre:
		//		파라메터검사:
		if(index < 0) return RESULT_TYPE_WARNING;
		if(index > getLengthLastIndex()) return RESULT_TYPE_WARNING; // setElement는 추가된 데이터의 수정만 가능하다. 만약, 데이터 추가를 원한다면 push를 사용하라.
		//		관련멤버변수 검사:
		if(_size <= 0) return RESULT_TYPE_WARNING; 


		InsideType* const_casted_source = const_cast<InsideType*>(source);
		*(_data + index) = const_casted_source;
		
		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	안의 데이터를 최대한 유지한 채 배열의 크기를 조절한다.
	//				당연히, 크기가 줄어들면 뒤의 데이터 일부분은 사라지게 된다.
	//	동작조건:
	//	메모	:	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename InsideType, NEType::Type type>
	type_result NEArrayTemplate<InsideType*, false, InsideType*, type>::resize(type_count size) // 가지고있는 데이터는 보존한채 크기만 변경한다.
	{
		//	pre:
		if(size < 0) return RESULT_TYPE_INFORMATION | RESULT_ABORT_ACTION;



		//	main:
		ThisClass& copied_in_heap = static_cast<ThisClass&>(clone());
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
	template <typename InsideType, NEType::Type type>
	type_result  NEArrayTemplate<InsideType*, false, InsideType*, type>::push(const ThisClass& source)
	{
		//	pre:
		//		파라메터검사:
		if(!source._length)	return RESULT_TYPE_WARNING | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION;
		if(!source._size) return RESULT_TYPE_WARNING | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION;
		if(&source == this) return RESULT_TYPE_WARNING | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION; // 가능은하지만, assign계열에서 자기자신은 에러처리하는게 원칙이므로 형평성을 위해서 에러처리를 한다.



		//	main:
		for(type_index index=0; index < source._length ;index++) // length는 index보다 1크므로 <= 대신 <를 사용한다
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
	template <typename InsideType, NEType::Type type>
	type_result NEArrayTemplate<InsideType*, false, InsideType*, type>::pushFront(const ThisClass& source)
	{
		//	pre:
		//		파라메터 검사:
		if(!source._length)	return RESULT_TYPE_WARNING | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION;
		if(!source._size) return RESULT_TYPE_WARNING | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION;
		if(&source == this) return RESULT_TYPE_WARNING | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION; // 가능은하지만, assign계열에서 자기자신은 에러처리하는게 원칙이므로 형평성을 위해서 에러처리를 한다.



		//	main:
		for(type_index index=0; index < source._length ;index++) // length는 index보다 1크므로 <= 대신 <를 사용한다
		{
			if(_length == _size) break;

			insert(index, &(source.getElement(index)));
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

	template <typename InsideType, NEType::Type type>
	type_index NEArrayTemplate<InsideType*, false, InsideType*, type>::insert(type_index index, const InsideType* const source) 
	{
		//	pre:
		//		파라메터검사:
		if(index < 0) return NE_INDEX_ERROR;
		if(index > _length) return NE_INDEX_ERROR;
		//		관련멤버변수 검사:
		if(_length >= _size) return NE_INDEX_ERROR;



		//	main:
		//		삽입될 공간생성:	데이터를 한칸씩 옆으로 옮긴다
		for(type_index n = getLengthLastIndex(); n >= index ;n--)
			_data[n + 1] = _data[n];



		//	post:
		//		데이터삽입:
		InsideType* const_casted_source = const_cast<InsideType*>(source);
		_data[index] = const_casted_source;
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
	template <typename InsideType, NEType::Type type>
	type_index NEArrayTemplate<InsideType*, false, InsideType*, type>::remove(type_index index) 
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
	//	설명	:	주어진 데이터와 일치하는 엘리먼트가 존재하는지 검색후, 인덱스를 전달
	//				한다.
	//	동작조건:	템플릿 인자 InsideType가 operator==가 정의되어 있어야 한다.
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename InsideType, NEType::Type type>
	type_index NEArrayTemplate<InsideType*, false, InsideType*, type>::find(const InsideType* const source) const
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



	//	---------------------------------------------------------------------------------
	//	설명	:	주어진 배열이 같은 배열인지 확인한다.
	//	동작조건:	같은 배열로 판정되기 위해서는 2가지 조건이 필요하다.
	//					조건 1.	같은 크기와 길이를 가지고 있어야 함.
	//					조건 2. 원소가 같아야 함.
	//					조건 3. 템플릿 인자 InsideType가 operator==를 정의했을 것.
	//	메모	:	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename InsideType, NEType::Type type>
	bool  NEArrayTemplate<InsideType*, false, InsideType*, type>::isEqualSizeAndElement(const ThisClass& source) const
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
	template <typename InsideType, NEType::Type type>
	bool  NEArrayTemplate<InsideType*, false, InsideType*, type>::isEqualElement(const ThisClass& source) const
	{
		if(getLengthLastIndex() != source.getLengthLastIndex()) return false;

		for(type_index index=0; index < _length ;index++)
			if(&getElement(index) != &source.getElement(index))
				return false;

		return true;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename InsideType, NEType::Type type>
	type_result NEArrayTemplate<InsideType*, false, InsideType*, type>::isValid() const  
	{
		//	상위 클래스의 valid 체크:
		type_result result = SuperClass::isValid();
		if(NEResult::hasError(result) == true) return result;
		//	멤버변수의 valid 체크:
		if(	_size > 0 && ! _data) return RESULT_TYPE_WARNING | RESULT_OUT_OF_MEMORY;

		return RESULT_SUCCESS;
	}			



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename InsideType, NEType::Type type>
	void  NEArrayTemplate<InsideType*, false, InsideType*, type>::release()  
	{		
		_release();
		/*
			의도적인 역순 처리:
				여기에서는 _release와 상위클래스의 release를 호출하는 순서가 뒤바뀌어야 한다.
		*/
		return SuperClass::release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename InsideType, NEType::Type type>
	NEType::Type NEArrayTemplate<InsideType*, false, InsideType*, type>::getType() const
	{
		if(type == NEType::NEARRAY_TEMPLATE)
			return NEType::NEPOINTER_ARRAY_TEMPLATE;
		
		
		
		return type;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	지정한 크기만큼의 메모리 공간을 할당한다.
	//				이전에 존재하던 데이터는 모두 초기화되어서 메모리에서 해제 된다.
	//	동작조건:
	//	메모	:	만약 데이터를 유지한 채 크기를 조절하고 싶다면 resize를 사용하라.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename InsideType, NEType::Type type>
	type_result NEArrayTemplate<InsideType*, false, InsideType*, type>::create(type_count size)
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
			_data = new InsideType*[size](); // **주의**	InsideType가 클래스의 경우, 기본생성자()가 필요하다.		

			_size = size;
			_length = 0;
		}

		return RESULT_SUCCESS;
	}	
	
	
	
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename InsideType, NEType::Type type>
	const NEArrayTemplate<InsideType*, false, InsideType*, type>&
		NEArrayTemplate<InsideType*, false, InsideType*, type>::_assign
		(
		const ThisClass& source
		)
	{	
		if(this == &source) return *this;

		create(source._size);
		push(source);
		return *this;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename InsideType, NEType::Type type>
	void  NEArrayTemplate<InsideType*, false, InsideType*, type>::_release() 
	{	
		if(_data)
			delete [] _data;
		_data = NE_NULL;		
	}



	template <typename InsideType, NEType::Type type>
	NEBinaryFileLoader& NEArrayTemplate<InsideType*, false, InsideType*, type>::serialize(NEBinaryFileLoader& loader)
	{	/*
			Serialize의 구현:
				포인터의 콜렉터는 serialize를 구현할 수 없다. 최대한 가능한 일
				(여기서는 콜렉터의 크기를 정하는 일)만 구현한다.
		*/
		//	pre:
		SuperClass::serialize(loader);



		//	main:
		//		길이 정보 보관:
		type_index length = getLength();
		//		버퍼 초기화:
		create(getSize());



		//	post:
		//		길이 정보 복원:
		_length = length;
		return loader;
	}



	template <typename InsideType, NEType::Type type>
	type_index NEArrayTemplate<InsideType*, false, InsideType*, type>::push(const InsideType* const source)
	{
		return insert(getLength(), source);
	}

	template <typename InsideType, NEType::Type type>
	type_index NEArrayTemplate<InsideType*, false, InsideType*, type>::insert(type_index index, const InsideType& source)
	{
		return insert(index, &source);
	}

	template <typename InsideType, NEType::Type type>
	type_index NEArrayTemplate<InsideType*, false, InsideType*, type>::pop()
	{
		return remove(getLengthLastIndex());
	}

	template <typename InsideType, NEType::Type type>
	type_index NEArrayTemplate<InsideType*, false, InsideType*, type>::pushFront(const InsideType& source)
	{
		return insert(0, &source);
	}

	template <typename InsideType, NEType::Type type>
	type_index NEArrayTemplate<InsideType*, false, InsideType*, type>::pushFront(const InsideType* const source)
	{
		return insert(0, source);
	}

	template <typename InsideType, NEType::Type type>
	type_index NEArrayTemplate<InsideType*, false, InsideType*, type>::popFront()
	{
		return remove(0);
	}
}
