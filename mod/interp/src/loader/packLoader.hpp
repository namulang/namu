#pragma once

#include "../ast/pack.hpp"
#include "packLoading.hpp"

namespace wrd {

    class failReport;

    class packLoader : public typeProvidable, public clonable {
        WRD(CLASS(packLoader))

    public:
        packLoader();

    public:
        me& addPath(const std::string& filePath) {
            _paths.push_back(filePath);
            return *this;
        }
        me& addPath(const std::vector<std::string> paths) {
            if(&_paths == &paths) return *this;

            _paths.insert(_paths.end(), paths.begin(), paths.end());
            return *this;
        }
        me& addPath(std::initializer_list<const wchar*> paths) {
            for(const wchar* e : paths)
                addPath(e);
            return *this;
        }

        me& setReport(failReport& report) {
            _report = &report;
            return *this;
        }

        me& setBasePacks(packs& basis) {
            _basePacks = &basis;
            return *this;
        }

        tstr<packs> load();

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

        void _makePacks(packs& tray) {
            std::string cwd = fsystem::getCurrentDir() + "/";
            WRD_I("finding packs relative to %s or absolute", cwd.c_str());

            for(const std::string& path : _paths) {
                WRD_I("try pack path: %s", path.c_str());

                _makePackAt(tray, cwd + path);
            }
        }

        void _makePackAt(packs& tray, const std::string& dirPath) {
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
                    _makePackAt(tray, filtered + DELIMITER + file->d_name);
                else if(file->d_name == MANIFEST_FILENAME)
                    _addNewPack(tray, filtered, file->d_name);
            }
        }

        void _addNewPack(packs& tray, const std::string& dirPath, const std::string& manifestName) {
            std::string manifestPath = dirPath + DELIMITER + manifestName;

            manifest mani = _interpManifest(dirPath, manifestPath);
            if(!mani.isValid()) {
                WRD_E("invalid manifest[%s] found.", manifestPath.c_str());
                return;
            }

            packLoadings loadings;
            for(entrypoint& point : mani.points) {
                packLoading* newLoading = _makeLoading(point.lang);
                if(!newLoading) {
                    WRD_W("%s language not supported for loading %s pack.", mani.points[0].lang.c_str(), mani.name.c_str());
                    continue;
                }

                newLoading->addPath(point.paths);
                loadings.push_back(newLoading);
            }

            pack* new1 = new pack(mani, loadings);
            tray.add(new1);
            _logPack(*new1);
        }

        void _logPack(const pack& pak) const {
            WRD_I("new pack [%s] has been added.", pak.getName().c_str());

            const manifest& mani = pak.getManifest();
            WRD_DI("\t.filePath=%s", mani.filePath.c_str());
            WRD_DI("\t.author=%s", mani.author.c_str());
            WRD_DI("\t.ver=%s", mani.ver.c_str());

            WRD_DI("\t.entrypoints=");
            for(const entrypoint& point : mani.points) {
                WRD_DI("\t\t.lang=%s", point.lang.c_str());
                WRD_DI("\t\t.paths=%s", point.paths[0].c_str());
            }
        }

        manifest _interpManifest(const std::string& dir, const std::string& manPath) const;

        packLoading* _makeLoading(const std::string& name) const {
            for(const packLoading* e : _getLoadings())
                if(e->getName() == name)
                    return (packLoading*) e->clone();

            WRD_E("can't find exact packLoading like %s", name.c_str());
            return nullptr;
        }
        const packLoadings& _getLoadings() const;

    private:
        packs* _basePacks;
        failReport* _report;
        std::vector<std::string> _paths;
        static constexpr wchar DELIMITER = '/';
    };
}
