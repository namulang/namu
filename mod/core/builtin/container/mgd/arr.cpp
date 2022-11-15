#include "arr.hpp"
#include "../../../visitor/visitor.hpp"
#include "../../../visitor/generalizer.hpp"
#include "../../../bridge/cpp.hpp"

namespace namu {

    NAMU(DEF_ME(arr), DEF_VISIT())

    namespace {
        typedef tucontainable<node>::iter niter;
        typedef tcppBridge<niter> __superMgdIter;
        class _nout mgdIter : public __superMgdIter {
            NAMU(CLASS(mgdIter, __superMgdIter))

        public:
            mgdIter(niter* real): super(real) {}

        public:
            using super::subs;
            nbicontainer& subs() override {
                static super* inner = nullptr;
                if(nul(inner)) {
                    inner = new super();
                    inner->func("isEnd", &niter::isEnd);
                    inner->func("next", &niter::next);
                    inner->func<node&>("get", &niter::get);
                }

                return inner->subs();
            }
        };

        class iterateFunc : public func {
            NAMU(CLASS(iterateFunc, func))

        public:
            const node& getRet() const override {
                static mgdIter inner(nullptr);
                return inner;
            }

            const params& getParams() const override {
                static params inner;
                if(inner.len() <= 0)
                    inner.add(new param("step", *new nInt()));

                return inner;
            }

            str run(const args& a) override {
                const params& ps = getParams();
                if(a.len() != ps.len()) return NAMU_W("a.len(%d) != ps.len(%d)", a.len(), ps.len()), str();
                arr& meObj = a.getMe().cast<arr>();
                if(nul(meObj)) return NAMU_E("meObj as arr == null"), str();

                str eval = a[0].as(ps[0].getOrigin().as<node>());
                if(!eval)
                    return NAMU_E("evaluation of arg[%s] -> param[%s] has been failed", a[0].getType().getName().c_str(), ps[0].getType().getName().c_str()), str();

                nint step = eval->cast<nint>();
                return new mgdIter(new niter(meObj.get().iterate(step)));
            }
        };

        class getElemTypeFunc : public func {
            NAMU(CLASS(getElemTypeFunc, func))

        public:
            getElemTypeFunc(): _ret(new getExpr("T")) {}

        public:
            const node& getRet() const override {
                return *_ret;
            }

            str run(const args& a) override {
                return *_ret;
            }

            nbool setRet(const node& newRet) override {
                return _ret.bind(newRet);
            }

        private:
            str _ret;
        };
    }

    me::arr(): super(new narr()), _type(new obj()) {}
    me::arr(const node& newType): super(new narr()), _type(newType) {}

    node& me::operator[](nidx n) {
        return get()[n];
    }

    ncnt me::len() const {
        return get().len();
    }

    nbool me::has(nidx n) const {
        return get().has(n);
    }

    node& me::get(nidx n) {
        return get().get(n);
    }

    nbool me::set(const iter& at, const node& new1) {
        str ased = new1.asImpli(*_type);
        if(!ased) return false;
        return get().set(at, *ased);
    }
    nbool me::set(nidx n, const node& new1) {
        str ased = new1.asImpli(*_type);
        if(!ased) return false;
        return get().set(n, *ased);
    }

    nbool me::add(const iter& at, const node& new1) {
        str ased = new1.asImpli(*_type);
        if(!ased) return false;

        return get().add(at, *ased);
    }

    nbool me::add(nidx n, const node& new1) {
        str ased = new1.asImpli(*_type);
        if(!ased) return false;

        return get().add(n, *ased);
    }

    void me::add(const iter& here, const iter& from, const iter& to) {
        get().add(here, from, to);
    }

    //  del:
    nbool me::del(nidx n) {
        return get().del(n);
    }

    nbool me::del(const iter& it) {
        return get().del(it);
    }

    nbool me::del(const iter& from, const iter& to) {
        return get().del(from, to);
    }

    //  etc:
    clonable* me::deepClone() const {
        me* ret = (me*) clone();
        ret->rel();
        tstr<tnarr<node>> cloned((tnarr<node>*) get().deepClone());
        ret->get().add(*cloned);
        return ret;
    }

    void me::rel() {
       get().rel();
    }

    me::iteration* me::_onMakeIteration(ncnt step) const {
        return get()._onMakeIteration(step);
    }

    scope& me::_defGeneric(const type* key) {
        tstr<scope> clone = _getOriginScope().deepClone();
        clone->add("getElemType", new getElemTypeFunc());

        _cache.insert({key, clone}); // this avoids infinite loop.

        generalizer g;
        g.add(*new param(TYPENAME, *_type))
         .setRoot(*this)
         .start();

        return *clone;
    }

    scope& me::_getOriginScope() {
        static super* inner = nullptr;
        if(nul(inner)) {
            inner = new super();
            inner->genericFunc("len", &narr::len);
            inner->genericFunc("rel", &narr::rel);
            inner->genericFunc<nbool, nidx>("del", &narr::del);
            inner->genericFunc<nbool, const node&>("add", &narr::add);
            inner->genericFunc<nbool, nidx, const node&>("add", &narr::add);
            inner->genericFunc<nbool, nidx, const node&>("set", &narr::set);
            inner->genericFunc<node&, nidx>("get", &narr::get);
            inner->genericFunc("has", &narr::has);
            inner->subs().add("iterate", new iterateFunc());
        }

        return inner->subs().cast<scope>();
    }
}
