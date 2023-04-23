#include "ifExpr.hpp"
#include "../../builtin/primitive/nVoid.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(ifExpr), DEF_VISIT())

    me::ifExpr(const node& exp, const blockExpr& thenBlk): _expr(exp), _thenBlk(thenBlk) {}
    me::ifExpr(const node& exp, const blockExpr& thenBlk, const blockExpr& elseBlk):
        _expr(exp), _thenBlk(thenBlk), _elseBlk(elseBlk) {}

    blockExpr& me::getThenBlk() { return *_thenBlk; }
    blockExpr& me::getElseBlk() { return *_elseBlk; }
    node& me::getCondition() { return *_expr; }

    str me::run(const args& a) {
        str res = _expr->run(a);
        if(res.cast<nbool>())
            return _thenBlk->run();
        else if(_elseBlk)
            return _elseBlk->run();

        return str(nVoid::singletone());
    }

    str me::getEval() const {
        str thenEval = _thenBlk->getEval();
        if(!thenEval) return thenEval;
        if(!_elseBlk)
            return thenEval;

        str elseEval = _elseBlk->getEval();
        return str(thenEval->deduce(*elseEval));
    }
}
