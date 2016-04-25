#pragma once

namespace NE
{
	//    Specialize NETClass for not templating NETClass<Unknown> class reculsively.
	template <>
	class NE_DLL NETClassBase<NEUnknown> : public NETClassBaseCommon<NEUnknown>
	{
	public:
		//	Can't use macro such as NE_DECLARE_CLASS:
		//		We'll specify METACLASS to NETUnknownMetaClass because of given 
		//		parameterized type, NEUnknown.
		//		So, we should declare all typedefs in manual.
		typedef NETClassBase<NEUnknown> This;
		typedef NETClassBaseCommon<NEUnknown> Super;
		//	type determind:
		typedef NEUnknown Trait;
		typedef NETSuperClassDeterminder<NEUnknown>::Super SuperTrait;
		typedef NETUnknownMetaClass<NEUnknown> MetaClass;

	public:
		virtual type_bool isMetaClassDefined() const;
		virtual type_bool isInstantiable() const;
		virtual type_bool isTemplate() const;
		virtual type_bool isBuiltInClass() const;
		virtual const NEClassBase& getTraitClass() const;

	public:
		static const NEClassBase& getTraitClassStatically();

	public:
		static const type_bool IS_ADT = true;
		static const type_bool IS_TEMPLATE = false;
		static const type_bool IS_DERIVED_OF = true;
		static const type_bool IS_METACLASS_DEFINED = false;
	};
	template <>
	class NE_DLL NETClassBase<NEAdam> : public NETClassBaseCommon<NEAdam>
	{
	public:
		typedef NETClassBase<NEAdam> This;
		typedef NETClassBaseCommon<NEAdam> Super;
		//	type determind:
		typedef NEAdam Trait;
		typedef NETSuperClassDeterminder<NEAdam>::Super SuperTrait;
		typedef NETInterface<NEAdam> MetaClass;

	public:
		virtual type_bool isMetaClassDefined() const;
		virtual type_bool isInstantiable() const;
		virtual type_bool isTemplate() const;
		virtual type_bool isBuiltInClass() const;
		virtual const NEClassBase& getTraitClass() const;

	public:
		static const NEClassBase& getTraitClassStatically();

	public:
		static const type_bool IS_ADT = true;
		static const type_bool IS_TEMPLATE = false;
		static const type_bool IS_DERIVED_OF = true;
		static const type_bool IS_METACLASS_DEFINED = false;
	};	

	//	Because NEIdableObject, NEObject is a superclass of NEClassBase, You can't define it with 
	//	NETClass class template. So, you should do it manually.
	template <>
	class NE_DLL NETClassBase<NEObject> : public NETClassBaseCommon<NEObject>
	{
	public:
		//	Can't use macro such as NE_DECLARE_CLASS:
		//		We'll specify METACLASS to NETUnknownMetaClass because of given 
		//		parameterized type, NEUnknown.
		//		So, we should declare all typedefs in manual.
		typedef NETClassBase<NEObject> This;
		typedef NETClassBaseCommon<NEObject> Super;
		//	type determind:
		typedef NEUnknown Trait;
		typedef NETSuperClassDeterminder<NEObject>::Super SuperTrait;
		typedef NETInterface<NEObject> MetaClass;

	public:
		virtual type_bool isMetaClassDefined() const;
		virtual type_bool isInstantiable() const;
		virtual type_bool isTemplate() const;
		virtual type_bool isBuiltInClass() const;
		virtual const NEClassBase& getTraitClass() const;

	public:
		static const NEClassBase& getTraitClassStatically();

	public:
		static const type_bool IS_ADT = true;
		static const type_bool IS_TEMPLATE = false;
		static const type_bool IS_DERIVED_OF = true;
		static const type_bool IS_METACLASS_DEFINED = true;
	};

	template <>
	class NE_DLL NETClassBase<NEIdableObject> : public NETClassBaseCommon<NEIdableObject>
	{
	public:
		//	Can't use macro such as NE_DECLARE_CLASS:
		//		We'll specify METACLASS to NETUnknownMetaClass because of given 
		//		parameterized type, NEUnknown.
		//		So, we should declare all typedefs in manual.
		typedef NETClassBase<NEIdableObject> This;
		typedef NETClassBaseCommon<NEIdableObject> Super;
		//	type determind:
		typedef NEUnknown Trait;
		typedef NETSuperClassDeterminder<NEIdableObject>::Super SuperTrait;
		typedef NETInterface<NEIdableObject> MetaClass;

	public:
		virtual type_bool isMetaClassDefined() const;
		virtual type_bool isInstantiable() const;
		virtual type_bool isTemplate() const;
		virtual type_bool isBuiltInClass() const;
		virtual const NEClassBase& getTraitClass() const;

	public:
		static const NEClassBase& getTraitClassStatically();

	public:
		static const type_bool IS_ADT = true;
		static const type_bool IS_TEMPLATE = false;
		static const type_bool IS_DERIVED_OF = true;
		static const type_bool IS_METACLASS_DEFINED = true;
	};

	template <>
	class NE_DLL NETClassBase<NEClassBase> : public NETClassBaseCommon<NEClassBase>
	{
	public:
		//	Can't use macro such as NE_DECLARE_CLASS:
		//		We'll specify METACLASS to NETUnknownMetaClass because of given 
		//		parameterized type, NEUnknown.
		//		So, we should declare all typedefs in manual.
		typedef NETClassBase<NEClassBase> This;
		typedef NETClassBaseCommon<NEClassBase> Super;
		//	type determind:
		typedef NEUnknown Trait;
		typedef NETSuperClassDeterminder<NEClassBase>::Super SuperTrait;
		typedef NETInterface<NEClassBase> MetaClass;

	public:
		virtual type_bool isMetaClassDefined() const;
		virtual type_bool isInstantiable() const;
		virtual type_bool isTemplate() const;
		virtual type_bool isBuiltInClass() const;
		virtual const NEClassBase& getTraitClass() const;

	public:
		static const NEClassBase& getTraitClassStatically();

	public:
		static const type_bool IS_ADT = true;
		static const type_bool IS_TEMPLATE = false;
		static const type_bool IS_DERIVED_OF = true;
		static const type_bool IS_METACLASS_DEFINED = true;
	};

	template <>
	class NE_DLL NETClassBase<NEModule> : public NETClassBaseCommon<NEModule>
	{
	public:
		//	Can't use macro such as NE_DECLARE_CLASS:
		//		We'll specify METACLASS to NETUnknownMetaClass because of given 
		//		parameterized type, NEUnknown.
		//		So, we should declare all typedefs in manual.
		typedef NETClassBase<NEModule> This;
		typedef NETClassBaseCommon<NEModule> Super;
		//	type determind:
		typedef NEUnknown Trait;
		typedef NETSuperClassDeterminder<NEModule>::Super SuperTrait;
		typedef NETInterface<NEModule> MetaClass;

	public:
		virtual type_bool isMetaClassDefined() const;
		virtual type_bool isInstantiable() const;
		virtual type_bool isTemplate() const;
		virtual type_bool isBuiltInClass() const;
		virtual const NEClassBase& getTraitClass() const;

	public:
		static const NEClassBase& getTraitClassStatically();

	public:
		static const type_bool IS_ADT = true;
		static const type_bool IS_TEMPLATE = false;
		static const type_bool IS_DERIVED_OF = true;
		static const type_bool IS_METACLASS_DEFINED = true;
	};
}