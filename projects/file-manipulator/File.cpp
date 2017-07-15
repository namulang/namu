#include <sys/stat.h>
#include "File.hpp"

namespace NE
{
    #define THIS File

    THIS::THIS(const File* owner, const string& name) : _owner(owner) { _setName(name); }
    THIS::~THIS() {}

    const string& THIS::getName() const { return _name; }
    const string& THIS::getPath() const { return _path; }

    const string& THIS::getBaseDirectory() const
    {
        static const string inner = "";
        if( ! _owner) return inner;

        return _owner->getPath();
    }

    type_bool THIS::isFolder() const { return _isFolder(_getInfo(getPath())); }
    type_ubyte THIS::getSize() const { return _getInfo(getPath()).st_size; }
    type_bool THIS::isNull() const { return ! this; }

    void THIS::release()
    {
        // _path.clear();
        // _owner should not be released.
    }

    const File& THIS::peek() const { return *this; }
    const File& THIS::next() { return *this; }

    type_bool THIS::_isFolder(struct stat& info) { return info.st_mode & S_IFDIR; }

    struct stat& THIS::_getInfo(const string& path)
    {
        static struct stat inner = {0, };

        stat(path.c_str(), &inner);
        return inner;
    }

    void THIS::_setName(const string& new_name)
    {
        _name = new_name;
        _path = _owner ? _owner->getPath() + "/" + _name : _path = _name;
    }

    File& THIS::operator=(const File& rhs) { return *this; }
    THIS::File(const File& rhs) : _owner(0), _path(rhs._path) {}
}