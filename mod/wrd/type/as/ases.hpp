#pragma once

#include "tas.hpp"

namespace wrd {

	class _wout ases: public asable {
	public:
		void add(const asable& newCast) {
			_casts.push_back((asable*) &newCast);
		}
		void add(const asable* newCast) {
			_casts.push_back((asable*) newCast);
		}

		int len() const {
			return _casts.size();
		}

		wbool is(const type& from, const type& to) const override {
            if(to.isSuper(from)) return true;

            for(auto e : _casts)
                if(e->is(from, to)) return true;
            return false;
		}

		str as(const node& from, const type& to) const override;

	private:
		asables _casts;
	};
}
