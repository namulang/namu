#pragma once

#include "parser.hpp"

namespace wrd {

    class interpreter : public typeProvidable, public clonable {
        WRD(CLASS(interpreter))

    public:
        me& setReport(errReport& report) {
            _report = &report;
            return *this;
        }

        str interpretBuffer(const std::string& buffer) {
            return interpret(buffer.c_str(), buffer.size());
        }
        str interpret(const wchar* buf, wcnt len) {
            // TODO:
            return str();
        }
        str interpret(const std::string& filePath) {
            // TODO:
            return str();
        }
        str interpret(const manifest& mani) {
            // TODO:
            return str();
        }

    private:
        errReport* _report;
    };
}
