#include "Object.hpp"
#include "../meta.hpp"

namespace wrd
{
#define THIS Object
	WRD_CLASS_DEF(THIS)

	Container& THIS::getShared() {	/* TODO: return */ return nulOf<Container>(); }
	const Container& THIS::getShared() const { /* TODO: */ return nulOf<const Container>(); }
	Container& THIS::getVars() {	/* TODO: return */ return nulOf<Container>(); }
	const Container& THIS::getVars() const { /* TODO: */ return nulOf<const Container>(); }

	Strong THIS::use(Msg& msg)
	{
		//	TODO:
		return Strong();
	}

	CStrong THIS::use(Msg& msg) const
	{
		//	TODO:
		return CStrong();
	}

	wbool THIS::canUse(const Msg& msg) const
	{
		//	TODO:
		return false;
	}

	const Origin& THIS::getOrigin() const
	{
		//	TODO:
		return nulOf<const Origin>();
	}

	Res& THIS::_initNodes()
	{	//	TODO:
		return wasgood;
	}
}
	
