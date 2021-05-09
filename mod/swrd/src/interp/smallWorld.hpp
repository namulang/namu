#pragma once

#include "../ast.hpp"
#include "../parser.hpp"

namespace wrd { namespace swrd {

    class smallWorld {
        WRD_DECL_ME(smallWorld)

    public:
        static tstr<obj> interp(const wchar* script);
        static tstr<obj> interp(const std::string& script);
        static tstr<obj> interpFile(const wchar* path);
        static tstr<obj> interpFile(const std::string& path);

    private:
        static tstr<obj> _runParser();
    };
}}
