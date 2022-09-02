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
        virtual void visit(const std::string& name, T& t); \
        virtual void onVisit(const std::string& name, T& t); \
        virtual void onLeave(const std::string& name, T& t);
#   include "visitee.inl"
#undef X

        void start(node& root);

        //  traverse:
        //      generalized-way:
        virtual void onTraverse(const std::string& name, node& t);
        //      specific-way:
        virtual void onTraverse(const std::string& name, asExpr& a);
        virtual void onTraverse(const std::string& name, assignExpr& a);
        virtual void onTraverse(const std::string& name, blockExpr& b);
        virtual void onTraverse(const std::string& name, defAssignExpr& d);
        virtual void onTraverse(const std::string& name, FAOExpr& f);
        virtual void onTraverse(const std::string& name, getExpr& e);
        virtual void onTraverse(const std::string& name, returnExpr& b);
        virtual void onTraverse(const std::string& name, runExpr& e);
        virtual void onTraverse(const std::string& name, mgdFunc& f);
        virtual void onTraverse(const std::string& name, frame& f);
    };
}
