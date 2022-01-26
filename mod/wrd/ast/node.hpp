#pragma once

#include "clonable.hpp"
#include "../builtin/container/native/tnarr.hpp"
#include "validable.hpp"

namespace wrd {

	class ases;

    /// node provides common API to manipulate its sub nodes.
    class node : public instance, public clonable {
        WRD(INTERFACE(node, instance))

    public:
        node& operator[](const std::string& name) const { return sub(name); }

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
        template <typename T = me>
        T& sub(const std::string& name) const;
        template <typename T = me>
        T& sub(const std::string& name, const containable& args);
        template <typename T = me>
        T& sub(const std::string& name, const wtypes& types);
        template <typename T = me>
        T& sub(const std::string& name, const containable& args) const;
        template <typename T = me>
        T& sub(const std::string& name, const wtypes& types) const;

        template <typename T>
        tnarr<T> subAll(std::function<wbool(const T&)> l) const {
            return subs().getAll<T>(l);
        }
        template <typename T = me>
        tnarr<T> subAll(const std::string& name) const;
        template <typename T = me>
        tnarr<T> subAll(const std::string& name, const ncontainer& args);
        template <typename T = me>
        tnarr<T> subAll(const std::string& name, const wtypes& types);
        template <typename T = me>
        tnarr<T> subAll(const std::string& name, const ncontainer& args) const;
        template <typename T = me>
        tnarr<T> subAll(const std::string& name, const wtypes& types) const;

        virtual wbool canRun(const wtypes& typs) const = 0;
        wbool canRun(const containable& args) const {
            return canRun(createTypesFromArgs(args));
        }

        /// @return object and parameter types.
        virtual const wtypes& getParams() const;

        virtual str run(const std::string& name, const containable& args);
        virtual str run(const containable& args) = 0;
        str run(const std::string& name);
        str run();

        /// release all holding resources and ready to be terminated.
        /// @remark some class won't be able to reinitialize after rel() got called.
        virtual void rel() {}

        virtual const std::string& getName() const {
            static std::string dummy = "";
            return dummy;
        }

        template <typename T>
        wbool is() const {
            return is(ttype<T>::get());
        }
        wbool is(const type& to) const {
			return getType().is(to);
        }
        template <typename T>
        tstr<T> as() const {
            return as(ttype<T>::get());
        }
        str as(const type& to) const {
			return getType().as(*this, to);
		}

        template <typename T>
        wbool isImpli() const {
            return isImpli(ttype<T>::get());
        }
        wbool isImpli(const type& to) const {
			return getType().isImpli(to);
        }
        template <typename T>
        tstr<T> asImpli() const {
			return asImpli(ttype<T>::get());
		}
        str asImpli(const type& to) const {
			return getType().asImpli(*this, to);
		}

        /// getType() returns what it is. opposite to it, this returns what this class will
        /// represents after evaluation.
        ///
        /// for example, the 'expr' class has derived from this node class. and if an user call the
        /// funcs to get type of it, class 'wtype' of 'expr' will be returned.
        /// but if that user call the 'getEvalType()' then the 'expr' object evaluate its terms and
        /// returns type of the output. it could be integer if it was 'addExpr' and all terms are
        /// constructed with integers.
        virtual const wtype& getEvalType() const {
            return getType();
        }

        static wtypes createTypesFromArgs(const containable& args) {
            wtypes ret;
            for(iter e=args.begin(); e ;e++)
                ret.push_back((wtype*) &e->getEvalType());
            return ret;
        }
    };

}
