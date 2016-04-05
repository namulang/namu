#pragma once

#include "../NETClass/NETClass.hpp"

namespace NE
{
	template <typename T>
	class NETHeader : public T
	{
		NE_DECLARE_CLASS(NETHeader, T)

	public:
		NETHeader();
		NETHeader(const This& rhs);

	public:
		virtual ~NETHeader();

	public:
		This& operator=(const This& rhs);
		type_bool operator==(const This& rhs);
		type_bool operator!=(const This& rhs);

	public:
		const NETString& getVersion() const;
		type_result setVersion(const NETString& new_version);
		const NETString& getComment() const;
		type_result setComment(const NETString& new_comment);
		const NEIntSet& getCompatibleSet() const;
		type_result setCompatibleSet(const NEIntSet& new_compatibles);

	public:
		virtual void release();
		virtual type_result isValid() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	private:
		NETString _version;
		NETString _comment;
		NEIntSet _compatibles;
	};

	template <typename T>
	NE::NETHeader<T>::NETHeader()
	{

	}

}

#include "NETHeader.inl"