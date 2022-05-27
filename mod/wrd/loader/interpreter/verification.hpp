#pragma once

#include <unordered_map>
#include "../errReport.hpp"

namespace wrd {

    class verifier;
    class frame;

    class _wout verification : public typeProvidable {
        WRD(ME(verification),
            INIT_META(me))

    public:
        virtual void verify(verifier& veri, typeProvidable& it) {
            _verifier = &veri;
        }
        void verify(typeProvidable& it);
        wbool logFrameInfo(const frame& newFr);

    protected:
        template <typename... Args>
        void _warn(Args... args);
        template <typename... Args>
        void _err(Args... args);
        template <typename... Args>
        void _info(Args... args);

        verifier& _getVerifier() { return *_verifier; }

    protected:
        verifier* _verifier;
    };

    typedef std::vector<verification*> verifications;
    typedef std::unordered_map<void*, verifications> verificationMap;
}
