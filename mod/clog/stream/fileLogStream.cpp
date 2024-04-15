#include "fileLogStream.hpp"

namespace namu {

    NAMU_DEF_ME(fileLogStream)
    typedef std::string string;

    me::fileLogStream() {}
    me::fileLogStream(const string& new_path): stream(), _path(new_path) {}

    const char* me::getName() const {
        return "fileLogStream";
    }

    nbool me::setPath(const string& new_path) {
        rel();
        _path = new_path;
        return false;
    }

    const string& me::getPath() const {
        return _path;
    }

    nbool me::logBypass(const char* message) {
        if(!isInit()) return true;
        if(super::logBypass(message)) return true;

        _file.open(_path.c_str(), std::fstream::out | std::fstream::app);
        _file << message;
        _file.close();
        return false;
    }

}
