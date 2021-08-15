#pragma once

#include "parserable.hpp"
#include "../ast/node.hpp"
#include "../verifier/failReport.hpp"

namespace wrd {

    class parser : public parserable, typeProvidable {
        WRD_INTERFACE(parser, parserable)

    public:
        str parseFile(const std::string& path, failReport& report) {
            _report = &report;
            // TODO:
            return _root;
        }
        str parseFile(const std::string& path) {
            return parseFile(path, nulOf<failReport>());
        }

        str parseBuffer(const std::string& buffer, failReport& report);
        str parseBuffer(const std::string& buffer) {
            return parseBuffer(buffer, nulOf<failReport>());
        }

    protected:
        str& getRootBinder() override {
            return _root;
        }

    private:
        str _root;
        failReport* _report;
    };
}
