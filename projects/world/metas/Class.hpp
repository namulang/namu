#pragma once

#include "../bases/Node.hpp"

namespace wrd
{
    template <typename T>
    class TStrong;
    class Classes; // Container of Class
    class Origin;
    class Array;
    class Class : public Node
    {	WRD_CLASS(Class, Node) // World에 visible해야 하기 때문이다.
        // TODO: classname
        /* remove this*/ typedef Class This;
        friend class Interpreter; // for interpreter class which can use _getNodes().

    public:
        wbool operator==(const This& rhs) const;
        wbool operator!=(const This& rhs) const;

    public:
		//	Class:
        virtual wbool isTemplate() const = 0;
        virtual wbool isADT() const = 0;
        virtual const Classes& getSubs() const = 0;
        virtual const String& getName() const = 0;
        virtual const Classes& getSupers() const = 0;
		const Classes& getLeafs() const;
		//	Node:
		//	means there is no origin or we can't designate origin.
		virtual WRD_LAZY_METHOD(Origin, getOrigin, const, WRD_VOID)
		//	State:
		virtual Result& init();
		virtual wbool isInit() const;
		//	Instance:
        virtual TStrong<Instance> instance() const = 0;
		//	Thing:
        virtual const Class& getSuper() const;
        virtual const Class& getClass() const;
        virtual wbool isSuper(const Class& it) const;

    protected:
		//	Composit:
        virtual Result& _initNodes();
    };
}
