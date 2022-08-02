#include "tokenDispatcher.hpp"

namespace namu {

    WRD_DEF_ME(tokenDispatcher)

    void me::add(wint newToken) {
        _toks.push_back(newToken);
    }

    void me::addFront(wint newToken) {
        _toks.insert(_toks.begin(), newToken);
    }

    wbool me::pop(wint& output) {
        if(_toks.size() <= 0)
            return false;

        output = _toks.front();
        _toks.pop_front();
        return true;
    }

    wcnt me::len() const {
        return _toks.size();
    }

    void me::rel() {
        _toks.clear();
    }
}
