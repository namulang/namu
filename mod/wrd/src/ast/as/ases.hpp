#pragma once

#include "tas.hpp"

namespace wrd {

	class ases: public asable {
	public:
		casts(const type& myType): _myType(myType) {}

	public:
		void add(const asables& newCast) {
			_casts.push_back(&newCast);
		}

		int len() const {
			return _casts.size();
		}

		wbool is(const type& to) const override {
            if(to.isSuper(_myType)) return true;

            for(auto e : _casts)
                if(e->is(to)) return true;
            return false;
		}

		str as(const node& from, const type& to) const override {
			if(to.isSuper(*this)) return ref(from);

			for(auto e : _casts)
				if(e->is(to))
					return e->as(from, to);
			return str();
		}

	private:
		asables _casts;
	};
}
