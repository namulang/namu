#pragma once

#include "../macro.hpp"
#include "../common.hpp"
#include <dirent.h>
#include <vector>

namespace wrd {

    /// fsystem is going to be used before filesystem library fully supported.
    /// to apply fsystem on clang++ is quite hard now.
    class fsystem {
        WRD_DECL_ME(fsystem)
        WRD(ME(fsystem))

        struct entry {
            DIR* dir;
            std::string path;
        };
        typedef std::vector<entry> entries;

        class iterator {
            WRD(ME(iterator))
            friend class fsystem;

        private:
            iterator(const std::string& path) {
                _addDir(path);
            }

        public:
            ~iterator() {
                rel();
            }

        public:
            const std::string& operator*() {
                return get();
            }

            me& operator++(int) {
                next();
                return *this;
            }

            operator wbool() const {
                return !isEnd();
            }

        public:
            void rel() {
                while(!isEnd())
                    _popDir();
            }

            wbool next();

            const std::string& get() const;

            std::string getName() const {
                const std::string& path = get();
                widx slash = path.rfind('/');
                return path.substr(slash + 1);
            }

            std::string getDir() const {
                const std::string& path = get();
                widx slash = path.rfind('/');
                return path.substr(0, slash);
            }

            wbool isEnd() const {
                return _entries.size() == 0;
            }

        private:
            void _addDir(const std::string& dirPath) {
                std::string path = _filterPath(dirPath);
                DIR* newDir = opendir(path.c_str());
                if(!newDir) return;

                _entries.push_back(entry {newDir, path});
            }
            void _popDir() {
                entry& e = _entries[_entries.size()-1];
                closedir(e.dir);
                _entries.pop_back();
            }

            std::string _filterPath(const std::string& org) {
                int last = org.length() - 1;
                if(org[last] == '/')
                    return org.substr(0, last);

                return org;
            }

        private:
            entries _entries;
            std::string _nowPath;
        };

    public:
        static iterator find(const std::string& path) {
            return iterator(path);
        }

    public:
        static std::string getCurrentDir() {
            char buf[256] = {};
            return getcwd(buf, 256);
        }
    };
}
