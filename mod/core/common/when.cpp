#include "when.hpp"
#include "../frame/thread.hpp"
#include "../builtin/err/nerr.hpp"
#include "../builtin/err/errReport.hpp"

namespace nm {

    NM(DEF_ME(__WHEN_OBJECT__))

    const me& me::get() {
        static me inner;
        return inner;
    }

    errReport& me::_getDefault() const {
        return thread::get() TO(getEx()) orRet dummyErrReport::singletone;
    }

    const point& me::_getPosFrom(const node& src) const { return src.getSrc().getPos(); }

    void me::_addNewErr(int code, errReport* rpt, ...) const {
        va_list args;
        va_start(args, rpt);
        rpt->add(nerr::newErr(code, args));
        va_end(args);
    }

    void me::_addNewErr(const point& src, int code, errReport* rpt, ...) const {
        va_list(args);
        va_start(args, rpt);
        rpt->add(nerr::newErr(src, code, args));
        va_end(args);
    }
}
