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
	Chunk& THIS::get(const Instance& it) { return *(Chunk*)_get(it.getId().s.chk_n); }
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
		void* ret = _chunks[n]->new1();
		Instance::_vault.set(ret, n);
		return ret;
	}

	Res& THIS::del(void* pt, wcnt sz)
	{
		//	in fact, cast wasn't be deallocated yet:
		//		if we guarrantee that destructor didn't change its _id value,
		//		_id will keep its value till now.
		widx chk_n = ((Instance*) pt)->_id.s.chk_n;
		return _chunks[chk_n]->del(pt, sz);
	}

	widx THIS::_findCapable()
	{
		wcnt sz = _chunks.size();
		widx end = _s;

		do
		{
			const Chunk& e = get(_s);
			if(e.isExist() && e.isCapable())
				return _s;
			_s++;
			if(_s >= sz) _s = 0;
		} while(_s != end);

		resize(getLen() + 1);
		return _s;
	}

	wbool THIS::has(const Instance& it) const { return _chunks[it.getId().s.chk_n]->has(it); }

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
