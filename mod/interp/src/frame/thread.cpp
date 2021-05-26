#include "thread.hpp"
#include "../loader/packLoader.hpp"

namespace wrd {

    WRD_DEF_ME(thread)

    const packLoader& me::getSystemPackLoader() {
        static packLoader system({"pack/"});
        return system;
    }
}
