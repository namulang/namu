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
        WRD(ME(verification),
            INIT_META(me))
        friend class verifier; // for _onPrepareVerify

    public:
        void verify(node& it);
        void verify(node& it, bicontainable& tray);
        nbool logFrameInfo(const frame& newFr);
        verifier& getVerifier();
        const verifier& getVerifier() const NAMU_UNCONST_FUNC(getVerifier())
        bicontainable& getTray();
        const bicontainable& getTray() const NAMU_UNCONST_FUNC(getTray())

    protected:
        template <typename... Args> void _warn(Args... args);
        template <typename... Args> void _err(Args... args);
        template <typename... Args> void _info(Args... args);
        template <typename... Args> void _srcWarn(Args... args);
        template <typename... Args> void _srcErr(Args... args);
        template <typename... Args> void _srcInfo(Args... args);

        node& _getIt();
        virtual void _onPrepareVerify(verifier& veri, node& it, bicontainable& tray) = 0;

    protected:
        node* _it;
        verifier* _verifier;
        bicontainable* _tray;
    };

    typedef std::vector<verification*> verifications;
    typedef std::unordered_map<void*, verifications> verificationMap;
}
