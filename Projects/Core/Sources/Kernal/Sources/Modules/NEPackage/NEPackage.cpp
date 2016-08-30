#include "NEPackage.hpp"

namespace NE
{
	NEPackage::NEPackage()
		: Super(), _instance(0), _entrypoint(0)
	{

	}

	NEPackage::NEPackage(const This& rhs)
		: Super(rhs)
	{
		_assign(rhs);
	}

	NEPackage& NEPackage::_assign(const This& rhs)
	{
		_path = rhs._path;
		_instance = rhs._instance;
		_entrypoint = rhs._entrypoint;
		_components = rhs._components;
		_id = rhs._id;

		return *this;
	}

	void NEPackage::_release()
	{
		_path.release();
		_instance = 0;
		_entrypoint = 0;
		_components.release();
		_id = NE_HAS_NO_ID;
	}

	NEPackage::~NEPackage()
	{

	}

	const NEPackage& NEPackage::operator=(const This& source)
	{
		if(this == &source) return *this;

		Super::operator=(source);

		return _assign(source);
	}

	type_bool NEPackage::operator!=(const This& source) const
	{
		return ! operator==(source);
	}

	type_bool NEPackage::operator==(const This& source) const
	{
		return	Super::operator==(source)			&&
			_path == source._path				&&
			_instance == source._instance		&&
			_entrypoint == source._entrypoint	&&
			_components == source._components	&&
			_id == source._id					;
	}

	NETString& NEPackage::getPath()
	{
		return _path;
	}

	const NETString& NEPackage::getPath() const
	{
		return _path;
	}

	HINSTANCE& NEPackage::getInstance()
	{
		return _instance;
	}

	const HINSTANCE& NEPackage::getInstance() const
	{
		return _instance;
	}

	EntryPoint& NEPackage::getEntryPoint()
	{
		return _entrypoint;
	}

	const EntryPoint& NEPackage::getEntryPoint() const
	{
		return _entrypoint;
	}

	const NEClassBaseList& NEPackage::getComponents() const
	{
		return _components;
	}

	NEClassBaseList& NEPackage::getComponents()
	{
		return _components;
	}

	type_id NEPackage::getId() const
	{
		return _id;
	}

	type_result NEPackage::_setId(type_id new_id)
	{
		_id = new_id;

		return RESULT_SUCCESS;
	}

	type_bool NEPackage::isLoaded() const
	{
		return _entrypoint != 0;
	}

	void NEPackage::release()
	{
		Super::release();

		_release();
	}

	//	You can't serialize Package class:
	//		It's dependent to system. it changes at every bootings. So, even if
	//		you can save it, but you can't restore it to original data.
	NEBinaryFileSaver& NEPackage::serialize(NEBinaryFileSaver& saver) const
	{
		return saver;
	}
	NEBinaryFileLoader& NEPackage::serialize(NEBinaryFileLoader& loader)
	{
		return loader;
	}

	type_result NEPackage::isValid() const
	{
		type_result result = Super::isValid();
		if(NEResult::hasError(result)) return result;
		if(isLoaded()) return RESULT_TYPE_WARNING;
		if(	_path.getLength() <= 0	||
			_path == _T("")			)	return RESULT_TYPE_WARNING;

		return RESULT_SUCCESS;
	}
}