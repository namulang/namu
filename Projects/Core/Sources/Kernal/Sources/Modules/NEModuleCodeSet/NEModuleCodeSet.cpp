#pragma message("NEModuleCodeSet.cpp - 1")
#include "NEModuleCodeSet.hpp"
#pragma message("NEModuleCodeSet.cpp - 2")
#include "../Kernal/Kernal.hpp"
#pragma message("NEModuleCodeSet.cpp - 3")
#include "../NEIndexedModuleSet/NEIndexedModuleSet.hpp"
#pragma message("NEModuleCodeSet.cpp - 4")

namespace NE
{
	NEModuleCodeSet::NEModuleCodeSet()
		: Super()
	{
		
	}
	NEModuleCodeSet::NEModuleCodeSet(type_index size)
		: Super(size)
	{
		
	}
	NEModuleCodeSet::NEModuleCodeSet(const This& source)
		: Super(source)
	{
		_assign(source);	//	이제, NENodeCodeSet::insert가 내부적으로 호출된다.
	}

	NEModuleCodeSet::~NEModuleCodeSet()
	{
		release();	//	여기서 해제 하지 않으면 상위클래스 소멸자에서 상위클래스 release를 호출해버릴 것이다.
	}

	const NEModuleCodeSet& NEModuleCodeSet::operator+=(const This& source)
	{
		if(this == &source)
		{
			This copyied(*this);
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

	NEModuleCodeSet NEModuleCodeSet::operator+(const This& source) const
	{
		This buffer(getSize() + source.getSize());

		buffer.push(*this);
		buffer.push(source);

		return buffer;
	}

	type_index NEModuleCodeSet::insert(type_index index, const NEModule& source)
	{
		//	pre:
		NEIndexedModuleSet& moduleset = _getModuleSet();
		if(! &moduleset)
		{
			KERNAL_ERROR(" : ");
			return NE_INDEX_ERROR;
		}


		//	main:
		type_index modulecode = moduleset.pushFront(source);
		if(modulecode == NE_INDEX_ERROR)
		{
			KERNAL_ERROR(" : ")
				return NE_INDEX_ERROR;
		}
		if( NEResult::hasError(_insert(index, modulecode)) )
		{
			KERNAL_ERROR(" : ");
			return NE_INDEX_ERROR;
		}
		//	Owner 설정:
		moduleset[modulecode]._owner = this;
		moduleset[modulecode]._index = index;
		


		//	post:
		return index;
	}
	type_index NEModuleCodeSet::remove(type_index index)
	{
		//	pre:
		NEIndexedModuleSet& moduleset = _getModuleSet();
		if(! &moduleset)
		{
			KERNAL_ERROR(" : ");
			return NE_INDEX_ERROR;
		}



		//	main:
		type_index modulecode = moduleset.remove(_getElement(index));
		if(modulecode == NE_INDEX_ERROR)
		{
			KERNAL_ERROR(" : ");
			return NE_INDEX_ERROR;
		}

		return _remove(index);
	}

	NEModule& NEModuleCodeSet::getElement(type_index index)
	{
		//	pre:
		NEModule* nullpointer = 0x00;
		NEIndexedModuleSet& moduleset = _getModuleSet();
		if(! &moduleset)
		{
			KERNAL_ERROR(" : ");
			return *nullpointer;
		}



		//	main:
		type_index& modulecode = _getElement(index);
		if( ! &modulecode)
		{
			KERNAL_ERROR(" : 주어진 인덱스가 범위를 벗어난 잘못된 참조입니다.");

			return *nullpointer;
		}

		return moduleset[modulecode];
	}
	const NEModule& NEModuleCodeSet::getElement(type_index index) const
	{
		//	pre:
		NEModule* nullpointer = 0x00;
		const NEIndexedModuleSet& moduleset = _getModuleSet();
		if(! &moduleset)
		{
			KERNAL_ERROR(" : ");
			return *nullpointer;
		}



		//	main:
		const type_code& modulecode = _getElement(index);
		if( ! &modulecode)
		{
			KERNAL_ERROR(" : 주어진 인덱스가 범위를 벗어난 잘못된 참조입니다.");

			return *nullpointer;
		}

		return moduleset[modulecode];
	}
	type_result NEModuleCodeSet::setElement(type_index index, const NEModule& source)
	{
		//	pre:
		NEIndexedModuleSet& moduleset = _getModuleSet();
		if(! &moduleset)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}



		//	main:
		//	TEST: 이코드만으로도 제대로 node::unlist가 동작하는가?
		type_index& modulecode = _getElement(index);
		if( ! &modulecode)
		{
			KERNAL_ERROR(" : 주어진 인덱스가 범위를 벗어난 잘못된 참조입니다.");

			return RESULT_TYPE_ERROR;
		}
		return moduleset.setElement(modulecode, source);
	}
	type_index NEModuleCodeSet::match(const NEModule& source) const
	{
		//	pre:
		const NEIndexedModuleSet& moduleset = _getModuleSet();
		if(! &moduleset)
		{
			KERNAL_ERROR(" : ");
			return NE_INDEX_ERROR;
		}



		//	main:
		for(int n=0; n < getLength() ;n++)
		{
			type_index modulecode = _getElement(n);
			const NEModule& unit = moduleset[modulecode];
			if( ! &unit)
			{
				KERNAL_ERROR(" : ");
				return NE_INDEX_ERROR;
			}

			if(unit == source)
				return n;
		}

		return NE_INDEX_ERROR;
	}
	type_result NEModuleCodeSet::execute()
	{
		//	pre:
		//		타겟팅:
		type_result result = RESULT_SUCCESS;
		NENodeManager::LocalStack& localstack = Kernal::getInstance().getNodeManager().getLocalStack();
		//		로컬 스택 조정:
		//			새로운 로컬스택을 넣기전에 이전 값 보존:
		//				왜 이전값을 보존하는가:
		//					모듈셋 안에 모듈셋이 있는 구조라면, 내부 모듈셋을 처리하고 다시
		//					외부 모듈셋으로 돌아왔을때 실제 모듈셋과 로컬스택에 저장된 모듈
		//					셋이 어긋날 수 있기 때문이다.
		This& before_stage_moduleset = localstack.getRecentModuleSet();
		localstack._setRecentModuleSet(*this);
		localstack._setRecentResultCode(RESULT_NOTHING);


		
		//	main:
		//		모듈 실행:
		for(type_index n=0; n < _length ;n++)
		{
			NEModule& module = getElement(n);

			//		실행:
			//			로컬 스택 갱신:
			if( ! module.isEnable()) continue;
			localstack._setRecentResultCode(module.execute());
			//			결과값 적용:	만약, 모듈중 하나라도 false 혹은 에러가 있다면, 에러여부를 리턴해야한다
			localstack._setRecentModuleSetIndex(n);
			if(localstack.getRecentResultCode() & RESULT_FALSE)
				result = result | RESULT_FALSE;			
#ifdef DEVELOPER			
			//			디버그 Flag 적용:	상위 클래스(node.execute)로 정보를 보낸다.
			if(NEResult::hasError(localstack.getRecentResultCode()) == true)
				NEResult::addErrorFlag(result, localstack.getRecentResultCode());
			//			디버그 출력:
			if(NEResult::hasError(localstack.getRecentResultCode()) == true)
			{
				const NEHeader& header = module.getClass().getHeader();
				type_result result_value = localstack.getRecentResultCode();
				KERNAL_ERROR("E100031C4 : 모듈의 에러 발생\n모듈셋에서 실행한 모듈이 에러를 반환했습니다\n프레임 카운트 : %d\t모듈번호 : %d\n결과코드 : %d\t에러코드 : %d\n모듈 식별자:\n\t이름 : %s\n\t개발자 : %s\n\t개정번호 : %d", localstack.getFrameCount(), n, result_value, NEResult::getErrorCode(result_value), header.getName().toCharPointer(), header.getAuthor().toCharPointer(), header.getRevisionCount())
			}
#endif
		}



		//	post:
		//		이전 함수에서 할당된 주소를 다시 복원:
		localstack._setRecentModuleSet(before_stage_moduleset);

		return RESULT_TRUE;
	}

	const NEModuleCodeSet& NEModuleCodeSet::_assign(const This& source)
	{
		if(this == &source) return *this;

		create(source.getSize());
		push(source);

		return *this;
	}

	type_result NEModuleCodeSet::resize(type_index new_size)
	{
		/*
			왜 resize를 재정의 하는가:
				NETVector<T, type_bool, Q>에서 정의한 resize 
				다른 원리로 동작하기 때문이다. 해당 함수에서는 clone
				함수를 사용해서 담아둘 인스턴스를 임시 버퍼에 담아두는
				역할을 수행하고 있는데, 실질적으로 이 코드는 NEIndexedNodeSet
				에서 동작이 불가능한 코드이기 때문이다.
				
			왜 clone을 사용할 수 없는가:
				관련한 내용은 NETEnlistableSet.hpp의 복사생성자 주석을 
				참고하라.

			알고리즘:	ShallowCopy로 효율을 높인다.
				이 방식은 인스턴스를 shallow copy함으로써 효율을 높이는 알고리즘이다.
				InnerTrait이 OuterTrait보다 가벼울 경우에만 사용이 가능한 방법이며,
				만약 전보다 크기를 축소시키는 resize라면, 그 차이만큼 인스턴스를 삭제해야한다.

				따라서 size가 5 -> 10으로 변경되는 경우, 이전 알고리즘은
					buffer.create()
					buffer.push(src);	<---	5 * (type_code + NEIndexedNodeSet에서 NENode) 복사
					src.resize(10);
					src.push(buffer)	<---	5 * (type_code + NEIndexedNodeSet에서 NENode) 복사
										+)		10 * (type_code + NENode) 비용 소모.
				반면, 이 알고리즘은,
					type_code buffer[5];
					buffer.push(src);	<---	5 * type_code 복사.
					delete src._data;	//	delete[]가 아님에 유의.
					src = new type_code[10];
					src.push(buffer);	<---	5 * type_code 복사.
										+)		10 * type_code 복사 비용 소모.
				이므로, 전체적으로 큰 효율을 얻을 수 있다.
		*/
		//	pre:		
		int instance_count = getLength() - new_size;	//	삭제하게될 인스턴스 갯수
		if(instance_count > 0)
			for(int n=0; n < instance_count ;n++)
				pop();	//	당연히 삭제되는 건 항상 뒤에서부터다. 


		//	main:
		//		얇은 복사를 수행한다:	버퍼를 만든다. ArrayTemplate을 사용할 수 없다.
		int length = getLength();
		InnerTrait* buffer = new InnerTrait[_length];
		for(int n=0; n < length ;n++)
			buffer[n] = _data[n];
		//		resize:
		_length = 0;	//	_length = 0을 했으므로 InnerElement를 delete하는 release()가 호출되지 않게 된다.		
		create(new_size);	//	내부에서 release()를 호출한다.


		//		post:
		for(int n=0; n < length ;n++)
			_data[n] = buffer[n];
		_length = length;
		delete [] buffer;
		return RESULT_SUCCESS;
	}

	void NEModuleCodeSet::release()
	{
		while(getLength())
			pop();

		Super::release();
	}

	NEIndexedModuleSet& NEModuleCodeSet::_getModuleSet()
	{
		NEIndexedModuleSet* nullpointer = 0x00;
		if( ! isManaged())
		{
			KERNAL_ERROR(" : ")
				return *nullpointer;
		}
		return getManager()._getModuleSet();
	}

	const NEIndexedModuleSet& NEModuleCodeSet::_getModuleSet() const
	{
		const NEIndexedModuleSet* nullpointer = 0x00;
		if( ! isManaged())
		{
			KERNAL_ERROR(" : ")
			return *nullpointer;
		}
		return getManager().getModuleSet();
	}
}