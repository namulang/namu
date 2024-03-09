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
        visitor();

    public:
        me& setRoot(node& root);
        node& getRoot();
        const node& getRoot() const NAMU_UNCONST_FUNC(getRoot())

        me& setLog(nbool toShow);
        nbool isLog() const;

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
        //  @ return false if the node is already visited.
        virtual nbool onTraverse(visitInfo i, node& me);
        //      specific-way:
        virtual nbool onTraverse(visitInfo i, asExpr& a);
        virtual nbool onTraverse(visitInfo i, assignExpr& a);
        virtual nbool onTraverse(visitInfo i, blockExpr& b);
        virtual nbool onTraverse(visitInfo i, defAssignExpr& d);
        virtual nbool onTraverse(visitInfo i, defPropExpr& d);
        virtual nbool onTraverse(visitInfo i, FBOExpr& f);
        virtual nbool onTraverse(visitInfo i, getExpr& e);
        virtual nbool onTraverse(visitInfo i, retExpr& b);
        virtual nbool onTraverse(visitInfo i, runExpr& e);
        virtual nbool onTraverse(visitInfo i, func& f);
        virtual nbool onTraverse(visitInfo i, frame& f);
        virtual nbool onTraverse(visitInfo i, forExpr& f);
        virtual nbool onTraverse(visitInfo i, retStateExpr& r);
        virtual nbool onTraverse(visitInfo i, ifExpr& f);
        virtual nbool onTraverse(visitInfo i, whileExpr& w);
        virtual nbool onTraverse(visitInfo i, defArrayExpr& d);
        virtual nbool onTraverse(visitInfo i, genericObj& g);

    private:
        /// @return false if the node is already visited.
        nbool _markVisited(node& me);

    private:
        tstr<errReport> _rpt;
        nbool _isLog;
        str _root;
        // value will be true if key is visited func or obj:
        //  obj usually has huge subs and was chained to its subpack. but subpack also has the
        //  obj as its one of subs, so visitor will fall in the infinite recursive loop.
        //  to prevent it, I prepare a map instance. that map will return true if the key,
        //  func or obj, already got visited.
        std::map<node*, nbool> _visited;
    };
}
