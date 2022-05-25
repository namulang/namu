#pragma once

#include "errCode.hpp"
#include "../ast/point.hpp"
#include "../common/wrdMetaExtension.hpp"
#include "../type/wtype.hpp"
#include <unordered_map>

namespace wrd {

	typedef std::unordered_map<widx, std::string> msgMap;

	struct _wout err : public instance {
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
		err(err::type t, wint newCode, ...): super(), fType(t), code((errCode) newCode) {
            va_list args;
            va_start(args, newCode);

            msg = _format(getErrMsg(code), args);
            va_end(args);
		}
        err(err::type t, int newCode, va_list args): super(), fType(t), code((errCode) newCode) {
            msg = _format(getErrMsg(code), args);
        }

	public:
		virtual void log() const {

            auto& log = logger::get();
			switch(fType) {
                case ERR:
                    std::cout << platformAPI::getConsoleFore(platformAPI::LIGHTRED);
                    log.dumpFormat("err%d(%s)", code, getErrName(code).c_str());
                    std::cout << platformAPI::getConsoleFore(platformAPI::LIGHTGRAY);
                    log.dumpFormat(": %s\n", msg.c_str());
                    break;

                case WARN:
                    std::cout << platformAPI::getConsoleFore(platformAPI::YELLOW);
                    log.dumpFormat("warn%d(%s)", code, getErrName(code).c_str());
                    std::cout << platformAPI::getConsoleFore(platformAPI::LIGHTGRAY);
                    log.dumpFormat(": %s\n", msg.c_str());
                    break;

                case INFO:
                    std::cout << platformAPI::getConsoleFore(platformAPI::BLUE);
                    log.dumpFormat("info%d(%s)", code, getErrName(code).c_str());
                    std::cout << platformAPI::getConsoleFore(platformAPI::LIGHTGRAY);
                    log.dumpFormat(": %s\n", msg.c_str());
                    break;
			}
		}
        void dbgLog() const {
            if(buildFeature::config::isDbg())
                log();
        }

		static const std::string& getErrMsg(errCode code);
        static const std::string& getErrName(errCode code);
        static err* newErr(int code, ...);
        static err* newErr(const area& src, int code, ...);
        static err* newWarn(int code, ...);
        static err* newWarn(const area& src, int code, ...);
        static err* newInfo(int code, ...);
        static err* newInfo(const area& src, int code, ...);

	public:
		err::type fType;
		errCode code;
		std::string msg;
		static constexpr wint BASE_TEST_CODE = 99999990; // not to be duplicated.

    private:
        std::string _format(const std::string& fmt, va_list args);
        err* _newRes(type t, errCode code, va_list args) {
            return new err(t, code, args);
        }
        err* _newRes(const area& src, type t, errCode code, va_list args);
	};

    struct _wout dummyErr : public err {
        WRD(ME(dummyErr, err),
            TYPE(wtype),
            INIT_META(me))

    public:
        dummyErr(): super(err::ERR, 0) {}

    public:
        void log() const override {}
    };

	struct _wout srcErr : public err {
		WRD(ME(srcErr, err),
			TYPE(wtype),
			INIT_META(me))

	public:
        template <typename... Args>
        srcErr(err::type t, const area& src, int code, Args... args): super(t, code, args...), srcArea(src) {}

		area srcArea;

    public:
        void log() const override {
            switch(fType) {
                case ERR: WRD_E("%d:%d: err(%d): %s", srcArea.start.row, srcArea.start.col, code, msg.c_str()); break;
                case WARN: WRD_W(":%d:%d: warn(%d): %s", srcArea.start.row, srcArea.start.col, code, msg.c_str()); break;
                case INFO: WRD_I(":%d:%d: info(%d): %s", srcArea.start.row, srcArea.start.col, code, msg.c_str()); break;
            }
        }
	};
}
