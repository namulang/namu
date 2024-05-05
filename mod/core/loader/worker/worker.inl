#include "worker.hpp"

namespace namu {

#define ME worker<R, T>
#define TEMPLATE template <typename R, typename T>

    TEMPLATE ME::worker() { _rel(); }

    TEMPLATE errReport& ME::getReport() { return *_rpt; }

    TEMPLATE
    ME& ME::setReport(errReport& rpt) {
        _rpt.bind(rpt);
        return *this;
    }

    TEMPLATE
    ME& ME::setFlag(nint newFlag) {
        _logFlag |= newFlag;
        return *this;
    }
    TEMPLATE
    ME& ME::clearFlag(nint clear) {
        _logFlag &= ~clear;
        return *this;
    }
    TEMPLATE nbool ME::isFlag(nint flag) { return (_logFlag & flag) == flag; }
    TEMPLATE nint ME::getFlag() const { return _logFlag; }

    TEMPLATE
    ME& ME::setTask(const T& task) {
        _task.bind(task);
        return *this;
    }

    TEMPLATE T& ME::getTask() { return *_task; }

    TEMPLATE void ME::rel() { _rel(); }

    TEMPLATE
    void ME::_rel() {
        _rpt.bind(dummyErrReport::singletone);
        _task.rel();
        _logFlag = DEFAULT;
    }

    TEMPLATE
    void ME::_prepare() {
        _area.rel();
    }

    TEMPLATE
    void ME::_report(err* e) {
        _rpt->add(e);
        if(isFlag(LOG_ON_EX))
            e->log();
        else if(isFlag(DUMP_ON_EX))
            e->dump();
    }

    TEMPLATE area& ME::_getArea() { return _area; }

    TEMPLATE nbool ME::isOk() const { return _rpt->hasErr(); }

    TEMPLATE
    void ME::_onEndWork() {
        _area.rel();

        if(isFlag(DUMP_ON_END))
            _rpt->dump();
        else if(isFlag(LOG_ON_END))
            _rpt->log();
    }

    TEMPLATE
    R ME::work() {
        if(isFlag(GUARD)) {
            NAMU_I("====================");
            NAMU_I("%s.work()...", getType().getName().c_str());
        }

        enablesZone prev;
        R ret;
        {
            enablesZone internal;
            if(!isFlag(INTERNAL)) logger::get().setEnable(false);
            ret = _onWork();
        }

        if(isFlag(GUARD)) {
            NAMU_I("--------------------");
            NAMU_I("%s._onEndWork()...");
        }

        prev.setPrev();
        _onEndWork();

        if(isFlag(GUARD))
            NAMU_I("====================");
        return ret;
    }

    TEMPLATE void ME::_setTask(const T& new1) { _task.bind(new1); }
    TEMPLATE void ME::_setTask(const T* new1) { _setTask(*new1); }

#undef TEMPLATE
#undef ME
}
