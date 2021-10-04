#pragma once

#include "verification.hpp"

namespace wrd {

	template <typename T>
	class tverification : public verification {
		WRD(ME(tverification, verification),
			INIT_META(me))
		typedef wtype metaType;

	public:
		const wtype& getType() const override {
			return ttype<T>::get();
		}
		void verify(const typeProvidable& it, errReport& report) override {
			super::verify(it, report);
			_onVerify((T&) it, report);
		}

	protected:
		virtual wbool _onVerify(const T& it, errReport& report) = 0;
	};
}
