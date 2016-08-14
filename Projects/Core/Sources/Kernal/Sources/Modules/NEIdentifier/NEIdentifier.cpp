#include "../NETClass/NETClass.hpp"
#include "../NEIdentifier.hpp"
#include '../NEPackage/NEPackage.hpp'
#include "../Kernal/Kernal.hpp"

namespace NE
{
	NE_DEFINE_CLASS_ONLY(NEIdentifier)

	NEIdentifier::NEIdentifier()
		: Super()
	{
		
	}

	NEIdentifier::NEIdentifier(const This& rhs)
		: Super(rhs)
	{
		_assign(rhs);
	}

	NEIdentifier::NEIdentifier(const NETString& new_name, const NETString& new_author, type_count new_revision_count, type_count new_version_count)
		: Super(), _name(new_name), _author(new_author), _revision_count(new_revision_count), _version_count(new_version_count)
	{
		
	}			

	const NETString& NEIdentifier::getName() const
	{
		return _name;
	}

	NETString& NEIdentifier::getName()
	{
		return _name;
	}

	const NETString& NEIdentifier::getAuthor() const
	{
		return _author;
	}

	NETString& NEIdentifier::getAuthor()
	{
		return _author;
	}

	type_count NEIdentifier::getRevisionCount() const
	{
		return _revision_count;
	}

	type_result NEIdentifier::setRevisionCount(type_count new_revision_count)
	{
		return _revision_count;
	}

	type_count NEIdentifier::getVersionCount() const
	{
		return _version_count;
	}

	type_result NEIdentifier::setVersionCount(type_count new_version_count)
	{
		return _version_count;
	}

	void NEIdentifier::release()
	{
		_release();
	}

	void NEIdentifier::_release()
	{
		_name.release();
		_author.release();
		_version_count = _revision_count = NE_DEFAULT;
	}

	NEBinaryFileSaver& NEIdentifier::serialize(NEBinaryFileSaver& saver) const
	{
		return saver << _name << _author << _revision_count << _version_count;
	}

	NEBinaryFileLoader& NEIdentifier::serialize(NEBinaryFileLoader& loader)
	{
		return loader >> _name >> _author >> _revision_count >> _version_count;
	}

	type_result NEIdentifier::isValid() const
	{
		NETString& queue[2] = {_name, _author};
		for(int n=0; n < 2 ;n++)
			if( NEResult::hasError(queue[n].isValid())	|| 
				! _name.getLength()						||
				_name == _T("")							) 
				return RESULT_TYPE_ERROR;

		if(_revision_count < 0 || _version_count < 0) return RESULT_TYPE_WARNING;

		return RESULT_SUCCESS;
	}

	NEIdentifier& NEIdentifier::_assign(const This& rhs)
	{
		if(this == &rhs) return *this;

		_release();

		_name = rhs._name;
		_author = rhs._author;
		_revision_count = rhs._revision_count;
		_version_count = rhs._version_count;
		
		return *this;
	}

	const This& NEIdentifier::operator=(const This& source)
	{
		if(this == &source) return *this;

		Super::operator=(source);

		return _assign(source);
	}

	type_bool NEIdentifier::operator==(const This& source) const
	{
		return	isEqualTo(source);
	}

	type_bool NEIdentifier::operator!=(const This& source) const
	{
		return ! isEqualTo(source);
	}

	type_bool NEIdentifier::isKindOf(const This& rhs) const
	{
		if( ! &rhs) return false;

		return	_name == rhs._name		&&
				_author == rhs._author	;
	}

	type_bool NEIdentifier::isCompatibleTo(const This& rhs) const
	{
		return	isKindOf(rhs)							&&
				_revision_count == rhs._revision_count	;
	}

	type_bool NEIdentifier::isEqualTo(const This& rhs) const
	{
		return	isCompatibleTo(rhs)					&&
				_version_count == rhs._version_count;
	}

	const NEClassBase& NEIdentifier::getClassStatically()
	{
		static NETClass<This> metaclass;

		return metaclass;
	}
}