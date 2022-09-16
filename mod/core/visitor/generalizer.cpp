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
    }*/

    void me::onVisit(visitInfo i, blockExpr& me) {
        narr& stmts = me.getStmts();
        for(int n=0; n < stmts.len() ;n++) {
            const node& org = _findOrigin(stmts[n]);
            if(nul(org)) continue;

            stmts.set(n, org);
        }
    }

    /*void me::onVisit(visitInfo i, defAssignExpr& me) {
    }*/

    void me::onVisit(visitInfo i, defVarExpr& me) {
        const node& org = _findOrigin(me.getOrigin());
        if(nul(org)) return;

        me.setOrigin(org);
    }

    /*void me::onVisit(visitInfo i, FAOExpr& me) {
    }*/

    /*void me::onVisit(visitInfo i, getExpr& me) {
    }*/

    /*void me::onVisit(visitInfo i, returnExpr& me) {
    }

    void me::onVisit(visitInfo i, runExpr& me) {
    }*/

    void me::onVisit(visitInfo i, params& me) {
        for(int n=0; n < me.len(); n++) {
            param& p = me[n];
            const node& org = _findOrigin(p.getOrigin());
            if(nul(org)) continue;

            p.setOrigin(org);
        }
    }

    void me::onVisit(visitInfo i, mgdFunc& me) {
        onVisit(i, (params&) me.getParams());

        const node& retOrg = _findOrigin(me.getRet());
        if(!nul(retOrg))
            me.setRet(retOrg);

        onVisit(i, (mgdFunc::super&) me);
    }

    void me::onVisit(visitInfo i, baseObj& me) {
        nbicontainer& subs = me.subs();
        for(auto e=subs.begin(); e ;++e) {
            const node& org = _findOrigin(e.getVal());
            if(nul(org)) continue;

            e.setVal(org);
        }


        onVisit(i, (baseObj::super&) me);
    }

    /*void me::onVisit(visitInfo i, genericObj& me) {
    }*/

}
