#pragma once

#include "verification.hpp"
#include "../../ast/slot.hpp"

struct verifierTest;
namespace wrd {

    class slot;
    class frame;
    typedef tnbicontainer<std::string, slot> slotContainer;

    class _wout verifier : public typeProvidable, clonable {
        WRD(CLASS(verifier))
        friend struct ::verifierTest;

    public:
        verifier();

    public:
        void rel();

        static void add(const verification* new1);

        me& setReport(errReport& rpt);
        me& setSlots(const slotContainer& slots);
        // @param newInfo is not a heap instance.
        me& setFrameInfo(tstr<frame>& newInfo);

        errReport& getReport();
        tstr<frame>& getFrameInfo();
        const slotContainer& getSlots();

        void verify(node& it);

    private:
        void _verify(node& it, const type& typ);
        static verifications& _getVerifications(const type& typ);

    private:
        tstr<errReport> _rpt;
        tstr<slotContainer> _slots;
        tstr<frame>* _frameInfo;
    };

#include "../../common/MSVCHack.hpp"

}
