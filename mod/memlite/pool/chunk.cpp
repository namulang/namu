#include "chunk.hpp"

namespace namu {

    WRD_DEF_ME(chunk, allocator)

    me::chunk(wcnt blksize, wcnt sz)
        : super(blksize), _head(0), _len(0), _sz(0), _heap(0) {
            _resize(sz);
        }
    me::~chunk() { me::rel(); }
    wcnt me::len() const { return _len; }
    wcnt me::size() const { return _sz; }

    wbool me::_resize(wcnt newSz) {
        //  pre:
        if(newSz < MIN_SZ) newSz = MIN_SZ;
        if(newSz == _sz) return false;

        //  main:
        wuchar* new1 = (wuchar*) _allocHeap(newSz);
        // considered if user resize far smaller rather than what it had.
        wcnt min = _sz < newSz ? _sz : newSz;
        memcpy(new1, _heap, min*_getRealBlkSize());

        //  post:
        _freeHeap(&_heap);
        _heap = new1;
        _sz = newSz;
        return _index(_len);
    }

    void* me::new1() {
        if(_len >= _sz)
            return WRD_E("new1() failed. chunk was full. you should have not called this in this situtation."), nullptr;

        widx* ret = (widx*)_get(_head);
        if(nul(ret))
            return nullptr;

        _head = *ret;
        _len++;
        return ret;
    }

    wbool me::del(void* used, wcnt) {
        if(!used) return false;

        *(widx*)used = _head;
        _head = ((wuchar*)used - _heap) / _getRealBlkSize();
        _len--;
        if(_head < 0)
            return WRD_E("chunk corrupted! used(%x) apparently wasn't on heap(%x).", used, _heap), false;
        return true;
    }

    wbool me::rel() {
        _len = _sz = 0;
        _head = 0;
        return _freeHeap(&_heap);
    }

    wbool me::has(const instance& it) const {
        void* pt = (void*) &it;
        return _heap && _heap <= pt && pt <= _getEOB();
    }

    wuchar* me::_getHeap() { return _heap; }

    void* me::_get(widx n) {
        if(n < 0 || n >= size()) return nullptr;

        return _heap + n*_getRealBlkSize();
    }

    wuchar* me::_getEOB() {
        wuchar* org = (wuchar*) _get(_sz - 1);
        if(!org)
            return nullptr;

        return org + _getRealBlkSize() - 1;
    }

    wbool me::_index(widx start) {
        for(wcnt n=start; n < _sz ;n++)
            *(widx*)_get(n) = n+1;

        return true;
    }

    wcnt me::_getRealBlkSize() {
        wcnt sz = getBlkSize();
        return sz < 4 ? 4 : sz;
    }

    void* me::_allocHeap(wcnt newSz) { return malloc(newSz * _getRealBlkSize()); }

    wbool me::_freeHeap(wuchar** heap) {
        if(*heap) {
            free(*heap);
            *heap = NULL;
        }
        return true;
    }
}
