#include "Object.hpp"
#include "../meta.hpp"

namespace wrd
{
#define THIS Object
	WRD_CLASS_DEF(THIS)

	Container& THIS::getShared() {	/* TODO: return */ return nulr<Container>(); }
	const Container& THIS::getShared() const { /* TODO: */ return nulr<const Container>(); }
	Container& THIS::getVars() {	/* TODO: return */ return nulr<Container>(); }
	const Container& THIS::getVars() const { /* TODO: */ return nulr<const Container>(); }

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
		return nulr<const Origin>();
	}

	Res& THIS::_initNodes()
	{	//	TODO:
		return wasgood;
	}
}
	
