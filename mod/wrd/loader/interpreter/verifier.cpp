#include "verifier.hpp"
#include "../../frame/thread.hpp"

namespace wrd {

    WRD_DEF_ME(verifier)

    void me::rel() {
        setReport(dummyErrReport::singletone);
        setPacks(thread::get().getSystemPacks());
        _frameInfo = nullptr;
    }
}
