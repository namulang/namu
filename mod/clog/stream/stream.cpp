#include "stream.hpp"

namespace namu {

    WRD_DEF_ME(stream)

    me::stream(wbool isEnable): _isEnable(isEnable) {}
    me::~stream() {}

    wbool me::dump(const char* message) { return ! _isEnable; }
    wbool me::isNull() const { return ! this; }
    wbool me::isEnable() const { return _isEnable; }
    void me::setEnable(wbool isEnable) { _isEnable = isEnable; }

    wbool me::init() {
        _isEnable = true;
        return ! isInit();
    }

    wbool me::isInit() const { return _isEnable; }

    wbool me::rel() {
        _isEnable = false;
        return false;
    }

    void me::saveStreamEnable() { _save = _isEnable; }
    void me::loadStreamEnable() { _isEnable = _save; }
}
