#pragma once

#pragma message("NETClassMetaClass.hpp - 1")

#include "../NEClassBase/NEClassBase.hpp"

#pragma message("NETClassMetaClass.hpp - 2")

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
	class NE_DLL NETClassMetaClass : public NEClassBase
	{
		NE_DECLARE_CLASS_ONLY(NETClassMetaClass, NEClassBase)

		//	Overrided:
		//		NEClassBase:
	public:
		virtual type_bool isInstantiable() const;
		virtual type_bool isTemplate() const;
		virtual type_bool isMetaClassDefined() const;
		virtual const type_bool& isRegistered() const;
		virtual const NEClassBase& getTraitClass() const;
		virtual const NEClassBaseList& getSuperClasses() const;
		virtual const NEClassBaseList& getChildrenClasses() const;
		virtual const NETString& getName() const;
		virtual NEObject& instantiate() const;
		virtual const NEHeader& getHeader() const;

	public:
		virtual const type_id& getId() const;

		//		NEObject:
	public:
		virtual type_result isValid() const;
		virtual void release();
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

		//	Statics:
	public:
		static const type_bool& isRegisteredStatically();
		static type_bool isMetaClassDefinedStatically();
		static type_bool isInstantiableStatically();
		static type_bool isTemplateStatically();
		static type_bool isBuiltInClassStatically();
		static const NEClassBase& getTraitClassStatically();
		static const NEClassBaseList& getSuperClassesStatically();
		static const NEClassBaseList& getChildrenClassesStatically();
		static const NEHeader& getHeaderStatically();
		static const NETString& getNameStatically();
		static const type_id& getIdStatically();

	private:
		virtual const NEPackagePtr& _getPackage() const;
	};
}