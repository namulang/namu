#include "graphVisitor.hpp"
#include "../ast.hpp"
#include "../frame/frame.hpp"

namespace namu {

    NAMU(DEF_ME(graphVisitor))

    void me::start() {
        _parentsLast.push_back(true);
        _isStart = false;
        super::start();

        std::cout << "\n";
    }

    void me::_drawIndent() {
        for(const char* e : _indents)
            std::cout << platformAPI::foreColor(LIGHTGRAY) << e;
    }

    void me::_onIndent() {
        nbool isParentLast = _parentsLast.back();
        _indents.push_back((isParentLast ? "    " : "┃    "));
    }

    void me::onVisit(visitInfo i, node& visitee) {
        if(_isStart)
            std::cout << "\n";
        _isStart = true;

        _onIndent();
        _drawIndent();

        nbool isLast = nul(i.parent) ? true : i.index >= i.len - 1;
        using platformAPI::foreColor;
        std::cout << foreColor(LIGHTGRAY) << (isLast ? "┗━[" : "┣━[") << foreColor(YELLOW) << i.index << foreColor(LIGHTGRAY) << "]: "
                  << foreColor(CYAN) << visitee.getType().getName()
                  << foreColor(LIGHTGRAY) << " \"" << foreColor(LIGHTBLUE) << i.name << foreColor(LIGHTGRAY) << "\" ";

        _parentsLast.push_back(isLast);
    }

    void me::onLeave(visitInfo i, node& visitee) {
        _indents.pop_back();
        _parentsLast.pop_back();
    }

    void me::onVisit(visitInfo i, baseFunc& fun) {
        onVisit(i, (node&) fun);
        using platformAPI::foreColor;
        std::cout << foreColor(MAGENTA) << "params" << foreColor(LIGHTGRAY) << "[" << foreColor(YELLOW) << fun.getParams().toStr()
                  << foreColor(LIGHTGRAY) << "] " << foreColor(MAGENTA) << "ret" << foreColor(LIGHTGRAY) << "["
                  << foreColor(CYAN) << fun.getRet()->getType().getName() << foreColor(LIGHTGRAY) << "]";
    }

    void me::onVisit(visitInfo i, genericObj& o) {
        onVisit(i, (node&) o);

        int n = 0;
        ncnt len = o._cache.size();
        for(auto e : o._cache)
            e.second->accept(visitInfo { e.first, &o, n++, len, i.depth+1}, *this);
    }

    void me::onVisit(visitInfo i, getExpr& e) {
        onVisit(i, (node&) e);

        std::string from;
        const node& me = e.getMe();
        if(nul(me))
            from = "frame";
        else
            from = me.getType().getName();

        using platformAPI::foreColor;
        std::cout << foreColor(MAGENTA) << " from" << foreColor(LIGHTGRAY) << "[" << foreColor(YELLOW) << from
                  << foreColor(LIGHTGRAY) << "] " << foreColor(MAGENTA) << "name" << foreColor(LIGHTGRAY) << "["
                  << foreColor(YELLOW) << e.getSubName() << foreColor(LIGHTGRAY) << "]";
    }
}
