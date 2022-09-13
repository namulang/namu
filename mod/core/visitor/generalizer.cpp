#include "generalizer.hpp"
#include "../ast.hpp"

namespace namu {

    NAMU(DEF_ME(generalizer))

    /*void me::start() {
    }*/

    const node& me::_findOrigin(const node& toReplace) const {
        const getExpr& cast = toReplace.cast<getExpr>();
        if(nul(cast)) return nulOf<node>();

        for(param p : _params)
            if(cast.getSubName() == p.getName())
                return p.getOrigin();
        return nulOf<node>();
    }

    void me::onVisit(visitInfo i, asExpr& me) {
        const node& org = _findOrigin(me.getAs());
        if(nul(org)) return;

        me.setAs(org);
    }

    /*void me::onVisit(visitInfo i, assignExpr& me) {
    }

    void me::onVisit(visitInfo i, blockExpr& me) {
    }

    void me::onVisit(visitInfo i, defAssignExpr& me) {
    }*/

    void me::onVisit(visitInfo i, defVarExpr& me) {
        const node& org = _findOrigin(me.getOrigin());
        if(nul(org)) return;

        me.setOrigin(org);
    }

    /*void me::onVisit(visitInfo i, FAOExpr& me) {
    }

    void me::onVisit(visitInfo i, getExpr& me) {
    }

    void me::onVisit(visitInfo i, returnExpr& me) {
    }

    void me::onVisit(visitInfo i, runExpr& me) {
    }

    void me::onVisit(visitInfo i, mgdFunc& me) {
    }

    void me::onVisit(visitInfo i, baseObj& me) {
    }

    void me::onVisit(visitInfo i, genericObj& me) {
    }*/

}
