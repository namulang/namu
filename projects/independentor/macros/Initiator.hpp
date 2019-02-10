#pragma once

#define WRD_INITIATOR(name, ...)									\
	static Initiator WRD_CONCAT(__initi__ ## name ##_, __COUNTER__) ([]() {\
		WRD_UNWRAP __VA_ARGS__										\
	});

namespace wrd
{
	///	Initiator can runs statements before main().
	///	@Usage	just @refer WRD_INITIATOR or,
	//			static<optional> Initiator <name>([]() { <your codes> });
	struct Initiator
	{
		template <typename T>
		Initiator(T func) { func(); }
	};
}

