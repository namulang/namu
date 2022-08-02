#pragma once

#include "verification.hpp"

namespace namu {

    template <typename T>
    class tverification : public verification {
        WRD(ME(tverification, verification),
            INIT_META(me))
        typedef ntype metaType;

    public:
        const ntype& getType() const override {
            return ttype<T>::get();
        }

    protected:
        void _onPrepareVerify(verifier& veri, node& it, bicontainable& tray) override {
            _it = &it;
            _verifier = &veri;
            _tray = &tray;

            _onVerify((T&) it);
        }
        virtual void _onVerify(T& it) = 0;
    };
}
