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

namespace NE
{
	template <typename T>
	class NETInterface : public NEClassBase
	{
		//	Declarations:
	public:
		typedef NETInterface<T> This;
		typedef NEClassBase Super;
		typedef T Trait;
		typedef typename Trait::Super SuperTrait;
		typedef NETInterface<SuperTrait> SuperClass;

		//	Constructors:
	public:
		NETInterface();
		NETInterface(const NETInterface& source);

		//	Destructors:
	public:
		virtual ~NETInterface();

		//	Interfaces:
		//		Virtuals:
	public:
		virtual const NETString& getName() const;
		virtual const NEClassBaseList& getSuperClasses() const;
		virtual const type_bool& isRegistered() const;
		virtual type_bool isInstantiatable() const;
		virtual const NEClassBaseList& getSubClasses() const;
		virtual NEObject& instantiate() const;
		//			Inherited:
		//				NEObject:
	public:
		virtual NEObject& clone() const;

	public:
		const NEClassBase& getSuperClass() const;

		//	Statics:
	public:
		static const NEClassBaseList& getSubClassesStatically();
		static const NEClassBaseList& getSuperClassesStatically();
		static const NETString& getNameStatically();
		static const type_bool& isRegisteredStatically();
	};
}

#include "NETInterface.inl"
#include "Specialization.inl"