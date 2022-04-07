#include "verification.hpp"
#include "../../ast/node.hpp"
#include "verifier.hpp"

namespace wrd {

	WRD_DEF_ME(verification)

    void me::verify(typeProvidable& it) {
        _getVerifier().verify(it);
    }
}
