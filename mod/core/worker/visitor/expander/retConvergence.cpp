#include "retConvergence.hpp"
#include "../../../ast/func.hpp"
#include "../../../frame/thread.hpp"

namespace nm {
    NM(DEF_ME(retConvergence))

    me::retConvergence(func& f, const node& org): _f(&f), _org(&org) {}

    nbool me::converge() const {
        if(!_f || !_org) return NM_E("some retConverge info is null"), false;

        str eval = _org->getEval();
        if(!eval) return false;
        const node& owner = _f->getOrigin();
        if(nul(owner)) return false;

        const frame& fr = thread::get().getNowFrame();
        if(&fr.getOwner(*eval) != &owner) return false;

        ((ntype&) _f->getType()).setRet(*eval);
        return true;
    }
}
