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
class NE::NEClassBase;

#include "../NETList/NETList.inl"	// include inl, not hpp

namespace NE
{
	typedef NETList<NEClassBase*, true> NEClassBaseList;

	class NE_DLL NEClassBase : public NEIdableObject
	{
		//    Declarations:
	public:
		typedef NEClassBase This;
		typedef NEIdableObject Super;
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
		virtual const type_bool& isRegistered() const = 0;
		virtual const NEClassBase& getClass() const = 0;
		virtual const This& getTraitClass() const = 0;
		virtual const NEClassBaseList& getSuperClasses() const = 0;
		virtual const NEClassBaseList& getSubClasses() const = 0;
		virtual const NETString& getName() const = 0;
		virtual NEObject& instantiate() const = 0;
		virtual const NEHeader& getHeader() const = 0;
		//            Inherits:
		//                NEObject:
	public:
		virtual type_result isValid() const;
		virtual void release();
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	protected:
		//    these method were used only for TypeManager friend class.
		virtual type_result _setRegistered(type_bool new_is_registered) = 0;
		virtual type_result _setIdentifier(const NEClassIdentifier& new_identifier) = 0;
		virtual type_result _setId(type_id new_id) = 0;
		virtual type_result _onInitialize(NEHeader& to_intiailize);

		//        General interfaces:
	public:
		type_result enroll();
		type_bool isEqualTypeWith(const This& source) const;
		type_bool isEqualTypeWith(const NEObject& source) const;
		type_bool isSuperClassOf(const This& parent) const;
		type_bool isSuperClassOf(const NEObject& parent) const;
		type_bool isSubClassOf(const This& parent) const;
		type_bool isSubClassOf(const NEObject& parent) const;
		const This& getSuperClass() const;

	protected:
		type_result _alert(type_result result, const type_tchar* message) const;
		//	instantiation function:
		//		to reduce dependencies for NETClassBase, we hide concrete couplings
		//		into implement file.
		NEHeader& _createHeader() const;
		NEClassBaseList& _createClassBaseList() const;

	private:
		type_result _registerSubClass(const NEClassBase& subclass);
		type_result _registerSubClassAsMyChild(const NEClassBase& subclass);
		NEClassBaseList& _getSubClasses();
	};
}