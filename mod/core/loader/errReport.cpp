#include "../ast/node.hpp"
#include "errReport.hpp"

namespace namu {

    NAMU_DEF_ME(errReport)

    const err& me::operator[](nidx n) const { return get(n); }
    me::operator nbool() const { return hasErr(); }

    nbool me::hasErr() const {
        return has(err::ERR);
    }
    nbool me::hasWarn() const {
        return has(err::WARN);
    }
    nbool me::has(err::type type) const {
        for(auto& elem : _errs)
            if(elem->fType == type)
                return true;
        return false;
    }

    const err& me::get(nidx n) const { return *_errs[n]; }

    ncnt me::len() const { return _errs.size(); }

    const err& me::add(const err* new1) {
        _errs.push_back(new1);
        return *new1;
    }

    void me::add(const me& rhs) {
        for(const auto& e : rhs)
            add(*e);
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
