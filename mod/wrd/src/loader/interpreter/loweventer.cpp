#include "loweventer.hpp"
#include "bison/lowparser.hpp"
#include "bison/scanMode.hpp"

namespace wrd {

    WRD_DEF_ME(loweventer)

    me::~loweventer() {
        if(_mode)
            delete _mode;
    }
}
