#pragma once

#include "../bind/TBindable.inl"
#include "../base/TGettable.inl"

namespace wrd
{
	typedef TBindable<TGettable<Instance, Instance> > Trace;
}
