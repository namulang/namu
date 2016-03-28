
#include "NEBinderBase.hpp"
#include "../NEEnlistableManager/NEEnlistableManager.hpp"
#include "../NENodeSelector/NENodeSelector.hpp"

namespace NE
{
	NEBinderBase::NEBinderBase()
		: Super()
	{
		_release();
		//_manager_type = NEType::NENODE_MANAGER;
	}

	NEBinderBase::NEBinderBase(const This& source)
		: Super(source)
	{
		_assign(source);
	}

	NEBinderBase::~NEBinderBase()
	{

	}

	const NEBinderBase& NEBinderBase::operator=(const This& source)
	{
		Super::operator=(source);

		return _assign(source);
	}

	bool NEBinderBase::operator==(const This& source) const
	{
		if(Super::operator!=(source)) return false;
		if(_real_index != source._real_index) return false;
		if(_comparing_id != source._comparing_id) return false;
		//if(_manager_type != source._manager_type) return false;

		return true;
	}

	bool NEBinderBase::operator!=(const This& source) const
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
		Super::release();

		_release();
	}

	NEBinaryFileLoader& NEBinderBase::serialize(NEBinaryFileLoader& loader)
	{
		Super::serialize(loader);

		return loader >> _real_index >> _comparing_id;// >> _manager_type;
	}

	NEBinaryFileSaver& NEBinderBase::serialize(NEBinaryFileSaver& saver) const
	{
		Super::serialize(saver);

		return saver << _real_index << _comparing_id;// << _manager_type;
	}

	type_result NEBinderBase::isValid() const
	{
		using namespace NEType;
		if(_real_index <= NE_INDEX_ERROR) return RESULT_TYPE_ERROR;
		if(_comparing_id <= NE_HAS_NO_ID) return RESULT_TYPE_ERROR;
// 		if( _manager_type != UNDEFINED								&& 
// 			! isValidHierachy(NEENLISTABLE_MANAGER, _manager_type)	)	//	UNDEFINED나 MANAGER의 하위클래만 통과.
// 			return RESULT_TYPE_ERROR;

		return RESULT_SUCCESS;
	}

	const NEBinderBase& NEBinderBase::_assign(const This& source)
	{
		if(this == &source) return *this;

		_real_index = source._real_index;
		_comparing_id = source._comparing_id;
		//_manager_type = source._manager_type;

		return *this;
	}

	void NEBinderBase::_release()
	{
		_real_index = NE_INDEX_ERROR;
		_comparing_id = NE_INDEX_ERROR;
		//_manager_type = NEType::UNDEFINED;
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
		NEEnlistableManager* nullptr = 0x00;
		return *nullptr; //NENodeSelector::_interface(_manager_type);
	}

	const NEEnlistableManager& NEBinderBase::getManager() const
	{
		const NEEnlistableManager* nullptr = 0x00;
		
		return *nullptr;//NENodeSelector::_interface(_manager_type);
	}

	type_result NEBinderBase::unbind()
	{
		_real_index = NE_INDEX_ERROR;
		_comparing_id = NE_INDEX_ERROR;

		return RESULT_SUCCESS;
	}
}