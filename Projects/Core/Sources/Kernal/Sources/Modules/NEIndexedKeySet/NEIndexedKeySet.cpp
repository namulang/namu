#include "NEIndexedKeySet.hpp"
#include "../Kernal/Kernal.hpp"

namespace NE
{
	type_id NEIndexedKeySet::_last_generated_id = 0;

	NEIndexedKeySet::NEIndexedKeySet(NEEnlistableManager& manager)
		: Super(manager)
	{

	}

	NEIndexedKeySet::NEIndexedKeySet(type_count size)
		: Super(size)
	{

	}

	NEIndexedKeySet::NEIndexedKeySet(const This& source)
		: Super(source)
	{

	}

	NEIndexedKeySet::~NEIndexedKeySet()
	{

	}

	const NEIndexedKeySet& NEIndexedKeySet::operator+=(const This& source)
	{
		Super::operator+=(source);

		return *this;
	}

	NEIndexedKeySet NEIndexedKeySet::operator+(const This& source) const
	{
		This buffer(getSize() + source.getSize());

		buffer.push(*this);
		buffer.push(source);

		return buffer;
	}

	type_id NEIndexedKeySet::peekLastGeneratedId() const
	{
		return _last_generated_id;
	}

	type_id NEIndexedKeySet::_generateId()
	{
		_last_generated_id++;
		if(_last_generated_id <= 0)
			KERNAL_ERROR(" : ");

		return _last_generated_id;
	}

	type_index NEIndexedKeySet::insert(type_index index, const NEKey* const source)
	{
		if( ! source)
		{
			KERNAL_ERROR(" : ");
			return NE_INDEX_ERROR;
		}
		if(_occupiedset[index])
		{
			type_result result = setElement(index, source);
			if(NEResult::hasError(result))
			{
				KERNAL_ERROR(" : ");
				return result;
			}
		}
		
		
		NEEnlistableManager& push = NEGlobalManagerOffer::getGlobalManager();
		NEGlobalManagerOffer::_setGlobalManager(getManager());

		type_index inputed_index = Super::insert(index, source);
		//		아이디 할당:
		//			타겟팅:
		NEKey& key = getElement(inputed_index);
		if(&key)
			key._id = _generateId();

		NEGlobalManagerOffer::_setGlobalManager(push);

		getElement(inputed_index)._id = _generateId();

		return inputed_index;
	}

	type_result NEIndexedKeySet::setElement(type_index index, const NEKey* const source)
	{
		if( ! source)
		{
			KERNAL_ERROR(" : ")
			return RESULT_TYPE_ERROR;
		}



		NEKey* const_casted = const_cast<NEKey*>(source);

		type_id original_id = const_casted->getId();
		const_casted->_id = _generateId();

		NEEnlistableManager& push = NEGlobalManagerOffer::getGlobalManager();
		NEGlobalManagerOffer::_setGlobalManager(getManager());

		type_result result = Super::setElement(index, source);

		NEGlobalManagerOffer::_setGlobalManager(push);

		const_casted->_id = original_id;

		return result;
	}

	NEBinaryFileSaver& NEIndexedKeySet::serialize(NEBinaryFileSaver& saver) const
	{
		Super::serialize(saver);



		//	main:
		//		실제 데이터 저장:
		for(type_index n=0; n < getSize() ;n++)
		{	
			const NEKey& key = getElement(n);
			if( ! &key)
				continue;
			//		헤더 추출
			/*NEType::Type type = key.getType();*/
			//		헤더 저장:	타입코드로, load시 어떤인스턴스를 생성해야하는가에 대한 정보를 남긴다
			/*saver << type; */
			//		실제 데이터 저정:	NEModule::serialize()를 호출한다.
			saver << key;
		}

		return saver << _last_generated_id;
	}

	NEBinaryFileLoader& NEIndexedKeySet::serialize(NEBinaryFileLoader& loader)
	{
		NEKeyManager& keyer = Kernal::getInstance().getKeyManager();		
		Super::serialize(loader);



		//	main:
		//		길이 정보 초기화:	push를 사용하기 위해서
		_length = 0;
		//		Occupied 탐색 인덱스 초기화:
		//			occupiedSet에서 index로부터 순서대로 올림차순으로 검색한다.
		//			가장 가까운 것중에 OccupiedSet[index] == true인 것이 모듈을 추가해야하는 
		//			부분이 된다.
		type_index occupied_index = -1;
		for(int n=0; n < getSize() ;n++)
		{
			if( ! _occupiedset[n])
				continue;

			/*NEType::Type type = NEType::UNDEFINED;
			loader >> type;*/

			const NEKey& source_key = keyer.getKey(type);
			if( ! &source_key)
			{
				KERNAL_ERROR(" : ")
				continue;
			}

			//	키 삽입:
			//		모듈 삽입을 위해서 소유권을 박탈:
			_occupiedset[n] = false;
			//		삽입:
			/*
				내부에서 NodeManager::KeySet에 인스턴스를 복제하여 
				추가하고, 인덱스를 _getElement한다.
				Length는 이미 0이므로 안심하고 push 가능.
			*/
			type_index index = insert(n, source_key);
			NEKey& unit = getElement(index);
			if( ! &unit)
			{
				KERNAL_ERROR(" : ");
				continue;
			}

			loader >> unit;
		}



		return loader >> _last_generated_id;
	}

	type_result NEIndexedKeySet::_onEnlisted()
	{
		return RESULT_SUCCESS;
	}

	type_result NEIndexedKeySet::resize(type_index new_size)
	{
		NEEnlistableManager& push = NEGlobalManagerOffer::getGlobalManager();
		NEGlobalManagerOffer::_setGlobalManager(getManager());

		type_result result = Super::resize(new_size);

		NEGlobalManagerOffer::_setGlobalManager(push);
		return result;
	}
}