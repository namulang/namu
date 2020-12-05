#include "FileLogStream.hpp"

namespace wrd { namespace clog {

    WRD_DEF_THIS(FileLogStream)
    typedef std::string string;

    This::FileLogStream() {}
    This::FileLogStream(const string& new_path) : Stream(), _path(new_path) {}

    const char* This::getName() const { return "FileLogStream"; }

    wbool This::setPath(const string& new_path) {
        release();
        _path = new_path;
        return false;
    }

    const string& This::getPath() const { return _path; }

    wbool This::dump(const char* message) {
        if(!isInit()) return true;
        if(Super::dump(message)) return true;

        _file.open(_path.c_str());
        _file << message;
        _file.close();
        return false;
    }

} }
