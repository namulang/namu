#include "../ast/node.hpp"
#include "errReport.hpp"

namespace namu {

    WRD_DEF_ME(errReport)

    const err& me::operator[](widx n) const { return get(n); }
    me::operator wbool() const { return hasErr(); }

    wbool me::hasErr() const {
        return has(err::ERR);
    }
    wbool me::hasWarn() const {
        return has(err::WARN);
    }
    wbool me::has(err::type type) const {
        for(auto& elem : _errs)
            if(elem->fType == type)
                return true;
        return false;
    }

    const err& me::get(widx n) const { return *_errs[n]; }

    wcnt me::len() const { return _errs.size(); }

    const err& me::add(const err* new1) {
        new1->dbgLog();
        _errs.push_back(new1);
        return *new1;
    }

    std::vector<tstr<err>>::const_iterator me::begin() const {
        return _errs.begin();
    }

    std::vector<tstr<err>>::const_iterator me::end() const {
        return _errs.end();
    }

    void me::log() const {
        for(auto& elem : _errs)
            elem->log();
    }

    void me::rel() {
        _errs.clear();
    }

    const err& dummyErrReport::add(const err* new1) {
        static dummyErr dum;
        return dum;
    }

    dummyErrReport dummyErrReport::singletone;

}
