#pragma once

#include "../../type/ntype.hpp"
#include "../errReport.hpp"

namespace namu {
    template <typename R, typename T>
    class _nout worker : public typeProvidable, public clonable {
        NAMU(ADT(worker))

    public:
        enum logFlag {
            LOG_ON_EX = 1, // logs the err instance when it just got reported.
            CSTACK_ON_EX = 1 << 2, // leave callstack from an err instance when it just got reported.
            GUARD = 1 << 3, // logs when func in, out.
            INTERNAL = 1 << 4, // logs all except above case.
            LOG_ON_END = 1 << 5, // log all report info when the work ends.
            CSTACK_ON_END = 1 << 6, // leave callstack for all report info when the work ends.
            DEFAULT = LOG_ON_EX & CSTACK_ON_EX & GUARD & INTERNAL & LOG_ON_END
        };

    public:
        worker();

    public:
        errReport& getReport();
        const errReport& getReport() const NAMU_UNCONST_FUNC(getReport())
        me& setReport(errReport& rpt);

        me& setFlag(nint newFlag);
        me& clearFlag(nint clear);
        nbool isFlag(nint flag);

        me& setTask(const T& root);
        T& getTask();
        const T& getTask() const NAMU_UNCONST_FUNC(getTask())

        template <typename... Args> void error(Args... args) { _report(err::newErr(args...)); }
        template <typename... Args> void warn(Args... args) { _report(err::newWarn(args...)); }
        template <typename... Args> void info(Args... args) { _report(err::newInfo(args...)); }
        template <typename... Args> void posError(Args... args) { _report(err::newErr(getArea().start, args...)); }
        template <typename... Args> void posWarn(Args... args) { _report(err::newWarn(getArea().start, args...)); }
        template <typename... Args> void posInfo(Args... args) { _report(err::newInfo(getArea().start, args...)); }

        virtual void rel();

        virtual R work();

        const area& getArea() const NAMU_UNCONST_FUNC(_getArea())

    protected:
        virtual void _prepare();

        void _report(err* e);

        virtual void _onEndWork();
        virtual R _onWork() = 0;

        area& _getArea();

        void _setTask(const T& new1);
        void _setTask(const T* new1);

    private:
        void _rel();

    private:
        tstr<errReport> _rpt;
        area _area;
        tstr<T> _task;
        nint _logFlag;
    };
}
