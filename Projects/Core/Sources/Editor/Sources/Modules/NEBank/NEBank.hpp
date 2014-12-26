#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL NEBank : public NETStringList
	{
	public:
		typedef NETStringList SuperClass;
		typedef NEBank ThisClass;

	public:
		NEBank();
		NEBank(const NECodeType& source);
		NEBank(const ThisClass& source);

	public:
		ThisClass& operator=(const ThisClass& source);
		bool operator==(const ThisClass& source) const;
		bool operator!=(const ThisClass& source) const;

	public:
		NECodeType& getCodeType();
		const NECodeType& getCodeType() const;

	public:
		virtual NEObject& clone() const;
		virtual void release();
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual type_result isValid() const;
		virtual NEType::Type getType() const;

	private:
		void _release();
		ThisClass& _assign(const ThisClass& source);

	private:
		NECodeType _type;
	};
}
