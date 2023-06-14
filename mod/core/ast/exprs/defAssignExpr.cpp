#include "defAssignExpr.hpp"
#include "../../frame/thread.hpp"
#include "../../visitor/visitor.hpp"

namespace namu {
    NAMU(DEF_ME(defAssignExpr), DEF_VISIT())

    str me::run(const args& a) {
        str new1 = _rhs->as<node>();
        if(!new1)
            return NAMU_E("new1 is null"), str();

        node& to = getTo();
        if(nul(to))
            thread::get()._getNowFrame().pushLocal(_name, *new1);
        else
            to.run()->subs().add(_name, *new1);

        return new1;
    }

    node& me::getTo() { return *_to; }
}
