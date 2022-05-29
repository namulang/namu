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
        verifier();

    public:
        void rel();

        static void add(const verification* new1);

        me& setReport(errReport& rpt);
        me& setPacks(const packContainer& packs);
        // @param newInfo is not a heap instance.
        me& setFrameInfo(tstr<frame>& newInfo);

        errReport& getReport();
        tstr<frame>& getFrameInfo();
        const packContainer& getPacks();

        void verify(typeProvidable& it);

    private:
        void _verify(typeProvidable& it, const type& typ);
        static verifications& _getVerifications(const type& typ);

    private:
        tstr<errReport> _rpt;
        tstr<packContainer> _packs;
        tstr<frame>* _frameInfo;
    };
}
