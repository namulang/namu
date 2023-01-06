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

    const node& me::getEval() const {
        const node& thenEval = _thenBlk->getEval();
        if(!_elseBlk)
            return thenEval;

        const node& elseEval = _elseBlk->getEval();
        return thenEval.deduce(elseEval);
    }
}
