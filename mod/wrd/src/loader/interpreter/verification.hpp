#pragma once

#include <unordered_map>
#include "../errReport.hpp"

namespace wrd {

	class verifier;

	class verification : public typeProvidable {
		WRD(ME(verification),
			INIT_META(me))

	public:
		virtual void verify(const verifier& veri, const typeProvidable& it, errReport& report) {
			_report = &report;
			_verifier = &veri;
		}

	protected:
		template <typename ErrT, typename... Args>
		wbool _warn(Args... args) {
			return _report->add(new ErrT(err::WARN, args...));
		}
		template <typename ErrT, typename... Args>
		wbool _err(Args... args) {
			return _report->add(new ErrT(err::ERR, args...));
		}
		template <typename ErrT, typename... Args>
		wbool _info(Args... args) {
			return _report->add(new ErrT(err::INFO, args...));
		}

		wbool _verify(const typeProvidable& it, errReport& report);

	protected:
		errReport* _report;
		const verifier* _verifier;
	};

	typedef std::vector<verification*> verifications;
	typedef std::unordered_map<void*, verifications> verificationMap;
}
