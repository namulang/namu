#include "worker.hpp"

namespace namu {

#define ME worker<R, T>
#define TEMPLATE template <typename R, typename T>

    TEMPLATE errReport& ME::getReport() { return *_rpt; }

    TEMPLATE
    ME& ME::setReport(errReport& rpt) {
        _rpt.bind(rpt);
        return *this;
    }

    TEMPLATE
    ME& ME::setTask(const T& task) {
        _task.bind(task);
        return *this;
    }

    TEMPLATE T& ME::getTask() { return *_task; }

    TEMPLATE
    void ME::rel() {
        _rpt.bind(dummyErrReport::singletone);
        _task.rel();
    }

    TEMPLATE
    void ME::_prepare() {
        _area.rel();
    }

    TEMPLATE
    void ME::_report(err* e) {
        e->log();
        _rpt->add(e);
    }

    TEMPLATE area& ME::_getArea() { return _area; }

    TEMPLATE
    void ME::_onEndWork() {
        _area.rel();
    }

    TEMPLATE
    R ME::work() {
        NAMU_I("====================");
        NAMU_I("%s.work()...", getType().getName().c_str());
        R ret = _onWork();
        NAMU_I("--------------------");
        NAMU_I("%s._onEndWork()...");
        _onEndWork();
        NAMU_I("====================");
    }

    TEMPLATE void ME::_setTask(const T& new1) { _task.bind(new1); }
    TEMPLATE void ME::_setTask(const T* new1) { _setTask(*new1); }

#undef TEMPLATE
#undef ME
}
