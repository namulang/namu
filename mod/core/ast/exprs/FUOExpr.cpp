#include "FUOExpr.hpp"
#include "../../builtin/primitive.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(FUOExpr), DEF_VISIT())

    str me::run(const args& a) {
        if(!_it) return str();
        tstr<arithmeticObj> it(_it->run());
        if(!it) return str();

        str ret((node*)it->deepClone());
        switch(_rule) {
            case POSTFIX_DOUBLE_PLUS: it->mov(*it->add(nInt(1))); break;
            case POSTFIX_DOUBLE_MINUS: it->mov(*it->sub(nInt(1))); break;
            default: ;
        }

        return ret;
    }

    const node& me::getEval() const {
        return *_it;
    }
}
