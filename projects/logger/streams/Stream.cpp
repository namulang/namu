#include "Stream.hpp"

namespace WRD
{
    #define THIS Stream

    THIS::THIS() : _is_enable(true) {}
    THIS::~THIS() {}

    wbool THIS::dump(const char* message) { return ! _is_enable; }
    wbool THIS::isNull() const { return ! this; }
    wbool THIS::isEnable() const { return _is_enable; }
    void THIS::setEnable(wbool is_enable) { _is_enable = is_enable; }
    wbool THIS::initialize()
    {
        _is_enable = true;
        return ! isInitialized();
    }
    wbool THIS::isInitialized() const { return _is_enable; }
    wbool THIS::release()
    {
        _is_enable = false;
        return false;
    }
}
