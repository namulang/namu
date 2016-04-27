#pragma once

namespace NE
{
	//    Specialize NETClass for not templating NETClass<Unknown> class reculsively.
	template <>
	class NE_DLL NETClassBase<NEUnknown, false> : public NETClassBaseCommon<NEUnknown, false>
	{
	public:
		//	Can't use macro such as NE_DECLARE_CLASS:
		//		We'll specify METACLASS to NETUnknownMetaClass because of given 
		//		parameterized type, NEUnknown.
		//		So, we should declare all typedefs in manual.
		typedef NETClassBase<NEUnknown, false> This;
		typedef NETClassBaseCommon<NEUnknown, false> Super;
		//	type determind:
		typedef NEUnknown Trait;
		typedef NETSuperClassDeterminder<NEUnknown, false>::Super SuperTrait;
		typedef NETUnknownMetaClass<NEUnknown, false> MetaClass;

	public:
		virtual type_bool isMetaClassDefined() const;
		virtual type_bool isInstantiable() const;
		virtual type_bool isTemplate() const;
		virtual type_bool isBuiltInClass() const;
		virtual const NEClassBase& getTraitClass() const;
		virtual const NEIdentifier& getIdentifier() const;
	protected:
		virtual NEIdentifier& _getIdentifier();

	public:
		static const NEClassBase& getTraitClassStatically();
		static const NEIdentifier& getIdentifierStatically();

	public:
		static const type_bool IS_ADT = true;
		static const type_bool IS_TEMPLATE = false;
		static const type_bool IS_BUILT_IN_CLASS = true;
		static const type_bool IS_METACLASS_DEFINED = false;
	};
	template <>
	class NE_DLL NETClassBase<NEAdam, false> : public NETClassBaseCommon<NEAdam, false>
	{
	public:
		typedef NETClassBase<NEAdam, false> This;
		typedef NETClassBaseCommon<NEAdam, false> Super;
		//	type determind:
		typedef NEAdam Trait;
		typedef NETSuperClassDeterminder<NEAdam, false>::Super SuperTrait;
		typedef NETInterface<NEAdam, false> MetaClass;

	public:
		virtual type_bool isMetaClassDefined() const;
		virtual type_bool isInstantiable() const;
		virtual type_bool isTemplate() const;
		virtual type_bool isBuiltInClass() const;
		virtual const NEClassBase& getTraitClass() const;
		virtual const NEIdentifier& getIdentifier() const;
	protected:
		virtual NEIdentifier& _getIdentifier();

	public:
		static const NEClassBase& getTraitClassStatically();

	public:
		static const type_bool IS_ADT = true;
		static const type_bool IS_TEMPLATE = false;
		static const type_bool IS_BUILT_IN_CLASS = true;
		static const type_bool IS_METACLASS_DEFINED = false;
	};	

	//	Because NEIdableObject, NEObject is a superclass of NEClassBase, You can't define it with 
	//	NETClass class template. So, you should do it manually.
	template <>
	class NE_DLL NETClassBase<NEObject, false> : public NETClassBaseCommon<NEObject, false>
	{
	public:
		//	Can't use macro such as NE_DECLARE_CLASS:
		//		We'll specify METACLASS to NETUnknownMetaClass because of given 
		//		parameterized type, NEUnknown.
		//		So, we should declare all typedefs in manual.
		typedef NETClassBase<NEObject, false> This;
		typedef NETClassBaseCommon<NEObject, false> Super;
		//	type determind:
		typedef NEUnknown Trait;
		typedef NETSuperClassDeterminder<NEObject, false>::Super SuperTrait;
		typedef NETInterface<NEObject, false> MetaClass;

	public:
		virtual type_bool isMetaClassDefined() const;
		virtual type_bool isInstantiable() const;
		virtual type_bool isTemplate() const;
		virtual type_bool isBuiltInClass() const;
		virtual const NEClassBase& getTraitClass() const;
		virtual const NEIdentifier& getIdentifier() const;
	protected:
		virtual NEIdentifier& _getIdentifier();

	public:
		static const NEClassBase& getTraitClassStatically();

	public:
		static const type_bool IS_ADT = true;
		static const type_bool IS_TEMPLATE = false;
		static const type_bool IS_BUILT_IN_CLASS = true;
		static const type_bool IS_METACLASS_DEFINED = true;
	};

	template <>
	class NE_DLL NETClassBase<NEIdableObject, false> : public NETClassBaseCommon<NEIdableObject, false>
	{
	public:
		//	Can't use macro such as NE_DECLARE_CLASS:
		//		We'll specify METACLASS to NETUnknownMetaClass because of given 
		//		parameterized type, NEUnknown.
		//		So, we should declare all typedefs in manual.
		typedef NETClassBase<NEIdableObject, false> This;
		typedef NETClassBaseCommon<NEIdableObject, false> Super;
		//	type determind:
		typedef NEUnknown Trait;
		typedef NETSuperClassDeterminder<NEIdableObject, false>::Super SuperTrait;
		typedef NETInterface<NEIdableObject, false> MetaClass;

	public:
		virtual type_bool isMetaClassDefined() const;
		virtual type_bool isInstantiable() const;
		virtual type_bool isTemplate() const;
		virtual type_bool isBuiltInClass() const;
		virtual const NEClassBase& getTraitClass() const;
		virtual const NEIdentifier& getIdentifier() const;
	protected:
		virtual NEIdentifier& _getIdentifier();

	public:
		static const NEClassBase& getTraitClassStatically();

	public:
		static const type_bool IS_ADT = true;
		static const type_bool IS_TEMPLATE = false;
		static const type_bool IS_BUILT_IN_CLASS = true;
		static const type_bool IS_METACLASS_DEFINED = true;
	};

	template <>
	class NE_DLL NETClassBase<NEClassBase, false> : public NETClassBaseCommon<NEClassBase, false>
	{
	public:
		//	Can't use macro such as NE_DECLARE_CLASS:
		//		We'll specify METACLASS to NETUnknownMetaClass because of given 
		//		parameterized type, NEUnknown.
		//		So, we should declare all typedefs in manual.
		typedef NETClassBase<NEClassBase, false> This;
		typedef NETClassBaseCommon<NEClassBase, false> Super;
		//	type determind:
		typedef NEUnknown Trait;
		typedef NETSuperClassDeterminder<NEClassBase, false>::Super SuperTrait;
		typedef NETInterface<NEClassBase, false> MetaClass;

	public:
		virtual type_bool isMetaClassDefined() const;
		virtual type_bool isInstantiable() const;
		virtual type_bool isTemplate() const;
		virtual type_bool isBuiltInClass() const;
		virtual const NEClassBase& getTraitClass() const;
		virtual const NEIdentifier& getIdentifier() const;
	protected:
		virtual NEIdentifier& _getIdentifier();

	public:
		static const NEClassBase& getTraitClassStatically();

	public:
		static const type_bool IS_ADT = true;
		static const type_bool IS_TEMPLATE = false;
		static const type_bool IS_BUILT_IN_CLASS = true;
		static const type_bool IS_METACLASS_DEFINED = true;
	};

	template <typename T>
	class NE_DLL NETClassBase<T, true> : public NETClassBaseCommon<T>
	{
	public:
		//	Can't use macro such as NE_DECLARE_CLASS:
		//		We'll specify METACLASS to NETUnknownMetaClass because of given 
		//		parameterized type, NEUnknown.
		//		So, we should declare all typedefs in manual.
		typedef NETClassBase<T> This;
		typedef NETClassBaseCommon<T> Super;
		//	type determind:
		typedef NEUnknown Trait;
		typedef NETSuperClassDeterminder<T>::Super SuperTrait;
		typedef NETInterface<T> MetaClass;

	public:
		virtual type_bool isMetaClassDefined() const;
		virtual type_bool isInstantiable() const;
		virtual type_bool isTemplate() const;
		virtual type_bool isBuiltInClass() const;
		virtual const NEClassBase& getTraitClass() const;
		virtual const NEHeader& getIdentifier() const;
	protected:
		virtual NEHeader& _getIdentifier();

	public:
		static const NEClassBase& getTraitClassStatically();

	public:
		static const type_bool IS_ADT = true;
		static const type_bool IS_TEMPLATE = false;
		static const type_bool IS_BUILT_IN_CLASS = true;
		static const type_bool IS_METACLASS_DEFINED = true;
	};
}