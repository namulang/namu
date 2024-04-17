#include "thread.hpp"
#include "../loader/slot/slotLoader.hpp"
#include "../loader/errReport.hpp"
#include "../ast/node.inl"
#include "../ast/baseFunc.hpp"
#include "../builtin/func.hpp"

namespace namu {

    NAMU_DEF_ME(thread)

    thread_local thread* me::_instance = nullptr;

    const nmap& me::getSlots() const {
        static tstr<nmap> _inner;
        if(!_inner)
            _inner = _initSlots();
        return *_inner;
    }

    str me::run(const args& a) { return str(); }

    me::thread(): _rpt(new errReport()) {} // for singleton
    me::thread(const node& root): _root(root), _rpt(new errReport()) {}

    thread& me::get() {
        return *_instance;
    }

    void me::set(thread* new1) {
        _instance = new1;
    }
    void me::set(thread& new1) { set(&new1); }
    void me::set() { set(nullptr); }

    const instancer& me::getInstancer() {
        return instancer::get();
    }

    errReport& me::getReport() {
        return *_rpt;
    }

    void me::setReport(const errReport& newRpt) {
        _rpt.bind(newRpt);
    }

    // node:
    nbicontainer& me::subs() {
        if(!_root) return nulOf<nbicontainer>();

        return _root->subs();
    }

    priority me::prioritize(const args& a) const {
        return NO_MATCH;
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

    void me::_loadBuiltIns(nmap& tray) const {
        tray.add("print", *new printFunc<nStr>());
        tray.add("input", *new inputFunc());
    }

    tstr<nmap> me::_initSlots() const {
        tstr<nmap> ret;
        NAMU_I("initiates loading system slots.");
        ret.bind(new nmap());
        errReport report;
        slotLoader().setReport(report).setBaseSlots(*ret)
#ifdef NAMU_BUILD_PLATFORM_IS_LINUX
            .addPath("/usr/share/namu/pack/")
#endif
            .addPath("pack/")
            .load();

        _loadBuiltIns(*ret);

        NAMU_I("%d system slots has been loaded.", ret->len());

#if NAMU_IS_DBG
        NAMU_I("next following is list for them.");
        for(const auto& s : *ret) {
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
        return ret;
    }
}
