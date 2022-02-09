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
        static err* newErr(wcnt errCode, ...);
        static err* newErr(const area& src, wcnt errCode, ...);
        static err* newWarn(wcnt errCode, ...);
        static err* newWarn(const area& src, wcnt errCode, ...);
        static err* newInfo(wcnt errCode, ...);
        static err* newInfo(const area& src, wcnt errCode, ...);

	public:
		err::type fType;
		wcnt code;
		std::string msg;
		static constexpr wint BASE_TEST_CODE = 99999990; // not to be duplicated.

    private:
        std::string _format(const std::string& fmt, va_list args);
        err* _newRes(type t, wcnt errCode, va_list args) {
            return new err(t, errCode, args);
        }
        err* _newRes(const area& src, type t, wcnt errCode, va_list args);
	};

    struct dummyErr : public err {
        WRD(ME(dummyErr, err),
            TYPE(wtype),
            INIT_META(me))

    public:
        dummyErr(): super(err::ERR, 0) {}

    public:
        void log() const override {}
    };

	struct srcErr : public err {
		WRD(ME(srcErr, err),
			TYPE(wtype),
			INIT_META(me))

	public:
        template <typename... Args>
        srcErr(err::type t, const area& src, wcnt errCode, Args... args): super(t, errCode, args...), srcArea(src) {}

		area srcArea;

    public:
        void log() const override {
            switch(fType) {
                case ERR: WRD_E("%d:%d: err(%d): %s", code, srcArea.start.row, srcArea.start.col, msg.c_str()); break;
                case WARN: WRD_W(":%d:%d: warn(%d): %s", code, srcArea.start.row, srcArea.start.col, msg.c_str()); break;
                case INFO: WRD_I(":%d:%d: info(%d): %s", code, srcArea.start.row, srcArea.start.col, msg.c_str()); break;
            }
        }
	};
}
