#pragma once

#include "src.hpp"
#include "point.hpp"

struct exprTest;

namespace namu {

    class _nout expr : public node {
    public:
        // expr can be casted to node. it's proxy of a node.
        class exprType : public ntype {
            WRD(ME(exprType, ntype))

        public:
            using super::asImpli;
            nbool isImpli(const type& to) const override { return to.isSub<node>(); }
            str asImpli(const node& from, const type& to) const override { return str(((node&)from).run()); }
        };

        WRD(ADT(expr, node, exprType))
        friend class exprMaker;
        friend struct ::exprTest;

    public:
        using super::subs;
        nbicontainer& subs() override;

        nbool isImpli(const type& to) const override {
            return getEval().isSub(to);
        }
        virtual str asImpli(const type& to) const override {
            me* unconst = const_cast<me*>(this);
            return str((unconst->run()->asImpli(to)));
        }

        /// run of expr class get treated like 'evaluate' in namu.
        /// it should not take any argument to run()
        using super::canRun;
        nbool canRun(const ucontainable& args) const override;
        const src& getSrc() const;
        const point& getPos() const override;
        void setPos(const point& newPos) override;

    protected:
        void _setSrc(const src& newSrc);

    protected:
        tstr<src> _src;
        point _pos;
    };
}
