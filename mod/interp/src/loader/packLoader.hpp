#pragma once

#include "../ast/pack.hpp"
#include "packLoading.hpp"

namespace wrd {

    class packLoader : public node {
        WRD_CLASS(packLoader, node)

    public:
        packLoader();
        packLoader(const wchar* path);
        packLoader(std::initializer_list<const wchar*> paths);
        ~packLoader() override {
            me::rel();
        }

    public:
        void addPath(const std::string& filePath) {
            _paths.push_back(filePath);
        }
        void addPath(const std::vector<std::string> paths) {
            if(&_paths == &paths) return;

            _paths.insert(_paths.end(), paths.begin(), paths.end());
        }
        void addPath(std::initializer_list<const wchar*> paths) {
            for(const wchar* e : paths)
                addPath(e);
        }

        wbool canRun(const wtypes& types) const override {
            return false;
        }

        str run(const ncontainer& args) override {
            return str();
        }

        using super::subs;
        ncontainer& subs() override {
            return _mergedChain;
        }

        void rel() override {
            _paths.clear();
            _loadedPacks.rel();
            _mergedChain.unlink();
        }

        wbool load();

        packs& getLoadedPacks() { return _loadedPacks; }
        const packs& getLoadedPacks() const { return _loadedPacks; }

        wbool link(const me& new1) {
            if(nul(new1)) return false;

            return _mergedChain.link(new1._mergedChain);
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

        void _makePacks() {
            std::string cwd = fsystem::getCurrentDir() + "/";
            WRD_I("finding packs relative to %s or absolute", cwd.c_str());

            for(const std::string& path : _paths) {
                WRD_I("try pack path: %s", path.c_str());

                _makePackAt(cwd + path);
            }
        }

        void _makePackAt(const std::string& dirPath) {
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
                    _makePackAt(filtered + DELIMITER + file->d_name);
                else if(file->d_name == MANIFEST_FILENAME)
                    _addNewPack(filtered, file->d_name);
            }
        }

        void _addNewPack(const std::string& dirPath, const std::string& manifestName) {
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
            _loadedPacks.add(new1);
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

    private:
        packLoading* _makeLoading(const std::string& name) const {
            for(const packLoading* e : _getLoadings())
                if(e->getName() == name)
                    return (packLoading*) e->clone();

            WRD_E("can't find exact packLoading like %s", name.c_str());
            return nullptr;
        }
        const packLoadings& _getLoadings() const;

    private:
        packs _loadedPacks;
        packChain _mergedChain;
        std::vector<std::string> _paths;
        static constexpr wchar DELIMITER = '/';
    };
}
