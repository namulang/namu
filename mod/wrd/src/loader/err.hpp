#pragma once

#include "../ast/point.hpp"
#include "../common/wrdMetaExtension.hpp"
#include "../type/wtype.hpp"
#include <unordered_map>

namespace wrd {

	typedef std::unordered_map<widx, std::string> msgMap;

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

	public:
		err(err::type t, wcnt errCode): super(), fType(t), code(errCode) {
			msg = getErrMsgs().at(code);
		}

	public:
		void log() const {
			switch(fType) {
				case ERR: WRD_E("%s", msg.c_str()); break;
				case WARN: WRD_W("%s", msg.c_str()); break;
				case INFO: WRD_I("%s", msg.c_str()); break;
			}
		}
		static const msgMap& getErrMsgs();

	public:
		err::type fType;
		wcnt code;
		std::string msg;
		static constexpr wint BASE_TEST_CODE = 99999990; // not to be duplicated.
	};

	struct srcErr : public err {
		WRD(ME(srcErr, err),
			TYPE(wtype),
			INIT_META(me))

	public:
		srcErr(err::type t, wcnt errCode, const area& srcStart, const area& srcEnd)
			: super(t, errCode), start(srcStart), end(srcEnd) {}

		area start;
		area end;
	};
}
