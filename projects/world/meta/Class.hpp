#pragma once

#include "../base/Composit.hpp"

namespace wrd
{
    class Classes; // Container of Class
    class Array;

    class Class : public Composit
    {	//	we can't put WRD_CLASS_DEF here:
		//		it'll generates TClass<TClass<TClass<....> infinitely.
		WRD_INHERIT(Class, Composit) // World에 visible해야 하기 때문이다.
	public:
		virtual const Class& getClass() const;
		TStrong<This> clone() const;
        friend class Interpreter; // for interpreter class which can use _getNodes().

    public:
        wbool operator==(const This& rhs) const;
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
		virtual wbool isInit() const;
		//	Thing:
        virtual const Class& getSuper() const;
        virtual wbool isSuper(const Class& it) const;

    protected:
		//	Class:
		Classes& _getSupers();
		Classes& _getSubs();
		//	Composit:
        virtual Res& _initNodes();
		//	Thing:
		virtual TStrong<Instance> _clone() const;
    };
}
