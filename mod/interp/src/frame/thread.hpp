#pragma once

#include "stackFrame.hpp"

namespace wrd {

    class packLoader;

    class thread : public node {
        WRD(CLASS(thread, node))
        friend class obj; // to access stackFrame.
        friend class mgdFunc; // to access stackFrame.
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
        str run(const ncontainer& args) override { return str(); }

        void rel() override { _sframe.rel(); }

        const packs& getPackLoader();

    protected:
        stackFrame& _getStackFrame() {
            return _sframe;
        }

    private:
        stackFrame _sframe;
    };

}
