#pragma once

#include "obj.hpp"

namespace namu {

    class visitor;
    class verifier;

    class _nout genericObj : public baseObj {
        NAMU(CLASS(genericObj, baseObj), VISIT())
        friend class verifier;
        friend class graphVisitor;
        typedef std::vector<std::string> strings;

    public:
        genericObj(const obj& orgObj, const strings& paramNames): _orgObj(orgObj),
                _paramNames(paramNames) {}

    public:
        const obj& getOrigin() const override { return *_orgObj; }
        const strings& getParamNames() const { return _paramNames; }

        nbool canRun(const args& a) const override;
        str run(const args& a) override;

        const node& getEval() const override {
            return *_orgObj;
        }

        virtual nbicontainer& subs() override;

        void inFrame(const bicontainable& args) override {}
        void outFrame() override {}
        void defGeneric(verifier& v, const visitInfo& info, const args& a);

    protected:
        str _onRunSub(node& sub, const args& a) override { return str(); }

    private:
        std::string _makeKey(const args& a) const;

        /// make a generic object.
        tstr<obj> _makeGeneric(const args& a) const;

    private:
        std::map<std::string, tstr<obj>> _cache;
        tstr<obj> _orgObj;
        strings _paramNames;
    };
}
