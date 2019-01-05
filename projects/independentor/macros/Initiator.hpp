#pragma once

#define WRD_INITIATOR(...)									\
	Initiator WRD_CONCAT(__initi__, __COUNTER__) ([]() {	\
		WRD_UNWRAP(__VA_ARGS__)								\
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

