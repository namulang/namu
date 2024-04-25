#include "../../../ast/node.hpp"
#include "srcSupply.hpp"
#include "../bison/lowscanner.hpp"

namespace namu {
    NAMU_DEF_ME(srcSupply)

    void* me::_scanString(parser& ps, const nchar* src, void* scanner) const {
        if(nul(src) || src[0] == '\0')
            return ps.getReport().add(err::newErr(errCode::SRC_EMPTY)), nullptr;

        return yy_scan_string((nchar*) src, (yyscan_t) scanner);
    }
}
