#pragma once

#include "verification.hpp"

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
	class verifier : public typeProvidable, clonable {
		WRD(CLASS(verifier))
		friend struct ::verifierTest;

	public:
		static void add(const verification* new1) const {
			if(!new1) return;

			_getVerifications(new1->getType()).push_back(const_cast<verification*>(new1));
		}

        me& setReport(errReport& rpt) {
            _rpt.bind(rpt);
            return *this;
        }

		void verify(const typeProvidable& it) const {
			_verifyWithType(it, it.getType());
		}

	private:
		void _verifyWithType(const typeProvidable& it, const type& typ) const {
			if(typ == ttype<adam>::get()) return;

			_verifyWithType(it, typ.getSuper());

			verifications& veris = _getVerifications(typ);
			for(auto* elem : veris)
				elem->verify(*this, it, *_rpt);
		}

		static verifications& _getVerifications(const type& typ) {
			static verificationMap inner;
			return inner[(void*) &typ];
		}

    private:
        tstr<errReport> _rpt;
	};
}
