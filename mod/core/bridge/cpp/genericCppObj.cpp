#include "genericCppObj.hpp"
#include "../../ast/exprs/getExpr.hpp"

namespace namu {
    NAMU(DEF_ME(genericCppObj))

    const node& me::getElemType() const {
        // why I used lazy initialization at here:
        //  when setElemType called, given newType argument contains what just parsed at that time.
        //  but 'T' can be introduced to what the parser read next.
        //  so the only available option can represent is 'getExpr("T")' mostly.
        //
        //  after that getElemType() func will be called in verification or running stage.
        //  in this case, if I return it as getExpr type, all things messed up.
        //  I need to evaluate it and returns what currently getExpr('T') means.
        //
        //  to optimize, feed back evaluated result into the holder.
        if(!_type) return *_type;
        getExpr& cast = _type->cast<getExpr>();
        if(!nul(cast))
            _type.bind(*_type->as<node>());
        return *_type;
    }

    nbool me::setElemType(const node& newType) {
        return _type.bind(newType);
    }

}
