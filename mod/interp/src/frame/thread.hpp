#pragma once

#include "stackFrame.hpp"

namespace wrd {

    class thread : public node {
        WRD_CLASS(thread, node)
        friend class obj; // to access stackFrame.
        friend class func; // to access stackFrame.
        friend class frameInteract; // to access stackFrame.

    private:
        thread() {} // singletone.

    public:
        const stackFrame& getStackFrame() const {
            return _sframe;
        }

        static thread& get() {
            thread_local static thread inner;
            return inner;
        }

        const instancer& getInstancer() const {
            return instancer::get();
        }

        // node:
        ncontainer& subs() override {
            // TODO: should fill with func, not sframe itself.
            return _sframe.getNative();
        }
        wbool canRun(const wtypes& types) const override { return false; }
        str run(ncontainer& args) override { return str(); }

        void rel() override { _sframe.rel(); }

    protected:
        stackFrame& _getStackFrame() {
            return _sframe;
        }

    private:
        stackFrame _sframe;
    };

}
