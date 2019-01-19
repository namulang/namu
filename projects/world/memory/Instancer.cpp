#include "Instancer.hpp"
#include "../meta.hpp"
#include "../pretypes.hpp"

namespace wrd
{
#define THIS Instancer
	WRD_CLASS_DEF(THIS)

	Res& THIS::bind(Instance& new1)
	{
		Unit& new1 = *(Unit*) _akashic.new1();
		return new1.blk.bind(it);
	}

	Res& THIS::unbind(Instance& old)
	{
		Unit& un = _akashic[it.getId()];
		return _akashic.del(&un, sizeof(Unit));
	}

	void* THIS::_new1(size_t sz) { return _pool[sz].new1(); }
	void THIS::_del(void* pt, wcnt sz) { _pool[sz].del(pt, sz); }
	const Pool& THIS::getPool() const { return _pool; }
	const Akashic& THIS::getAkashic() const { return _akashic; } 

#undef THIS
}
