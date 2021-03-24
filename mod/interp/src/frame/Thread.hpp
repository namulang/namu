#pragma once

#include "StackFrame.hpp"

namespace wrd {

    class Thread : public Node {
        WRD_CLASS(Thread, Node)
        friend class Obj; // to access StackFrame.
        friend class Func; // to access StackFrame.

    private:
        Thread() {} // singletone.

    public:
        const StackFrame& getStackFrame() const {
            return _sframe;
        }

        static Thread& get() {
            thread_local static Thread inner;
            return inner;
        }

        const Instancer& getInstancer() const {
            return Instancer::get();
        }

        // Node:
        NContainer& subs() override {
            // TODO: should fill with func, not sframe itself.
            return _sframe.getNative();
        }
        wbool canRun(const WTypes& types) const override { return false; }
        Str run(NContainer& args) override { return Str(); }

        void rel() override { _sframe.rel(); }

    private:
        StackFrame _sframe;
    };

}
