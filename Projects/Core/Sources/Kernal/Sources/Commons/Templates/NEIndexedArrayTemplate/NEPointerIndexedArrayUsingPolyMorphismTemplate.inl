namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	NEIndexedArrayTemplate<Type*, true, type>::NEIndexedArrayTemplate()
		: SuperClass(0), _data(NE_NULL)
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	NEIndexedArrayTemplate<Type*, true, type>::NEIndexedArrayTemplate(type_count size)
		: SuperClass(size), _data(NE_NULL)
	{
		create(size);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	NEIndexedArrayTemplate<Type*, true, type>::NEIndexedArrayTemplate(const ThisClass& source)
		: SuperClass(source), _data(NE_NULL)
	{
		_assign(source);
	}	



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	NEIndexedArrayTemplate<Type*, true, type>::~NEIndexedArrayTemplate()
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	const NEIndexedArrayTemplate<Type*, true, type>& NEIndexedArrayTemplate<Type*, true, type>::operator=(const ThisClass& source) 
	{
		NEReservedCollectorTemplate::operator=(source);

		return _assign(source);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	NEIndexedArrayTemplate<Type*, true, type> NEIndexedArrayTemplate<Type*, true, type>::operator+(const ThisClass& source) const 
	{
		//	pre:
		//		파라메터 검사:
		if(source._length <= 0)	return ThisClass(*this);



		//	main:				
		//		임시 버퍼 생성:
		ThisClass buffer(source._length + _length);
		//		버퍼에 복사:
		buffer.push(*this);
		buffer.push(source);



		//	post:
		//		버퍼를 값으로 반환:
		return buffer;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	bool  NEIndexedArrayTemplate<Type*, true, type>::operator==(const ThisClass& source) const
	{
		if(this == &source) return true;
		if(SuperClass::operator==(source) == false) return false;

		return isEqualElement(source);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	bool  NEIndexedArrayTemplate<Type*, true, type>::operator!=(const ThisClass& source) const
	{
		return !(operator==(source));
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//				2011-11-20	이태훈	버그 수정	source가 *this일 때 발생하게될 오류 대처 추가
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	const NEIndexedArrayTemplate<Type*, true, type>& NEIndexedArrayTemplate<Type*, true, type>::operator+=(const ThisClass& source)
	{
		if(this == &source)
		{
			ThisClass copyied(*this);
			resize(_length + copyied._length);
			push(copyied);
		}
		else 
		{
			resize(_length + source._length);		
			push(source);
		}

		return *this;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	Type& NEIndexedArrayTemplate<Type*, true, type>::getElement(type_index index) 
	{
		//	pre:
		//		널 레퍼런스:
		Type* null_pointer = NE_NULL;
		//		파라메터 검사:
		if(index < 0) return *null_pointer;
		if(index > getSizeLastIndex()) return *null_pointer;
		//		관련멤버변수 검사:
		if(_size <= 0) return *null_pointer;
		if( ! _occupiedset[index]) return *null_pointer;



		//	post:
		return *(_data[index]);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	const Type& NEIndexedArrayTemplate<Type*, true, type>::getElement(type_index index) const 
	{			
		//	pre:
		//		널 레퍼런스:
		Type* null_pointer = NE_NULL;
		//		파라메터검사:
		if(index < 0) return *null_pointer;
		if(index > getSizeLastIndex()) return *null_pointer;
		//		관련멤버변수 검사:
		if(_size <= 0) return *null_pointer;
		if( ! _occupiedset[index]) return *null_pointer;



		//	post:
		return *(_data[index]);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	type_result NEIndexedArrayTemplate<Type*, true, type>::setElement(type_index index, const Type* const source)  
	{
		//	pre:
		//		파라메터검사:
		if( !(&source) ) return NE_INDEX_ERROR;
		if(index < 0) return NE_INDEX_ERROR;
		if(index > getSizeLastIndex()) return NE_INDEX_ERROR; // setElement는 추가된 데이터의 수정만 가능하다. 만약, 데이터 추가를 원한다면 push를 사용하라.
		//		관련멤버변수 검사:
		if(_size <= 0) return NE_INDEX_ERROR;
		if( ! _occupiedset[index]) return RESULT_TYPE_ERROR;



		//	main:
		//		포인터 변경:
		//			메모리 해제:	포인터값을 바꾸기전에 동적생성한 메모리를 먼저 없애야 한다.
		_returnHeapMemory(index);
		//			포인터 변경:
		_data[index] = static_cast<Type*>( &(source->clone()) ); // clone (= virtual 복사생성자 )으로 값을 삽입한다
		_occupiedset[index] = true;

		return NE_INDEX_ERROR;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	주어진 데이터와 일치하는 엘리먼트가 존재하는지 검색후, 인덱스를 전달
	//				한다.
	//	동작조건:	템플릿 인자 Type가 operator==가 정의되어 있어야 한다.
	//	메모	:
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	type_index NEIndexedArrayTemplate<Type*, true, type>::find(const Type* const source) const
	{
		//	pre:
		//		파라메터 검사:
		if( !(&source) ) return RESULT_TYPE_ERROR | RESULT_WRONG_POINTER_ADDRESSING | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION;
		if(_length < 0) return NE_INDEX_ERROR;



		//	main:
		//		검색:
		for(type_index index=0; index < _length ;index++)
			if( _data[index] == source)
				return index;



		//	post:
		//		에러반환:	못찾았다
		return NE_INDEX_ERROR; // -1
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	임의의 인덱스에 위치한 데이터를 하나 삭제한다.
	//	동작조건:	지정한 인덱스가 최대 인덱스보다 작고, 0 이상이다.
	//	메모	:
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	type_result NEIndexedArrayTemplate<Type*, true, type>::resize(type_count size) // 가지고있는 데이터는 보존한채 크기만 변경한다.
	{
		//	pre:
		//		파라메터 검사:
		if(size < 0) return RESULT_TYPE_INFORMATION | RESULT_ABORT_ACTION;



		//	main:
		ThisClass& copied_in_heap = static_cast<ThisClass&>(clone());
		create(size); // size도 내부에서 세팅됨.
		for(int n=0; n < copied_in_heap.getSize() ;n++)
			insert(n, copied_in_heap[n]);



		//	post:
		delete &copied_in_heap;
		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	배열 자체를 push한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	type_result NEIndexedArrayTemplate<Type*, true, type>::push(const ThisClass& source)
	{
		//	pre:
		//		파라메터 검사:
		if(!source._length)	return RESULT_TYPE_INFORMATION | RESULT_ABORT_ACTION;
		if(!source._size) return RESULT_TYPE_INFORMATION | RESULT_ABORT_ACTION;
		if(&source == this) return RESULT_TYPE_WARNING | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION; // 가능은하지만, assign계열에서 자기자신은 에러처리하는게 원칙이므로 형평성을 위해서 에러처리를 한다.



		//	main:
		//		데이터 복사:
		for(type_index index=0; index < source._length ;index++) // length는 index보다 1크므로 <= 대신 <를 사용한다
		{
			if(_length == _size) break;

			push(source.getElement(index));
		}



		//	post:
		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	type_result NEIndexedArrayTemplate<Type*, true, type>::pushFront(const ThisClass& source)
	{
		//	pre:
		//		파라메터검사:
		if(!source._length)	return RESULT_TYPE_INFORMATION | RESULT_ABORT_ACTION;
		if(!source._size) return RESULT_TYPE_INFORMATION | RESULT_ABORT_ACTION;
		if(&source == this) return RESULT_TYPE_WARNING | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION; // 가능은하지만, assign계열에서 자기자신은 에러처리하는게 원칙이므로 형평성을 위해서 에러처리를 한다.



		//	main:
		//		복사:
		for(type_index index=0; index < source._length ;index++) // length는 index보다 1크므로 <= 대신 <를 사용한다
		{
			if(_length == _size) break;

			pushFront(source.getElement(index));
		}



		//	post:
		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	데이터를 임의의 인덱스에 삽입한다.	
	//	동작조건:	길이가 크기보다 작아야 한다. 데이터의 공간이 존재해야 한다.
	//	메모	:	만약 5에 데이터를 삽입하면, 5에 있던 데이터는 6으로 밀려난다.
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	//	중간에 값을 삽입. 길이 == 크기 일경우, 전체 크기가 + 1 증가한다.
	template <typename Type, NEType::Type type>
	type_index NEIndexedArrayTemplate<Type*, true, type>::insert(type_index index, const Type* const source) 
	{
		//	pre:
		//		파라메터 검사:
		if( !(&source) ) return NE_INDEX_ERROR;
		if(index < 0) return NE_INDEX_ERROR;
		if(index > getSizeLastIndex()) return NE_INDEX_ERROR;
		//		관련 멤버변수 검사:
		//			NEArray와 다르게, 꽉차있다면 지정한 장소에 setElement를 시도한다.
		if(_length > _size) return NE_INDEX_ERROR;
		//		지정한 자리가 이미 뭔가 있다면:
		//			덮어쓰기로 동작한다.
		if(_occupiedset.getSize() != getSize()) return RESULT_TYPE_ERROR | RESULT_WRONG_BOUNDARY;
		if(_occupiedset[index]) 
		{
			if(NEResult::hasError(setElement(index, source)))
				return NE_INDEX_ERROR;
			return index;			
		}




		//	main:
		//		소유권 획득:
		//			왜 소유권을 먼저 획득하는가:
		//				source->clone에 의해서 생성된 데이터들 안에 또 다시 NEIndexTemplate을 쓰는 
		//				경우가 있을 수 있다. 이때 만들어질 인스턴스를 자식이라 하고, 현재의 호출자를
		//				부모라 하자.
		//				부모의 소유권 테이블을 set 하지 않고 clone으로 자식을 생성해버리면, 자식에 
		//				입장에서 같은 NEIndexeTemplate에 소유권 비어있는 인덱스를 찾고, 결과적으로
		//				부모의 자리를 들어꿰차게 된다.
		_occupiedset[index] = true;
		//		데이터삽입:
		//			데이터 변환:
		_data[index] = static_cast<Type*>( &(source->clone()) );
		
		//		길이 증가:
		_length++;



		//	post:
		return index;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	임의의 인덱스에 위치한 데이터를 하나 삭제한다.
	//	동작조건:	지정한 인덱스가 최대 인덱스보다 작고, 0 이상이다.
	//	메모	:
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	type_index NEIndexedArrayTemplate<Type*, true, type>::remove(type_index index) 
	{
		//	pre:
		//		파라메터 검사:
		if(index < 0) return NE_INDEX_ERROR;
		if(index > getSizeLastIndex()) return NE_INDEX_ERROR;
		//		지정한 자리에 아무것도 없다면:
		if(_occupiedset.getSize() != getSize()) return RESULT_TYPE_ERROR | RESULT_WRONG_BOUNDARY;
		if( ! _occupiedset[index]) return RESULT_SUCCESS | RESULT_ABORT_ACTION;



		//	main:
		//		포인터(= 데이터 ) 삭제:
		//			메모리 해제:	포인터를 삭제하기 전에 동적으로 생성한 메모리를 먼저 해제해야 한다
		_returnHeapMemory(index);


		//	post:
		//		길이 정보 수정:
		_length--;
		return index;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	주어진 배열이 같은 배열인지 확인한다.
	//	동작조건:	같은 배열로 판정되기 위해서는 2가지 조건이 필요하다.
	//					조건 1.	같은 크기와 길이를 가지고 있어야 함.
	//					조건 2. 원소가 같아야 함.
	//					조건 3. 템플릿 인자 Type가 operator==를 정의했을 것.
	//	메모	:
	//	히스토리:	2013-01-10	이태훈	개발 완료				
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	bool  NEIndexedArrayTemplate<Type*, true, type>::isEqualSizeAndElement(const ThisClass& source) const
	{
		//	pre:
		if(_size != source._size) return false;
		if(getLength() != source.getLength()) return false;
		if(isEqualElement(source) == false) return false;
		


		//	post:
		return true;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	크기와 길이를 고려하지 않고, 같은 원소를 가지고 있는지 만을 따진다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	bool  NEIndexedArrayTemplate<Type*, true, type>::isEqualElement(const ThisClass& source) const
	{
		//	pre:
		if(getLengthLastIndex() != source.getLengthLastIndex()) return false;
		if(_occupiedset != source._occupiedset) return false;

		//	main:
		for(type_index index=0; index < _length ;index++)
		{				
			if(getElement(index) != source.getElement(index))
				return false;
		}

		//	post:
		return true;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	type_result NEIndexedArrayTemplate<Type*, true, type>::isValid() const  
	{
		//	pre:
		//		상위 클래스의 VALID 체크:
		type_result result = SuperClass::isValid();
		if(NEResult::hasError(result) == true) return result;		
		//		멤버변수:
		if(	_size > 0 && ! _data) return RESULT_TYPE_WARNING | RESULT_OUT_OF_MEMORY;
		if(_occupiedset.getSize() != getSize()) return RESULT_TYPE_ERROR | RESULT_WRONG_BOUNDARY;

		//	post:
		return RESULT_SUCCESS;
	}			



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	void  NEIndexedArrayTemplate<Type*, true, type>::release()  
	{		
		_release();
		/*
			의도적인 역순 처리:
				여기에서는 _release와 상위클래스의 release를 호출하는 순서가 뒤바뀌어야 한다.
		*/
		return SuperClass::release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	NEType::Type NEIndexedArrayTemplate<Type*, true, type>::getType() const
	{
		if(type == NEType::NEARRAY_TEMPLATE)
			return NEType::NEPOINTER_ARRAY_WITH_POLYMORPHISM_TEMPLATE;



		return type;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	지정한 크기만큼의 메모리 공간을 할당한다.
	//				이전에 존재하던 데이터는 모두 초기화되어서 메모리에서 해제 된다.
	//	동작조건:
	//	메모	:	만약 데이터를 유지한 채 크기를 조절하고 싶다면 resize를 사용하라.
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	type_result NEIndexedArrayTemplate<Type*, true, type>::create(type_count size)
	{
		release();

		if(size > 0)
		{
			//	보통, Type가 primitive일경우에, 0으로 대입을 해야한다. 이걸 배열로 표현하면
			//		new Type[size] = {0, }; 
			//	가 된다는 건 알고있다.
			//	그러나 Type가 클래스일경우에는, 위의 코드에서 int 생성자가 호출된다. 즉, 쓸데없는 int생성자를 만들지 않으면
			//	클래스를 이 템플릿클래스에 넣을 수 없다.
			//	그러나, new int(); 가 0으로 초기화가 된다는 사실에서 착안,
			//	밑의 코드는, Type가 클래스이건, primitive이건 같은 생성자를 호출하게 만들어주는 단 하나의 코드다.			
			_data = new Type*[size](); //주의: 클래스의 경우, 기본생성자()가 필요하다.

			_occupiedset.create(size);
			for(int n=0; n < _occupiedset.getSize() ;n++)
				_occupiedset.push(false);

			_size = size;
			_length = 0;
		}

		return RESULT_SUCCESS;
	}	
	
	
	
	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	const NEIndexedArrayTemplate<Type*, true, type>& NEIndexedArrayTemplate<Type*, true, type>::_assign(const ThisClass& source)
	{	//	pre:
		if(this == &source) return *this;

		//	main:
		//		버퍼 정의:
		create(source._size);
		//		복사:
		//			복사 알고리즘:
		/*
						소유권을 전부 해제하고, source의 소유권을 탐색한다.
						탐색하면서 source의 소유권이 존재하면, 해당 원소만 복사하고,
						소유권을 set 한다.
					push(ThisClass)를 쓰지 않는 이유:
						push는 "가장 최초 빈자리"에 넣는 함수이므로, 이렇게 하면
						source의 인덱스와 달라지게 된다.
		*/
		const NEBooleanSet& source_occupiedset = source._occupiedset;
		for(int n=0; n < source_occupiedset.getLength() ;n++)
			if(source_occupiedset[n])
				insert(n, source.getElement(n));

		//	pre:
		return *this;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	void  NEIndexedArrayTemplate<Type*, true, type>::_release() 
	{	
		if(_data)
		{
			while(_size)
			{				
				_returnHeapMemory(getSizeLastIndex());
				_size--;
			}

			delete [] _data;
		}
		_data = NE_NULL;
		_occupiedset.release();
	}		



	//	---------------------------------------------------------------------------------
	//	설명	:	메모리할당을 해제한다.
	//	동작조건:
	//	메모	:	setElement, push 등, 데이터를 할당하기 전에 호출된다.
	//	히스토리:	2013-01-10	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename Type, NEType::Type type>
	type_result NEIndexedArrayTemplate<Type*, true, type>::_returnHeapMemory(type_index index)
	{
		//	pre:
		//		파라메터 검사:
		if(index < 0) return RESULT_TYPE_WARNING | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION;
		if(_length <= 0) return RESULT_TYPE_WARNING | RESULT_WRONG_BOUNDARY | RESULT_ABORT_ACTION;



		//	main:
		//		메모리해제:	먼저, 소유권을 확인한다.
		if(_occupiedset[index])
			delete _data[index];
		//		소유권 소멸:
		//			객체가 실제로 사라지는 건 insert에서 덮어씌워진다.
		//			메모리가 반환되는 건, NEIndexedArrayTemplate 자체가 반환될때다.
		_occupiedset[index] = false;

		return RESULT_SUCCESS;
	}



	template <typename Type, NEType::Type type>
	NEBinaryFileLoader& NEIndexedArrayTemplate<Type*, true, type>::serialize(NEBinaryFileLoader& loader)
	{
		/*
			Serialize의 구현:
				포인터의 콜렉터는 serialize를 구현할 수 없다. 최대한 가능한 일
				(여기서는 콜렉터의 크기를 정하는 일)만 구현한다.
		*/
		//	pre:
		SuperClass::serialize(loader);



		//	main:
		//		길이정보 보관:
		type_index length = getLength();
		//		버퍼 초기화:
		create(getSize());


	
		//	post:
		//		길이 정보 복원:
		_length = length;
		return loader >> _occupiedset;
	}



	template <typename Type, NEType::Type type>
	NEBinaryFileSaver& NEIndexedArrayTemplate<Type*, true, type>::serialize(NEBinaryFileSaver& saver) const
	{
		SuperClass::serialize(saver);

		return saver << _occupiedset;
	}



	template <typename Type, NEType::Type type>
	type_index NEIndexedArrayTemplate<Type*, true, type>::_searchIndex(bool by_decreasing, bool target_is_occupied) const
	{
		if( ! by_decreasing)
		{
			for(int n=0; n < _occupiedset.getLength() ;n++)
				if(_occupiedset[n] == target_is_occupied)
					return n;
		}
		else
		{
			for(int n=_occupiedset.getLengthLastIndex(); n >= 0 ;n--)
				if(_occupiedset[n] == target_is_occupied)
					return n;
		}


		return NE_INDEX_ERROR;
	}



	template <typename Type, NEType::Type type>
	NEObject& NEIndexedArrayTemplate<Type*, true, type>::clone() const
	{
		return *(new ThisClass(*this));
	}



	template <typename Type, NEType::Type type>
	type_index NEIndexedArrayTemplate<Type*, true, type>::push(const Type* const source)
	{
		type_index highest_vacant_index = _searchIndex(true, false);
		if(highest_vacant_index == NE_INDEX_ERROR) return NE_INDEX_ERROR;

		return insert(highest_vacant_index, source);
	}

	template <typename Type, NEType::Type type>
	type_index NEIndexedArrayTemplate<Type*, true, type>::insert(type_index index, const Type& source)
	{
		return insert(index, &source);
	}

	template <typename Type, NEType::Type type>
	type_index NEIndexedArrayTemplate<Type*, true, type>::pop()
	{
		type_index highest_occupied_index = _searchIndex(true, true);
		if(highest_occupied_index == NE_INDEX_ERROR) return NE_INDEX_ERROR;

		return remove(highest_occupied_index);
	}

	template <typename Type, NEType::Type type>
	type_index NEIndexedArrayTemplate<Type*, true, type>::pushFront(const Type& source)
	{
		return pushFront(&source);
	}

	template <typename Type, NEType::Type type>
	type_index NEIndexedArrayTemplate<Type*, true, type>::pushFront(const Type* const source)
	{
		type_index lowest_vacant_index = _searchIndex(false, false);
		if(lowest_vacant_index == NE_INDEX_ERROR) return NE_INDEX_ERROR;

		return insert(lowest_vacant_index, source);
	}

	template <typename Type, NEType::Type type>
	type_index NEIndexedArrayTemplate<Type*, true, type>::popFront()
	{
		type_index lowest_occupied_index = _searchIndex(false, true);
		if(lowest_occupied_index == NE_INDEX_ERROR) return NE_INDEX_ERROR;

		return remove(lowest_occupied_index);
	}



	template <typename Type, NEType::Type type>
	const NEOccupiedSet& NEIndexedArrayTemplate<Type*, true, type>::getOccupiedSet() const
	{
		return _occupiedset;
	}
}