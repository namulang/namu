#include "NEBlockedNodeSet.hpp"
#include "define/define.hpp"

namespace NE
{
	type_result NE_DLL NEBlockedNodeSet::initialize()
	{
		getKeySet().create(_KEY_NUMBER);
		getKeySet().push(NENodeCodeSetKey());
		
		return RESULT_SUCCESS;
	}

	type_result NE_DLL NEBlockedNodeSet::execute()
	{
		if(	getKeySet().getLength() <= 0							||
			getKeySet()[0].getType() != NEType::NENODE_CODESET_KEY)
		{
			ALERT_ERROR(" : 0번키는 노드셋키가 아닙니다. 키셋이 손상되었습니다.");
			return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION;
		}
		NENodeCodeSet& actionset = (static_cast<NENodeCodeSetKey&>(	getKeySet()[0]	)).getValue();
						
		

		//	main:
		return actionset.execute();
	}

	NEObject NE_DLL &NEBlockedNodeSet::clone() const
	{
		return *(new NEBlockedNodeSet(*this));
	}

	const NEExportable::ModuleHeader NE_DLL &NEBlockedNodeSet::getHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T( _NAME );
			_header.getDeveloper() = _T( _DEVELOPER );
			_header.setRevision(_REVISION);
			_header.getComment() = _T( _COMMENT );
			_header.getVersion()  = _T( _VERSION );
			_header.getReleaseDate() = _T( _DATE );
			_header.getModuleDependencies().create(_DEPENDENCIES_COUNT);
			_header.setMaxErrorCodeCount(1);
		}

		return _header;
	}
}
