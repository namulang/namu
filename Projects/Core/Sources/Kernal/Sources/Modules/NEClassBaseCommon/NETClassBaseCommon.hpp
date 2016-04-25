#pragma once

#include "../NEClassBase/NEClassBase.hpp"

namespace NE
{
	///	@class	NETClassBaseCommon
	///	@brief	Implemented common method and data among specialized from NETClassBase
	///			class.
	template <typename T>
	class NETClassBaseCommon : public NEClassBase
	{
	public:
		typedef NETClassBaseCommon<T> This;
		typedef NEClassBase Super;

	public:
		virtual const NEClassBase& getClass() const;
		virtual const type_bool& isRegistered() const;
		virtual const NETString& getName() const;
		virtual const NEClassBaseList& getSuperClasses() const;
		virtual const NEClassBaseList& getSubClasses() const;

		///	@brief	returns this ClassIdentifer.
		///			As you can inspect codes, this returns the static variable.
		///	@remark	ClassIdentifier's Name attribute doesn't mean ClassName only.
		///			In fact, it consists of "PackageName(which contains this class)::ClassName". 
		///			for instance,
		///				* if NETClassBaseCommon<MyClass>::getName returns "class MyClass" as result of 'typeid(T)',
		///				* and MyClass is distributed within 'MyPackage.dll/so',
		///
		///				NETClassBaseCommon<MyClass>::getIdentifier's Name would be, 
		///					= "MyPackage" + "::" + getName();
		///					= "MyPackage::class MyClass"
		virtual const NEIdentifier& getIdentifier() const;
	protected:
		virtual type_result _setRegistered(type_bool new_is_registered);
		virtual type_result _setIdentifier(const NEIdentifier& new_identifier);

	public:
		static const type_bool& isRegisteredStatically();
		static const NEClassBaseList& getSuperClassesStatically();
		static const NEClassBaseList& getSubClassesStatically();
		static const NEIdentifier& getIdentifierStatically();
		static const NEClassBase& getClassStatically();
		static const NETString& getNameStatically();
		static const type_id& getIdStatically();
	};

	template <>
	class NE_DLL NETClassBaseCommon<NEModule> : public 
}

#include "NETClassBaseCommon.inl"