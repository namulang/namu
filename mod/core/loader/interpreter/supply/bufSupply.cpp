#include "../../../ast/node.hpp"
#include "bufSupply.hpp"

namespace namu {
    NAMU_DEF_ME(bufSupply)

    me::bufSupply(const std::string& buf): _buf(buf) {}

    void* me::onSupplySrc(parser& ps, void* scanner) const {
        return _scanString(ps, _buf.c_str(), scanner);
    }
}
