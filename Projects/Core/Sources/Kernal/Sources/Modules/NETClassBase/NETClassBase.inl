#pragma once

#include "../NETSuperClassDeterminder/NETSuperClassDeterminder.hpp"
#include "../NETMetaClassDeterminder/NETMetaClassDeterminder.hpp"
#include "../NETTraitDeterminder/NETTraitDeterminder.hpp"
#include "../NEClassBase/NEClassBase.hpp"

namespace NE
{
	//	What is this:
	//		When NETClass is templated with some parameter type T,
	//		it's a problem to provide metaclass of NETClass. (of course, 
	//		because NETClass is a kind of metaclass, giving metaclass of
	//		metaclass is the problem mentioned above)
	//		The reason which this going to be a problem is templating reculsively.
	//		Just imagine NETClass<T> that is returning NETClass<NETClass<T> for
	//		its metaclass.
	//		so, this get crack the codes. to prevent this, we replace metaclass
	//		to NETMetaClass. Dummy.
	//		All NETClass<T> will return NETClass<NETMetaClass>() for getClass()
	//		method.
	class NE_DLL NETMetaClass {};

	///	@class	NETClassBase
	///	@brief	Implemented common method and data among specialized from NETClassBase
	///			class.
	template <typename T>
	class NETClassBase : public NEClassBase
	{
		NE_DECLARE_CLASS_ONLY(NETClassBase, NEClassBase)

	public:
		virtual const type_bool& isRegistered() const;
		virtual const NETString& getName() const;
		virtual const NEClassBaseList& getSuperClasses() const;
		virtual const NEClassBaseList& getChildrenClasses() const;
		virtual type_bool isMetaClassDefined() const;
		virtual type_bool isInstantiable() const;
		virtual type_bool isTemplate() const;
		virtual type_bool isBuiltInClass() const;
		virtual const NEClassBase& getTraitClass() const;
		///	@brief	returns this ClassIdentifer.
		///			As you can inspect codes, this returns the static variable.
		virtual const NEHeader& getHeader() const;
		virtual const NEPackage& getPackage() const;

	public:
		static const type_bool& isRegisteredStatically();
		static const NEClassBaseList& getSuperClassesStatically();
		static const NEClassBaseList& getChildrenClassesStatically();
		static const NEHeader& getHeaderStatically();
		static const NETString& getNameStatically();
		static const type_id& getIdStatically();
		static type_bool isMetaClassDefinedStatically();
		static type_bool isInstantiableStatically();
		static type_bool isTemplateStatically();
		static type_bool isBuiltInClassStatically();
		static const NEClassBase& getTraitClassStatically();
	};
}