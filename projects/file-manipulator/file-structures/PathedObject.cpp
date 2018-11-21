#include "PathedObject.hpp"

namespace WRD
{
    #define THIS PathedObject

    using namespace std;

    THIS::THIS() {}
    THIS::THIS(const string& path) : _path(path) {}
    THIS::THIS(const THIS& rhs) : _path(rhs._path) {}
    const string& THIS::getPath() const { return _path; }
    type_bool THIS::isNull() const { return ! this; }
    type_bool THIS::release() { _path.clear(); return false; }

    THIS& THIS::operator=(const THIS& rhs) { return *this; }    

    type_bool THIS::_setPath(const string& new_path) { _path = new_path; return false; }
}
