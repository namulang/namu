#pragma once

#include "src.hpp"
#include "point.hpp"

struct exprTest;

namespace wrd {

    class _wout expr : public node {
    public:
        class exprType : public wtype {
            WRD(ME(exprType, wtype))

        public:
            using super::asImpli;
            wbool isImpli(const type& to) const override {
                return to.isSub<node>();
            }

            str asImpli(const node& from, const type& to) const override {
                return str(((node&) from).run());
            }
        };

        WRD(INTERFACE(expr, node, exprType))
        friend class exprMaker;
        friend struct ::exprTest;

    public:
        expr(): _pos{0, 0} {}

    public:
        using super::subs;
        nbicontainer& subs() override;

        /// run of expr class get treated like 'evaluate' in wrd.
        /// it should not take any argument to run()
        using super::canRun;
        wbool canRun(const ucontainable& args) const override { return args.len() == 0; }
        const src& getSrc() const { return *_src; }
        const point& getPos() const { return _pos; }

    protected:
        void _setSrc(const src& newSrc) {
            _src.bind(newSrc);
        }

        void _setPos(const point& newPos) {
            _pos = newPos;
        }

    private:
        tstr<src> _src;
        point _pos;
    };
}
