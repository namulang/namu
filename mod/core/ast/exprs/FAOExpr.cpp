#include "FAOExpr.hpp"
#include "../../frame/thread.hpp"
#include "../../builtin/primitive.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {

    NAMU(DEF_ME(FAOExpr), DEF_VISIT())

    namespace {
        str primitives[] = {
            new nInt(),
            new nFlt(),
            new nStr(),
            new nChar(),
            new nBool(),
        };

        nbool checkEvalType(const node& eval) {
            if(nul(eval)) return false;
            for(str e : primitives)
                if(eval.isSub(*e))
                    return true;

            return false;
        }
    }

    const node& me::getEval() const {
        if(!_lhs || !_rhs) return nulOf<node>();
        const node& lhsEval = _lhs->getEval();
        if(nul(lhsEval)) return nulOf<node>();
        const node& rhsEval = _rhs->getEval();
        if(nul(rhsEval)) return nulOf<node>();

        return lhsEval.reduce(rhsEval);
    }
}
