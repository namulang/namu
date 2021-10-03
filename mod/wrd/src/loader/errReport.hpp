#pragma once

#include "err.hpp"
#include "../type/wtype.hpp"
#include "../ast/clonable.hpp"

namespace wrd {

    class errReport : public typeProvidable, public clonable {
        WRD(CLASS(errReport))

	public:
		const err& operator[](widx n) const { return get(n); }

    public:
        wbool hasErr() const {
            return has(err::ERR);
        }
        wbool hasWarn() const {
            return has(err::WARN);
        }
        wbool has(err::type type) const {
            // TODO:
            return false;
        }

		const err& get(widx n) const { return _errs[n]; }

		wcnt len() const { return _errs.size(); }

		virtual void add(const err& new1) {
			_errs.push_back(new1);
		}

		std::vector<err>::const_iterator begin() const {
			return _errs.begin();
		}

		std::vector<err>::const_iterator end() const {
			return _errs.end();
		}

		void rel() {
			_errs.clear();
		}

	private:
		std::vector<err> _errs;
    };

	class dummyErrReport : public errReport {
		WRD(CLASS(dummyErrReport, errReport))

	public:
		void add(const err& new1) override {}

		static me singletone;
	};
}
