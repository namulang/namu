#include "Pool.hpp"
#include "../meta.hpp"
#include "../pretypes.hpp"

namespace wrd
{
#define THIS Pool
	WRD_CLASS_DEF(THIS)

	THIS::Pool() {}
	THIS::~Pool() { release(); }

	Chunks& THIS::operator[](widx n) { return get(n); }
	Chunks& THIS::operator[](const Instance& inst) { return get(inst); }
	const Chunks& THIS::operator[](widx n) const { return get(n); }
	const Chunks& THIS::operator[](const Instance& inst) const { return get(inst); }
	Chunks& THIS::get(const Instance& inst) { return get(inst.getClass().getSize()); }
	const Chunks& THIS::get(const Instance& inst) const { return get(inst.getClass().getSize()); }
	const Chunks& THIS::get(widx n) const { return ((Pool*)this)->get(n); }
	Chunks& THIS::get(widx n) { return *(Chunks*)_get(n); }

	wbool THIS::has(const Instance& it) const
	{
		const Chunks& got = get(it.getClass().getSize());
		WRD_IS_NULL(got, wasnull, false)

		return got.has(it);
	}

	wcnt THIS::getSize() const { return _chunkset.capacity(); }
	wcnt THIS::getLen() const { return _chunkset.size(); }

	Res& THIS::release()
	{
		for(Chunks* e : _chunkset)
		{
			if (!e) continue;
			e->release();
			delete e;
		}

		_chunkset.clear();
		return wasgood;
	}

	void* THIS::_get(widx n)
	{
		if(0 > n) return NULL;

		while((int)_chunkset.size() - 1 < n)
			_chunkset.push_back(NULL);

		if(!_chunkset[n])
			_chunkset[n] = new Chunks(n);

		return _chunkset[n];
	}
}
