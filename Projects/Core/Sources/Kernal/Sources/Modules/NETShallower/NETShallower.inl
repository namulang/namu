#pragma once

#include "../NETCollectorProxy/NETCollectorProxy.inl"
#include "../NETWeakBinder/NETWeakBinder.inl"

namespace NE
{
	template <typename Collector>
	using NETShallow = NETCollectorProxy<Collector, NETWeakBinder>;
}