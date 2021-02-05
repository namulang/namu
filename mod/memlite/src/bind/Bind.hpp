#pragma once

#include "TBindable.hpp"
#include "../interface/Instance.hpp"

namespace wrd {

    class BindTacticable;
    ///	Bind:
    ///		Overview:
    ///			can guarrantee that specific instance freed completely and track of them.
    ///			this has 3 features.
    ///				1) can distringuish what given abstract type actually was and reject or accept it regarding that.
    ///				2) free instance completely. using RAII.
    ///				3) can notice that binding Instance was replaced or freed without unexpected exception.
    ///			in conlusion, it prevent halting process or give a chance to let developer be advised.
    ///
    ///		TypeCheking:
    ///			This was most valuable requirement when I design component of bind.
    ///			in fact, Bind was suggested to replace sort of exisiting smart-ptr concept things, such as weakptr.
    ///			because weakptr was planned to replace and enhance existing pointer of c/c++, they were very strict to
    ///			check type and whether template param T was const or not.
    ///			this characteristic was pretty worked good in most environment but not on usage of World frx.
    ///
    ///			Why was it not proper to use as before?:
    ///				World is based on class Node and make user not need to know what really was.
    ///				all actions (including calling some func on World env) can be replacable to sending msg using "use()".
    ///				To say the least, what World doing is loose-check.
    ///				so, strict type-checking of existing smart pointers doesn't matched to what Worldfrx willing to do.
    ///
    ///		Design:
    ///			Bind components are mostly constructed to 3 classes and they form 2 layers vertically.
    ///			class Bind:
    ///				represents Binder on loose-checking layer. user can try any type to bind or get from the
    ///				binded. compiler won't complain about.
    ///				but because of loose-checking, if it's not proper request, binder will warn you at runtime as result.
    ///				constness of binding instance was persisted. (for ex, if user try to get non-const instance
    ///				from consted Binder, s/he will get nulled reference.) user needs to checks that returned value
    ///				was nullref on using loose-checking API.
    ///
    ///			class TWeak, class TStrong:
    ///				these represent Binder on strict-checking layer.
    ///				because it was declared to class template, user need to bind or get binded using type T.
    ///				of course these are based on class Bind, user can use loose-check API case by case.
    ///
    class Bind : public Instance, public TBindable<Instance> {
        WRD_DECL_THIS(Bind, Instance)
        WRD_INIT_META(This)
        template <typename T> friend class TWeakTactic;
        template <typename T> friend class TStrongTactic;
		friend class BindTag; // for _get()

	public:
        Bind() {} // TODO: remove this line
        Bind(BindTacticable* tactic);
        Bind(const This& rhs);
        ~Bind();

		wbool operator==(const This& rhs) const;
		wbool operator!=(const This& rhs) const;
		This& operator=(const This& rhs);

        //	Bind:
		wbool bind(Instance& new1);
		Id getItsId() const;
        wbool isConst() const;
        //  TBindable:
		wbool isBind() const;
		wbool unbind();
		using TBindable::canBind;
		wbool canBind(const Type& cls) const;
        //  Instance:
        const Type& getType() const;

	protected:
        wbool _assign(const Bind& rhs);
        //  TBindable:
		wbool _bind(const Instance& it);
		Instance& _get();

	private:
		Id _itsId; // id for binded one
        BindTacticable* _tactic;
	};
}
