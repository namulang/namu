#include "thread.hpp"
#include "../ast/packLoader.hpp"

namespace wrd {

    WRD_DEF_ME(thread)

    const packLoader& me::getSystemPackLoader() {
        return packLoader::get();
    }
}
