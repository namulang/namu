#pragma once

#include <unordered_map>
#include "../errReport.hpp"

namespace wrd {

	class verification : public typeProvidable {
		WRD(ME(verification),
			INIT_META(me))

	public:
		virtual void verify(const typeProvidable& it, errReport& report) {
			_report = &report;
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

	protected:
		errReport* _report;
	};

	typedef std::vector<verification*> verifications;
	typedef std::unordered_map<void*, verifications> verificationMap;
}
