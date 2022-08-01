#pragma once

#include "../ast.hpp"

namespace wrd {

    class _wout sinterpreter {
        WRD_DECL_ME(sinterpreter)

    public:
        static tstr<sobj> interp(const wchar* script);
        static tstr<sobj> interp(const std::string& script);
        static tstr<sobj> interpFile(const wchar* path);
        static tstr<sobj> interpFile(const std::string& path);
        static const std::string& getFileName();

    private:
        static std::string _extractFileName(const std::string& path);
        static tstr<sobj> _runParser();
    };
}
