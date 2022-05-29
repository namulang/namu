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
            wbool isImpli(const type& to) const override;
            str asImpli(const node& from, const type& to) const override;
        };

        WRD(ADT(expr, node, exprType))
        friend class exprMaker;
        friend struct ::exprTest;

    public:
        expr();

    public:
        using super::subs;
        nbicontainer& subs() override;

        /// run of expr class get treated like 'evaluate' in wrd.
        /// it should not take any argument to run()
        using super::canRun;
        wbool canRun(const ucontainable& args) const override;
        const src& getSrc() const;
        const point& getPos() const;

    protected:
        void _setSrc(const src& newSrc);
        void _setPos(const point& newPos);

    private:
        tstr<src> _src;
        point _pos;
    };
}
