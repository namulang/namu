#pragma once

#include "visitor.hpp"
#include "../frame/frame.hpp"
#include "../ast/params.hpp"

struct verifierTest;

namespace namu {

    class loopExpr;
    class thread;
    class _nout verifier : public visitor {
        NAMU(ME(verifier, visitor))
        friend struct ::verifierTest;
        friend class genericObj;

    public:
        verifier();

    public:
        void rel() override;

        frame& getErrFrame();

        void start() override;

        void onVisit(visitInfo i, node& me) override;
        void onVisit(visitInfo i, asExpr& me) override;
        void onVisit(visitInfo i, assignExpr& me) override;
        void onVisit(visitInfo i, blockExpr& me) override;
        void onLeave(visitInfo i, blockExpr& me) override;
        void onLeave(visitInfo i, defAssignExpr& me) override;
        void onVisit(visitInfo i, defPropExpr& me) override;
        void onVisit(visitInfo i, defSeqExpr& me) override;
        void onVisit(visitInfo i, defArrayExpr& me) override;
        void onVisit(visitInfo i, FBOExpr& me) override;
        void onVisit(visitInfo i, FUOExpr& me) override;
        void onVisit(visitInfo i, getExpr& me) override;
        void onVisit(visitInfo i, retExpr& me) override;
        void onVisit(visitInfo i, runExpr& me) override;
        void onVisit(visitInfo i, func& me) override;
        void onLeave(visitInfo i, func& me) override;
        void onVisit(visitInfo i, baseObj& me) override;
        void onLeave(visitInfo i, baseObj& me) override;
        void onVisit(visitInfo i, genericObj& me) override;
        void onLeave(visitInfo i, genericObj& me) override;
        void onVisit(visitInfo i, forExpr& me) override;
        void onLeave(visitInfo i, forExpr& me) override;
        void onVisit(visitInfo i, whileExpr& me) override;
        void onLeave(visitInfo i, whileExpr& me) override;
        void onVisit(visitInfo i, breakExpr& me) override;
        void onVisit(visitInfo i, nextExpr& me) override;
        void onVisit(visitInfo i, ifExpr& me) override;

    private:
        void _prepare();
        void _postpare();
        std::string _asStr(const params& ps);

        // @param newInfo is not a heap instance.
        void _leaveErrFrame();
        void _verifyMgdFuncImplicitReturn(func& me);
        void _rel();
        void _report(err* new1);

        template <typename... Args> void _err(Args... args);
        template <typename... Args> void _err(const point& pos, errCode code, Args... args);
        template <typename... Args> void _warn(Args... args);
        template <typename... Args> void _warn(const point& pos, errCode code, Args... args);
        template <typename... Args> void _info(Args... args);
        template <typename... Args> void _info(const point& pos, errCode code, Args... args);

    private:
        tstr<frame> _frame;
        std::vector<baseObj*> _us; // multiple 'me'
        std::vector<loopExpr*> _recentLoops;
    };
}
