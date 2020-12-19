#include "Stream.hpp"

namespace wrd { namespace clog {

    WRD_DEF_THIS(Stream)

    This::Stream(): _isEnable(true) {}
    This::~Stream() {}

    wbool This::dump(const char* message) { return ! _isEnable; }
    wbool This::isNull() const { return ! this; }
    wbool This::isEnable() const { return _isEnable; }
    void This::setEnable(wbool isEnable) { _isEnable = isEnable; }

    wbool This::init() {
        _isEnable = true;
        return ! isInit();
    }

    wbool This::isInit() const { return _isEnable; }

    wbool This::rel() {
        _isEnable = false;
        return false;
    }
} }
