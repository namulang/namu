#include "smartDedent.hpp"

namespace namu {

    NAMU_DEF_ME(smartDedent)

    me::smartDedent() { setEnable(false); }

    void me::countDown() { if(_cnt > OFF) _cnt--; }
    void me::countUp() { if(_cnt > OFF) _cnt++;   }
    void me::setDedentNow() { _cnt = CAUGHT; }
    nbool me::canDedent() const { return _cnt == CAUGHT; }
    void me::setEnable(nbool to) { _cnt = to ? ON : OFF; }
    nbool me::isOn() const { return _cnt > OFF; }
}
