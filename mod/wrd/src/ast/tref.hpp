#pragma once

#include "refTactic.hpp"

namespace wrd {

	class node;

	template<typename T>
	class tref : public tstr<T> {
		WRD(ME(tref, tstr<T>),
			INIT_META(me))

		static_assert(tifSub<T, node>::is == true, "type T should be derived from the 'node' class.");

	public:
		tref(): super(refTactic::_singletone) {}
		tref(const T& it): super(refTactic::_singletone) { this->bind(it); }
		tref(const T* it): super(refTactic::_singletone) { this->bind(it); }
		tref(const me& rhs): super(refTactic::_singletone) { this->bind(rhs.get()); }
		explicit tref(const binder& rhs): super(refTactic::_singletone) { this->bind(rhs.get()); }
	};

	typedef tref<node> ref;
}
