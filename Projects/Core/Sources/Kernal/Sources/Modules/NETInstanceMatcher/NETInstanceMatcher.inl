#pragma once

#include "../NEMatcher/NEMatcher.hpp"

namespace NE
{
	template <typename T>
	class NETInstanceMatcher : public NEMatcher
	{
		NE_DECLARE_CLASS_ONLY(NETInstanceMatcher, NEMatcher)

	public:
		NETInstanceMatcher(const T& instance_target);

	public:
		virtual type_bool operator()() const;

	public:
		const T& getTarget() const;

	private:
		const T& _target;
	};
}