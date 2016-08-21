//    ---------------------------------------------------------------------------------
//    클래스명:    NEClassBase
//    설명    :    
//    관계    :    
//    특성    :    
//    알고리즘:    
//    사용방법:    
//    메모    :    
//    히스토리:    2016-02-09    이태훈    생성
//    ---------------------------------------------------------------------------------
#pragma once

//    include:
#include "../NEIdableObject/NEIdableObject.hpp"
#include "../NETString/NETString.hpp"	//	forward declaration
//		include NETList as declaration, not definition:
//			if we include it as definition, we'll be falled into the deep of templating reculsion.
//			it'll cause to NEClassBaseList that is also a kind of NEObject. of course it has TClass<T>
//			too.
//			so in order to prevent that, we should be include headers along with following sequence.
//				*) "declaration of T" means "T.inl"
//				*) "definition of T" means "T.hpp"
//
//				1. declaration of NEClassBase. (for declaring NETList)
//				2. declaration of NETList
//				3. typedef NETList<NEClassBase*> to NEClassBaseList
//				4. declaration of TClass
//				5. definition of NETList (there is no need to define NEClassBase, because it isn't 
//					a class template)
//				6. definition of TClass.
//			this header files kept 1 to 4 contents among above ones.

#include "../NETList/NETList.inl"	// include inl, not hpp

namespace NE
{
	class NE_DLL NEHeader;
	class NE_DLL NEClassBase;
	class NE_DLL NEMethodList;
	class NE_DLL NEPackage;
	template <typename T, type_bool useHeap>
	class NETList;

	typedef NETList<NEClassBase*, true> NEClassBaseList;

	class NE_DLL NEClassBase : public NEIdableObject
	{
		NE_DECLARE_INTERFACE_ONLY(NEClassBase, NEIdableObject)

		//    Declarations:
	public:
		friend class NEPackageManager;

		//    Constructors:
	public:
		NEClassBase();
		NEClassBase(const NEClassBase& source);

		//    Destructors:
	public:
		virtual ~NEClassBase();

		//    Interfaces:
		//        Virtuals:
	public:
		virtual type_bool isInstantiable() const = 0;
		virtual type_bool isTemplate() const = 0;
		virtual type_bool isMetaClassDefined() const = 0;
		virtual type_bool isBuiltInClass() const = 0;
		virtual type_bool isRegistered() const = 0;
		virtual const This& getTraitClass() const = 0;
		virtual const NEClassBaseList& getSuperClasses() const = 0;
		virtual const NEClassBaseList& getChildrenClasses() const = 0;
		virtual const NETString& getName() const = 0;
		virtual NEObject& instantiate() const = 0;
		virtual const NEHeader& getHeader() const = 0;
		virtual const NEPackage& getPackage() const = 0;

		//            Inherits:
		//                NEObject:
	public:
		virtual type_result isValid() const;
		virtual void release();
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	protected:
		//	these method were used only for ClassManager/PackageManager friend class.
		//	by setting id >= 0, Class can be classified to be registered.
		//	In fact, this Id was meant to index of buffer belonged to ClassManager.
		virtual type_result _onInitializeHeader(NEHeader& to_intiailize);
		virtual type_result _onInitializeMethods(NEMethodList& to_initialize);

		//        General interfaces:
	public:
		type_bool isEqualClassTo(const This& source) const;
		type_bool isEqualClassTo(const NEObject& source) const;
		type_bool isSuperClassOf(const This& parent) const;
		type_bool isSuperClassOf(const NEObject& parent) const;
		type_bool isSubClassOf(const This& parent) const;
		type_bool isSubClassOf(const NEObject& parent) const;
		const This& getSuperClass() const;
		type_result setPackage(const NEPackage& new_package);

	protected:
		type_result _alert(type_result result, const type_tchar* message) const;
		NEClassBaseList& _getChildrenClasses();
		NEClassBaseList& _getSuperClasses();
		NEHeader& _getHeader();
		type_result _enrollSuperClasses(const NEClassBase& super);
		type_result _enrollChildClass(const NEClassBase& child);
		type_id& _getId();
	};
}