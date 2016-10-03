#pragma once

#include "../NETCollectorProxy/NETCollectorProxy.inl"
#include "../NETBinder/NETBinder.inl"

namespace NE
{
	template <typename Collector>
	using NETDeeper = NETCollectorProxy<Collector, NETBinder>;
}