#include "threadUse.hpp"

namespace namu {
    NAMU(DEF_ME(threadUse))

    me::threadUse(): _thr() {
        use();
    }
    me::threadUse(const node& ast): _thr(ast) {
        use();
    }
    me::~threadUse() {
        rel();
    }

    thread& me::get() {
        return _thr;
    }

    void me::use() {
        thread::set(_thr);
    }

    void me::rel() {
        thread::set();
    }
}
