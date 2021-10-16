#pragma once

#include "../../ast/pack.hpp"
#include "packLoading.hpp"

namespace wrd {

    class errReport;

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

        me& setReport(errReport& report) {
            _report.bind(report);
            return *this;
        }

        me& setBasePacks(packs& basis) {
            _basePacks = &basis;
            return *this;
        }

        tstr<packs> load();

    private:
        void _makePacks(packs& tray) {
            std::string cwd = fsystem::getCurrentDir() + "/";
            WRD_I("finding packs relative to %s or absolute", cwd.c_str());

            for(const std::string& path : _paths) {
                WRD_I("try pack path: %s", path.c_str());

                _makePackAt(tray, cwd + path);
            }
        }

        void _makePackAt(packs& tray, const std::string& dirPath) {
            auto e = fsystem::find(dirPath);
            while(e.next())
                if(e.getName() == MANIFEST_FILENAME)
                    _addNewPack(tray, e.getDir(), e.getName());
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
        tstr<errReport> _report;
        std::vector<std::string> _paths;
        static constexpr wchar DELIMITER = '/';
    };
}
