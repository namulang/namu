#include "../../../ast/node.hpp"
#include "bufferSrcSupply.hpp"

namespace namu {
    NAMU_DEF_ME(bufferSrcSupply)

    me::bufferSrcSupply(const std::string& buf): _buf(buf) {}

    const std::string& me::onSupplySrc(parser& ps) const {
        return _buf;
    }
}
