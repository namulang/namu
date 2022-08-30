#include "visitor.hpp"
#include "../../ast.hpp"

namespace namu {

    NAMU_DEF_ME(visitor)

#define X(T) \
    void me::visit(T& t) { \
        onEnter(t); \
        onTraverse(t); \
        onLeave(t); \
    } \
    void me::onEnter(T& t) {} \
    void me::onLeave(T& t) {}

#   include "visitee.inl"
#undef X

    void me::onTraverse(node& t) {
        for(auto& e : t.subs())
            e.accept(*this);
    }
}
