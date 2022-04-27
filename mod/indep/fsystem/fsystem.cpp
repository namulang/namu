#include "fsystem.hpp"

namespace wrd {

    WRD_DEF_ME(fsystem)

    const std::string& me::iterator::get() const {
        return _nowPath;
    }

    wbool me::iterator::next() {
        // assume that all of data to _entries was valid:
        //  which means, if returning value from readdir() was null,
        //  then the most top element of entries should be removed.
        while(!isEnd()) {
            entry& e = _entries[_entries.size()-1];
#ifdef WRD_BUILD_PLATFORM_IS_WINDOWS
            int res = _findnext(e.dir, &e.file);
            if(res == -1) {
#else
            struct dirent* file = readdir(e.dir);
            if(!file) {
#endif
                _popDir();
                continue;
            }
#ifdef WRD_BUILD_PLATFORM_IS_WINDOWS
            std::string name = e.file.name;
            char delimiter = '\\';
#else
            std::string name = file->d_name;
            char delimiter = '/';
#endif
            if(name == ".." || name == ".")
                continue;
            std::string path = e.path + "/" + name;
#ifdef WRD_BUILD_PLATFORM_IS_WINDOWS
            if(e.file.attrib & _A_SUBDIR) {
#else
            if(file->d_type == DT_DIR) {
#endif
                _addDir(path);
                continue;
            }

            _nowPath = path;
            return true;
        }

        _nowPath = "";
        return false;
    }
}
