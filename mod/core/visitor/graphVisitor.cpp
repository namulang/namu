#include "graphVisitor.hpp"
#include "../ast.hpp"
#include "../frame/frame.hpp"

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
        std::cout << "\n";
        _onIndent();
        _drawIndent();

        nbool isLast = nul(i.parent) ? true : &i.parent->subs().last().getVal() == &visitee;
        std::cout << (isLast ? "┗━[" : "┣━[") << i.index << "]: " << visitee.getType().getName() << " \"" << i.name << "\" ";

        _parentsLast.push_back(isLast);
    }

    void me::onLeave(visitInfo i, node& visitee) {
        _indents.pop_back();
        _parentsLast.pop_back();
    }

    void me::onVisit(visitInfo i, func& fun) {
        onVisit(i, (node&) fun);

        std::string msg;
        int n=0;
        const params& ps = fun.getParams();
        for(const param& p : ps)
            msg += "\"" + p.getName() + "\" " + p.getOrigin().getType().getName() +
                    (++n >= ps.len() ? "" : ",");
        std::cout << "params[" << msg << "]";
    }

    void me::onVisit(visitInfo i, genericObj& o) {
        onVisit(i, (node&) o);

        int n = 0;
        for(auto e : o._cache)
            e.second->accept(visitInfo { e.first, &o, n++, i.depth+1}, *this);
    }

    void me::onVisit(visitInfo i, getExpr& e) {
        onVisit(i, (node&) e);

        std::string from;
        const node& me = e.getMe();
        if(nul(me))
            from = "null";
        else if(me.isSub<frame>())
            from = "frame";
        else
            from = me.getType().getName();

        std::cout << " from[" << from << "] name[" << e.getSubName() << "]";
    }
}
