#pragma once

#include "../common.hpp"
#include "as/ases.hpp"

namespace wrd {

    class ref;
    template <typename T> class tref;
    class wtype : public type {
        WRD_DECL_ME(wtype, type)

    public:
        // wtype:
        template <typename T>
        wbool isImpli() const {
			return this->isImpli(ttype<T>::get());
		}
        wbool isImpli(const type& to) const {
            return _getImpliAses().is(*this, to);
        }

        template <typename T>
        tstr<T> asImpli(const node& it) const {
			return this->asImpli(ttype<T>::get());
		}
        str asImpli(const node& from, const type& to) const {
			return _getImpliAses().as(from, to);
		}

        template <typename T>
        wbool is() const {
			return this->is(ttype<T>::get());
		}
        wbool is(const type& to) const {
			if(isImpli(to)) return true;

            return _getAses().is(*this, to);
        }

        template <typename T>
        tstr<T> as(const node& it) const {
			return this->as(it, ttype<T>::get());
		}
        str as(const node& from, const type& to) const {
			if(isImpli(to))
				return asImpli(from, to);

			return _getAses().as(from, to);
		}

        virtual wbool isImmutable() const {
            return false;
        }

    protected:
        // wtype:
        virtual const ases& _getImpliAses() const {
            static ases inner;
            return inner;
        }

        virtual const ases& _getAses() const {
			static ases inner;
			return inner;
		}
    };

    typedef std::vector<const wtype*> wtypes;
}
