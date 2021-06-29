#pragma once

#include "../ast/pack.hpp"

namespace wrd {

    class packLoader : public node {
        WRD_CLASS(packLoader, node)

    public:
        packLoader(std::initializer_list<const wchar*> paths)
            : _subs(new nchain()) {

            const std::string& cwd = fsystem::getCurrentDir();
            WRD_I("find packs relative to %s or absolute", cwd.c_str());

            for(const wchar* path : paths) {
                WRD_I("pack path: %s", path);
                _traversePack(std::string(path));
            }
        }

        wbool canRun(const wtypes& types) const override {
            return false;
        }

        str run(const ncontainer& args) override {
            return str();
        }

        using super::subs;
        ncontainer& subs() override {
            return *_subs;
        }

    private:
        wbool _isExcludedFile(const std::string& fileName) {
            static const std::string EXCLUDED_FILES[] = {".", ".."};
            for(std::string exclusion : EXCLUDED_FILES)
                if(fileName == exclusion)
                    return true;

            return false;
        }

        std::string _filterDirPath(const string& dirPath) {
            int last = dirPath.length() - 1;
            if(dirPath[last] == DELIMITER)
                return dirPath.substr(0, last);

            return dirPath;
        }

        void _traversePack(const std::string& dirPath) {
            const std::string& filtered = _filterDirPath(dirPath);
            DIR* dir = opendir(dirPath.c_str());
            if(!dir) {
                WRD_E("path %s permission denied.");
                return;
            }

            struct dirent* file = nullptr;
            while((file = readdir(dir))) {
                if(_isExcludedFile(file->d_name))
                    continue;

                // TODO: refactor to be extentiable.
                if(file->d_type == DT_DIR)
                    _traversePack(filtered + DELIMITER + file->d_name);
                else if(file->d_name == MANIFEST_FILENAME)
                    _createPack(filtered, file->d_name);
            }
        }

        void _createPack(const std::string& dirPath, const std::string& manifestName) {
            // TODO:
            WRD_E("found pack at %s / %s", dirPath.c_str(), manifestName.c_str());
        }

    private:
        tstr<nchain> _subs;
        static constexpr wchar DELIMITER = '/';
    };
}
