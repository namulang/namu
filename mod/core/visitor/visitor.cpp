#include "visitor.hpp"
#include "../ast.hpp"
#include "../frame/frame.hpp"
#include "../builtin.hpp"

namespace namu {

    NAMU_DEF_ME(visitor)

#define X(T) \
    void me::visit(visitInfo i, T& me) { \
        if(nul(me)) return; \
        if(_isLog) \
            NAMU_DI("%s[%s].visit()", me.getType().getName().c_str(), i.name.c_str()); \
        onVisit(i, me); \
        onTraverse(i, me); \
        onLeave(i, me); \
    } \
    void me::onVisit(visitInfo i, T& me) { onVisit(i, (T::super&) me); } \
    void me::onLeave(visitInfo i, T& me) { onLeave(i, (T::super&) me); }

#   include "visitee.inl"
#undef X

    void me::visit(visitInfo i, node& me) {
        if(nul(me)) return;
        if(_isLog)
            NAMU_DI("%s[%s].visit()", me.getType().getName().c_str(), i.name.c_str());

        onVisit(i, me);
        onTraverse(i, me);
        onLeave(i, me);
    }
    void me::onVisit(visitInfo i, node& me) {}
    void me::onLeave(visitInfo i, node& me) {}

    void me::start() {
        if(!_root) return;

        _root->accept(visitInfo {"", nullptr, 0, 1, 1}, *this);
    }

    void me::onTraverse(visitInfo i, node& me) {
        if(_isLog)
            NAMU_DI("node[%s]::onTraverse", i.name.c_str());

        nbicontainer& subs = me.subs();
        int n=0;
        ncnt len = me.subs().len();
        for(auto e=subs.begin(); e ;++e, ++n)
            e->accept(visitInfo {e.getKey(), &me, n, len, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, getExpr& e) {
        if(_isLog)
            NAMU_DI("getExpr[%s]::onTraverse", i.name.c_str());
    }

    void me::onTraverse(visitInfo i, frame& f) {
        if(_isLog)
            NAMU_DI("frame[%s]::onTraverse", i.name.c_str());
        // do nothing.
    }

    void me::onTraverse(visitInfo i, runExpr& e) {
        if(_isLog)
            NAMU_DI("runExpr[%s]::onTraverse", i.name.c_str());

        int n = 0;
        node& me = e.getMe();
        node& subject = e.getSubject();
        int len = e.getArgs().len() + (nul(me) ? 0 : 1) + (nul(subject) ? 0 : 1);
        if(!nul(me))
            me.accept(visitInfo {"", &e, n++, len, i.depth+1}, *this);
        if(!nul(subject))
            subject.accept(visitInfo {"", &e, n++, len, i.depth+1}, *this);

        for(auto& elem : e.getArgs())
            elem.accept(visitInfo {"", &e, n++, len, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, mgdFunc& f) {
        if(_isLog)
            NAMU_DI("mgdFunc[%s]::onTraverse", i.name.c_str());

        f.getBlock().accept(i, *this);
    }

    void me::onTraverse(visitInfo i, blockExpr& b) {
        if(_isLog)
            NAMU_DI("blockExpr[%s]::onTraverse", i.name.c_str());

        int n = 0;
        narr& stmts = b.getStmts();
        int len = stmts.len();
        for(auto& stmt : stmts)
            stmt.accept(visitInfo {"", &b, n++, len, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, returnExpr& b) {
        if(_isLog)
            NAMU_DI("returnExpr[%s]::onTraverse", i.name.c_str());

        int n = 0;
        node& ret = b.getRet();
        if(!nul(ret))
            ret.accept(visitInfo {"", &b, n++, 1, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, asExpr& a) {
        if(_isLog)
            NAMU_DI("asExpr[%s]::onTraverse", i.name.c_str());

        int n = 0;
        node& me = (node&) a.getMe();
        node& as = (node&) a.getAs();
        ncnt len = (nul(me) ? 0 : 1) + (nul(as) ? 0 : 1);
        if(!nul(me))
            me.accept(visitInfo {"", &a, n++, len, i.depth+1}, *this);
        if(!nul(as))
            as.accept(visitInfo {"", &a, n++, len, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, assignExpr& a) {
        if(_isLog)
            NAMU_DI("assignExpr[%s]::onTraverse", i.name.c_str());

        int n = 0;
        node& left = (node&) a.getLeft();
        node& right = (node&) a.getRight();
        ncnt len = (nul(left) ? 0 : 1) + (nul(right) ? 0 : 1);
        if(!nul(left))
            left.accept(visitInfo {"", &a, n++, len, i.depth+1}, *this);
        if(!nul(right))
            right.accept(visitInfo {"", &a, n++, len, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, defAssignExpr& d) {
        if(_isLog)
            NAMU_DI("defAssignExpr[%s]::onTraverse", i.name.c_str());

        node& right = d.getRight();
        if(!nul(right))
            right.accept(visitInfo {"", &d, 0, 1, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, FAOExpr& f) {
        if(_isLog)
            NAMU_DI("FAOExpr[%s]::onTraverse", i.name.c_str());

        int n = 0;
        node& left = (node&) f.getLeft();
        node& right = (node&) f.getRight();
        ncnt len = (nul(left) ? 0 : 1) + (nul(right) ? 0 : 1);
        if(!nul(left))
            left.accept(visitInfo {"", &f, n++, len, i.depth+1}, *this);
        if(!nul(right))
            right.accept(visitInfo {"", &f, n++, len, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, forExpr& f) {
        if(_isLog)
            NAMU_DI("forExpr[%s]::onTraverse", i.name.c_str());

        f.getBlock().accept(i, *this);
    }

    void me::onTraverse(visitInfo i, retStateExpr& r) {
        if(_isLog)
            NAMU_DI("%s[%s]::onTraverse", r.getType().getName().c_str(), i.name.c_str());

        int n = 0;
        node& ret = r.getRet();
        if(!nul(ret))
            ret.accept(visitInfo {"", &r, n++, 1, i.depth+1}, *this);
    }
}
