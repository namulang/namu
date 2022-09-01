#include "visitor.hpp"
#include "../../ast.hpp"
#include "../../frame/frame.hpp"
#include "../../builtin/primitive.hpp"

namespace namu {

    NAMU_DEF_ME(visitor)

#define X(T) \
    void me::visit(const std::string& name, T& t) { \
        if(nul(t)) return; \
        NAMU_DI("%s[%s].visit()", t.getType().getName().c_str(), name.c_str()); \
        onVisit(name, t); \
        onTraverse(name, t); \
        onLeave(name, t); \
    } \
    void me::onVisit(const std::string& name, T& t) {} \
    void me::onLeave(const std::string& name, T& t) {}

#   include "visitee.inl"
#undef X

    void me::start(node& root) {
        root.accept(std::string(""), *this);
    }

    void me::onTraverse(const std::string& name, node& t) {
        NAMU_DI("node[%s]::onTraverse", name.c_str());

        nbicontainer& subs = t.subs();
        for(auto e=subs.begin(); e ;++e)
            e->accept(e.getKey(), *this);
    }

    void me::onTraverse(const std::string& name, getExpr& e) {
        NAMU_DI("getExpr[%s]::onTraverse", name.c_str());

        node& me = (node&) e.getMe();
        if(!nul(me))
            me.accept("", *this);
    }

    void me::onTraverse(const std::string& name, frame& f) {
        NAMU_DI("frame[%s]::onTraverse", name.c_str());
        // do nothing.
    }

    void me::onTraverse(const std::string& name, runExpr& e) {
        NAMU_DI("runExpr[%s]::onTraverse", name.c_str());

        node& me = e.getMe();
        if(!nul(me))
            me.accept("", *this);
        node& subject = e.getSubject();
        if(!nul(subject))
            subject.accept("", *this);

        for(auto& elem : e.getArgs())
            elem.accept("", *this);
    }

    void me::onTraverse(const std::string& name, mgdFunc& f) {
        NAMU_DI("mgdFunc[%s]::onTraverse", name.c_str());

        onTraverse("", f.getBlock());
    }

    void me::onTraverse(const std::string& name, blockExpr& b) {
        NAMU_DI("blockExpr[%s]::onTraverse", name.c_str());

        for(auto& stmt : b.getStmts())
            stmt.accept("", *this);
    }

    void me::onTraverse(const std::string& name, returnExpr& b) {
        NAMU_DI("returnExpr[%s]::onTraverse", name.c_str());

        node& ret = b.getRet();
        if(!nul(ret))
            ret.accept("", *this);
    }

    void me::onTraverse(const std::string& name, asExpr& a) {
        NAMU_DI("asExpr[%s]::onTraverse", name.c_str());

        node& me = (node&) a.getMe();
        if(!nul(me))
            me.accept("", *this);
        node& as = (node&) a.getAs();
        if(!nul(as))
            as.accept("", *this);
    }
}
