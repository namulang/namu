#pragma once

#include "../msg-usr/Object.hpp"

namespace wrd
{
	class Res : public Object
	{	WRD_CLASS_DECL(Res, Object)
		//	TODO: fill this.
	public:
		operator wbool() const;
		wbool isErr() const;
		wbool isWarn() const;
		wbool isInfo() const;
		//	TODO: imple these funcs.
		Res& warn(...);
		Res& err(...);
		Res& info(...);
		Res& dbg(...);
		/*
		template <typename T>
		T returns() {
			return nulr<T>();
		}
		template <typename T>
		T returns(T value) {
			return value;
		}*/
	};
}
