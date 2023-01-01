#pragma once

#include "visitInfo.hpp"

namespace namu {

    class retStateExpr;
#define X(T) class T;
#   include "visitee.inl"
#undef X
    class _nout visitor {
        NAMU(ME(visitor))

    public:
        visitor(): _isLog(false) {}

    public:
        me& setRoot(node& root) {
            _root.bind(root);
            return *this;
        }
        me& setLog(nbool toShow) {
            _isLog = toShow;
            return *this;
        }

        virtual void start();

#define X(T) \
        virtual void visit(visitInfo i, T& me); \
        virtual void onVisit(visitInfo i, T& me); \
        virtual void onLeave(visitInfo i, T& me);
#   include "visitee.inl"
#undef X

        virtual void visit(visitInfo i, node& me);
        virtual void onVisit(visitInfo i, node& me);
        virtual void onLeave(visitInfo i, node& me);

        //  traverse:
        //      generalized-way:
        virtual void onTraverse(visitInfo i, node& me);
        //      specific-way:
        virtual void onTraverse(visitInfo i, asExpr& a);
        virtual void onTraverse(visitInfo i, assignExpr& a);
        virtual void onTraverse(visitInfo i, blockExpr& b);
        virtual void onTraverse(visitInfo i, defAssignExpr& d);
        virtual void onTraverse(visitInfo i, FAOExpr& f);
        virtual void onTraverse(visitInfo i, getExpr& e);
        virtual void onTraverse(visitInfo i, returnExpr& b);
        virtual void onTraverse(visitInfo i, runExpr& e);
        virtual void onTraverse(visitInfo i, mgdFunc& f);
        virtual void onTraverse(visitInfo i, frame& f);
        virtual void onTraverse(visitInfo i, forExpr& f);
        virtual void onTraverse(visitInfo i, retStateExpr& r);

    private:
        nbool _isLog;
        str _root;
    };
}
