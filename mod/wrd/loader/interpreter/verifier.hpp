#pragma once

#include "verification.hpp"
#include "../../ast/pack.hpp"
#include "../../frame/frame.hpp"

struct verifierTest;

namespace wrd {

    // TODO:
    //  if verifier detects an access to a pack:
    //      void onGetPack(targetPack, currentPack) {
    //          targetPack.setReport(currentPack.getReport());
    //          targetPack.subs();
    //          if(!targetPack.isValid())
    //              currentPack.setValid(false); // never set to valid again if it's invalid once.
    //          targetPack.addDepedent(currentPack);
    //      }
    class _wout verifier : public typeProvidable, clonable {
        WRD(CLASS(verifier))
        friend struct ::verifierTest;

    public:
        verifier() { rel(); }

    public:
        void rel();

        static void add(const verification* new1) {
            if(!new1) return;

            _getVerifications(new1->getType()).push_back(const_cast<verification*>(new1));
        }

        me& setReport(errReport& rpt) {
            _rpt.bind(rpt);
            return *this;
        }
        me& setPacks(const packContainer& packs) {
            _packs.bind(packs);
            return *this;
        }
        // @param newInfo is not a heap instance.
        me& setFrameInfo(tstr<frame>& newInfo) {
            _frameInfo = &newInfo;
            return *this;
        }

        errReport& getReport() { return *_rpt; }
        tstr<frame>& getFrameInfo() { return *_frameInfo; }
        const packContainer& getPacks() { return *_packs; }

        void verify(typeProvidable& it) {
            _verify(it, it.getType());
        }

    private:
        void _verify(typeProvidable& it, const type& typ) {
            if(nul(it)) return;
            if(typ == ttype<adam>::get()) return;

            _verify(it, typ.getSuper());

            verifications& veris = _getVerifications(typ);
            for(auto* elem : veris)
                elem->verify(*this, it);
        }

        static verifications& _getVerifications(const type& typ) {
            static verificationMap inner;
            return inner[(void*) &typ];
        }

    private:
        tstr<errReport> _rpt;
        tstr<packContainer> _packs;
        tstr<frame>* _frameInfo;
    };
}
