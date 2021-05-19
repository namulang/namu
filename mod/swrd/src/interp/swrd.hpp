#pragma once

#include "../ast.hpp"
#include "../parser.hpp"

namespace wrd {

    class swrd {
        WRD_DECL_ME(swrd)

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
