#include "graphVisitor.hpp"
#include "../ast.hpp"
#include "../frame/frame.hpp"
#include "../loader/worker/worker.inl"
#include <regex>

namespace nm {

    NM(DEF_ME(graphVisitor))
    using platformAPI::foreColor;
    using namespace std;

    void me::_onWork() {
        _parentsLast.push_back(true);
        _isStart = false;
        super::_onWork();

        clog << "\n";
    }

    void me::_drawIndent() {
        for(const char* e : _indents)
            clog << platformAPI::foreColor(LIGHTGRAY) << e;
    }

    void me::_onIndent() {
        nbool isParentLast = _parentsLast.back();
        _indents.push_back((isParentLast ? "   " : "┃  "));
    }

    nbool me::onVisit(const visitInfo& i, nInt& e) { return _onVisitPrimitive<nInt>(i, e); }
    nbool me::onVisit(const visitInfo& i, nFlt& e) { return _onVisitPrimitive<nFlt>(i, e); }
    nbool me::onVisit(const visitInfo& i, nStr& e) {
        _drawFrame(i);
        clog << foreColor(LIGHTRED) << i.name << " "
             << foreColor(CYAN) << e.getType().getName()
             << foreColor(LIGHTGRAY) << " = " << foreColor(YELLOW) << _encodeNewLine(e.get());
        return false;
    }
    nbool me::onVisit(const visitInfo& i, nChar& e) { return _onVisitPrimitive<nChar>(i, e); }
    nbool me::onVisit(const visitInfo& i, nByte& e) { return _onVisitPrimitive<nByte>(i, e); }
    nbool me::onVisit(const visitInfo& i, nBool& e) { return _onVisitPrimitive<nBool>(i, e); }

    nbool me::onVisit(const visitInfo& i, node& visitee) {
        _drawFrame(i);
        clog << foreColor(LIGHTRED) << i.name << " "
             << foreColor(CYAN) << visitee.getType().getName()
             << foreColor(LIGHTGRAY) << "@" << foreColor(RED) << platformAPI::toAddrId(&visitee);
        return true;
    }

    void me::_drawFrame(const visitInfo& i) {
        if(_isStart)
            clog << "\n";
        _isStart = true;

        _onIndent();
        _drawIndent();

        nbool isLast = nul(i.parent) ? true : i.index >= i.len - 1;
        clog << foreColor(LIGHTGRAY) << (isLast ? "┗━[" : "┣━[") << foreColor(YELLOW) << i.index << foreColor(LIGHTGRAY) << "] ";
        _parentsLast.push_back(isLast);
    }

    void me::onLeave(const visitInfo& i, node& visitee) {
        _indents.pop_back();
        _parentsLast.pop_back();
    }

    nbool me::onVisit(const visitInfo& i, baseFunc& fun) {
        _drawFrame(i);

        clog << foreColor(LIGHTGRAY) << "@" << foreColor(RED) << platformAPI::toAddrId(&fun) << " "
             << foreColor(LIGHTBLUE) << i.name
             << foreColor(LIGHTGRAY) << "(" << foreColor(CYAN) << fun.getParams().toStr() << foreColor(LIGHTGRAY) << ") "
             << foreColor(CYAN) << fun.getRet()->getType().getName();
        return true;
    }

    nbool me::onVisit(const visitInfo& i, genericObj& o) {
        onVisit(i, (node&) o);

        int n = 0;
        ncnt len = o._cache.size();
        for(auto e : o._cache)
            e.second->accept(visitInfo { e.first, &o, n++, len, i.depth+1}, *this);
        return true;
    }

    nbool me::onVisit(const visitInfo& i, getExpr& e) {
        onVisit(i, (node&) e);

        string args = e.getArgs().toStr();

        clog << foreColor(LIGHTGRAY) << " = "
             << foreColor(MAGENTA) << _getNameFrom(e.getMe()) << foreColor(LIGHTGRAY) << "." << foreColor(YELLOW) << e.getName();
        if(!args.empty())
            clog << foreColor(LIGHTGRAY) << "(" << foreColor(CYAN) << args << foreColor(LIGHTGRAY) << ")";
        return true;
    }

    nbool me::onVisit(const visitInfo& i, runExpr& e) {
        onVisit(i, (node&) e);

        clog << foreColor(LIGHTGRAY) << " = "
             << foreColor(MAGENTA) << _getNameFrom(e.getMe()) << foreColor(LIGHTGRAY) << "."
             << foreColor(YELLOW) << _getNameFrom(e.getSubj())
             << foreColor(LIGHTGRAY) << "(" << foreColor(YELLOW) << e.getArgs().toStr() << foreColor(LIGHTGRAY) << ")";
        return true;
    }

    nbool me::onVisit(const visitInfo& i, FBOExpr& e) {
        onVisit(i, (node&) e);

        clog << foreColor(LIGHTGRAY) << " = "
             << foreColor(CYAN) << e.getLeft().getType().getName();
        str leftVal = e.getLeft();
        const std::string& leftName = leftVal->isSub<getExpr>() ? leftVal->cast<getExpr>().getName() : leftVal->getType().getName();
        clog << foreColor(LIGHTGRAY) << "(" << foreColor(YELLOW) << _encodeNewLine(leftName) << foreColor(LIGHTGRAY) << ")";

        clog << " " << foreColor(LIGHTGRAY) << e.getRuleName(e.getRule()) << " "
             << foreColor(CYAN) << e.getRight().getType().getName();
        str rightVal = e.getRight();
        const std::string& rightName = rightVal->isSub<getExpr>() ? rightVal->cast<getExpr>().getName() : rightVal->getType().getName();
        clog << foreColor(LIGHTGRAY) << "(" << foreColor(YELLOW) << _encodeNewLine(rightName) << foreColor(LIGHTGRAY) << ")";

        return !e.getLeft().isSub<arithmeticObj>() || !e.getRight().isSub<arithmeticObj>();
    }

    nbool me::onVisit(const visitInfo& i, FUOExpr& e) {
        onVisit(i, (node&) e);

        const node& op = e.getOperand();
        clog << foreColor(LIGHTGRAY) << " = "
             << foreColor(CYAN) << op.getType().getName() << " "
             << foreColor(LIGHTGRAY) << e.getRuleName(e.getRule());
        return true;
    }

    nbool me::onVisit(const visitInfo& i, assignExpr& e) {
        onVisit(i, (node&) e);

        clog << foreColor(LIGHTGRAY) << " = "
             << foreColor(MAGENTA) << _getNameFrom(e.getLeft()) << foreColor(LIGHTGRAY) << " = "
             << foreColor(MAGENTA) << _getNameFrom(e.getRight());

        return true;
    }

    nbool me::onVisit(const visitInfo& i, defVarExpr& e) {
        onVisit(i, (node&) e);

        clog << foreColor(LIGHTGRAY) << " = "
             << foreColor(MAGENTA) << e.getName() << foreColor(LIGHTGRAY) << " := "
             << foreColor(CYAN) << _getNameFrom(e.getRight());
        return true;
    }

    string me::_getNameFrom(const node& it) const {
        if(nul(it)) return "frame";

        string ret = it.getType().getName();
        const auto& name = safeGet(it.cast<getExpr>(), getName());
        if(!nul(name))
            ret = name;
        return ret;
    }

    string me::_encodeNewLine(const string& msg) const {
        return "\"" + regex_replace(msg, regex("\n"), "\\n") + "\"";
    }
}
