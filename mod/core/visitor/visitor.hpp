#pragma once

#include "visitInfo.hpp"
#include "../loader/errReport.hpp"

namespace namu {

    class retStateExpr;
#define X(T) class T;
#   include "visitee.inl"
#undef X
    class _nout visitor {
        NAMU(ME(visitor))

    public:
        visitor(): _isLog(false) { me::rel(); }

    public:
        me& setRoot(node& root) {
            _root.bind(root);
            return *this;
        }
        node& getRoot() { return *_root; }
        const node& getRoot() const NAMU_UNCONST_FUNC(getRoot())

        me& setLog(nbool toShow) {
            _isLog = toShow;
            return *this;
        }
        nbool isLog() const {
            return _isLog;
        }

        me& setReport(errReport& rpt);
        errReport& getReport();

        virtual void start();

        virtual void rel();

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
        virtual void onTraverse(visitInfo i, FBOExpr& f);
        virtual void onTraverse(visitInfo i, getExpr& e);
        virtual void onTraverse(visitInfo i, retExpr& b);
        virtual void onTraverse(visitInfo i, runExpr& e);
        virtual void onTraverse(visitInfo i, mgdFunc& f);
        virtual void onTraverse(visitInfo i, frame& f);
        virtual void onTraverse(visitInfo i, forExpr& f);
        virtual void onTraverse(visitInfo i, retStateExpr& r);
        virtual void onTraverse(visitInfo i, ifExpr& f);
        virtual void onTraverse(visitInfo i, whileExpr& w);
        virtual void onTraverse(visitInfo i, defArrayExpr& d);

    private:
        tstr<errReport> _rpt;
        nbool _isLog;
        str _root;
    };
}
