#pragma warning(push)
#pragma warning(disable : 4146)	//	unsigned에 -를 사용함

#include "NEKeyManager.hpp"
#include "define/define.hpp"
#include "../Kernal/Kernal.hpp"
#include "../NEBooleanKey/NEBooleanKey.hpp"
#include "../NECharKey/NECharKey.hpp"
#include "../NEByteKey/NEByteKey.hpp"
#include "../NEUByteKey/NEUByteKey.hpp"
#include "../NEWCharKey/NEWCharKey.hpp"
#include "../NEShortKey/NEShortKey.hpp"
#include "../NEUShortKey/NEUShortKey.hpp"
#include "../NEIntKey/NEIntKey.hpp"
#include "../NEUIntKey/NEUIntKey.hpp"
#include "../NEInt64Key/NEInt64Key.hpp"
#include "../NEFloatKey/NEFloatKey.hpp"
#include "../NEDoubleKey/NEDoubleKey.hpp"
#include "../NEStringKey/NEStringKey.hpp"
#include "../NEWStringKey/NEWStringKey.hpp"
#include "../NEBooleanSetKey/NEBooleanSetKey.hpp"
#include "../NEByteSetKey/NEByteSetKey.hpp"
#include "../NEUByteSetKey/NEUByteSetKey.hpp"
#include "../NEShortSetKey/NEShortSetKey.hpp"
#include "../NEUShortSetKey/NEUShortSetKey.hpp"
#include "../NEIntSetKey/NEIntSetKey.hpp"
#include "../NEUIntSetKey/NEUIntSetKey.hpp"
#include "../NEInt64SetKey/NEInt64SetKey.hpp"
#include "../NEFloatSetKey/NEFloatSetKEy.hpp"
#include "../NEDoubleSetKey/NEDoubleSetKey.hpp"
#include "../NEStringSetKey/NEStringSetKey.hpp"
#include "../NEWStringSetKey/NEWStringSetKey.hpp"
#include "../NENodeSelector/NENodeSelector.hpp"
#include "../NEModuleSelector/NEModuleSelector.hpp"
#include "../NEKeySelector/NEKeySelector.hpp"
#include "../NEModuleCodeSetKey/NEModuleCodeSetKey.hpp"
#include "../NENodeCodeSetKey/NENodeCodeSetKey.hpp"
#include "../NECodeKey/NECodeKey.hpp"
#include "../NECodeSetKey/NECodeSetKey.hpp"

namespace NE
{
	type_bool NEKeyManager::operator==(const This& source) const
	{
		if(this == &source) return true;

		return NEModule::operator==(source);	
	}
	type_bool NEKeyManager::operator!=(const This& source) const
	{
		return ! operator==(source);
	}
// 	const NEKey& NEKeyManager::getKey(NEType::Type type) const
// 	{
// 		for(int n=0; n < _keyset.getLength() ;n++)
// 			if(_keyset[n].getType() == type)
// 				return _keyset[n];
// 
// 		KERNAL_ERROR("주어진 타입에 알맞는 키를 못찾았습니다.\n\t: 요청한 키는 %s(%d)", NEType::getTypeName(type), type);
// 		NEKey* nullpointer = 0x00;
// 		return *nullpointer;
// 	}

	const NEKey NE_DLL &NEKeyManager::getKey(const NEString& type_name) const
	{
		for(int n=0; n < _keyset.getLength() ;n++)
			if(type_name == _keyset[n].getClass().getName())
				return _keyset[n];

		const NEKey* nullpointer = 0x00;
		return *nullpointer;
	}

	type_result NEKeyManager::initialize()
	{
		_keyset.create(33);
		_keyset.push(NEBooleanKey());
		_keyset.push(NECharKey());
		_keyset.push(NEByteKey());
		_keyset.push(NEUByteKey());
		_keyset.push(NEWCharKey());
		_keyset.push(NEShortKey());
		_keyset.push(NEUShortKey());
		_keyset.push(NEIntKey());
		_keyset.push(NEUIntKey());
		_keyset.push(NEInt64Key());
		_keyset.push(NEFloatKey());
		_keyset.push(NEDoubleKey());
		_keyset.push(NEStringKey());
		_keyset.push(NEWStringKey());
		_keyset.push(NEBooleanSetKey());
		_keyset.push(NEByteSetKey());
		_keyset.push(NEUByteSetKey());
		_keyset.push(NEShortSetKey());
		_keyset.push(NEUShortSetKey());
		_keyset.push(NEIntSetKey());
		_keyset.push(NEUIntSetKey());
		_keyset.push(NEInt64SetKey());
		_keyset.push(NEFloatSetKey());
		_keyset.push(NEDoubleSetKey());
		_keyset.push(NEStringSetKey());
		_keyset.push(NEWStringSetKey());
		_keyset.push(NEModuleCodeSetKey());
		_keyset.push(NENodeCodeSetKey());
		_keyset.push(NENodeSelector());
		_keyset.push(NEModuleSelector());
		_keyset.push(NEKeySelector());		
		_keyset.push(NECodeKey());
		_keyset.push(NECodeSetKey());	

		return RESULT_SUCCESS;
	}
	const NEExportable::ModuleHeader& NEKeyManager::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_SUCCESS)
		{
			_header.getName() = _T(_NAME);
			_header.getDeveloper() = _T(_DEVELOPER);;
			_header.setRevision(_REVISION);
			_header.getReleaseDate() = _T(_DATE);
			_header.getVersion()  = _T(_VERSION);
			_header.getComment() = _T(_COMMENT);
			//_header.setMaxErrorCodeCount(NEKeyManager::END_OF_ERROR_CODE - 1);
		}

		return _header;
	}
	type_result NEKeyManager::execute()
	{
		return RESULT_SUCCESS;
	}
	const NEKeySet NE_DLL &NEKeyManager::getKeySet() const
	{
		return _keyset;
	}
}
#pragma warning(pop)