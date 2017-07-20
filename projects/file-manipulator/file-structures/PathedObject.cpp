#include "PathedObject.hpp"

namespace NE
{
    #define THIS PathedObject

    using namespace std;

    THIS::THIS() {}
    THIS::THIS(const string& path) : _path(path) {}    
    const string& THIS::getPath() const { return _path; }
    type_bool THIS::isNull() const { return ! this; }
    void THIS::release() { _path.clear(); }

    THIS& THIS::operator=(const THIS& rhs) { return *this; }
    THIS::THIS(const THIS& rhs) {}

    type_bool THIS::_setPath(const string& new_path) { _path = new_path; return false; }
}