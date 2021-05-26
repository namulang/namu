#include "packLoader.hpp"

namespace wrd {

    WRD_DEF_ME(packLoader)

    void me::_init(std::initializer_list<const wchar*> paths) {
        for(const wchar* path : paths) {
            WRD_I("search packfiles at %s", path);
            //TODO:
        }
    }
}
