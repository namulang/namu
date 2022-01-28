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
		void add(const verification* new1) const {
			if(!new1) return;

			_getVerifications(new1->getType()).push_back(const_cast<verification*>(new1));
		}

		void verify(const typeProvidable& it, errReport& report) const {
			_verifyWithType(it, report, it.getType());
		}

	private:
		void _verifyWithType(const typeProvidable& it, errReport& report, const type& typ) const {
			if(typ == ttype<adam>::get()) return;

			_verifyWithType(it, report, typ.getSuper());

			verifications& veris = _getVerifications(typ);
			for(auto* elem : veris)
				elem->verify(*this, it, report);
		}

		static verifications& _getVerifications(const type& typ) {
			static verificationMap inner;
			return inner[(void*) &typ];
		}
	};
}
