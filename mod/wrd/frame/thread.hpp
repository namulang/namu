#pragma once

#include "stackFrame.hpp"

namespace wrd {

    class packLoader;

    class thread : public node {
        WRD(CLASS(thread, node))
        friend class mgdObj; // for stackFrame.
        friend class mgdFunc; // for stackFrame.
        friend class blockExpr; // for stackFrame.
        friend class defVarExpr; // for stackFrame
        friend class verifier;

    private:
        thread() {} // for singleton
        thread(const node& root): _root(root) {}

    public:
        const stackFrame& getStackFrame() const {
            return _sframe;
        }

        static thread& get() {
            return **_get();
        }

        static const instancer& getInstancer() {
            return instancer::get();
        }

        // node:
        ncontainer& subs() override {
            if(!_root) return nulOf<ncontainer>();

            return _root->subs();
        }

        wbool canRun(const containable& args) const override { return false; }

        str run(const containable& args) override;

        void rel() override { _sframe.rel(); }

        const packs& getSystemPacks();

    protected:
        stackFrame& _getStackFrame() {
            return _sframe;
        }

    private:
        static thread** _get() {
            thread_local static thread* inner = new thread();
            return &inner;
        }

    private:
        stackFrame _sframe;
        str _root;
    };

}
