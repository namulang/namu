#pragma once

#include "../../ast/pack.hpp"
#include "packLoading.hpp"

namespace wrd {

    class errReport;

    class _wout packLoader : public typeProvidable, public clonable {
        WRD(CLASS(packLoader))

    public:
        packLoader();

    public:
        me& addPath(const std::string& filePath);
        me& addPath(const std::vector<std::string> paths);
        me& addPath(std::initializer_list<const wchar*> paths);

        me& setReport(errReport& report);
        me& setBasePacks(packs& basis);

        tstr<packs> load();

    private:
        void _makePacks(packs& tray);
        void _addNewPack(packs& tray, const std::string& dirPath, const std::string& manifestName);

        void _logPack(const pack& pak) const;

        manifest _interpManifest(const std::string& dir, const std::string& manPath) const;

        packLoading* _makeLoading(const std::string& name) const;
        const packLoadings& _getLoadings() const;

    private:
        packs* _basePacks;
        tstr<errReport> _report;
        std::vector<std::string> _paths;
        static constexpr wchar DELIMITER = '/';
    };
}