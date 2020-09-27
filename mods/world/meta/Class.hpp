#pragma once

#include "../base/Composit.hpp"

namespace wrd
{
    class Classes; // Container of Class
    class Array;

	///	@remark	Class returning TClass<Class> as result of getClass()
	///			because this func always returns metaclass no matter of what This type is,
	///			users need to care about getting meta of metaclass on calling getClass().
	///			for example,
	///				Thing& thing1 = ...; // let's assume that got from outside.
	///				Object obj;
	///
	///				wbool compare = obj.isSub(thing1.getClass()); // user intend to get class of Thing.
	///				// however, value 'compare' will definitely be false if
	///				// thing was actually a retrived one by calling Thing.getClass() before.
	///
	///				// because Class::getClass() will return TClass<TClass<T> >,
	///				// that stmt will be translated that checks object vs TClass<T>.
    class Class : public Composit
    {	WRD_CLASS_DECL(Class, Composit)
        friend class Interpreter; // for interpreter class which can use _getNodes().
    public:
        virtual wbool operator==(const This& rhs) const;
        wbool operator!=(const This& rhs) const;

    public:
		//	Class:
        virtual wbool isTemplate() const = 0;
        virtual wbool isADT() const = 0;
        virtual const Classes& getSubs() const = 0;
        virtual const Str& getName() const = 0;
        virtual const Classes& getSupers() const = 0;
        virtual TStrong<Instance> instance() const = 0;
		const Classes& getLeafs() const;
		virtual const Array& getVars() const; // class can't include Array. we can use WRD_LAZY_METHOD here.
		virtual wcnt getSize() const = 0;
		//	State:
		virtual Res& init();
		//	Thing:
        virtual const Class& getSuper() const = 0;
        wbool isSuperCls(const Class& it) const;
		template <typename T> wbool isSuperCls() const { return isSuperCls(T::getClassStatic()); }
		wbool isSubCls(const Class& it) const { return it.isSuperCls(*this); }
		template <typename T> wbool isSubCls() const { return T::getClassStatic().isSuperCls(*this); }

    protected:
		//	Class:
		Classes& _getSupers();
		Classes& _getSubs();
		//	Composit:
        virtual Res& _initNodes();
    };
}
