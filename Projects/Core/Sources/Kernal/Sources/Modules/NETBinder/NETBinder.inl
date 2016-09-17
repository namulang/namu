#pragma once

#include "../NETWeakBinder/NETWeakBinder.inl"

namespace NE
{
	template <typename T>
	class NETBinder : public NETWeakBinder<T>
	{
		NE_DECLARE_CLASS(NETBinder, NETWeakBinder<T>)

	public:
		NETBinder();
		NETBinder(const T& target);
		NETBinder(const Super& rhs);
		virtual ~NETBinder();

	public:
		virtual type_result bind(const T& target);
		virtual type_result unbind();

	private:
		type_result _bind(const T& target);
		type_result _unbind();
	};
}