#pragma once

#include "visitor.hpp"

namespace namu {

    class graphVisitor : public visitor {
        NAMU(ME(graphVisitor, visitor))

    public:
        void start() override;
        void onVisit(visitInfo i, node& visitee) override;
        void onLeave(visitInfo i, node& visitee) override;
        void onVisit(visitInfo i, func& fun) override;
        void onVisit(visitInfo i, genericObj& o) override;
        void onVisit(visitInfo i, getExpr& e) override;

    private:
        void _drawIndent();
        void _onIndent();

    private:
        std::vector<nbool> _parentsLast;
        std::vector<const char*> _indents;
    };
}
