#pragma once

#include "primitiveObj.hpp"
#include "nChar.hpp"
#include "../container/tucontainable.hpp"

namespace namu {

    class _nout nStr : public primitiveObj<std::string>, public tucontainable<nChar> {

        struct _nout nStrType : public ntype {
        public:
            nbool isImmutable() const override;

        protected:
            const ases& _getAses() const override;
        };
        NAMU(CLASS(nStr, primitiveObj, nStrType), VISIT())

        typedef typename tucontainable<nChar>::iter iter;
        typedef typename tucontainable<nChar>::iteration iteration;

    public:
        nStr();
        nStr(const nchar* val);
        nStr(const std::string& val);

    public:
        nchar operator[](nint n) const { return get()[n]; }

        nint len() const override { return get().length(); }

        tstr<arithmeticObj> bitwiseNot() const override {
            return *this;
            // TODO: throw error
        }

        /// @param end is exclusive.
        tstr<nStr> substr(nint start, nint end) {
            return tstr<nStr>(new nStr(get().substr(start, end - start)));
        }

        nbool has(nidx n) const {
            return 0 <= n && n < get().size();
        }

        using super::get;
        nchar get(nidx n) const {
            return get()[n];
        }

        void add(const iter& here, const iter& from, const iter& to) override {}
        nbool add(const iter& at, const nChar& new1) override { return false; /* nStr is immutable*/ }
        nbool set(const iter& at, const nChar& new1) override { return false; }
        nbool del(const iter& at) override { return false; }
        nbool del(const iter& from, const iter& end) override { return false; }
        void rel() override {}


    protected:
        iteration* _onMakeIteration(ncnt step) const override;

        void _onMakeSubs(scope& tray) const override;

        tstr<arithmeticObj> _add(const arithmeticObj& rhs, nbool reversed) const override {
            return reversed ?
                    new me(rhs.as<me>()->get() + get()):
                    new me(get() + rhs.as<me>()->get());
        }
        tstr<arithmeticObj> _sub(const arithmeticObj& rhs, nbool reversed) const override {
            return *this;
            // TODO: throw error
        }
        tstr<arithmeticObj> _mul(const arithmeticObj& rhs, nbool reversed) const override {
            return *this;
            // TODO: throw error
        }
        tstr<arithmeticObj> _div(const arithmeticObj& rhs, nbool reversed) const override {
            return *this;
            // TODO: throw error
        }
        tstr<arithmeticObj> _mod(const arithmeticObj& rhs, nbool reversed) const override {
            return *this;
            // TODO: throw error
        }
        tstr<arithmeticObj> _bitwiseAnd(const arithmeticObj& rhs, nbool reversed) const override {
            return *this;
            // TODO: throw error
        }
        tstr<arithmeticObj> _bitwiseXor(const arithmeticObj& rhs, nbool reversed) const override {
            return *this;
            // TODO: throw error
        }
        tstr<arithmeticObj> _bitwiseOr(const arithmeticObj& rhs, nbool reversed) const override {
            return *this;
            // TODO: throw error
        }
        tstr<arithmeticObj> _lshift(const arithmeticObj& rhs, nbool reversed) const override {
            return *this;
            // TODO: throw error
        }
        tstr<arithmeticObj> _rshift(const arithmeticObj& rhs, nbool reversed) const override {
            return *this;
            // TODO: throw error
        }

        nbool _eq(const arithmeticObj& rhs) const override { return get() == rhs.asImpli<me>()->get(); }
        nbool _ne(const arithmeticObj& rhs) const override { return get() != rhs.asImpli<me>()->get(); }
        nbool _gt(const arithmeticObj& rhs) const override { return get() > rhs.asImpli<me>()->get(); }
        nbool _lt(const arithmeticObj& rhs) const override { return get() < rhs.asImpli<me>()->get(); }
        nbool _ge(const arithmeticObj& rhs) const override { return get() >= rhs.asImpli<me>()->get(); }
        nbool _le(const arithmeticObj& rhs) const override { return get() <= rhs.asImpli<me>()->get(); }
        nbool _logicalAnd(const arithmeticObj& rhs) const override {
            // TODO: throw error
            return false;
        }
        nbool _logicalOr(const arithmeticObj& rhs) const override {
            // TODO: throw error
            return false;
        }

        arithmeticObj& _mov(const arithmeticObj& rhs) override {
            get() = rhs.asImpli<me>()->get();
            return *this;
        }
    };
}
