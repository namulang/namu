#include "NENodeCodeSet.hpp"
#include "../Kernal/Kernal.hpp"
#include "../NEIndexedNodeSet/NEIndexedNodeSet.hpp"

namespace NE
{
	NENodeCodeSet::NENodeCodeSet()
		: SuperClass()
	{
		
	}

	NENodeCodeSet::NENodeCodeSet(type_index size)
		: SuperClass(size)
	{
		
	}
	NENodeCodeSet::NENodeCodeSet(const NENodeCodeSet& source)
		: SuperClass(source)
	{
		_assign(source);	//	이제, NENodeCodeSet::insert가 내부적으로 호출된다.
	}

	NENodeCodeSet::~NENodeCodeSet()
	{
		release();	//	여기서 해제 하지 않으면 상위클래스 소멸자에서 상위클래스 release를 호출해버릴 것이다.
	}

	const NENodeCodeSet& NENodeCodeSet::operator+=(const NENodeCodeSet& source)
	{
		if(this == &source)
		{
			NENodeCodeSet copyied(*this);
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

	NENodeCodeSet NENodeCodeSet::operator+(const NENodeCodeSet& source) const
	{
		ThisClass buffer(getSize() + source.getSize());

		buffer.push(*this);
		buffer.push(source);

		return buffer;
	}

	type_index NENodeCodeSet::insert(type_index index, const NENode& source)
	{
		//	pre:
		
		//	TEST: serialize가 없더라도 insert만으로도 올바르게 _enlist가 동작할 것이다.

		NEIndexedNodeSet& nodeset = _getNodeSet();
		if(! &nodeset)
		{
			KERNAL_ERROR(" : ");
			return NE_INDEX_ERROR;
		}



		//	main:
		type_index nodecode = nodeset.pushFront(source);
		if(nodecode == NE_INDEX_ERROR)
		{
			KERNAL_ERROR(" : 인스턴스가 제대로 들어가지 않았습니다.\n\t코드: %d", nodecode);
			return NE_INDEX_ERROR;
		}
		if( NEResult::hasError(_insert(index, nodecode)) )
		{
			KERNAL_ERROR(" : ");
			return NE_INDEX_ERROR;
		}
		//		Owner 설정:
		nodeset[nodecode]._owner = this;

		if(isEnlisted())
		{
			NENode& node = getElement(index);			
			if( NEResult::hasError(_onEnlisted(node)) )
			{
				KERNAL_ERROR(" : ");
				return NE_INDEX_ERROR;
			}
		}

		return index;
	}
	type_index NENodeCodeSet::remove(type_index index)
	{
		//	pre:
		if(	index < 0					|| 
			index > getLengthLastIndex())
		{
			KERNAL_ERROR(" : 주어진 인덱스가 범위를 넘습니다.");
			return NE_INDEX_ERROR;
		}
		NEIndexedNodeSet& nodeset = _getNodeSet();
		if(! &nodeset)
		{
			KERNAL_ERROR(" : ");
			return NE_INDEX_ERROR;
		}



		//	main:
		type_index nodecode = nodeset.remove(_getElement(index));
		if(nodecode == NE_INDEX_ERROR)
		{
			KERNAL_ERROR(" : ");
			return NE_INDEX_ERROR;
		}

		return _remove(index);
	}

	NENode& NENodeCodeSet::getElement(type_index index)
	{
		//	pre:
		NENode* nullpointer = 0x00;
		NEIndexedNodeSet& nodeset = _getNodeSet();
		if(! &nodeset)
		{
			KERNAL_ERROR(" : ");
			return *nullpointer;
		}



		//	main:
		type_index& nodecode = _getElement(index);
		if( ! &nodecode)
		{
			KERNAL_ERROR(" : 주어진 인덱스가 범위를 벗어난 잘못된 참조입니다.");

			return *nullpointer;
		}



		//	post:
		return nodeset[nodecode];
	}
	const NENode& NENodeCodeSet::getElement(type_index index) const
	{
		//	pre:
		NENode* nullpointer = 0x00;
		const NEIndexedNodeSet& nodeset = _getNodeSet();
		if(! &nodeset)
		{
			KERNAL_ERROR(" : ");
			return *nullpointer;
		}



		//	main:
		const type_index& nodecode = _getElement(index);
		if( ! &nodecode)
		{
			KERNAL_ERROR(" : 주어진 인덱스가 범위를 벗어난 잘못된 참조입니다.");
			
			return *nullpointer;
		}



		//	post:
		return nodeset[nodecode];
	}
	type_result NENodeCodeSet::setElement(type_index index, const NENode& source)
	{
		//	pre:
		NEIndexedNodeSet& nodeset = _getNodeSet();
		if(! &nodeset)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}



		//	main:
		type_index& nodecode = _getElement(index);
		if( ! &nodecode)
		{
			KERNAL_ERROR(" : 주어진 인덱스가 범위를 벗어난 잘못된 참조입니다.");

			return RESULT_TYPE_ERROR;
		}
		return nodeset.setElement(nodecode, source);
	}
	type_index NENodeCodeSet::find(const NENode& source) const
	{
		//	pre:
		const NEIndexedNodeSet& nodeset = _getNodeSet();
		if(! &nodeset)
		{
			KERNAL_ERROR(" : ");
			return NE_INDEX_ERROR;
		}



		//	main:
		for(int n=0; n < getLength() ;n++)
		{
			type_index nodecode = _getElement(n);
			const NENode& unit = nodeset[nodecode];
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
	NEObject& NENodeCodeSet::clone() const
	{
		return *(new ThisClass(*this));
	}
	NEType::Type NENodeCodeSet::getType() const
	{
		return NEType::NENODE_CODESET;
	}
	NEIndexedNodeSet& NENodeCodeSet::_getNodeSet()
	{
		NEIndexedNodeSet* nullpointer = 0x00;
		if( ! isManaged())
		{
			KERNAL_ERROR(" : ")
				return *nullpointer;
		}
		return getManager()._getNodeSet();
	}
	const NEIndexedNodeSet& NENodeCodeSet::_getNodeSet() const
	{
		NEIndexedNodeSet* nullpointer = 0x00;
		if( ! isManaged())
		{
			KERNAL_ERROR(" : ")
				return *nullpointer;
		}
		return getManager().getNodeSet();
	}



	type_result NENodeCodeSet::execute()
	{
		//	pre:
		//		타겟팅:
		type_result result = RESULT_SUCCESS;
		NEEnlistableManager& manager = getManager();
		if( ! &manager || manager.getType() != NEType::NENODE_MANAGER)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}
		NENodeManager& noder = static_cast<NENodeManager&>(manager);
		NENodeManager::LocalStack& localstack = noder.getLocalStack();
		//		로컬 스택 조정:
		//			새로운 로컬스택을 넣기전에 이전 값 보존:
		//				왜 이전값을 보존하는가:
		//					모듈셋 안에 모듈셋이 있는 구조라면, 내부 모듈셋을 처리하고 다시
		//					외부 모듈셋으로 돌아왔을때 실제 모듈셋과 로컬스택에 저장된 모듈
		//					셋이 어긋날 수 있기 때문이다.
		NENodeCodeSet& before_stage_nodeset = localstack.getRecentNodeSet();
		localstack._setRecentNodeSet(*this);
		localstack._setRecentResultCode(RESULT_NOTHING);



		//	main:
		//		실행:
		//			로컬 스택 갱신:
		for(int n=0; n < getLength() ;n++)
		{
			NENode& node = getElement(n);
			if( ! node.isEnable()) continue;
			localstack._setRecentNodeSetIndex(n);
			localstack._setRecentNode(node);
			localstack._setRecentNodeRealIndex(_getElement(n));
			type_result result = node.getModuleSet().execute();
			localstack._setRecentResultCode(result);				
#ifdef DEVELOPER			
			//			디버그 출력:
			if(NEResult::hasError(result))
			{
				type_result result_value = localstack.getRecentResultCode();
				KERNAL_ERROR("E100031C4 : 노드셋에서 에러 발생\n노드셋에서 실행한 노드가 에러를 반환했습니다\n프레임 카운트 : %d\t노드인덱스 : %d\n결과코드 : %d\t에러코드 : %d", localstack.getFrameCount(), n, result_value, NEResult::getErrorCode(result_value));
			}
#endif
		}



		//	post:
		//		이전 함수에서 할당된 주소를 다시 복원:
		localstack._setRecentNodeSet(before_stage_nodeset);

		return RESULT_TRUE;
	}

	type_result NENodeCodeSet::_onEnlisted()
	{
		if( ! isManaged()	||
			isEnlisted()	) 
			return RESULT_TYPE_ERROR;



		//	main:
		_setEnlisted(true);

		type_result result = RESULT_SUCCESS;
		for(int n=0; n < getLength() ;n++)
			result |= _onEnlisted(getElement(n));

		return result;
	}

	type_result NENodeCodeSet::_onEnlisted(NENode& node)
	{
		if( ! isManaged()	||
			! isEnlisted()	) 
			return RESULT_TYPE_ERROR;
		if( ! &node) return RESULT_TYPE_ERROR;
		
		return node._onEnlisted();
	}

	NEBinaryFileLoader& NENodeCodeSet::serialize(NEBinaryFileLoader& loader)
	{
		SuperClass::serialize(loader);

		if(isEnlisted())
			_onEnlisted();

		return loader;
	}

	const NENodeCodeSet& NENodeCodeSet::_assign(const NENodeCodeSet& source)
	{
		if(this == &source) return *this;

		create(source.getSize());
		push(source);

		return *this;
	}

	type_result NENodeCodeSet::resize(type_index new_size)
	{		
		/*
			왜 resize를 재정의 하는가:
				NETArray<T, bool, Q>에서 정의한 resize 
				다른 원리로 동작하기 때문이다. 해당 함수에서는 clone
				함수를 사용해서 담아둘 인스턴스를 임시 버퍼에 담아두는
				역할을 수행하고 있는데, 실질적으로 이 코드는 NEIndexedNodeSet
				에서 동작이 불가능한 코드이기 때문이다.
				
			왜 clone을 사용할 수 없는가:
				관련한 내용은 NETEnlistableSet.hpp의 복사생성자 주석을 
				참고하라.

			알고리즘:	ShallowCopy로 효율을 높인다.
				이 방식은 인스턴스를 shallow copy함으로써 효율을 높이는 알고리즘이다.
				InnerType이 OuterType보다 가벼울 경우에만 사용이 가능한 방법이며,
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
		InnerType* buffer = new InnerType[_length];
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

	void NENodeCodeSet::release()
	{
		while(getLength())
			pop();

		SuperClass::release();
	}
}