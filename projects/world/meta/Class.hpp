#pragma once

#include "../base/Composit.hpp"

namespace wrd
{
    template <typename T> class TStrong;
    class Classes; // Container of Class
    class Origin;
    class Array;

    class Class : public Composit
    {	WRD_CLASS_DECL(Class, Composit) // World에 visible해야 하기 때문이다.
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
		//	Node:
		//	means there is no origin or we can't designate origin.
		virtual WRD_LAZY_METHOD(Origin, getOrigin, const)
		virtual const Array& getVars() const; // class can't include Array. we can use WRD_LAZY_METHOD here.
		//	State:
		virtual Res& init();
		virtual wbool isInit() const;
		//	Thing:
        virtual const Class& getSuper() const;
        virtual wbool isSuper(const Class& it) const;

    protected:
		//	Composit:
        virtual Res& _initNodes();
    };
}
