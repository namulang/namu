#pragma once

#include "verification.inl"

namespace wrd {

    template <typename T>
    class tverification : public verification {
        WRD(ME(tverification, verification),
            INIT_META(me))
        typedef wtype metaType;

    public:
        const wtype& getType() const override {
            return ttype<T>::get();
        }

        using super::verify;
        void verify(verifier& veri, typeProvidable& it) override {
            super::verify(veri, it);
            _onVerify((T&) it);
        }

    protected:
        virtual void _onVerify(T& it) = 0;
    };
}
