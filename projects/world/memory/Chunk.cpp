#include "Chunk.hpp"
#include "../meta.hpp"
#include "../pretypes.hpp"

namespace wrd
{
#define THIS Chunk
	WRD_CLASS_DEF(THIS)

	THIS::THIS(wcnt blksize, wbool is_fixed)
		: Allocator(blksize), _head(0), _len(0), _sz(0), _heap(0), _is_fixed(is_fixed) {}
	THIS::~THIS() { _release(); }
	wcnt THIS::getLen() const { return _len; }
	wcnt THIS::getSize() const { return _sz; }

	void* THIS::new1()
	{
		if(	_len >= _sz	&& 
			resize((getSize() + 1) * 2))
			return NULL;

		widx* ret = (widx*)_get(_head);
		_head = *ret;
		_len++;
		return ret;
	}

	Res& THIS::del(void* used, wcnt)
	{
		*(widx*)used = _head;

		_head = ((wuchar*)used - _heap) / _getRealBlkSize();
		_len--;
		return wasgood;
	}

	Res& THIS::release()
	{
		_release();
		return Super::release();
	}

	Res& THIS::resize(wcnt new_size)
	{
		if(new_size < INIT_SZ) new_size = INIT_SZ;
		if(_is_fixed && new_size > INIT_SZ) new_size = INIT_SZ;
		if(new_size == _sz) return wasoob;
	
		wuchar* new1 = (wuchar*) _allocHeap(new_size);
		memcpy(new1, _heap, _sz*_getRealBlkSize());

		int prev_len = _len,
			prev_size = _sz;
		release();
		_len = prev_len;
		_heap = new1;
		_sz = new_size;
		return _index(prev_size);
	}

	wbool THIS::has(const Instance& it) const
	{
		void* pt = (void*)&it;
		return _heap && _heap <= pt && pt <= getEOB();
	}

	const wuchar* THIS::getEOB() const
	{
		WRD_UNCONST()
		return unconst._getEOB();
	}

	const wuchar* THIS::getHeap() const { return _heap; }
	wbool THIS::isFixed() const { return _is_fixed; }

	void* THIS::_get(widx n)
	{
		if(n < 0 || n >= _sz)
			return NULL;
		return _heap + n * _getRealBlkSize();
	}

	wuchar* THIS::_getEOB()
	{
		wuchar* org = (wuchar*) _get(_sz - 1);
		if( ! org)
			return NULL;

		return org + _getRealBlkSize() - 1;
	}

	Res& THIS::_index(widx start)
	{
		wuchar*	eob = _getEOB(),
			*	e = (wuchar*)_get(start);
		_head = start;
		widx* put = NULL;
		do {
			put = (widx*)e;
			*put = ++start;
		} while ((e += _getRealBlkSize()) < eob);

		*put = -1;
		return wasgood;
	}

	wcnt THIS::_getRealBlkSize() const
	{
		wcnt sz = getBlkSize();
		return sz < 4 ? 4 : sz;
	}

	void* THIS::_allocHeap(wcnt new_size) { return malloc(new_size * _getRealBlkSize()); }

	Res& THIS::_freeHeap(wuchar** heap)
	{
		if(*heap)
		{
			free(*heap);
			*heap = NULL;
		}
		return wasgood;
	}

	Res& THIS::_release()
	{
		_len = _sz = 0;
		return _freeHeap(&_heap);
	}
}
