#pragma once

#include "Thing.inl"
#include "../pretypes/Str.hpp"
#include "../containers/Array.hpp"

namespace wrd
{
	class Msg : public Thing
	{	WRD_CLASS_DECL(Msg, Thing)
	public:
		/* TODO: Msg();
		Msg(const Str& new_name); */
		//TODO: Msg(.....);

		/*TODO: Str& getName() { return _name; }
		const Str& getName() const { return _name; } */

		//	사용자가 World코드에서 함수의 인자로 const를 준경우는 Args의 임의의 원소1개가 Refer<const T>로 되어있을 것이다.
		/*TODO: Manipulatable& getArgs() {
			return _args;
		}
		const Manipulatable& getArgs() const {
			return _args;
		}*/

	private:
		/*TODO: Str _name;
		Array _args; */

	public:
		/* TODO: static Object* _thisptr; // Message는_name_thisptr_args를_모두_하나의_Array로_구성한다 
		friend class Object; // _thisptr 조작을 위해
		static Object& getThis() { return *_thisptr; }
		static Result& _setThis(Object& newone) { _thisptr = &newone; }

		static Method* _me;
		friend class Method;
		static const Method& getMe() const { return *_me; }
		static Result& _setMe(Method& newone) { _me = newone; } */
	};
}
