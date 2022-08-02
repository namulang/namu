#include "../../ast/node.hpp"
#include "bufferSrcSupply.hpp"

namespace namu {
    WRD_DEF_ME(bufferSrcSupply)

    me::bufferSrcSupply(const std::vector<string>& buf): _srcs(buf) { ret(); }

    wbool me::next() {
        if(++_cursor >= _srcs.size()) return false;

        return true;
    }

    const char* me::get() const {
        return _srcs[_cursor].c_str();
    }

    void me::ret() {
        _cursor = -1;
    }
}
