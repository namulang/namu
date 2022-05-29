#include "thread.hpp"
#include "../loader/pack/packLoader.hpp"
#include "../loader/errReport.hpp"
#include "../ast/node.inl"
#include "../ast/func.hpp"

namespace wrd {

    WRD_DEF_ME(thread)

    const packs& me::getSystemPacks() {
        static tstr<packs> inner;

        if(!inner) {
            packLoader loader;

            WRD_I("initiates loading system packs.");
            errReport report;
            inner = loader.setReport(report).addPath("pack/").load();
            WRD_I("%d system packs has been loaded.", inner->len());

#if WRD_IS_DBG
            WRD_I("next following is list for them.");
            for(const auto& pak : *inner) {
                if(nul(pak)) {
                    WRD_E("cast isn't type of pack&");
                    continue;
                }

                const manifest& mani = pak.getManifest();
                WRD_DI(" - %s v%s", mani.name.c_str(), mani.version.c_str());
            }
#endif
        }

        return *inner;
    }

    str me::run(const ucontainable& args) {
        // TODO: args validness check.

        // find 'main' func:
        func& fun = _root->sub<func>("main"); // TODO: support generic type of str[]
        if(nul(fun))
            return WRD_E("there is no 'main' func."), str();

        thread* prev = *_get();
        *_get() = this;
        str res = fun.run(args);
        *_get() = prev;

        return res;
    }

    me::thread() {} // for singleton
    me::thread(const node& root): _root(root) {}

    thread& me::get() {
        return **_get();
    }

    const instancer& me::getInstancer() {
        return instancer::get();
    }

    // node:
    nbicontainer& me::subs() {
        if(!_root) return nulOf<nbicontainer>();

        return _root->subs();
    }

    wbool me::canRun(const ucontainable& args) const { return false; }

    void me::rel() { _frames.rel(); }

    frames& me::_getFrames() {
        return _frames;
    }
    frame& me::_getNowFrame() {
        return _frames[_frames.len() - 1];
    }

    thread** me::_get() {
        thread_local static thread* inner = new thread();
        return &inner;
    }
}
