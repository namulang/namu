#include "Instancer.hpp"
#include "../meta.hpp"
#include "../pretypes.hpp"

namespace wrd
{
#define THIS Instancer
	WRD_CLASS_DEF(THIS)

	Res& THIS::bind(Instance& new1)
	{
		Unit& un = *(Unit*) _akashic.new1();
		return un.blk.bind(new1);
	}

	Res& THIS::unbind(Instance& old)
	{
		if( ! _hasInstanceBlock(old)) return wascancel; // optimization.
		Unit& un = _akashic[old.getId()];
		return _akashic.del(&un, sizeof(Unit));
	}

	void* THIS::_new1(size_t sz) { return _pool[sz].new1(); }
	void THIS::_del(void* pt, wcnt sz) { _pool[sz].del(pt, sz); }
	const Pool& THIS::getPool() const { return _pool; }
	const Akashic& THIS::getAkashic() const { return _akashic; } 
	wbool THIS::_hasInstanceBlock(const Instance& it) const { return it._id.s.blk_n != WRD_INDEX_ERROR; }


#undef THIS
}
