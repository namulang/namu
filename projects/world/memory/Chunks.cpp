#include "Chunks.hpp"
#include "../meta.hpp"
#include "../pretypes.hpp"
#include "../base/Instance.hpp"

namespace wrd
{
#define THIS Chunks
	WRD_CLASS_DEF(THIS)

	THIS::Chunks(wcnt blkbyte) : Super(blkbyte), _s(0) {}
	THIS::~Chunks() { _release(); }

	Chunk& THIS::operator[](widx n) { return get(n); }
	Chunk& THIS::operator[](const Instance& inst) { return get(inst); }
	const Chunk& THIS::operator[](widx n) const { return get(n); }
	const Chunk& THIS::operator[](const Instance& inst) const { return get(inst); }

	Chunk& THIS::get(widx n) { return *(Chunk*)_get(n); }
	Chunk& THIS::get(const Instance& it) { return *(Chunk*)_get(it.getId().sep.chk_n); }
	const Chunk& THIS::get(const Instance& it) const { return ((Chunks*)this)->get(it); }
	const Chunk& THIS::get(widx n) const { return ((Chunks*)this)->get(n); }

	Res& THIS::release()
	{
		_release();
		return wasgood;
	}

	wcnt THIS::getLen() const { return _chunks.size(); }
	wcnt THIS::getSize() const { return getLen(); }

	void* THIS::new1()
	{
		widx n = _findCapable();
		Instance::_chk_n_from_alloc = n;
		return _chunks[n]->new1();
	}

	Res& THIS::del(void* pt, wcnt sz)
	{
		return _chunks[Instance::_from_dtor.sep.chk_n]->del(pt, sz);
	}

	widx THIS::_findCapable()
	{
		int end = _s;
		for(; _s != end ;_s++)
		{		
			if(_s > _chunks.size()) _s = 0;

			const Chunk& e = *(_chunks[_s]);
			if(e.isNull() || e.isFull()) continue;
			return _s;
		}

		resize(getLen() + 1);
		return _s;
	}

	wbool THIS::has(const Instance& it) const
	{
		return _chunks[it.getId().sep.chk_n]->has(it);
	}

	Res& THIS::resize(wcnt new1)
	{
		_s = _chunks.size();
		if(_s > new1) _s = new1-1;
		if(_s < 0) _s = 0;

		while(_chunks.size() < new1)
			_chunks.push_back(new Chunk(getBlkSize()));
		return wasgood;
	}

	Res& THIS::_release()
	{
		for(Chunk* e : _chunks)
			e->release();
		_chunks.clear();
		_s = 0;
		return wasgood;
	}

	void* THIS::_get(widx n)
	{
		if (0 > n || n >= _chunks.size())
			return NULL;

		return _chunks[n];
	}
}
