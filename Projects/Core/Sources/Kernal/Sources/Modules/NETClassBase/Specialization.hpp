#pragma once

namespace NE
{
	//    Specialize NETClass for not templating NETClass<Unknown> class reculsively.
	template <>
	class NE_DLL NETClassBase<NEUnknown> : public NEClassBase
	{
	public:
		//	Can't use macro such as NE_DECLARE_CLASS:
		//		We'll specify METACLASS to NETUnknownMetaClass because of given 
		//		parameterized type, NEUnknown.
		//		So, we should declare all typedefs in manual.
		typedef NETClassBase<NEUnknown> This;
		typedef NEClassBase Super;
		//	type determind:
		typedef NEUnknown Trait;
		typedef NETSuperClassDeterminder<NEUnknown>::Super SuperTrait;
		typedef NETUnknownMetaClass<NEUnknown> MetaClass;

	public:
		virtual type_bool isMetaClassDefined() const;
		virtual type_bool isInstantiable() const;
		virtual type_bool isTemplate() const;
		virtual type_bool isBuiltInClass() const;
		virtual const type_bool& isRegistered() const;
		virtual const NEClassBase& getTraitClass() const;
		virtual const NEClassBaseList& getSuperClasses() const;
		virtual const NEClassBaseList& getSubClasses() const;
		virtual const NETString& getName() const;
		virtual const NEClassBase& getClass() const;
	protected:
		virtual type_result _setRegistered(type_bool new_is_registered);

	public:
		static const NEClassBase& getTraitClassStatically();
		static const NETString& getNameStatically();
		static const type_bool& isRegisteredStatically();
		static const NEClassBaseList& getSuperClassesStatically();
		static const NEClassBaseList& getSubClassesStatically();
		static const NEClassBase& getClassStatically();

	protected:

	public:
		static const type_bool IS_ADT = true;
		static const type_bool IS_TEMPLATE = false;
		static const type_bool IS_BUILT_IN_CLASS = true;
		static const type_bool IS_METACLASS_DEFINED = false;
	};
	template <>
	class NE_DLL NETClassBase<NEAdam> : public NEClassBase
	{
	public:
		typedef NETClassBase<NEAdam> This;
		typedef NEClassBase Super;
		//	type determind:
		typedef NEAdam Trait;
		typedef NETSuperClassDeterminder<NEAdam>::Super SuperTrait;
		typedef NETInterface<NEAdam> MetaClass;

	public:
		virtual type_bool isMetaClassDefined() const;
		virtual type_bool isInstantiable() const;
		virtual type_bool isTemplate() const;
		virtual type_bool isBuiltInClass() const;
		virtual const type_bool& isRegistered() const;
		virtual const NEClassBase& getTraitClass() const;
		virtual const NEClassBaseList& getSuperClasses() const;
		virtual const NEClassBaseList& getSubClasses() const;
		virtual const NETString& getName() const;
		virtual const NEClassBase& getClass() const;
	protected:
		virtual type_result _setRegistered(type_bool new_is_registered);

	public:
		static const NEClassBase& getTraitClassStatically();
		static const NETString& getNameStatically();
		static const type_bool& isRegisteredStatically();
		static const NEClassBaseList& getSuperClassesStatically();
		static const NEClassBaseList& getSubClassesStatically();
		static const NEClassBase& getClassStatically();


	public:
		static const type_bool IS_ADT = true;
		static const type_bool IS_TEMPLATE = false;
		static const type_bool IS_BUILT_IN_CLASS = true;
		static const type_bool IS_METACLASS_DEFINED = false;
	};	
}