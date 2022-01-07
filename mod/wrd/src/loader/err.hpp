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
		err(err::type t, wcnt errCode, ...): super(), fType(t), code(errCode) {
            va_list args;
            va_start(args, errCode);

            msg = _format(getErrMsgs().at(code), args);
            va_end(args);
		}
        err(err::type t, wcnt errCode, va_list args): super(), fType(t), code(errCode) {
            msg = _format(getErrMsgs().at(code), args);
        }

	public:
		virtual void log() const {
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

    private:
        std::string _format(const std::string& fmt, va_list args);
	};

	struct srcErr : public err {
		WRD(ME(srcErr, err),
			TYPE(wtype),
			INIT_META(me))

	public:
        template <typename... Args>
        srcErr(err::type t, wcnt errCode, const area& newArea, Args... args): super(t, errCode, args...), srcArea(newArea) {}

		area srcArea;

    public:
        void log() const override {
            switch(fType) {
                case ERR: WRD_E("err: %s at %d, %d", msg.c_str(), srcArea.start.row, srcArea.start.col); break;
                case WARN: WRD_W("err: %s at %d, %d", msg.c_str(), srcArea.start.row, srcArea.start.col); break;
                case INFO: WRD_I("err: %s at %d, %d", msg.c_str(), srcArea.start.row, srcArea.start.col); break;
            }
        }
	};
}
