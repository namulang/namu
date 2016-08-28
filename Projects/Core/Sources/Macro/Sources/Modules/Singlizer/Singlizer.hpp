#pragma once

//	Singlizer:
//		This macro is used for macro to ignore commas of arguments.
//		When macro expands, sometimes it treat comma of the value of a argument
//		as comma of the meaning of "delimeter".
//		For instance, it's about passing template class as the argument.
//
//			NE_DEFINE_CLASS(MyClass<int, float>)
//		
//		As you can see, user just tried to pass the single argument, but
//		when the compiler watches, it interpret this as 2 arguments.
//			1 : MyClass<int   2: float>
//		it can't understand that comma is part of the argument for some reason.
//		
//		So, when we've met the situation just like above, use NE_SINGLIZER and
//		paranthesis in order to let it understand that comma is just one of the
//		argument.
//
//		Usage:
//			NE_DEFINE_CLASS(NE_SINGLIZER(MyClass<int, float>))

#define NE_SINGLIZER(...)	__VA_ARGS__