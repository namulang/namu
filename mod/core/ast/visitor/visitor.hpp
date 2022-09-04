#pragma once

#include "visitInfo.hpp"

namespace namu {

#define X(T) class T;
#   include "visitee.inl"
#undef X
    class visitor {
        NAMU(ME(visitor))

    public:
#define X(T) \
        virtual void visit(visitInfo i, T& me); \
        virtual void onVisit(visitInfo i, T& me); \
        virtual void onLeave(visitInfo i, T& me);
#   include "visitee.inl"
#undef X

        virtual void visit(visitInfo i, node& me);
        virtual void onVisit(visitInfo i, node& me);
        virtual void onLeave(visitInfo i, node& me);

        virtual void start(node& root);

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
    };
}
