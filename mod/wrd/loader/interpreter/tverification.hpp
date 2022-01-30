#pragma once

#include "verification.inl"

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

		void verify(verifier& veri, const typeProvidable& it) override {
			super::verify(veri, it);
			_onVerify((T&) it);
		}

	protected:
		virtual wbool _onVerify(const T& it) = 0;
	};
}
