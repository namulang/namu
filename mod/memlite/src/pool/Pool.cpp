#include "Pool.hpp"
#include "../interface/Instance.hpp"

namespace wrd { namespace memlite {

	WRD_DEF_THIS(Pool, MemoryHaver)

	This::Pool() {}
	This::~Pool() { rel(); }

	Chunks& This::operator[](widx n) { return get(n); }
	Chunks& This::operator[](const Instance& inst) { return get(inst); }
	const Chunks& This::operator[](widx n) const { return get(n); }
	const Chunks& This::operator[](const Instance& inst) const { return get(inst); }
	Chunks& This::get(const Instance& inst) { return get(inst.getType().getSize()); }
	const Chunks& This::get(const Instance& inst) const { return get(inst.getType().getSize()); }
	const Chunks& This::get(widx n) const { return ((Pool*)this)->get(n); }
	Chunks& This::get(widx n) { return *(Chunks*)_get(n); }

	wbool This::has(const Instance& it) const {
		const Chunks& got = get(it.getType().getSize());
        WRD_NUL(got, false)

		return got.has(it);
	}

	wcnt This::getSize() const { return _chunks.capacity(); }
	wcnt This::getLen() const { return _chunks.size(); }

	wbool This::rel() {
		for(Chunks* e : _chunks) {
			if (!e) continue;
			e->rel();
			delete e;
		}

		_chunks.clear();
		return true;
	}

	void* This::_get(widx n) {
		if(0 > n) return WRD_NULL;

		while((int)_chunks.size() - 1 < n)
			_chunks.push_back(NULL);

		if(!_chunks[n])
			_chunks[n] = new Chunks(n);

		return _chunks[n];
	}
}}
