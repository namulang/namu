#include "FBOExpr.hpp"
#include "../../builtin/primitive.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(FBOExpr), DEF_VISIT())

    str me::getEval() const {
        static str inner(new nBool());
        if(isLogicalOp()) return inner;

        if(!_lhs || !_rhs) return str();
        str lhsEval = _lhs->getEval();
        if(!lhsEval) return lhsEval;
        str rhsEval = _rhs->getEval();
        if(rhsEval) return rhsEval;

        return str(lhsEval->deduce(*rhsEval));
    }

    nbool me::isLogicalOp() const {
        return LOGIC_START <= _rule && _rule < LOGIC_END;
    }

    str me::run(const args& a) {
        if(!_lhs || !_rhs) return str();

        tstr<arithmeticObj> lhs(_lhs->as<arithmeticObj>());
        tstr<arithmeticObj> rhs(_rhs->as<arithmeticObj>());
        if(!lhs || !rhs) return str();

        switch(_rule) {
            case ADD: return lhs->add(*rhs);
            case SUB: return lhs->sub(*rhs);
            case MUL: return lhs->mul(*rhs);
            case DIV: return lhs->div(*rhs);
            case MOD: return lhs->mod(*rhs);
            case BITWISE_AND: return lhs->bitwiseAnd(*rhs);
            case BITWISE_XOR: return lhs->bitwiseXor(*rhs);
            case BITWISE_OR: return lhs->bitwiseOr(*rhs);
            case LSHIFT: return lhs->lshift(*rhs);
            case RSHIFT: return lhs->rshift(*rhs);
            case EQ: return str(new nBool(lhs->eq(*rhs)));
            case NE: return str(new nBool(lhs->ne(*rhs)));
            case GT: return str(new nBool(lhs->gt(*rhs)));
            case LT: return str(new nBool(lhs->lt(*rhs)));
            case GE: return str(new nBool(lhs->ge(*rhs)));
            case LE: return str(new nBool(lhs->le(*rhs)));
            case AND: return str(new nBool(lhs->logicalAnd(*rhs)));
            case OR: return str(new nBool(lhs->logicalOr(*rhs)));
            default:
                return str();
        }
    }
}
