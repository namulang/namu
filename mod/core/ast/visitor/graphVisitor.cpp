#include "graphVisitor.hpp"
#include "../node.hpp"

namespace namu {

    NAMU(DEF_ME(graphVisitor))

    void me::start() {
        _parentsLast.push_back(true);
        super::start();
    }

    void me::_drawIndent() {
        for(const char* e : _indents)
            std::cout << e;
    }

    void me::_onIndent() {
        nbool isParentLast = _parentsLast.back();
        _indents.push_back((isParentLast ? "    " : "┃    "));
    }

    void me::onVisit(visitInfo i, node& visitee) {
        _onIndent();
        _drawIndent();

        nbool isLast = nul(i.parent) ? true : &i.parent->subs().last().getVal() == &visitee;
        std::cout << (isLast ? "┗━[" : "┣━[") << i.index << "]: " << visitee.getType().getName() << " \"" << i.name << "\"\n";

        _parentsLast.push_back(isLast);
    }

    void me::onLeave(visitInfo i, node& visitee) {
        _indents.pop_back();
        _parentsLast.pop_back();
    }
}
