#pragma once

#include "termSobj.hpp"

namespace namu {

    class _nout verSobj : public termSobj {
        NAMU_DECL_ME(verSobj, termSobj)
        NAMU_INIT_META(verSobj)

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
        explicit verSobj(const nchar* verStr): super(verStr) {
            _parseVerStr(std::string(verStr));
        }

        nbool operator>(const me& rhs) const {
            nint res = _isFromBigger(_maj, rhs._maj);
            if(res != 0) return res == 1;

            res = _isFromBigger(_min, rhs._min);
            if(res != 0) return res == 1;

            return _isFromBigger(_fix, rhs._fix) > 0;
        }

        nbool operator<(const me& rhs) const {
            nint res = _isFromBigger(rhs._maj, _maj);
            if(res != 0) return res == 1;

            res = _isFromBigger(rhs._min, _min);
            if(res != 0) return res == 1;

            return _isFromBigger(rhs._fix, _fix) > 0;
        }
        nbool operator==(const me& rhs) const {
            if(this == &rhs) return true;

            return _maj == rhs._maj &&
                _min == rhs._min &&
                _fix == rhs._fix;
        }
        nbool operator!=(const me& rhs) const { return !operator==(rhs); }
        nbool operator<=(const me& rhs) const { return !operator>(rhs); }
        nbool operator>=(const me& rhs) const { return !operator<(rhs); }

        nint asMajor() const { return _maj; }
        nint asMinor() const { return _min; }
        nint asFix() const { return _fix; }

        const type& getType() const override {
            return ttype<me>::get();
        }


    private:
        static nint _isFromBigger(nint from, nint to) {
            if(from > to) return 1;
            if(from == to) return 0;
            return -1;
        }

        void _parseVerStr(const std::string& verStr) {
            std::stringstream ss(verStr);
            std::string token;

            nint* them[] = {&_maj, &_min, &_fix};
            for(int n = 0; n < VER_LEN; n++) {
                if(!std::getline(ss, token, DELIMITER[0])) {
                    NAMU_E("error parsing to %s", verStr.c_str());
                    return;
                }

                *them[n] = std::stoi(token);
            }
        }

    private:
        nint _maj;
        nint _min;
        nint _fix;
        static constexpr nint VER_LEN = 3;
        static constexpr const nchar* DELIMITER = ".";
    };
}

