#include "seq.hpp"
#include "../../../visitor/visitInfo.hpp"
#include "../../../visitor/visitor.hpp"
#include "../../../bridge/cpp.hpp"

namespace namu {

    NAMU(DEF_ME(seq), DEF_VISIT())

    me::seq(nint start, nint end): super(new nseq(start, end)) {}
    me::seq(nint start, nint end, nint step): super(new nseq(start, end, step)) {}

    namespace {
        typedef tucontainable<nint>::iter niter;
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
                    inner->func<nint&>("get", &niter::get);
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
                seq& meObj = a.getMe().cast<seq>();
                if(nul(meObj)) return NAMU_E("meObj as arr == null"), str();

                str eval = a[0].as(ps[0].getOrigin().as<node>());
                if(!eval)
                    return NAMU_E("evaluation of arg[%s] -> param[%s] has been failed", a[0].getType().getName().c_str(), ps[0].getType().getName().c_str()), str();

                nint step = eval->cast<nint>();
                static tucontainable<nint>::iter (tucontainable<nint>::*specifier)(ncnt) const = &seq::iterate;
                return new mgdIter(new niter((meObj.get().*specifier)(step)));
            }
        };

        class getElemTypeFunc : public func {
            NAMU(CLASS(getElemTypeFunc, func))

        public:
            const node& getRet() const override {
                static nInt inner;
                return inner;
            }

            str run(const args& a) override {
                return getRet();
            }
        };
    }

    nbicontainer& me::subs() {
        static super* inner;
        if(nul(inner)) {
            inner = new super();
            inner->func("len", &nseq::len);
            inner->func("get", &nseq::get);
            inner->func("has", &nseq::has);
            inner->subs().add("iterate", new iterateFunc());
            inner->subs().add("getElemType", new getElemTypeFunc());
        }

        return inner->subs();
    }

    me::iteration* me::_onMakeIteration(ncnt step) const {
        return get()._onMakeIteration(step);
    }
}
