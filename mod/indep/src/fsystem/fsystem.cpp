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
            struct dirent* file = readdir(e.dir);
            if(!file) {
                _popDir();
                continue;
            }
            std::string name = file->d_name;
            if(name == ".." || name == ".")
                continue;
            std::string path = e.path + "/" + name;
            if(file->d_type == DT_DIR) {
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
