#include "visitor.hpp"
#include "../../ast.hpp"
#include "../../builtin/primitive.hpp"

namespace namu {

    NAMU_DEF_ME(visitor)

#define X(T) \
    void me::visit(const std::string& name, T& t) { \
        onVisit(name, t); \
        onTraverse(t); \
        onLeave(name, t); \
    } \
    void me::onVisit(const std::string& name, T& t) {} \
    void me::onLeave(const std::string& name, T& t) {}

#   include "visitee.inl"
#undef X

    void me::onTraverse(node& t) {
        nbicontainer& subs = t.subs();
        for(auto e=subs.begin(); e ;++e)
            e->accept(e.getKey(), *this);
    }

    void me::start(node& root) {
        root.accept(std::string(""), *this);
    }
}
