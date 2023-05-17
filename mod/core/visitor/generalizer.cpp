#include "generalizer.hpp"
#include "../ast.hpp"

namespace namu {

    NAMU(DEF_ME(generalizer))

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

    void me::onVisit(visitInfo i, blockExpr& me) {
        narr& stmts = me.getStmts();
        for(int n=0; n < stmts.len() ;n++) {
            const node& org = _findOrigin(stmts[n]);
            if(nul(org)) continue;

            stmts.set(n, org);
        }
    }

    void me::onVisit(visitInfo i, defVarExpr& me) {
        const node& org = _findOrigin(me.getOrigin());
        if(nul(org)) return;

        me.setOrigin(org);
    }

    void me::onVisit(visitInfo i, runExpr& me) {
        const node* org = &_findOrigin(me.getMe());
        if(!nul(org))
            me.setMe(*org);

        org = &_findOrigin(me.getSubject());
        if(!nul(org))
            me.setSubject(*org);

        args& a = me.getArgs();
        for(int n=0; n < a.len(); n++) {
            const node& org = _findOrigin(a[n]);
            if(nul(org)) continue;

            a.set(n, org);
        }
    }

    void me::onVisit(visitInfo i, params& me) {
        NAMU_DI("generic: params[%d]", me.len());

        for(int n=0; n < me.len(); n++) {
            param& p = me[n];
            const node& org = _findOrigin(p.getOrigin());
            if(nul(org)) continue;

            p.setOrigin(org);
        }
    }

    void me::onVisit(visitInfo i, ctor& me) {
        // why do you clone to getRoot()?:
        //  generalizer can be called when there is no proper value against given
        //  parameterized type.
        //  however, it doesn't guarantee that getRoot() is always on the heap.
        //
        //  that is, when user make local variable of arr class and call subs() of it,
        //  getRoot() func holds a local variable.
        //
        //  but ctor usually lives longer than local variable. I make it be on the heap.
        me._setOrigin(*(node*) getRoot().clone());

        onVisit(i, (func&) me);
    }

    void me::onVisit(visitInfo i, func& me) {
        NAMU_DI("generic: func[%s, %x]", i.name.c_str(), &me);

        onVisit(i, (params&) me.getParams());

        const node& retOrg = _findOrigin(*me.getRet());
        if(!nul(retOrg)) {
            me.setRet(retOrg);
            genericCppObj& parent = i.parent->cast<genericCppObj>();
            if(nul(parent))
                getReport().add(err::newErr(errCode::IS_NULL, "parent"));
            else
                parent.setElemType(retOrg);
        }

        onVisit(i, (func::super&) me);
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

    void me::onVisit(visitInfo i, FBOExpr& me) {
        const node* org = &_findOrigin(me.getLeft());
        if(!nul(org))
            me.setLeft(*org);

        org = &_findOrigin(me.getRight());
        if(!nul(org))
            me.setRight(*org);
    }
}
