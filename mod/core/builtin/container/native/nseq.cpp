#include "../tucontainable.inl"
#include "nseq.hpp"

namespace namu {

    NAMU(DEF_ME(nseq))

    me::nseq(nint start, nint end): _start(start), _end(end) {
        _updateStep();
    }

    me::nseq(nint start, nint end, nint step): _start(start), _end(end), _step(step) {}

    nint& me::operator[](nidx n) {
        return get(n);
    }

    nint me::getStart() const {
        return _start;
    }

    nint me::getEnd() const {
        return _end;
    }

    nint me::getStep() const {
        return _step;
    }

    void me::rel() {}

    nbool me::add(const iter& at, const nint& new1) {
        return false;
    }

    void me::add(const iter& at, const iter& from, const iter& to) {}

    nbool me::add(nidx n, const nint& new1) {
        return false;
    }

    nbool me::set(const iter& at, const nint& new1) {
        return false;
    }

    nbool me::set(nidx n, const nint& new1) {
        return false;
    }

    nbool me::del(const iter& it) {
        return false;
    }

    nbool me::del(const iter& from, const iter& end) {
        return false;
    }

    nbool me::del(nidx n) {
        return false;
    }

    void me::_updateStep() {
        _step = _end >= _start ? 1 : -1;
    }

    ncnt me::len() const {
        return abs(_end - _start);
    }

    me::iteration* me::_onMakeIteration(ncnt step) const {
        me* unconst = const_cast<me*>(this);
        return new nseqIteration(*unconst, step);
    }

    nint& me::get(nidx n) {
        static nint inner;
        if(n >= len()) n = len() - 1;
        if(n < 0) n = 0;

        return inner = _start + _step * n;
    }

    nbool me::has(nidx n) const {
        return len() > n && n >= 0;
    }
}
