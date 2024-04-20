#pragma once

#include "visitor.hpp"

namespace namu {

    class _nout graphVisitor : public visitor {
        NAMU(ME(graphVisitor, visitor))

    public:
        void start() override;
        nbool onVisit(visitInfo i, node& visitee) override;
        void onLeave(visitInfo i, node& visitee) override;
        nbool onVisit(visitInfo i, baseFunc& fun) override;
        nbool onVisit(visitInfo i, genericObj& o) override;
        nbool onVisit(visitInfo i, getExpr& e) override;
        nbool onVisit(visitInfo i, runExpr& e) override;

    private:
        void _drawIndent();
        void _onIndent();

    private:
        std::vector<nbool> _parentsLast;
        std::vector<const char*> _indents;
        nbool _isStart;
    };
}
