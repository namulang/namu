#pragma once

#include "termSobj.hpp"

namespace wrd {

    class _wout verSobj : public termSobj {
        WRD_DECL_ME(verSobj, termSobj)
        WRD_INIT_META(verSobj)

    public:
        verSobj(int major, int minor, int fix)
            : super(std::to_string(major) + DELIMITER + std::to_string(minor) + DELIMITER + std::to_string(fix)) {

            _maj = major;
            _min = minor;
            _fix = fix;
        }
        explicit verSobj(const std::string& verStr): super(verStr) {
            _parseVerStr(verStr);
        }
        explicit verSobj(const wchar* verStr): super(verStr) {
            _parseVerStr(std::string(verStr));
        }

        wbool operator>(const me& rhs) const {
            wint res = _isFromBigger(_maj, rhs._maj);
            if(res != 0) return res == 1;

            res = _isFromBigger(_min, rhs._min);
            if(res != 0) return res == 1;

            return _isFromBigger(_fix, rhs._fix) > 0;
        }

        wbool operator<(const me& rhs) const {
            wint res = _isFromBigger(rhs._maj, _maj);
            if(res != 0) return res == 1;

            res = _isFromBigger(rhs._min, _min);
            if(res != 0) return res == 1;

            return _isFromBigger(rhs._fix, _fix) > 0;
        }
        wbool operator==(const me& rhs) const {
            if(this == &rhs) return true;

            return _maj == rhs._maj &&
                _min == rhs._min &&
                _fix == rhs._fix;
        }
        wbool operator!=(const me& rhs) const { return !operator==(rhs); }
        wbool operator<=(const me& rhs) const { return !operator>(rhs); }
        wbool operator>=(const me& rhs) const { return !operator<(rhs); }

        wint asMajor() const { return _maj; }
        wint asMinor() const { return _min; }
        wint asFix() const { return _fix; }

        const type& getType() const override {
            return ttype<me>::get();
        }


    private:
        static wint _isFromBigger(wint from, wint to) {
            if(from > to) return 1;
            if(from == to) return 0;
            return -1;
        }

        void _parseVerStr(const std::string& verStr) {
            std::stringstream ss(verStr);
            std::string token;

            wint* them[] = {&_maj, &_min, &_fix};
            for(int n = 0; n < VER_LEN; n++) {
                if(!std::getline(ss, token, DELIMITER[0])) {
                    WRD_E("error parsing to %s", verStr.c_str());
                    return;
                }

                *them[n] = std::stoi(token);
            }
        }

    private:
        wint _maj;
        wint _min;
        wint _fix;
        static constexpr wint VER_LEN = 3;
        static constexpr const wchar* DELIMITER = ".";
    };
}

