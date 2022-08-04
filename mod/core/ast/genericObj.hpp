#pragma once

#include "obj.hpp"

namespace namu {

    class _nout genericObj : public baseObj {
        WRD(CLASS(genericObj, baseObj),
            FRIEND_VERIFY(genericObj, iterateGenerics))
        typedef std::vector<std::string> strings;

    public:
        genericObj(const obj& orgObj, const strings& paramNames): _orgObj(orgObj),
                _paramNames(paramNames) {}

    public:
        const obj& getOrigin() const override { return *_orgObj; }
        const strings& getParamNames() const { return _paramNames; }

        nbool canRun(const ucontainable& args) const override {
            std::string key = _makeKey(args);
            if(key.empty()) return false;
            if(!_cache.count(key)) return false;
            // after verification, making GenericObject is supressed.

            return true;
        }

        str run(const ucontainable& args) override {
            std::string key = _makeKey(args);
            if(key.empty()) return nulOf<obj>();

            if(!_cache.count(key))
                _cache.insert({key, _makeGeneric(args)});

            return _cache[key];
        }

        const node& getEval() const override {
            return *_orgObj;
        }

        virtual nbicontainer& subs() override;

    protected:
        void _inFrame(const bicontainable& args) override {}
        void _outFrame() override {}
        str _onRunSub(node& sub, const ucontainable& args) override { return str(); }

    private:
        std::string _makeKey(const ucontainable& args) const {
            if(args.len() != _paramNames.size()) return NAMU_E("len of args doesn't match to _paramNames"), std::string();

            std::string ret;
            for(auto& e : args)
                ret += e.getType().getName();

            return ret;
        }

        /// make a generic object.
        tstr<obj> _makeGeneric(const ucontainable& args) const {
            if(!_orgObj) return NAMU_E("_orgObj is null"), tstr<obj>();

            tstr<obj> ret = _orgObj->clone();
            scope& owns = ret->getOwns();
            ncnt n = 0;
            for(auto& e : args)
                owns.add(_paramNames[n++], e);
            return ret;
        }

    private:
        std::map<std::string, tstr<obj>> _cache;
        tstr<obj> _orgObj;
        strings _paramNames;
    };
}
