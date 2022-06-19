#pragma once

#include "../../ast/slot.hpp"
#include "../pack/packLoading.hpp"

namespace wrd {

    class errReport;

    class _wout slotLoader : public typeProvidable, public clonable {
        WRD(CLASS(slotLoader))

    public:
        slotLoader();

    public:
        me& addPath(const std::string& filePath);
        me& addPath(const std::vector<std::string> paths);
        me& addPath(std::initializer_list<const wchar*> paths);

        me& setReport(errReport& report);
        me& setBaseSlots(slots& basis);

        tstr<slots> load();

    private:
        void _makeSlots(slots& tray);
        void _addNewSlot(slots& tray, const std::string& dirPath, const std::string& manifestName);

        void _logSlot(const slot& pak) const;

        manifest _interpManifest(const std::string& dir, const std::string& manPath) const;

        packLoading* _makeLoading(const std::string& name) const;
        const packLoadings& _getLoadings() const;

    private:
        slots* _baseSlots;
        tstr<errReport> _report;
        std::vector<std::string> _paths;
        static constexpr wchar DELIMITER = '/';
    };
}
