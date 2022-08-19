#include "genericObj.hpp"
#include "../builtin/container/native/tndumMap.hpp"
#include "../loader/interpreter/tverification.hpp"
#include "../loader/interpreter/verification.inl"
#include "../loader/interpreter/verifier.hpp"

namespace namu {

    NAMU_DEF_ME(genericObj)

    nbicontainer& me::subs() {
        static ndumMap inner;
        return inner;
    }

    nbool me::canRun(const args& a) const {
        std::string key = _makeKey(a);
        if(key.empty()) return false;
        if(!_cache.count(key)) return false;
        // after verification, making GenericObject is supressed.

        return true;
    }

    str me::run(const args& a) {
        std::string key = _makeKey(a);
        if(key.empty()) return NAMU_E("key is empty"), nulOf<obj>();

        if(!_cache.count(key))
            _cache.insert({key, _makeGeneric(a)});

        return _cache[key];
    }

    std::string me::_makeKey(const args& a) const {
        if(a.len() != _paramNames.size()) return NAMU_E("len of args doesn't match to _paramNames"), std::string();
        return a.asStr();
    }

    /// make a generic object.
    tstr<obj> me::_makeGeneric(const args& a) const {
        if(!_orgObj) return NAMU_E("_orgObj is null"), tstr<obj>();

        tstr<obj> ret = _orgObj->clone();
        scope& owns = ret->getOwns();
        ncnt n = 0;
        for(auto& e : a)
            owns.add(_paramNames[n++], e);
        return ret;
    }



    NAMU_VERIFY(genericObj, iterateGenerics, {
        for(auto e : it._cache)
            if(nul(e.second))
                _srcErr(MAKE_GENERIC_FAIL, e.first.c_str());
    })
}
