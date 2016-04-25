#pragma once

namespace NE
{
	//	declare specialized for NEClassBaseList of class template, NETClassBase.
	//	why do we have to declare at first?:
	//		NETClassBase uses NEClassBaseList. and of course NEClassBaseList 
	//		is a templated from NETList, it needs fully defined NETClass at get
	//		Class() methods.
	//		So, it causes an another reculsive header problem.
	//		to prevent it, we're going to declare specialized NETClass<NEClassBa
	//		seList> at first. by doing this, we can hide its dependency to
	//		NETClass from NETClass<NEClassBaseList>.

	template <>
	class NE_DLL NETClassBase<NEClassBaseList> : public NEClassBase
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

	public:
		static const type_bool IS_ADT = true;
		static const type_bool IS_TEMPLATE = false;
		static const type_bool IS_DERIVED_OF = true;
		static const type_bool IS_METACLASS_DEFINED = false;
	};
}