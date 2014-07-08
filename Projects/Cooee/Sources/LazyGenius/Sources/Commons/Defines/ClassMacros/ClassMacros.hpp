#pragma once

#define FUNC_CLONE(CLASSNAME)	\
	NEObject& clone() const { return *(new CLASSNAME(*this)); }
#define FUNC_TO_OWNER(OWNER_CLASSNAME)	\
	OWNER_CLASSNAME* toOwner() { return (OWNER_CLASSNAME*) owner; }
#define FUNC_TO_CALLER(OWNER_CLASSNAME)	\
	OWNER_CLASSNAME& toCaller() { return (OWNER_CLASSNAME&) getCaller(); }