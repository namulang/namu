#pragma once

#include "../common.hpp"

namespace wrd {

	class immutableTactic : public strTactic {
		WRD(ME(immutableTactic, strTactic))
		friend class ref;

	public:
		wbool bind(binder& me, const instance& it) override;

	public:
		static me singletone;
	};
}
