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
#include "../NEUnit/NEUnit.hpp"
#include "../../Modules/NETString/NETString.hpp"

namespace NE
{
	class NEClassBaseList;

	class NE_DLL NEClassBase : public NEUnit
	{
		//    Declarations:
	public:
		typedef NEClassBase This;
		typedef NEUnit Super;
		friend class NEClassManager;

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

		//        General interfaces:
	public:
		type_result enroll();
		bool isEqualTypeWith(const This& source) const;
		bool isEqualTypeWith(const NEObject& source) const;
		bool isSuperClassOf(const This& parent) const;
		bool isSuperClassOf(const NEObject& parent) const;
		bool isSubClassOf(const This& parent) const;
		bool isSubClassOf(const NEObject& parent) const;
		const This& getSuperClass() const;

	protected:
		type_result _alert(type_result result, const type_tchar* message) const;

	private:
		type_result _registerSubClass(const NEClassBase& subclass);
		type_result _registerSubClassAsMyChild(const NEClassBase& subclass);
		NEClassBaseList& _getSubClasses();
	};
}