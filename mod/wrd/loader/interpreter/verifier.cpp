#include "verifier.hpp"

namespace wrd {

    WRD_DEF_ME(verifier)

    void me::rel() {
        setReport(dummyErrReport::singletone);
    }
}
