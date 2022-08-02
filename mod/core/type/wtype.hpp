#pragma once

#include "../common.hpp"
#include "as/ases.hpp"

namespace namu {

    class _wout wtype : public type {
        WRD_DECL_ME(wtype, type)

    private:
        typedef std::map<const wtype*, const wtype*> reducer;
        typedef std::map<const wtype*, reducer> reducers;

    public:
        // wtype:
        /// whether variable 'it' can be a subtype of T
        template <typename T>
        wbool isImpli() const {
            return this->isImpli(ttype<T>::get());
        }
        virtual wbool isImpli(const type& to) const;
        wbool isImpli(const typeProvidable& to) const;

        template <typename T>
        tstr<T> asImpli(const node& it) const {
            return this->asImpli(ttype<T>::get());
        }
        virtual str asImpli(const node& from, const type& to) const;

        template <typename T>
        wbool is() const {
            return this->is(ttype<T>::get());
        }
        wbool is(const type& to) const;

        template <typename T>
        tstr<T> as(const node& it) const {
            return this->as(it, ttype<T>::get());
        }
        str as(const node& from, const type& to) const;

        virtual wbool isImmutable() const;
        /// @return null if it's not relative between l & r.
        const wtype& reduce(const wtype& r) const;
        const wtype& reduce(const typeProvidable& r) const {
            return reduce((const wtype&) r.getType());
        }
        template <typename T>
        const wtype& reduce() const {
            return reduce(ttype<T>::get());
        }
        /// @return null it it's not relative between l & r.
        static const wtype& reduce(const wtype& l, const wtype& r);

    protected:
        // wtype:
        virtual const ases& _getImpliAses() const;
        virtual const ases& _getAses() const;

    private:
        static reducers* _makeReducers();
        static const wtype& _reduceSuperType(const wtype& l, const wtype& r);
    };

    typedef std::vector<const wtype*> wtypes;
}
