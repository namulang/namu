#pragma once

#include "../NEObject/NEObject.hpp"

namespace NE
{
	template <typename T>
	class NETInterface;

	class NEClassBase;

	///	@class	Identifier
	/// @brief	Identifier uses to identify package among one of world packages
	///			fetched by @PackageManager.
	class NE_DLL NEIdentifier : public NEObject
	{
		//	declare rtti info manually:
		//		to prevent reculsive templating.
	public:
		typedef NEIdentifier		This;
		typedef NEObject			Super;
		typedef NETInterface<This>	MetaClass;

	public:
		virtual const NEClassBase& getClass() const { return getClassStatically(); }
		static const NEClassBase& getClassStatically();

	public:
		NEIdentifier();
		NEIdentifier(const NETString& new_name, const NETString& new_author, type_count new_revision_count, type_count new_version_count);
		NEIdentifier(const This& rhs);
	
	public:
		virtual ~NEIdentifier();

	public:
		const This& operator=(const This& source);
		bool operator==(const This& source) const;
		bool operator!=(const This& source) const;

	public:
		const NETString& getName() const;
		NETString& getName();
		const NETString& getAuthor() const;
		NETString& getAuthor();
		const type_int getRevisionCount() const;
		type_result setRevisonCount(type_int new_revision);
		const type_int getVersionCount() const;
		type_result setVersionCount(type_int new_version);
		///	@brief	this will detect that this.identifier instance is a kind of given one.
		///	@remark	About Identifier, kind quality of Identifier is determined only with name and author.
		///			so, actually this method returns true when argument matches with name and author. 
		///			counts aren't concerned as a target.
		type_bool isKindOf(const This& identifier) const;
		type_bool isCompatibleTo(const This& identifier) const;
		type_bool isEqualTo(const This& identifier) const;

	public:
		virtual void release();
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual type_result isValid() const;

	private:
		This& _assign(const This& rhs);

	private:
		NETString _name; 
		NETString _author;
		type_count _revision_count;
		type_count _version_count;				
	};
}