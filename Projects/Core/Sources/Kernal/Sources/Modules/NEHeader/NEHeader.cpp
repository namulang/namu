#include "NEHeader.hpp"

namespace NE
{
	NEHeader::NEHeader()
		: Super()
	{

	}

	NEHeader::NEHeader(const NETString& new_name, const NETString& new_author, type_count new_revision_count, type_count new_version_count, const NETString& new_comment, const NETString& new_version, const NETString& new_release_date)
		:	Super(new_name, new_author, new_revision_count, new_version_count),
			_comment(new_comment), _version(new_version), _release_date(new_release_date)
	{

	}

	NEHeader::NEHeader(const This& rhs)
		: Super(rhs)
	{
		_assign(rhs);
	}

	NEHeader::~NEHeader()
	{

	}

	NEHeader& NEHeader::operator=(const This& rhs)
	{
		if(this == &rhs) return *this;

		Super::operator=(rhs);

		return _assign(rhs);
	}

	type_bool NEHeader::operator==(const This& rhs) const
	{
		return	Super::operator==(rhs)				&&
				_comment == rhs._comment			&&
				_version == rhs._version			&&
				_release_date == rhs._release_date	;
	}

	type_bool NEHeader::operator!=(const This& rhs) const
	{
		return ! operator==(rhs);
	}

	const NETString& NEHeader::getComment() const
	{
		return _comment;
	}

	NETString& NEHeader::getComment()
	{
		return _comment;
	}

	const NETString& NEHeader::getVersion() const
	{
		return _version;

	}

	NETString& NEHeader::getVersion()
	{
		return _version;
	}

	const NETString& NEHeader::getReleaseDate() const
	{
		return _release_date;
	}

	NETString& NEHeader::getReleaseDate()
	{
		return _release_date;
	}

	void NEHeader::release()
	{
		Super::release();

		_release();
	}

	NEBinaryFileSaver& NEHeader::serialize(NEBinaryFileSaver& saver) const
	{
		Super::serialize(saver);

		return saver << _comment << _version << _release_date;
	}

	NEBinaryFileLoader& NEHeader::serialize(NEBinaryFileLoader& loader)
	{
		Super::serialize(loader);

		return loadre >> _comment >> _version >> _release_date;
	}

	type_result NEHeader::isValid() const
	{
		type_result result = Super::isValid();
		if(NEResult::hasError(result)) return result;

		return RESULT_SUCCESS;
	}

	NEHeader& NEHeader::_assign(const This& rhs)
	{
		if(this == &rhs) return *this;

		_comment = rhs._comment;
		_version = rhs._version;
		_release_date = rhs._release_date;

		return *this;
	}

	void NEHeader::_release()
	{
		_comment.release();
		_version.release();
		_release_date.release();
	}
}