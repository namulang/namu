#include "../../ast/node.hpp"
#include "bufferSrcSupply.hpp"

namespace namu {
    NAMU_DEF_ME(bufferSrcSupply)

    me::bufferSrcSupply(const std::vector<string>& buf): _srcs(buf) { ret(); }

    nbool me::next() {
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
