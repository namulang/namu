#pragma once

#include "../base/Composit.hpp"

namespace wrd
{
    class Classes; // Container of Class
    class Array;

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
        virtual wbool isSuper(const Class& it) const;

    protected:
		//	Class:
		Classes& _getSupers();
		Classes& _getSubs();
		//	Composit:
        virtual Res& _initNodes();
    };
}
