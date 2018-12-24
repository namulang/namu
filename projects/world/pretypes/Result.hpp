#pragma once

#include "../msg-usrs/Object.hpp"

namespace wrd
{
	class Result : public Object
	{	WRD_CLASS(Result, Object)
		//	TODO: fill this.
	public:
		operator wbool() { return isErr(); }
		wbool isErr() const;
		wbool isWarn() const;
		wbool isInfo() const;
		/*wint warn(.....);
		wint err(....);
		wint info(....);
		wint dbg(..);

		template <typename T>
		T returns() {
			return nulr<T>::null();
		}
		template <typename T>
		T returns(T value) {
			return value;
		}*/
	};
}
