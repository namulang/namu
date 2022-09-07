#pragma once

#include <unordered_map>
#include "../errReport.hpp"

namespace namu {

    class node;
    class frame;
    class verifier;
    template <typename K, typename V> class tbicontainable;
    typedef tbicontainable<std::string, node> bicontainable;

    class _nout verification : public typeProvidable {
        NAMU(ME(verification),
            INIT_META(me))
        friend class verifier; // for _onPrepareVerify

    public:
        void verify(node& it);
        nbool logFrameInfo(const frame& newFr);
        verifier& getVerifier();
        const verifier& getVerifier() const NAMU_UNCONST_FUNC(getVerifier())

    protected:
        template <typename... Args> void _warn(Args... args);
        template <typename... Args> void _err(Args... args);
        template <typename... Args> void _info(Args... args);
        template <typename... Args> void _srcWarn(Args... args);
        template <typename... Args> void _srcErr(Args... args);
        template <typename... Args> void _srcInfo(Args... args);

        node& _getIt();
        virtual void _onPrepareVerify(verifier& veri, node& it) = 0;

    protected:
        node* _it;
        verifier* _verifier;
    };

    typedef std::vector<verification*> verifications;
    typedef std::unordered_map<void*, verifications> verificationMap;
}
