#include "thread.hpp"
#include "../loader/slot/slotLoader.hpp"
#include "../loader/errReport.hpp"
#include "../ast/node.inl"
#include "../ast/baseFunc.hpp"
#include "../builtin/func.hpp"

namespace namu {

    NAMU_DEF_ME(thread)

    const nmap& me::getSlots() const {
        static tstr<nmap> inner;

        if(!inner) {
            NAMU_I("initiates loading system slots.");
            inner.bind(new nmap());
            errReport report;
            slotLoader().setReport(report).setBaseSlots(*inner)
#ifdef NAMU_BUILD_PLATFORM_IS_LINUX
                .addPath("/usr/share/namu/pack/")
#endif
                .addPath("pack/")
                .load();

            _loadBuiltIns(*inner);

            NAMU_I("%d system slots has been loaded.", inner->len());

#if NAMU_IS_DBG
            NAMU_I("next following is list for them.");
            for(const auto& s : *inner) {
                if(nul(s)) {
                    NAMU_E("cast isn't type of slot&");
                    continue;
                }

                const slot& sl = s.cast<slot>();
                if(nul(sl)) continue;

                const manifest& mani = sl.getManifest();
                NAMU_DI(" - %s v%s", mani.name.c_str(), mani.version.c_str());
            }
#endif
        }

        return *inner;
    }

    str me::run(const args& a) {
        // TODO: a validness check.

        // find 'main' func:
        baseFunc& fun = _root->sub<baseFunc>("main"); // TODO: support generic type of str[]
        if(nul(fun))
            return NAMU_E("there is no 'main' func."), str();

        thread* prev = *_get();
        *_get() = this;
        str res = fun.run(a);
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

    me::priority me::prioritize(const args& a) const {
        return node::NO_MATCH;
    }

    void me::rel() {
        _frames.rel();
    }

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

    void me::_loadBuiltIns(nmap& tray) const {
        tray.add("print", *new printFunc<nStr>());
        tray.add("input", *new inputFunc());
    }
}
