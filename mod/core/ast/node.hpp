#pragma once

#include "validable.hpp"
#include "../builtin/container/native/tnbicontainer.hpp"
#include "../builtin/container/native/tnarr.hpp"
#include "point.hpp"
#include "../type/ntype.hpp"
#include "../frame/frameInteractable.hpp"

namespace namu {

    class ases;
    class args;
    class visitor;
    struct visitInfo;

    /// node provides common API to manipulate its sub nodes.
    class _nout node : public instance, public frameInteractable {
        NAMU(ADT(node, instance))

    public:
        node& operator[](const std::string& name) const;

    public:
        virtual nbicontainer& subs() = 0;
        const nbicontainer& subs() const NAMU_UNCONST_FUNC(subs())

        /// @return null if it's not relative between l & r.
        const node& deduce(const node& r) const {
            const ntype& mine = getType();
            const ntype& res = mine.deduce(r.getType());
            if(nul(res) || nul(mine)) return nulOf<node>();

            return res == mine ? *this : r;
        }

        template <typename T>
        T& sub(std::function<nbool(const std::string&, const T&)> l) const {
            return subs().get<T>(l);
        }
        template <typename T = me> T& sub() const;
        template <typename T = me> T& sub(const std::string& name) const;
        template <typename T = me> T& sub(const std::string& name, const args& a);
        template <typename T = me> T& sub(const std::string& name, const args& a) const;

        template <typename T>
        tnarr<T> subAll(std::function<nbool(const std::string&, const T&)> l) const {
            return subs().getAll<T>(l);
        }

        template <typename T = me> tnarr<T, strTactic> subAll() const;
        template <typename T = me> tnarr<T, strTactic> subAll(const std::string& name) const;
        template <typename T = me> tnarr<T, strTactic> subAll(const std::string& name, const args& a);
        template <typename T = me> tnarr<T, strTactic> subAll(const std::string& name, const args& a) const;

        virtual nbool canRun(const args& a) const = 0;

        virtual str run(const args& a) = 0;
        str run(const std::string& name, const args& a);
        str run(const std::string& name);
        str run();

        /// release all holding resources and ready to be terminated.as(
        /// @remark some class won't be able to reinitialize after rel() got called.
        virtual void rel() {}

        template <typename T> nbool is() const { return is(ttype<T>::get()); }
        nbool is(const typeProvidable& to) const;
        nbool is(const type& to) const;

        template <typename T> tstr<T> as() const { return as(ttype<T>::get()); }
        str as(const typeProvidable& to) const;
        str as(const type& to) const;

        template <typename T>
        nbool isImpli() const { return isImpli(ttype<T>::get()); }
        nbool isImpli(const typeProvidable& to) const;
        virtual nbool isImpli(const type& to) const;

        template <typename T> tstr<T> asImpli() const { return asImpli(ttype<T>::get()); }
        str asImpli(const typeProvidable& to) const;
        virtual str asImpli(const type& to) const;

        virtual const point& getPos() const {
            static point inner;
            return inner;
        }

        clonable* deepClone() const override {
            return (me*) clone();
        }

        virtual void setPos(const point& new1) {}

        /// getType() returns what it is. opposite to it, this returns what this class will
        /// represents after evaluation.
        ///
        /// for example, the 'expr' class has derived from this node class. and if an user call the
        /// funcs to get type of it, class 'ntype' of 'expr' will be returned.
        /// but if that user call the 'getEval()' then the 'expr' object evaluate its terms and
        /// returns it as a node from the output. it could be an integer if it was 'addExpr' and all
        /// terms are constructed with integers.
        ///
        /// and also this func requires frames. means that you have to interact frame first before
        /// call this func.
        virtual const node& getEval() const;

        virtual void accept(visitInfo i, visitor& v);

        void inFrame(const bicontainable& args) override {}
        void outFrame() override {}

    protected:
        virtual str _onRunSub(node& sub, const args& a);
    };
}
