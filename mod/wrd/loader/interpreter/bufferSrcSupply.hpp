#pragma once

#include "srcSupply.hpp"

namespace wrd {
    class _wout bufferSrcSupply : public srcSupply {
        WRD(CLASS(bufferSrcSupply, srcSupply))

    public:
        bufferSrcSupply(const std::vector<string>& buf): _srcs(buf) { ret(); }

    public:
        wbool next() override {
            if(++_cursor >= _srcs.size()) return false;

            return true;
        }

        const char* get() const override {
            return _srcs[_cursor].c_str();
        }

        void ret() override {
            _cursor = -1;
        }

    private:
        std::vector<string> _srcs;
        int _cursor;
    };
}
