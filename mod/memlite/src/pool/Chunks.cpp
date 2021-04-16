#include "Chunks.hpp"
#include "../interface/Instance.hpp"

namespace wrd {

    WRD_DEF_ME(Chunks, Allocator)

    me::Chunks(wcnt blkbyte) : super(blkbyte), _s(0) {}
    me::~Chunks() { _rel(); }

    Chunk& me::operator[](widx n) { return get(n); }
    Chunk& me::operator[](const Instance& inst) { return get(inst); }

    Chunk& me::get(widx n) { return *(Chunk*)_get(n); }
    Chunk& me::get(const Instance& it) { return *(Chunk*)_get(it.getId().chkN); }

    wbool me::rel() { return _rel(); }
    wcnt me::getLen() const { return _chunks.size(); }
    wcnt me::getSize() const { return getLen(); }

    void* me::new1() {
        widx n = _findCapable();
        void* ret = _chunks[n]->new1();
        Instance::_vault.set(ret, n);
        return ret;
    }

    wbool me::del(void* pt, wcnt sz) {
        //  in fact, cast wasn't be deallocated yet:
        //      if we guarrantee that destructor didn't change its _id value,
        //      _id will keep its value till now.
        widx chkN = ((Instance*) pt)->_id.chkN;
        return _chunks[chkN]->del(pt, sz);
    }

    widx me::_findCapable() {
        wcnt sz = _chunks.size();
        widx end = _s;

        do {
            Chunk& e = get(_s);
            if(!nul(e) && e.isCapable())
                return _s;
            _s++;
            if(_s >= sz) _s = 0;
        } while(_s != end);

        resize(getLen() + 1);
        return _s;
    }

    wbool me::has(const Instance& it) const { return _chunks[it.getId().chkN]->has(it); }

    wbool me::resize(wcnt new1) {
        _s = _chunks.size();
        if(_s > new1) _s = new1-1;
        if(_s < 0) _s = 0;

        while(_chunks.size() < new1)
            _chunks.push_back(new Chunk(getBlkSize()));
        return true;
    }

    wbool me::_rel() {
        for(Chunk* e : _chunks)
            e->rel();
        _chunks.clear();
        _s = 0;
        return true;
    }

    void* me::_get(widx n) {
        if(n < 0 || n >= getLen()) return nullptr;

        return _chunks[n];
    }
}
