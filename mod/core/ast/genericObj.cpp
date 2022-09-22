#include "genericObj.hpp"
#include "../builtin/container/native/tndumMap.hpp"
#include "../visitor/generalizer.hpp"
#include "args.hpp"
#include "../visitor/verifier.hpp"
#include "func.hpp"

namespace namu {

    NAMU(DEF_ME(genericObj), DEF_VISIT())

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
            return NAMU_E("generic not verified"), str();

        return _cache[key];
    }

    void me::defGeneric(verifier& v, const visitInfo& info, const args& a) {
        std::string key = _makeKey(a);
        if(key.empty()) {
            NAMU_E("key is empty");
            return;
        }

        tstr<obj> gen = _makeGeneric(a);
        gen->accept(visitInfo {"", this, 0, (ncnt) _cache.size(), info.depth+1}, v);
        _cache.insert({key, gen});
    }

    std::string me::_makeKey(const args& a) const {
        if(a.len() != _paramNames.size()) return NAMU_E("len of args doesn't match to _paramNames"), std::string();
        return a.asStr();
    }

    /// make a generic object.
    tstr<obj> me::_makeGeneric(const args& a) const {
        if(!_orgObj) return NAMU_E("_orgObj is null"), tstr<obj>();

        NAMU_DI("=========================");
        NAMU_DI("        make generic     ");
        NAMU_DI("=========================");
        tstr<obj> ret = (obj*) _orgObj->deepClone();
        NAMU_DI("=========================");

        ncnt n = 0;
        generalizer g;
        for(auto& e : a)
            g.add(*new param(_paramNames[n++], e));

        g.setRoot(*ret).start();
        return ret;
    }
}
