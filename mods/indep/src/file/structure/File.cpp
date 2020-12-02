#include "File.hpp"

namespace wrd { namespace indep {

    using namespace std;
    WRD_DEF_THIS(File)

    This::File(const std::string& path) : Super(path), _owner(0) {}
    This::File(const File* owner, const string& name) : _owner(owner) { _setName(name); }
    This::~File() {}

    const string& This::getName() const { return _name; }

    wbool This::remove() {
        wbool result = ::remove(getPath().c_str());
        if(!result)
            return release();

        return result;
    }

    wbool This::init() { return false; }
    wbool This::isInit() const { return true; }

    const string& This::getBaseDirectory() const {
        static const string inner = "";
        if(!_owner) return inner;

        return _owner->getPath();
    }

    wbool This::isFolder() const { return _isFolder(_getInfo(getPath())); }
    wubyte This::getSize() const { return _getInfo(getPath()).st_size; }

    wbool This::release() {
        // PathedObject::release(); --> _path should not be released.
        // _owner should not be released.
        return false;
    }

    const File& This::peek() const { return *this; }
    const File& This::next() { return *this; }

    wbool This::_isFolder(struct stat& info) { return info.st_mode & S_IFDIR; }

    struct stat& This::_getInfo(const string& path) {
        static struct stat inner = {0, };

        stat(path.c_str(), &inner);
        return inner;
    }

    void This::_setName(const string& new_name) {
        _name = new_name;
        _setPath(_owner ? _owner->getPath() + "/" + _name : _name);
    }

    File& This::operator=(const File& rhs) { return *this; }
    This::File(const File& rhs) : _owner(0){}
} }
