#pragma once

#include "../NEKeyNameBinder/NEKeyNameBinder.hpp"

namespace NE
{
	class NEArgumentBaseList;

	class NE_DLL NEArgumentBase : public NEKeyNameBinder
	{
	public:
		friend class NEModule;

	public:
		typedef NEArgumentBase ThisClass;
		typedef NEKeyNameBinder SuperClass;

	public:
		NEArgumentBase(NEType::Type type);
		NEArgumentBase(const ThisClass& rhs);

	public:
		~NEArgumentBase();

	public:
		bool operator==(const NEArgumentBase& source) const;
		bool operator!=(const NEArgumentBase& source) const;

	public:
		NEType::Type getTypeToBeBinded() const;
		bool isValidToBind(const NEObject& to_be_bind) const;
		const NEKey& getValueKey() const;
		NEKey& getValueKey();

	public:		
		virtual type_result bind();
		virtual NEKey& getDefaultKey() = 0;
		virtual const NEKey& getDefaultKey() const = 0;

	public:
		virtual NEType::Type getType() const;
		virtual type_result isValid() const;
		virtual void release();
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	public:
		bool isNeedingBinding() const;		

	private:
		void _release();

	private:
		NEType::Type _type_validation;
	};
}