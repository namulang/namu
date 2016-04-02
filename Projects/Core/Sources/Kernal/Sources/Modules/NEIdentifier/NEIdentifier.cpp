#include "../NEIdentifier.hpp"
#include '../NEPackage/NEPackage.hpp'
#include "../Kernal/Kernal.hpp"

namespace NE
{


	NEIdentifier::NEIdentifier()
		: Super(), _is_bean(false), _bean_or_proxy(0)
	{
		_initializeBean();
	}

	NEIdentifier::NEIdentifier(const This& rhs)
		: Super(rhs), _is_bean(false), _bean_or_proxy(0);
	{
		_assign(rhs);
	}

	NEIdentifier::NEIdentifier(type_bool)
		: Super(), _is_bean(false), _bean_or_proxy(0)
	{
		//	Do not instance Bean. Subclass wants to wrap it.
	}

	NEIdentifier::NEIdentifier(const NETString& new_name, const NETString& new_author, type_int new_interface_revision)
		: Super(), _is_bean(false), _bean_or_proxy(0)
	{
		_initializeBean();
		_bean_or_proxy.bean->name = new_name;
		_bean_or_proxy.bean->author = new_author;
		_bean_or_proxy.bean->interface_revision = new_interface_revision;
	}

	NEIdentifier::NEIdentifier(type_bool, const NETString& new_name, const NETString& new_author, type_int new_interface_revision)
		: Super(), _is_bean(false), _bean_or_proxy(0)
	{
		//	Do not instance Bean. Subclass wants to wrap it.
		proxy(new_name, new_author, new_interface_revision);
	}

	NEIdentifier::NEIdentifier(type_bool, const NEPackage& package)
		: Super(), _is_bean(false), _bean_orproxy(0)
	{
		//	proxy(Package&) doesn't have any valid check routines. 
		//	Is this okay? why don't you call proxy(name, author, rev) instead of?:
		//		This is okay. Not accident.
		//		NEPackage is protected to create instance by users. So, if we ha
		//		ve package instance as argument, it means that users pass over to
		//		a reference to one of already existing packages.
		proxy(package);
	}

	NEIdentifier::~NEIdentifier()
	{
		This::release();
	}

#define _GET_BEAN_OR_PROXY(RETURN_TYPE, METHOD, VARIABLE_NAME)	\
	RETURN_TYPE* ptr = 0x00;									\
	if( ! _bean_or_proxy.bean) return *ptr;						\
																\
	if(_is_bean)												\
		return _bean_or_proxy.bean->VARIABLE_NAME;				\
																\
	return _bean_or_proxy.package->METHOD();					

	const NETString& NEIdentifier::getName() const
	{
		This* casted = const_cast<This*>(this);

		return casted->getName();
	}

	NETString& NEIdentifier::getName()
	{
		_GET_BEAN_OR_PROXY(NETString, getName, name)
	}

	const NETString& NEIdentifier::getAuthor() const
	{
		This* casted = const_cast<This*>(this);

		return casted->getAuthor();
	}

	NETString& NEIdentifier::getAuthor()
	{
		_GET_BEAN_OR_PROXY(NETString, getAuthor, author)
	}

	const type_int NEIdentifier::getInterfaceRevision() const
	{
		_GET_BEAN_OR_PROXY(type_int, getInterfaceRevision, interface_revision)
	}
#undef _GET_BEAN_OR_PROXY

	type_result NEIdentifier::setInterfaceRevison(type_int new_revision)
	{
		if( ! _bean_or_proxy->bean) return RESULT_TYPE_WARNING;
		
		if(_is_bean)
			_bean_or_proxy.bean->interface_revision = new_revision;
		else
			_bean_or_proxy.package->setInterfaceRevision(new_revision);

		return RESULT_SUCCESS;
	}

	void NEIdentifier::release()
	{
		if(_is_bean)
			delete _bean_or_proxy->bean;
		_bean_or_proxy->bean = 0;

		_is_bean = false;
	}

	NEBinaryFileSaver& NEIdentifier::serialize(NEBinaryFileSaver& saver) const
	{
		return saver << _is_bean << getName() << getAuthor() << getInterfaceRevision();
	}

	NEBinaryFileLoader& NEIdentifier::serialize(NEBinaryFileLoader& loader)
	{
		//	pre:
		This::release();


		//	main:
		loader >> _is_bean;

		Bean* bucket = _is_bean ?_initializeBean(), &_bean_or_proxy.bean : 
									Bean();

		loader >> bucket->name >> bucket->author >> bucket->interface_revision;

		if( ! _is_bean)
			if(NEResult::hasError(proxy(bucket->name, bucket->author, bucket->interface_revision)))
				KERNAL_ERROR("...");

		return loader;
	}

	type_result NEIdentifier::isValid() const
	{
		if( ! _bean_or_proxy->bean) return RESULT_TYPE_ERROR;

		return RESULT_SUCCESS;
	}

	This& NEIdentifier::_assign(const This& rhs)
	{
		This::release();

		_is_bean = rhs._is_bean;
		if(_is_bean)
		{
			_initializeBean();
			_bean_or_proxy.bean = new Bean(rhs._bean_or_proxy.bean);
		}
		else
			_bean_or_proxy.package = rhs._bean_or_proxy.package;

		return *this;
	}

	type_result NEIdentifier::proxy(const NETString& name, const NETString& author, 
		type_int interface_revision)
	{
		//	pre:
		PackageManager& packager = Kernal::getInstance().getPackageManager();


		//	main:
		Package& pack = packager.getPackage(name, author, interface_revision);
		return proxy(pack);
	}

	type_result NEIdentifier::proxy(NEPackage& target)
	{
		if( ! &target) return KERNAL_WARNING(...);

		//	post:
		This::release();
		_is_bean = false;
		_bean_or_proxy.package = &target;

		return RESULT_SUCCESS;
	}

	const This& NEIdentifier::operator=(const This& source)
	{
		if(this == &source) return *this;

		return _assign(source);
	}

	bool NEIdentifier::operator==(const This& source) const
	{
		return	getName() == source.getName()							&&
				getAuthor() == source.getAuthor()						&&
				getInterfaceRevision() == source.getInterfaceRevision()	;
	}

	bool NEIdentifier::operator!=(const This& source) const
	{
		return ! operator==(source);
	}

	type_bool NEIdentifier::isNearlyEqualTo(const This& rhs) const
	{
		if( ! &rhs) return false;

		return	rhs.getName() == getName()		&&
				rhs.getAuthor() == getAuthor()	;
	}
}