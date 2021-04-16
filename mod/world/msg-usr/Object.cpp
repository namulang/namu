#include "Object.hpp"
#include "../meta.hpp"

namespace wrd
{
#define ME Object
	WRD_CLASS_DEF(ME)

	Container& ME::getShared() {	/* TODO: return */ return nulOf<Container>(); }
	const Container& ME::getShared() const { /* TODO: */ return nulOf<const Container>(); }
	Container& ME::getVars() {	/* TODO: return */ return nulOf<Container>(); }
	const Container& ME::getVars() const { /* TODO: */ return nulOf<const Container>(); }

	Strong ME::use(Msg& msg)
	{
		//	TODO:
		return Strong();
	}

	CStrong ME::use(Msg& msg) const
	{
		//	TODO:
		return CStrong();
	}

	wbool ME::canUse(const Msg& msg) const
	{
		//	TODO:
		return false;
	}

	const Origin& ME::getOrigin() const
	{
		//	TODO:
		return nulOf<const Origin>();
	}

	Res& ME::_initNodes()
	{	//	TODO:
		return wasgood;
	}
}
	
