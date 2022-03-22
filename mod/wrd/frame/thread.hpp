#pragma once

#include "../builtin/container/mgd/tarr.hpp"
#include "frame.hpp"

namespace wrd {

    class packLoader;
    typedef tnarr<frame> frames;

    class thread : public node {
        WRD(CLASS(thread, node))
        friend class obj; // for frames.
        friend class mgdFunc; // for frames.
        friend class blockExpr; // for frames.
        friend class defVarExpr; // for frames
        friend class verifier;
        friend class returnExpr;
        friend class func; // for frames.

    private:
        thread() {} // for singleton
        thread(const node& root): _root(root) {}

    public:
        const frames& getFrames() const WRD_UNCONST_FUNC(_getFrames())
        const frame& getNowFrame() const WRD_UNCONST_FUNC(_getNowFrame())

        static thread& get() {
            return **_get();
        }

        static const instancer& getInstancer() {
            return instancer::get();
        }

        // node:
        nucontainer& subs() override {
            if(!_root) return nulOf<nucontainer>();

            return _root->subs();
        }

        wbool canRun(const ucontainable& args) const override { return false; }

        str run(const ucontainable& args) override;

        void rel() override { _frames.rel(); }

        const packs& getSystemPacks();

    protected:
        frames& _getFrames() {
            return _frames;
        }
        frame& _getNowFrame() {
            return _frames[_frames.len() - 1];
        }

    private:
        static thread** _get() {
            thread_local static thread* inner = new thread();
            return &inner;
        }

    private:
        frames _frames;
        str _root;
    };

}
