#pragma once

#include "TWeak.hpp"

namespace wrd {

	template <typename T>
	class TStrong : public TWeak<T> {
        WRD_DECL_THIS(TStrong, TWeak<T>)
        WRD_INIT_META(This)

	public:
        //  TStrong:
		TStrong();
		TStrong(T& it);
		TStrong(T* it);
		TStrong(const Bind& rhs);

        using Super::operator=;
	};

	template <typename T>
	class TStrong<const T> : public TWeak<const T> {
        WRD_DECL_THIS(TStrong, TWeak<T>)
        WRD_INIT_META(This)

	public:
        //  TStrong:
		TStrong();
		TStrong(T& it);
		TStrong(T* it);
		TStrong(const T& it);
		TStrong(const T* it);
		TStrong(const Bind& rhs);

        using Super::operator=;
	};
}
