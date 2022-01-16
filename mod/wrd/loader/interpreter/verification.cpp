#include "verification.hpp"
#include "verifier.hpp"

namespace wrd {

	WRD_DEF_ME(verification)

	wbool me::_verify(const typeProvidable& it, errReport& report) {
		_verifier->verify(it, report);
		return false;
	}
}
