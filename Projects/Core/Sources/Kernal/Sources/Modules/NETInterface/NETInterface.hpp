//	---------------------------------------------------------------------------------
//	Name			:	NETInterface
//	Comments		:	
//	Releationships	:
//	Charateristics	:	
//	Usage			:	
//	Memo			:	
//	Author			:	2016-02-13	kniz	Creations
//	---------------------------------------------------------------------------------
#pragma once

#include "../NEClassBase/NEClassBase.hpp"
#include "../NEClassBaseList/NEClassBaseList.hpp"
#include "../NEMetaInterface/NEMetaInterface.hpp"

namespace NE
{
	template <typename T>
	class NETInterface : public NEClassBase
	{
		//	Declarations:
	public:
		typedef NETInterface<T> This;
		typedef NETClass<NEInterfaceClass> MetaClass;
		typedef NEClassBase Super;
		typedef T Trait;
		typedef typename Trait::Super SuperTrait;		

		//	Constructors:
	public:
		NETInterface();
		NETInterface(const NETInterface& source);

		//	Destructors:
	public:
		virtual ~NETInterface();

		//	Inherited:
		//		NEClassBase:
	public:
		virtual const NETString& getName() const;
		virtual const NEClassBaseList& getSuperClasses() const;
		virtual const type_bool& isRegistered() const;
		virtual const NEClassBaseList& getSubClasses() const;
		virtual NEObject& instantiate() const;
		//				NEObject:
	public:
		virtual const NEClassBase& getClass() const;
		virtual NEObject& clone() const;

		//	Statics:
	public:
		static const NEClassBaseList& getSubClassesStatically();
		static const NEClassBaseList& getSuperClassesStatically();
		static const NETString& getNameStatically();
		static const type_bool& isRegisteredStatically();
		static const NEClassBase& getClassStatically();
	};
}

#include "NETInterface.inl"
#include "Specialization.inl"