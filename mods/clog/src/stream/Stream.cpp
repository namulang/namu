#include "Stream.hpp"

namespace wrd { namespace clog {

    WRD_DEF_THIS(Stream)

    This::Stream(): _is_enable(true) {}
    This::~Stream() {}

    wbool This::dump(const char* message) { return ! _is_enable; }
    wbool This::isNull() const { return ! this; }
    wbool This::isEnable() const { return _is_enable; }
    void This::setEnable(wbool is_enable) { _is_enable = is_enable; }

    wbool This::init() {
        _is_enable = true;
        return ! isInit();
    }

    wbool This::isInit() const { return _is_enable; }

    wbool This::release() {
        _is_enable = false;
        return false;
    }
} }
