#include "NEKeyCodeSet.hpp"

#include "../Kernal/Kernal.hpp"
#include "../NEIndexedKeySet/NEIndexedKeySet.hpp"
#include "../NEModuleCodeSetKey/NEModuleCodeSetKey.hpp"
#include "../NENodeCodeSetKey/NENodeCodeSetKey.hpp"

namespace NE
{
	NEKeyCodeSet::NEKeyCodeSet()
		: SuperClass()
	{
		
	}
	NEKeyCodeSet::NEKeyCodeSet(type_index size)
		: SuperClass(size)
	{
		
	}
	NEKeyCodeSet::NEKeyCodeSet(const NEKeyCodeSet& source)
		: SuperClass(source)
	{
		_assign(source);	//	이제, NENodeCodeSet::insert가 내부적으로 호출된다.
	}

	NEKeyCodeSet::~NEKeyCodeSet()
	{
		release();	//	여기서 해제 하지 않으면 상위클래스 소멸자에서 상위?클래스 release를 호출해버릴 것이다.
	}

	const NEKeyCodeSet& NEKeyCodeSet::operator+=(const NEKeyCodeSet& source)
	{
		if(this == &source)
		{
			NEKeyCodeSet copyied(*this);
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

	NEKeyCodeSet NEKeyCodeSet::operator+(const NEKeyCodeSet& source) const
	{
		ThisClass buffer(getSize() + source.getSize());

		buffer.push(*this);
		buffer.push(source);

		return buffer;
	}

	type_index NEKeyCodeSet::insert(type_index index, const NEKey& source)
	{
		//	pre:
		NEIndexedKeySet& keyset = _getKeySet();
		if(! &keyset)
		{
			KERNAL_ERROR(" : ")
			return NE_INDEX_ERROR;
		}



		//	main:
		type_index keycode = keyset.pushFront(source);
		if(keycode == NE_INDEX_ERROR)
		{
			KERNAL_ERROR(" : ")
			return NE_INDEX_ERROR;
		}

		if( NEResult::hasError(_insert(index, keycode)) )
		{
			KERNAL_ERROR(" : ");
			return NE_INDEX_ERROR;
		}
		//	Owner 설정:
		keyset[keycode]._owner = this;

		if(isEnlisted())
		{
			NEKey& key = getElement(index);
			if( NEResult::hasError(_onEnlisted(key)) )
			{
				KERNAL_ERROR(" : ");
				return NE_INDEX_ERROR;
			}
		}		

		return index;
	}
	type_index NEKeyCodeSet::remove(type_index index)
	{
		//	pre:
		NEIndexedKeySet& keyset = _getKeySet();
		if(! &keyset)
		{
			KERNAL_ERROR(" : ")
			return NE_INDEX_ERROR;
		}



		//	main:
		type_index keycode = keyset.remove(_getElement(index));
		if(keycode == NE_INDEX_ERROR)
		{
			KERNAL_ERROR(" : ")
			return NE_INDEX_ERROR;
		}

		return _remove(index);
	}

	NEKey& NEKeyCodeSet::getElement(type_index index)
	{
		//	pre:
		NEKey* nullpointer = 0x00;
		NEIndexedKeySet& keyset = _getKeySet();
		if(! &keyset)
		{
			KERNAL_ERROR(" : ")
			return *nullpointer;
		}



		//	main:
		type_index& keycode = _getElement(index);
		if( ! &keycode)
		{
			KERNAL_ERROR(" : 주어진 인덱스가 범위를 벗어난 잘못된 참조입니다.");

			return *nullpointer;
		}
		
		return keyset[keycode];
	}
	const NEKey& NEKeyCodeSet::getElement(type_index index) const
	{
		//	pre:
		NEKey* nullpointer = 0x00;
		const NEIndexedKeySet& keyset = _getKeySet();
		if(! &keyset)
		{
			KERNAL_ERROR(" : ")
			return *nullpointer;
		}



		//	main:
		const type_code& keycode = _getElement(index);
		if( ! &keycode)
		{
			KERNAL_ERROR(" : 주어진 인덱스가 범위를 벗어난 잘못된 참조입니다.");

			return *nullpointer;
		}

		return keyset[keycode];
	}
	type_result NEKeyCodeSet::setElement(type_index index, const NEKey& source)
	{
		//	pre:
		NEIndexedKeySet& keyset = _getKeySet();
		if(! &keyset)
		{
			KERNAL_ERROR(" : ")
			return RESULT_TYPE_ERROR;
		}



		//	main:
		type_index& keycode = _getElement(index);
		if( ! &keycode)
		{
			KERNAL_ERROR(" : 주어진 인덱스가 범위를 벗어난 잘못된 참조입니다.");

			return RESULT_TYPE_ERROR;
		}

		return keyset.setElement(keycode, source);
	}
	type_index NEKeyCodeSet::find(const NEKey& source) const
	{
		//	pre:
		const NEIndexedKeySet& keyset = _getKeySet();
		if(! &keyset)
		{
			KERNAL_ERROR(" : ");
			return NE_INDEX_ERROR;
		}



		//	main:
		for(int n=0; n < getLength() ;n++)
		{
			type_index keycode = _getElement(n);
			const NEKey& unit = keyset[keycode];
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
	NEObject& NEKeyCodeSet::clone() const
	{
		return *(new ThisClass(*this));
	}
	NEType::Type NEKeyCodeSet::getType() const
	{
		return NEType::NEKEY_CODESET;
	}
	NEIndexedKeySet& NEKeyCodeSet::_getKeySet()
	{
		NEIndexedKeySet* nullpointer = 0x00;
		if( ! isManaged())
		{
			KERNAL_ERROR(" : ")
			return *nullpointer;
		}
		return getManager()._getKeySet();
	}
	const NEIndexedKeySet& NEKeyCodeSet::_getKeySet() const
	{
		NEIndexedKeySet* nullpointer = 0x00;
		if( ! isManaged())
		{
			KERNAL_ERROR(" : ")
			return *nullpointer;
		}
		return getManager().getKeySet();
	}

	type_result NEKeyCodeSet::_onEnlisted(NEKey& key)
	{
		if( ! &key)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}
		NEType::Type type = key.getType();

		switch(type)
		{
		case NEType::NENODE_CODESET_KEY:
			{
				NENodeCodeSetKey& casted = static_cast<NENodeCodeSetKey&>(key);
				NENodeCodeSet& node_codeset = casted.getValue();

				return node_codeset._onEnlisted();
			}
			break;

		default:
			return RESULT_SUCCESS;
		}
	}

	type_result NEKeyCodeSet::_onEnlisted()
	{
		_setEnlisted(true);

		type_result result = RESULT_SUCCESS;
		for(int n=0; n < getLength() ;n++)
		{
			NEKey& key = getElement(n);
			if( ! &key)
				continue;

			result = result | _onEnlisted(key);
		}

		return result;
	}

	const NEKeyCodeSet& NEKeyCodeSet::_assign(const NEKeyCodeSet& source)
	{
		if(this == &source) return *this;

		create(source.getSize());
		push(source);

		return *this;
	}

	type_result NEKeyCodeSet::resize(type_index new_size)
	{
		/*
			왜 resize를 재정의 하는가:
				NEArrayTemplate<T, bool, Q, Type>에서 정의한 resize 
				다른 원리로 동작하기 때문이다. 해당 함수에서는 clone
				함수를 사용해서 담아둘 인스턴스를 임시 버퍼에 담아두는
				역할을 수행하고 있는데, 실질적으로 이 코드는 NEIndexedNodeSet
				에서 동작이 불가능한 코드이기 때문이다.
				
			왜 clone을 사용할 수 없는가:
				관련한 내용은 NEEnlistableSetTemplate.hpp의 복사생성자 주석을 
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

	void NEKeyCodeSet::release()
	{
		while(getLength())
			pop();

		SuperClass::release();
	}
}