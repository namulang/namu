#pragma once

#include "visitor.hpp"

namespace namu {

    class _nout preEvaluator : public visitor {
        NAMU(ME(preEvaluator, visitor))

        struct _nout evaluation {
            tweak<obj> me;
            tweak<func> fun;
            nbool evaluated;
        };

    public:
        preEvaluator();

    public:
        void rel() override;

        using super::onVisit;

        nbool onVisit(visitInfo i, obj& me) override;
        void onLeave(visitInfo i, obj& me) override;
        nbool onVisit(visitInfo i, func& me) override;
        void onLeave(visitInfo i, func& me) override;
        nbool onVisit(visitInfo i, getGenericExpr& me) override;

    protected:
        void _onWork() override;

    private:
        void _rel();
        void _preEvalStack(errReport& rpt);
        nbool _preEvalFunc(errReport& rpt, evaluation& eval);
        void _delPreCtors();
        void _preEval();

    private:
        std::vector<evaluation> _stack;
        tstr<obj> _obj;
        tstr<func> _func;
    };
}
