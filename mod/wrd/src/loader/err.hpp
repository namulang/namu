#pragma once

#include "../ast/point.hpp"
#include "../common/wrdMetaExtension.hpp"
#include "../type/wtype.hpp"

namespace wrd {

	struct err : public instance {
		WRD(ME(err, instance),
			TYPE(wtype),
			INIT_META(me))

	public:
		enum type {
			ERR = 0,
			WARN,
			INFO,
		};

		err(err::type t, wcnt errCode, const std::string& errMsg)
			: super(), fType(t), code(errCode), msg(errMsg) {}

		err::type fType;
		wcnt code;
		std::string msg;
	};

	struct srcErr : public err {
		WRD(ME(srcErr, err),
			TYPE(wtype),
			INIT_META(me))

	public:
		srcErr(err::type t, wcnt errCode, const std::string& errMsg, const area& srcStart, const area& srcEnd)
			: super(t, errCode, errMsg), start(srcStart), end(srcEnd) {}

		area start;
		area end;
	};
}
