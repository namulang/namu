#pragma once

#include "../common.hpp"

namespace wrd {

	class _wout immutableTactic : public strTactic {
		WRD(ME(immutableTactic, strTactic))

	public:
		wbool bind(binder& me, const instance& it) override;

	public:
		static me singletone;
	};
}
