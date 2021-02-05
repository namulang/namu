#pragma once

#include "../common.hpp"

namespace wrd {

    class Node : public Instance {
        WRD_CLASS(Node, Instance)
    public:
        wbool isInit() const {
            return _isInit;
        }
        virtual wbool init() {
            if(isInit()) return true;

            _setInit(true)
            return true;
        }
        virtual void rel() {
            _setInit(false);
        }

    protected:
        void _setInit(wbool newVal) { _isInit = newVal; }

    private:
        wbool _isInit;
    };

    class Chain {
    };
    class TRef {
    };
    typedef TRef<Node> Ref;
    class Scope : public Node {
    };
    class Func : public Scope {
    };
    /*
    class Obj : public Scope {
    };
    class WType : public Type {
    };
    class Frame {
    };
    class StackFrame {
    };*/
}
