#include "FAOExpr.hpp"
#include "../../frame/thread.hpp"
#include "../../builtin/primitive.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(FAOExpr), DEF_VISIT())

    const node& me::getEval() const {
        if(!_lhs || !_rhs) return nulOf<node>();
        const node& lhsEval = _lhs->getEval();
        if(nul(lhsEval)) return nulOf<node>();
        const node& rhsEval = _rhs->getEval();
        if(nul(rhsEval)) return nulOf<node>();

        return lhsEval.deduce(rhsEval);
    }

    str me::run(const args& a) {
        if(!_lhs || !_rhs) return str();

        tstr<arithmeticObj> lhs(_lhs->run());
        tstr<arithmeticObj> rhs(_rhs->run());
        if(!lhs || !rhs) return str();

        switch(mRule) {
            case ADD: return lhs->add(*rhs);
            case SUB: return lhs->sub(*rhs);
            case MUL: return lhs->mul(*rhs);
            case DIV: return lhs->div(*rhs);
            case MOD: return lhs->mod(*rhs);
            case EQ: return str(new nBool(lhs->eq(*rhs)));
            case NE: return str(new nBool(lhs->ne(*rhs)));
            case GT: return str(new nBool(lhs->gt(*rhs)));
            case LT: return str(new nBool(lhs->lt(*rhs)));
            case GE: return str(new nBool(lhs->ge(*rhs)));
            case LE: return str(new nBool(lhs->le(*rhs)));
            default:
                return str();
        }
    }
}
