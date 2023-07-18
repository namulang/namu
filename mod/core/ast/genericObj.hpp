#pragma once

#include "obj.hpp"

namespace namu {

    class visitor;
    class verifier;

    class _nout genericObj : public baseObj {
        NAMU(CLASS(genericObj, baseObj), VISIT())
        friend class verifier;
        friend class graphVisitor;
        friend class exprMaker;
        typedef std::vector<std::string> strings;

    public:
        genericObj(const obj& orgObj, const strings& paramNames): _orgObj(orgObj),
                _paramNames(paramNames) {}

    public:
        const obj& getOrigin() const override { return *_orgObj; }
        const strings& getParamNames() const { return _paramNames; }

        nbool canRun(const args& a) const override;
        str run(const args& a) override;

        str getEval() const override {
            return _orgObj;
        }

        virtual nbicontainer& subs() override;

        const std::map<std::string, tstr<obj>>& getCache() const {
            return _cache;
        }

        using super::inFrame;
        void inFrame(const bicontainable& args) override {}
        void outFrame() override {}

    protected:
        str _onRunSub(node& sub, const args& a) override { return str(); }

    private:
        std::string _makeKey(const args& a) const;

        /// make a generic object.
        tstr<obj> _makeGeneric(const args& a) const;
        tstr<obj> _defGeneric(const std::string& key, const args& a) const;
        void _setSrc(const src& newSrc) { _src.bind(newSrc); }
        void _setPos(const point& new1) override { _pos = new1; }

    private:
        std::map<std::string, tstr<obj>> _cache;
        tstr<obj> _orgObj;
        strings _paramNames;
        tstr<src> _src;
        point _pos;
    };
}
