#include "chunks.hpp"
#include "../interface/instance.hpp"

namespace namu {

    WRD_DEF_ME(chunks, allocator)

    me::chunks(wcnt blkbyte) : super(blkbyte), _s(0) {}
    me::~chunks() { _rel(); }

    chunk& me::operator[](widx n) { return get(n); }
    chunk& me::operator[](const instance& inst) { return get(inst); }

    chunk& me::get(widx n) { return *(chunk*)_get(n); }
    chunk& me::get(const instance& it) { return *(chunk*)_get(it.getId().chkN); }

    wbool me::rel() { return _rel(); }
    wcnt me::len() const { return _chunks.size(); }
    wcnt me::size() const { return len(); }

    void* me::new1() {
        widx n = _findCapable();
        void* ret = _chunks[n]->new1();
        instance::_vault.set(ret, n);
        return ret;
    }

    wbool me::del(void* pt, wcnt sz) {
        //  in fact, cast wasn't be deallocated yet:
        //      if we guarrantee that destructor didn't change its _id value,
        //      _id will keep its value till now.
        widx chkN = ((instance*) pt)->_id.chkN;
        return _chunks[chkN]->del(pt, sz);
    }

    widx me::_findCapable() {
        wcnt sz = _chunks.size();
        widx end = _s;

        do {
            chunk& e = get(_s);
            if(!nul(e) && e.isCapable())
                return _s;
            _s++;
            if(_s >= sz) _s = 0;
        } while(_s != end);

        resize(len() + 1);
        return _s;
    }

    wbool me::has(const instance& it) const { return _chunks[it.getId().chkN]->has(it); }

    wbool me::resize(wcnt new1) {
        _s = _chunks.size();
        if(_s > new1) _s = new1-1;
        if(_s < 0) _s = 0;

        while(_chunks.size() < new1)
            _chunks.push_back(new chunk(getBlkSize()));
        return true;
    }

    wbool me::_rel() {
        for(chunk* e : _chunks)
            e->rel();
        _chunks.clear();
        _s = 0;
        return true;
    }

    void* me::_get(widx n) {
        if(n < 0 || n >= len()) return nullptr;

        return _chunks[n];
    }
}
