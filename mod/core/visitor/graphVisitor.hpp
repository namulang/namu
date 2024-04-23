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
        nbool onVisit(visitInfo i, FBOExpr& e) override;
        nbool onVisit(visitInfo i, FUOExpr& e) override;
        nbool onVisit(visitInfo i, nInt& e) override;
        nbool onVisit(visitInfo i, nFlt& e) override;
        nbool onVisit(visitInfo i, nStr& e) override;
        nbool onVisit(visitInfo i, nChar& e) override;
        nbool onVisit(visitInfo i, nByte& e) override;
        nbool onVisit(visitInfo i, nBool& e) override;

    private:
        void _drawIndent();
        void _onIndent();
        void _drawFrame(visitInfo i);
        template <typename T>
        nbool _onVisitPrimitive(visitInfo i, T& e) {
            _drawFrame(i);
            using platformAPI::foreColor;
            std::clog << foreColor(LIGHTRED) << i.name << " "
                      << foreColor(CYAN) << e.getType().getName()
                      << foreColor(LIGHTGRAY) << " = " << foreColor(YELLOW) << e.get();
            return false;
        }

    private:
        std::vector<nbool> _parentsLast;
        std::vector<const char*> _indents;
        nbool _isStart;
    };
}
