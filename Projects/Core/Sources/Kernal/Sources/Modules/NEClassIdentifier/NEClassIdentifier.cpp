#include "../NETClass/NETClass.hpp"
#include "NEClassIdentifier.hpp"

namespace NE
{
	NEClassIdentifier::NEClassIdentifier()
		: Super() // let NEIdentifier create bean.
	{
		
	}

	NEClassIdentifier::NEClassIdentifier(const NETString& name, const NETString& author, type_int new_interface_revision, const NETString& new_classname)
		//	if 1st argument's type is booean, superclass accept that it's request 
		//	to be going to wrap it.
		: Super(false, name, author, new_interface_revision), _classname(new_classname)
	{
	
	}

	NEClassIdentifier::NEClassIdentifier(const NEPackage& package, const NETString& class_name)
		// Same as above, this makes NEIdentifier not to create bean
		: Super(false, package), _classname(class_name)
	{
		
	}

	NEClassIdentifier::NEClassIdentifier(const This& rhs)
		: Super(rhs), _classname(rhs._classname)
	{

	}

	NEClassIdentifier::~NEClassIdentifier()
	{

	}

	const NETString& NEClassIdentifier::getClassName() const
	{
		return _classname;
	}

	NETString& NEClassIdentifier::getClassName()
	{
		return _classname;
	}

	void NEClassIdentifier::release()
	{
		_classname.release();
	}

	NEBinaryFileSaver& NEClassIdentifier::serialize(NEBinaryFileSaver& saver) const
	{
		Super::serialize(saver);

		return saver << _classname;
	}

	NEBinaryFileLoader& NEClassIdentifier::serialize(NEBinaryFileLoader& loader)
	{
		Super::serialize(loader);

		return loader >> _classname;
	}

	type_result NEClassIdentifier::isValid() const
	{
		if(_classname.getLength() <= 0) return RESULT_TYPE_WARNING;

		return RESULT_SUCCESS;
	}

	const NEClassIdentifier& NEClassIdentifier::operator=(const This& source)
	{
		if(this == &source) return *this;

		Super::operator=(source);

		_classname = source._classname;

		return *this;
	}

	bool NEClassIdentifier::operator==(const This& source) const
	{
		return	Super::operator==(source)		&&
				_classname == source._classname	;
	}

	bool NEClassIdentifier::operator!=(const This& source) const
	{
		return ! operator==(source);
	}

}