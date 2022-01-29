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
			_report.bind(report);
			_verifier = &veri;
		}

	protected:
		template <typename ErrT, typename... Args>
		wbool _warn(Args... args) {
			_report->add(new ErrT(err::WARN, args...));
            return false;
		}
		template <typename ErrT, typename... Args>
		wbool _err(Args... args) {
			_report->add(new ErrT(err::ERR, args...));
            return true;
		}
		template <typename ErrT, typename... Args>
		wbool _info(Args... args) {
			_report->add(new ErrT(err::INFO, args...));
            return false;
		}

		wbool _verify(const typeProvidable& it, errReport& report);

        const verifier& _getVerifier() const { return *_verifier; }

	protected:
		tstr<errReport> _report;
		const verifier* _verifier;
	};

	typedef std::vector<verification*> verifications;
	typedef std::unordered_map<void*, verifications> verificationMap;
}
