#pragma once

#include "clonable.hpp"
#include "validable.hpp"
#include "../builtin/container/native/tnarr.hpp"

namespace wrd {

	class ases;
    class ref;
    typedef tnarr<ref, str> params;

    /// node provides common API to manipulate its sub nodes.
    class node : public instance, public clonable {
        WRD(INTERFACE(node, instance))

    public:
        node& operator[](const std::string& name) const;

    public:
        wbool isSub(const type& it) const { return getType().isSub(it); }
        wbool isSuper(const type& it) const { return getType().isSuper(it); }
        template <typename T>
        wbool isSub() const { return getType().isSub<T>(); }
        template <typename T>
        wbool isSuper() const { return getType().isSuper<T>(); }

        virtual ncontainer& subs() = 0;
        const ncontainer& subs() const WRD_UNCONST_FUNC(subs())

        template <typename T>
        T& sub(std::function<wbool(const T&)> l) const {
            return subs().get<T>(l);
        }
        template <typename T = me> T& sub(const std::string& name) const;
        template <typename T = me> T& sub(const std::string& name, const containable& args);
        template <typename T = me> T& sub(const std::string& name, const containable& args) const;

        template <typename T>
        tnarr<T, str> subAll(std::function<wbool(const T&)> l) const {
            return subs().getAll<T>(l);
        }

        template <typename T = me> tnarr<T, str> subAll(const std::string& name) const;
        template <typename T = me> tnarr<T, str> subAll(const std::string& name, const containable& args);
        template <typename T = me> tnarr<T, str> subAll(const std::string& name, const containable& args) const;

        virtual wbool canRun(const containable& args) const = 0;

        /// @return parameters of run() func.
        ///         parameter is just a type. and I don't care about the value of each parameters.
        ///         that is the reason why I uses a ref to represents parameter.
        ///
        ///         I need the name and which types should be casted and binded from given arguments
        ///         are matters.
        virtual const params& getParams() const;

        virtual str run(const containable& args) = 0;
        str run(const std::string& name, const containable& args);
        str run(const std::string& name);
        str run();

        /// release all holding resources and ready to be terminated.
        /// @remark some class won't be able to reinitialize after rel() got called.
        virtual void rel() {}

        virtual wbool isRef() const { return false; }

        virtual const std::string& getName() const {
            static std::string dummy = "";
            return dummy;
        }

        virtual wbool setName(const std::string& new1) {
            return false; // usually modifying name is not permitted.
        }

        template <typename T> wbool is() const { return is(ttype<T>::get()); }
        wbool is(const typeProvidable& to) const { return is(to.getType()); }
        wbool is(const type& to) const { return getType().is(to); }

        template <typename T> tstr<T> as() const { return as(ttype<T>::get()); }
        str as(const typeProvidable& to) const { return as(to.getType()); }
        str as(const type& to) const { return getType().as(*this, to); }

        template <typename T>
        wbool isImpli() const {
            return isImpli(ttype<T>::get());
        }
        wbool isImpli(const typeProvidable& to) const { return isImpli(to.getType()); }
        wbool isImpli(const type& to) const { return getType().isImpli(to); }

        template <typename T> tstr<T> asImpli() const { return asImpli(ttype<T>::get()); }
        str asImpli(const typeProvidable& to) const { return asImpli(to.getType()); }
        str asImpli(const type& to) const { return getType().asImpli(*this, to); }

        /// getType() returns what it is. opposite to it, this returns what this class will
        /// represents after evaluation.
        ///
        /// for example, the 'expr' class has derived from this node class. and if an user call the
        /// funcs to get type of it, class 'wtype' of 'expr' will be returned.
        /// but if that user call the 'getEvalType()' then the 'expr' object evaluate its terms and
        /// returns type of the output. it could be integer if it was 'addExpr' and all terms are
        /// constructed with integers.
        /// and also this func requires frames. means that you have to interact frame first before
        /// call this func.
        virtual const wtype& getEvalType() const {
            return getType();
        }

        /// @return true if this class needs to get mgd subnodes from frame instance.
        ///         the owner of this instance will interact current frame if subnodes returns true.
        virtual wbool doesNeedScope() const { return false; }

    protected:
        virtual str _onRunSub(node& sub, const containable& args) {
            return sub.run(args);
        }
    };
}
