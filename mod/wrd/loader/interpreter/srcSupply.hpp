#pragma once

#include "flag.hpp"

namespace wrd {

    class srcSupply : public instance, public clonable {
        WRD(INTERFACE(srcSupply, instance))

    public:
        /// @return true if there is no more data to process.
        virtual wbool next() = 0;
        virtual const char* get() const = 0;
        /// return to first cursor.
        virtual void ret() = 0;
    };

    class bufferSrcSupply : public srcSupply {
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
