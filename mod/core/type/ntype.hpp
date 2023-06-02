#pragma once

#include "../common.hpp"
#include "as/ases.hpp"

namespace namu {

    class _nout ntype : public type {
        NAMU_DECL_ME(ntype, type)

    private:
        typedef std::map<const ntype*, const ntype*> deducer;
        typedef std::map<const ntype*, deducer> deducers;

    public:
        ntype(): _bean(nullptr) {}
        ntype(const me& rhs): _bean(nullptr) {
            setBean(rhs.getBean());
        }

        ~ntype() override {
            setBean(nulOf<node>());
        }

    public:
        nbool operator==(const type& rhs) const override;
        me& operator=(const me& rhs) {
            if(this == &rhs) return *this;

            setBean(rhs.getBean());
            return *this;
        }

    public:
        // ntype:
        /// whether variable 'it' can be a subtype of T
        template <typename T>
        nbool isImpli() const {
            return this->isImpli(ttype<T>::get());
        }
        virtual nbool isImpli(const type& to) const;
        nbool isImpli(const typeProvidable& to) const;

        template <typename T>
        tstr<T> asImpli(const node& it) const {
            return this->asImpli(ttype<T>::get());
        }
        virtual str asImpli(const node& from, const type& to) const;

        /// @return whether this's a custom type.
        virtual nbool isCustom() const { return false; }

        template <typename T>
        nbool is() const {
            return this->is(ttype<T>::get());
        }
        nbool is(const type& to) const;

        template <typename T>
        tstr<T> as(const node& it) const {
            return this->as(it, ttype<T>::get());
        }
        str as(const node& from, const type& to) const;

        virtual nbool isImmutable() const;
        /// @return null if it's not relative between l & r.
        const ntype& deduce(const ntype& r) const;
        const ntype& deduce(const typeProvidable& r) const {
            return deduce((const ntype&) r.getType());
        }
        template <typename T>
        const ntype& deduce() const {
            return deduce(ttype<T>::get());
        }
        /// @return null it it's not relative between l & r.
        static const ntype& deduce(const ntype& l, const ntype& r);

        virtual const node& getBean() const {
            if(nul(_bean)) return nulOf<node>();

            return **_bean;
        }
        nbool setBean(const node& newBean) {
            if(nul(newBean)) {
                if(_bean)
                    delete _bean;
                _bean = nullptr;
                return true;
            }
            if(nul(_bean))
                _bean = new str();
            return _bean->bind(newBean);
        }

    protected:
        // ntype:
        virtual const ases& _getImpliAses() const;
        virtual const ases& _getAses() const;

    private:
        static deducers* _makeDeducers();
        static const ntype& _deduceSuperType(const ntype& l, const ntype& r);

    private:
        str* _bean;
    };

    typedef std::vector<const ntype*> ntypes;
}
