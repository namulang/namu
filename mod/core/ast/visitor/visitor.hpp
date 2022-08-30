#pragma once

#include "../../common.hpp"

namespace namu {

#define X(T) class T;
#   include "visitee.inl"
#undef X

    class visitor {
        NAMU(ME(visitor))

    public:
#define X(T) \
        virtual void visit(T& t); \
        virtual void onEnter(T& t); \
        virtual void onLeave(T& t);
#   include "visitee.inl"
#undef X

        virtual void onTraverse(node& t);
    };
}
