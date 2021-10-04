#pragma once

#include "err.hpp"
#include "../type/wtype.hpp"
#include "../ast/clonable.hpp"

namespace wrd {

    class errReport : public typeProvidable, public clonable {
        WRD(CLASS(errReport))

	public:
		const err& operator[](widx n) const { return get(n); }
		operator wbool() const { return hasErr(); }

    public:
        wbool hasErr() const {
            return has(err::ERR);
        }
        wbool hasWarn() const {
            return has(err::WARN);
        }
        wbool has(err::type type) const {
			for(auto& elem : _errs)
				if(elem->fType == type)
					return true;
            return false;
        }

		const err& get(widx n) const { return *_errs[n]; }

		wcnt len() const { return _errs.size(); }

		virtual wbool add(const err* new1) {
			_errs.push_back(new1);
			return true;
		}

		std::vector<tstr<err>>::const_iterator begin() const {
			return _errs.begin();
		}

		std::vector<tstr<err>>::const_iterator end() const {
			return _errs.end();
		}

		void log() const {
			for(auto& elem : _errs)
				elem->log();
		}

		void rel() {
			_errs.clear();
		}

	private:
		std::vector<tstr<err>> _errs;
    };

	class dummyErrReport : public errReport {
		WRD(CLASS(dummyErrReport, errReport))

	public:
		wbool add(const err* new1) override { return false; }

		static me singletone;
	};
}
