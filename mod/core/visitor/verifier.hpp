#pragma once

#include "visitor.hpp"
#include "../loader/errReport.hpp"
#include "../frame/frame.hpp"

struct verifierTest;

namespace namu {

    class _nout verifier : public visitor {
        NAMU(ME(verifier, visitor))
        friend struct ::verifierTest;

    public:
        verifier();

    public:
        void rel();

        me& setReport(errReport& rpt);

        errReport& getReport();
        frame& getErrFrame();

        void start() override {
            _us.clear();
            super::start();
        }

        void onVisit(visitInfo i, node& me) override;
        void onVisit(visitInfo i, asExpr& me) override;
        void onVisit(visitInfo i, assignExpr& me) override;
        void onVisit(visitInfo i, blockExpr& me) override;
        void onLeave(visitInfo i, blockExpr& me) override;
        void onVisit(visitInfo i, defAssignExpr& me) override;
        void onVisit(visitInfo i, defVarExpr& me) override;
        void onVisit(visitInfo i, FAOExpr& me) override;
        void onVisit(visitInfo i, getExpr& me) override;
        void onVisit(visitInfo i, returnExpr& me) override;
        void onVisit(visitInfo i, runExpr& me) override;
        void onVisit(visitInfo i, mgdFunc& me) override;
        void onLeave(visitInfo i, mgdFunc& me) override;
        void onVisit(visitInfo i, baseObj& me) override;
        void onLeave(visitInfo i, baseObj& me) override;
        void onVisit(visitInfo i, genericObj& me) override;
        void onLeave(visitInfo i, genericObj& me) override;
        void onVisit(visitInfo i, getGenericExpr& me) override;

    private:
        // @param newInfo is not a heap instance.
        void _leaveErrFrame();

        template <typename... Args> void _warn(Args... args);
        template <typename... Args> void _err(Args... args);
        template <typename... Args> void _info(Args... args);
        template <typename... Args> void _srcWarn(const point& pos, Args... args);
        template <typename... Args> void _srcErr(const point& pos, Args... args);
        template <typename... Args> void _srcInfo(const point& pos, Args... args);

    private:
        tstr<errReport> _rpt;
        tstr<frame> _frame;
        std::vector<baseObj*> _us; // multiple 'me'
    };

#include "../common/MSVCHack.hpp"

}
