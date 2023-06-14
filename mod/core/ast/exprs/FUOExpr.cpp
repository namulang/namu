#include "FUOExpr.hpp"
#include "../../builtin/primitive.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(FUOExpr), DEF_VISIT())

    str me::run(const args& a) {
        if(!_it) return str();
        tstr<arithmeticObj> it(_it->as<node>());
        if(!it) return str();

        str ret((node*)it->deepClone());
        switch(_rule) {
            case POSTFIX_DOUBLE_PLUS: {
                tstr<arithmeticObj> rhs = it->add(nInt(1));
                if(rhs)
                    it->mov(*rhs);
                break;
            }

            case POSTFIX_DOUBLE_MINUS: {
                tstr<arithmeticObj> rhs = it->sub(nInt(1));
                if(rhs)
                    it->mov(*rhs);
                break;
            }

            case BITWISE_NOT:
                ret = it->bitwiseNot();
                break;

            default: ;
        }

        return ret;
    }

    str me::getEval() const {
        return _it->getEval();
    }
}
