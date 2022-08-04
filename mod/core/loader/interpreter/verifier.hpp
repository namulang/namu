#pragma once

#include "verification.hpp"
#include "../../ast/slot.hpp"

struct verifierTest;
namespace namu {

    class slot;
    class frame;
    typedef tnbicontainer<std::string, slot> slotContainer;

    class _nout verifier : public typeProvidable, clonable {
        NAMU(CLASS(verifier))
        friend struct ::verifierTest;

    public:
        verifier();

    public:
        void rel();

        static void add(const verification* new1);

        me& setReport(errReport& rpt);
        // @param newInfo is not a heap instance.
        me& setFrameInfo(tstr<frame>& newInfo);

        errReport& getReport();
        tstr<frame>& getFrameInfo();

        void verify(node& it);
        void verify(node& it, bicontainable& tray);
        void verify(node& it, const type& typ, bicontainable& tray);

    private:
        static verifications& _getVerifications(const type& typ);

    private:
        tstr<errReport> _rpt;
        tstr<frame>* _frameInfo;
    };

#include "../../common/MSVCHack.hpp"

}
