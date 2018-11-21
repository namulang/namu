#include "Stream.hpp"

namespace WRD
{
    #define THIS Stream

    THIS::THIS() : _is_enable(true) {}
    THIS::~THIS() {}

    type_bool THIS::dump(const char* message) { return ! _is_enable; }
    type_bool THIS::isNull() const { return ! this; }
    type_bool THIS::isEnable() const { return _is_enable; }
    void THIS::setEnable(type_bool is_enable) { _is_enable = is_enable; }
    type_bool THIS::initialize()
    {
        _is_enable = true;
        return ! isInitialized();
    }
    type_bool THIS::isInitialized() const { return _is_enable; }
    type_bool THIS::release()
    {
        _is_enable = false;
        return false;
    }
}
