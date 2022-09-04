#include "visitor.hpp"
#include "../../ast.hpp"
#include "../../frame/frame.hpp"
#include "../../builtin/primitive.hpp"

namespace namu {

    NAMU_DEF_ME(visitor)

#define X(T) \
    void me::visit(visitInfo i, T& me) { \
        if(nul(me)) return; \
        NAMU_DI("%s[%s].visit()", me.getType().getName().c_str(), i.name.c_str()); \
        onVisit(i, me); \
        onTraverse(i, me); \
        onLeave(i, me); \
    } \
    void me::onVisit(visitInfo i, T& me) { onVisit(i, (node&) me); } \
    void me::onLeave(visitInfo i, T& me) { onLeave(i, (node&) me); }

#   include "visitee.inl"
#undef X

    void me::visit(visitInfo i, node& me) {
        if(nul(me)) return;
        NAMU_DI("%s[%s].visit()", me.getType().getName().c_str(), i.name.c_str());

        onVisit(i, me);
        onTraverse(i, me);
        onLeave(i, me);
    }
    void me::onVisit(visitInfo i, node& me) {}
    void me::onLeave(visitInfo i, node& me) {}

    void me::start(node& root) {
        root.accept(visitInfo {"", nullptr, 0, 1}, *this);
    }

    void me::onTraverse(visitInfo i, node& me) {
        NAMU_DI("node[%s]::onTraverse", i.name.c_str());

        nbicontainer& subs = me.subs();
        int n=0;
        for(auto e=subs.begin(); e ;++e, ++n)
            e->accept(visitInfo {e.getKey(), &me, n, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, getExpr& e) {
        NAMU_DI("getExpr[%s]::onTraverse", i.name.c_str());
    }

    void me::onTraverse(visitInfo i, frame& f) {
        NAMU_DI("frame[%s]::onTraverse", i.name.c_str());
        // do nothing.
    }

    void me::onTraverse(visitInfo i, runExpr& e) {
        NAMU_DI("runExpr[%s]::onTraverse", i.name.c_str());

        int n = 0;
        node& me = e.getMe();
        if(!nul(me))
            me.accept(visitInfo {"", &e, n++, i.depth+1}, *this);
        node& subject = e.getSubject();
        if(!nul(subject))
            subject.accept(visitInfo {"", &e, n++, i.depth+1}, *this);

        for(auto& elem : e.getArgs())
            elem.accept(visitInfo {"", &e, n++, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, mgdFunc& f) {
        NAMU_DI("mgdFunc[%s]::onTraverse", i.name.c_str());

        onTraverse(i, f.getBlock());
    }

    void me::onTraverse(visitInfo i, blockExpr& b) {
        NAMU_DI("blockExpr[%s]::onTraverse", i.name.c_str());

        int n = 0;
        for(auto& stmt : b.getStmts())
            stmt.accept(visitInfo {"", &b, n++, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, returnExpr& b) {
        NAMU_DI("returnExpr[%s]::onTraverse", i.name.c_str());

        int n = 0;
        node& ret = b.getRet();
        if(!nul(ret))
            ret.accept(visitInfo {"", &b, n++, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, asExpr& a) {
        NAMU_DI("asExpr[%s]::onTraverse", i.name.c_str());

        int n = 0;
        node& me = (node&) a.getMe();
        if(!nul(me))
            me.accept(visitInfo {"", &a, n++, i.depth+1}, *this);
        node& as = (node&) a.getAs();
        if(!nul(as))
            as.accept(visitInfo {"", &a, n++, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, assignExpr& a) {
        NAMU_DI("assignExpr[%s]::onTraverse", i.name.c_str());

        int n = 0;
        node& left = (node&) a.getLeft();
        if(!nul(left))
            left.accept(visitInfo {"", &a, n++, i.depth+1}, *this);
        node& right = (node&) a.getRight();
        if(!nul(right))
            right.accept(visitInfo {"", &a, n++, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, defAssignExpr& d) {
        NAMU_DI("defAssignExpr[%s]::onTraverse", i.name.c_str());

        node& right = d.getRight();
        if(!nul(right))
            right.accept(visitInfo {"", &d, 0, i.depth+1}, *this);
    }

    void me::onTraverse(visitInfo i, FAOExpr& f) {
        NAMU_DI("FAOExpr[%s]::onTraverse", i.name.c_str());

        int n = 0;
        node& left = (node&) f.getLeft();
        if(!nul(left))
            left.accept(visitInfo {"", &f, n++, i.depth+1}, *this);
        node& right = (node&) f.getRight();
        if(!nul(right))
            right.accept(visitInfo {"", &f, n++, i.depth+1}, *this);
    }
}
