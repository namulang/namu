#pragma once

#include <unordered_map>
#include "../errReport.hpp"

namespace wrd {

	class verifier;

	class verification : public typeProvidable {
		WRD(ME(verification),
			INIT_META(me))

	public:
		virtual void verify(verifier& veri, const typeProvidable& it) {
			_verifier = &veri;
		}

	protected:
		template <typename... Args>
		wbool _warn(Args... args);
		template <typename... Args>
		wbool _err(Args... args);
		template <typename... Args>
		wbool _info(Args... args);

        verifier& _getVerifier() { return *_verifier; }

	protected:
		verifier* _verifier;
	};

	typedef std::vector<verification*> verifications;
	typedef std::unordered_map<void*, verifications> verificationMap;
}
