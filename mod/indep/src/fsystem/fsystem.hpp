#pragma once

#include "../macro.hpp"
#include "../common.hpp"

namespace wrd {

    class fsystem {
        WRD_DECL_ME(fsystem)

    public:
        static std::string getCurrentDir() {
            char buf[256] = {};
            return getcwd(buf, 256);
        }
    };
}
