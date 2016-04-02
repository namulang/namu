#pragma once

#include "../NEObject/NEObject.hpp"
#include "../NETClass/NETClass.hpp"

namespace NE
{
	///	@class	Identifier
	/// @brief	Identifier uses to identify package among one of world packages
	///			fetched by @PackageManager.
	class NE_DLL NEIdentifier : public NEObject
	{
		NE_DECLARE_CLASS(NEIdentifier, NEObject)

	public:
		#include "innerclass/Bean.hpp"

	public:
		NEIdentifier();
		NEIdentifier(const NETString& new_name, const NETString& new_author, type_int new_interface_revision);
		NEIdentifier(const This& rhs);

	protected:
		//	this constructor only for not creating bean.
		NEIdentifier(type_bool);
		NEIdentifier(type_bool, const NETString& new_name, const NETString& new_author, type_int new_interface_revision);
		NEIdentifier(type_bool, const NEPackage& package);
	
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
		const type_int getInterfaceRevision() const;
		type_result setInterfaceRevison(type_int new_revision);
		///	@brief	this method returns true when argument matches with name and 
		///			author. 
		///			interface revision is not concerned target.
		type_bool isNearlyEqualTo(const This& rhs) const;

	public:
		virtual void release();
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual type_result isValid() const;

	public:
		type_result proxy(NEPackage& target);
		type_result proxy(const NETString& name, const NETString& author, type_int interface_revision);

	private:
		type_result _initializeBean();
		This& _assign(const This& rhs);

	private:
		type_bool _is_bean;
		BeanOrWrapper _bean_or_proxy;
	};
}