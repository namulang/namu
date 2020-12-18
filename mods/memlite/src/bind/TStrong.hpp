#pragma once

#include "TWeak.hpp"

namespace wrd { namespace memlite {

	template <typename T>
	class TStrong : public TWeak<T> {
        WRD_DECL_THIS(TStrong, TWeak<T>)

	public:
		TStrong();
		TStrong(T& it);
		TStrong(T* it);
		TStrong(const This& rhs);
		virtual ~TStrong();

		This& operator=(const This& rhs);

		virtual wbool unbind();

	protected:
		//Bind:
		virtual wbool _bind(const Instance& it);
	};

	template <typename T>
	class TStrong<const T> : public TWeak<const T> {
        WRD_DECL_THIS(TStrong, TWeak<const T>)

	public:
		TStrong();
		TStrong(T& it);
		TStrong(T* it);
		TStrong(const T& it);
		TStrong(const T* it);
		TStrong(const This& rhs);
		TStrong(const TStrong<T>& rhs);
		virtual ~TStrong();

		This& operator=(const This& rhs);
		This& operator=(const TStrong<T>& rhs);

		virtual wbool unbind();

	protected:
		//Bind:
		virtual wbool _bind(const Instance& it);
	};
}}
