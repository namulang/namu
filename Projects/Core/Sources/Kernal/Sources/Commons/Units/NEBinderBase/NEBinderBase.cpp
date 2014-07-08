#include "NEBinderBase.hpp"
#include "../../../Modules/NEEnlistableManager/NEEnlistableManager.hpp"
#include "../../../Modules/NENodeSelector/NENodeSelector.hpp"

namespace NE
{
	NEBinderBase::NEBinderBase()
		: SuperClass()
	{
		_release();
		_manager_type = NEType::NENODE_MANAGER;
	}

	NEBinderBase::NEBinderBase(const ThisClass& source)
		: SuperClass(source)
	{
		_assign(source);
	}

	NEBinderBase::~NEBinderBase()
	{

	}

	const NEBinderBase& NEBinderBase::operator=(const ThisClass& source)
	{
		return _assign(source);
	}

	bool NEBinderBase::operator==(const ThisClass& source) const
	{
		if(_real_index != source._real_index) return false;
		if(_comparing_id != source._comparing_id) return false;
		if(_manager_type != source._manager_type) return false;

		return true;
	}

	bool NEBinderBase::operator!=(const ThisClass& source) const
	{
		return ! operator==(source);
	}

	bool NEBinderBase::isBinded() const
	{
		if(	_real_index <= NE_INDEX_ERROR	||
			_comparing_id <= NE_HAS_NO_ID	)
			return false;

		return true;
	}

	void NEBinderBase::release()
	{
		_release();
	}

	NEBinaryFileLoader& NEBinderBase::serialize(NEBinaryFileLoader& loader)
	{
		return loader >> _real_index >> _comparing_id >> _manager_type;
	}

	NEBinaryFileSaver& NEBinderBase::serialize(NEBinaryFileSaver& saver) const
	{
		return saver << _real_index << _comparing_id << _manager_type;
	}

	type_result NEBinderBase::isValid() const
	{
		using namespace NEType;
		if(_real_index <= NE_INDEX_ERROR) return RESULT_TYPE_ERROR;
		if(_comparing_id <= NE_HAS_NO_ID) return RESULT_TYPE_ERROR;
		if( _manager_type != UNDEFINED								&& 
			! isValidHierachy(NEENLISTABLE_MANAGER, _manager_type)	)	//	UNDEFINED나 MANAGER의 하위클래만 통과.
			return RESULT_TYPE_ERROR;

		return RESULT_SUCCESS;
	}

	NEObject& NEBinderBase::clone() const
	{
		return *(new NEBinderBase(*this));
	}

	NEType::Type NEBinderBase::getType() const
	{
		return NEType::NEBINDER_BASE;
	}

	const NEBinderBase& NEBinderBase::_assign(const ThisClass& source)
	{
		if(this == &source) return *this;

		_real_index = source._real_index;
		_comparing_id = source._comparing_id;
		_manager_type = source._manager_type;

		return *this;
	}

	void NEBinderBase::_release()
	{
		_real_index = NE_INDEX_ERROR;
		_comparing_id = NE_INDEX_ERROR;
		_manager_type = NEType::UNDEFINED;
	}

	type_index NEBinderBase::getRealIndex() const
	{
		return _real_index;
	}

	type_id NEBinderBase::getComparingId() const
	{
		return _comparing_id;
	}

	NEEnlistableManager& NEBinderBase::getManager()
	{
		return NENodeSelector::_interface(_manager_type);
	}

	const NEEnlistableManager& NEBinderBase::getManager() const
	{
		return NENodeSelector::_interface(_manager_type);
	}
}