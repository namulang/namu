
#include "NEBinderBase.hpp"
//#include "../NEIntanceManager/NEInstanceManager.hpp"
#include "../NENodeSelector/NENodeSelector.hpp"

namespace NE
{
	NEBinderBase::NEBinderBase()
		: Super()
	{
		_release();
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

	type_bool NEBinderBase::operator==(const This& source) const
	{
		if(Super::operator!=(source)) return false;
		if(_binded_id != source._binded_id) return false;

		return true;
	}

	type_bool NEBinderBase::operator!=(const This& source) const
	{
		return ! operator==(source);
	}

	type_bool NEBinderBase::isBinded() const
	{
		//	_id cannot be 0.
		return _binded_id > NE_HAS_NO_ID;
	}

	void NEBinderBase::release()
	{
		Super::release();

		_release();
	}

	NEBinaryFileLoader& NEBinderBase::serialize(NEBinaryFileLoader& loader)
	{
		Super::serialize(loader);

		return loader >> _binded_id;
	}

	NEBinaryFileSaver& NEBinderBase::serialize(NEBinaryFileSaver& saver) const
	{
		Super::serialize(saver);

		return saver << _binded_id;
	}

	type_result NEBinderBase::isValid() const
	{
		type_result result = Super::isValid();
		if(NEResult::hasError(result)) return result;
		if(_binded_id <= NE_HAS_NO_ID) return RESULT_TYPE_ERROR;

		return RESULT_SUCCESS;
	}

	const NEBinderBase& NEBinderBase::_assign(const This& source)
	{
		if(this == &source) return *this;

		_binded_id = source._binded_id;

		return *this;
	}

	void NEBinderBase::_release()
	{
		unbind();
	}

	type_id NEBinderBase::getBindedId() const
	{
		return _binded_id;
	}

	type_result NEBinderBase::unbind()
	{
		_binded_id = NE_HAS_NO_ID;

		return RESULT_SUCCESS;
	}

	NEUnit& NEBinderBase::get() 
	{
		// TODO:
		return 
	}

	const NEUnit& NEBinderBase::get() const
	{
		//	TODO:
		return 
	}

	type_result NEBinderBase::_bind(const NEUnit& target)
	{
		// TODO:
		return RESULT_SUCCESS;
	}
}