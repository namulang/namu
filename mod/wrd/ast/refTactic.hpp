#pragma once

#include "../common.hpp"

namespace wrd {

	class refTactic : public strTactic {
		WRD(ME(refTactic, strTactic))
		friend class ref;

	public:
		wbool bind(binder& me, const instance& it) override;

	private:
		static me _singletone;
	};
}
