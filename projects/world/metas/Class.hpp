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
    { //    World에 visible해야 하기 때문이다.
        // TODO: classname
        /* remove this*/ typedef Class This;
        friend class Interpreter; // for interpreter class which can use _getNodes().

    public:
        wbool operator==(const This& rhs) const;
        wbool operator!=(const This& rhs) const;

    public:
        virtual wbool isTemplate() const = 0;
        virtual wbool isADT() const = 0;
        virtual TStrong<Instance> instance() const = 0;
        virtual const String& getName() const = 0;
        virtual const Classes& getSupers() const = 0;
        const Class& getSuper() const;
        virtual const Classes& getSubs() const = 0;
        virtual const Class& getClass() const;
        virtual wbool isSuper(const Class& it) const;
        virtual Result& init();
        const Classes& getLeafs() const;
        virtual const Origin& getOrigin();

    protected:
        virtual Result& _initNodes();
        virtual Result& _setInit(wbool new1) = 0;
    };
}
