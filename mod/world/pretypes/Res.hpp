#pragma once

#include "../msg-usr/Object.hpp"

namespace wrd
{
	class Res : public Object
	{	WRD_CLASS_DECL(Res, Object)
		//	TODO: fill this.
	public:
		explicit operator wbool() const;
		virtual wbool isGood() const = 0;
		wbool isErr() const;
		//	TODO: imple these funcs.
		Res& warn(...);
		Res& err(...);
		Res& info(...);
		Res& dbg(...);

		template <typename T> T returns() { return nulOf<T>(); }
		template <typename T> T returns(T value) { return value; }
	};
}
