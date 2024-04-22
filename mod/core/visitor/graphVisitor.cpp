#include "graphVisitor.hpp"
#include "../ast.hpp"
#include "../frame/frame.hpp"

namespace namu {

    NAMU(DEF_ME(graphVisitor))

    void me::start() {
        _parentsLast.push_back(true);
        _isStart = false;
        super::start();

        std::clog << "\n";
    }

    void me::_drawIndent() {
        for(const char* e : _indents)
            std::clog << platformAPI::foreColor(LIGHTGRAY) << e;
    }

    void me::_onIndent() {
        nbool isParentLast = _parentsLast.back();
        _indents.push_back((isParentLast ? "   " : "┃  "));
    }

    nbool me::onVisit(visitInfo i, node& visitee) {
        _drawFrame(i);
        using platformAPI::foreColor;
        std::clog << foreColor(LIGHTRED) << i.name << " "
                  << foreColor(CYAN) << visitee.getType().getName();

        return !visitee.isSub<arithmeticObj>();
    }

    void me::_drawFrame(visitInfo i) {
        if(_isStart)
            std::clog << "\n";
        _isStart = true;

        _onIndent();
        _drawIndent();

        nbool isLast = nul(i.parent) ? true : i.index >= i.len - 1;
        using platformAPI::foreColor;
        std::clog << foreColor(LIGHTGRAY) << (isLast ? "┗━[" : "┣━[") << foreColor(YELLOW) << i.index << foreColor(LIGHTGRAY) << "] ";
        _parentsLast.push_back(isLast);
    }

    void me::onLeave(visitInfo i, node& visitee) {
        if(isLog())
            NAMU_DI("%s.onLeave(name=%s parent=%s, index=%d, depth=%d)",
                   visitee.getType().getName().c_str(), i.name.c_str(), i.parent->getType().getName().c_str(), i.index, i.depth);
        _indents.pop_back();
        _parentsLast.pop_back();
    }

    nbool me::onVisit(visitInfo i, baseFunc& fun) {
        _drawFrame(i);

        using platformAPI::foreColor;
        std::clog << foreColor(LIGHTBLUE) << i.name
                  << foreColor(LIGHTGRAY) << "(" << foreColor(CYAN) << fun.getParams().toStr() << foreColor(LIGHTGRAY) << ") "
                  << foreColor(CYAN) << fun.getRet()->getType().getName();
        return true;
    }

    nbool me::onVisit(visitInfo i, genericObj& o) {
        onVisit(i, (node&) o);

        int n = 0;
        ncnt len = o._cache.size();
        for(auto e : o._cache)
            e.second->accept(visitInfo { e.first, &o, n++, len, i.depth+1}, *this);
        return true;
    }

    nbool me::onVisit(visitInfo i, getExpr& e) {
        onVisit(i, (node&) e);

        std::string from;
        const node& me = e.getMe();
        if(nul(me))
            from = "frame";
        else
            from = me.getType().getName();

        using platformAPI::foreColor;
        std::clog << foreColor(LIGHTGRAY) << " -> "
                  << foreColor(MAGENTA) << "from" << foreColor(LIGHTGRAY) << "[" << foreColor(YELLOW) << from << foreColor(LIGHTGRAY) << "] "
                  << foreColor(MAGENTA) << "name" << foreColor(LIGHTGRAY) << "[" << foreColor(YELLOW) << e.getSubName() << foreColor(LIGHTGRAY) << "] "
                  << foreColor(MAGENTA) << "args" << foreColor(LIGHTGRAY) << "[" << foreColor(YELLOW) << e.getSubArgs().toStr() << foreColor(LIGHTGRAY) << "]";
        return true;
    }

    nbool me::onVisit(visitInfo i, runExpr& e) {
        onVisit(i, (node&) e);

        std::string from;
        const node& me = e.getMe();
        if(nul(me))
            from = "frame";
        else
            from = me.getType().getName();

        using platformAPI::foreColor;
        std::clog << foreColor(LIGHTGRAY) << " -> "
                  << foreColor(MAGENTA) << "args" << foreColor(LIGHTGRAY) << "[" << foreColor(YELLOW) << e.getArgs().toStr() << foreColor(LIGHTGRAY) << "]";
        return true;
    }

    nbool me::onVisit(visitInfo i, FBOExpr& e) {
        onVisit(i, (node&) e);

        using platformAPI::foreColor;
        std::clog << foreColor(LIGHTGRAY) << " -> "
                  << foreColor(CYAN) << e.getLeft().getType().getName() << " "
                  << foreColor(LIGHTGRAY) << e.getRuleName(e.getRule()) << " "
                  << foreColor(CYAN) << e.getRight().getType().getName();

        return !e.getLeft().isSub<arithmeticObj>() || !e.getRight().isSub<arithmeticObj>();
    }

    nbool me::onVisit(visitInfo i, FUOExpr& e) {
        onVisit(i, (node&) e);

        const node& op = e.getOperand();
        using platformAPI::foreColor;
        std::clog << foreColor(CYAN) << op.getType().getName() << " "
                  << foreColor(LIGHTGRAY) << e.getRuleName(e.getRule());

        return !op.isSub<arithmeticObj>();
    }
}
