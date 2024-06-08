#include "thread.hpp"
#include "../loader/slot/slotLoader.hpp"
#include "../loader/errReport.hpp"
#include "../ast/node.inl"
#include "../ast/baseFunc.hpp"
#include "../builtin/pkgs/default/defaultPack.hpp"
#include "../ast/dumScope.hpp"

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

    me::thread(): _ex(new errReport()) {} // for singleton
    me::thread(const errReport& ex): _ex(ex) {}

    thread& me::get() {
        return *_instance;
    }

    namespace {
        class dumFrames : public frames {
            NAMU(CLASS(dumFrames, frames))

        public:
            using super::add;
            nbool add(const iter& e, const frame& new1) override { return true; }
            nbool add(nidx n, const frame& new1) override { return true; }
            void add(const iter& here, const iter& from, const iter& to) override {}

            using super::set;
            using tarrayable<frame>::set;
            nbool set(const iter& at, const frame& new1) override { return true; }
            nbool set(nidx n, const frame& new1) override { return true; }
        };
        class dumThread : public thread {
            NAMU(CLASS(dumThread, thread))

        public:
            dumThread() {
                super::setEx(dummyErrReport::singletone);
            }

        public:
            void setEx(const errReport& new1) override {}
            void rel() override {}

        protected:
            frames& _getFrames() override {
                static dumFrames inner;
                return inner;
            }
        };
    }

    void me::set(thread* new1) {
        static dumThread inner;
        _instance = new1 ? new1 : &inner;
    }
    void me::set(thread& new1) { set(&new1); }
    void me::set() { set(nullptr); }

    const instancer& me::getInstancer() {
        return instancer::get();
    }

    errReport& me::getEx() { return *_ex; }
    void me::setEx(const errReport& new1) { _ex.bind(new1); }

    // node:
    scope& me::subs() {
        static dumScope inner;
        return inner;
    }

    priorType me::prioritize(const args& a) const {
        return NO_MATCH;
    }

    void me::rel() {
        _frames.rel();
    }

    frames& me::_getFrames() {
        return _frames;
    }

    frame& me::_getNowFrame() {
        return _getFrames()[_getFrames().len() - 1];
    }

    void me::_loadBuiltIns(nmap& tray) const {
        tray.add(defaultPack().subs());
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

    void me::dump() const {
        // TODO:
    }
}
