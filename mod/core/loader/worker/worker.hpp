#pragma once

#include "../../type/ntype.hpp"
#include "../errReport.hpp"

namespace namu {

    template <typename R, typename T>
    class worker : public typeProvidable, public clonable {
        NAMU(ADT(worker))
        template <typename R1, typename T1>
        friend class workerAdapter;

    public:
        enum logFlag {
            LOG_ON_EX = 1, // logs the err instance when it just got reported.
            DUMP_ON_EX = 1 << 2, // log and leave callstack from an err instance when it just got reported.
            GUARD = 1 << 3, // logs when func in, out.
            INTERNAL = 1 << 4, // logs all except above case.
            LOG_ON_END = 1 << 5, // log all report info when the work ends.
            DUMP_ON_END = 1 << 6, // log and leave callstack for all report info when the work ends.
            DEFAULT = DUMP_ON_EX & GUARD & INTERNAL & LOG_ON_END
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
        nint getFlag() const;

        me& setTask(const T& root);
        T& getTask();
        const T& getTask() const NAMU_UNCONST_FUNC(getTask())

        template <typename... Args> void error(Args... args) { _report(err::newErr(args...)); }
        template <typename... Args> void warn(Args... args) { _report(err::newWarn(args...)); }
        template <typename... Args> void info(Args... args) { _report(err::newInfo(args...)); }

        virtual void rel();

        R work();

        const area& getArea() const NAMU_UNCONST_FUNC(_getArea())

        nbool isOk() const;

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
        void _applyLogger(const enables& enbs);
        nbool _applyLogger(logFlag flag);

    private:
        tstr<errReport> _rpt;
        area _area;
        tstr<T> _task;
        nint _logFlag;
    };

    template <typename R, typename T>
    struct workerAdapter {
        static R adaptWork(worker<R, T>& w);
    };
    template <typename T>
    struct workerAdapter<void, T> {
        static void adaptWork(worker<void, T>& w);
    };
}
