#pragma once

#include "../base/Node.hpp"
#include "Bindable.hpp"

namespace wrd
{
	///	Bind:
	///		Overview:
	///			can guarrantee that specific instance freed completely and track of them.
	///			this has 3 features.
	///				1) can distringuish what given abstract type actually was and reject or accept it regarding that.
	///				2) free instance completely. using RAII.
	///				3) can notice that binding Instance was replaced or freed without unexpected exception.
	///				in conlusion, it prevent halting process or give a change to let developer be advised.
	///
	///		TypeCheking:
	///			This was most valuable requirement when I design component of bind.
	///			in fact, Bind was suggested to replace sort of exisiting smart-ptr concept things, such as weakptr.
	///			because weakptr was planned to replace and enhanced existing pointer of c/c++, they were very strict to
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
	///				becuase it was declared to class template, user need to bind or get binded using type T.
	///				of course these are based on class Bind, user can use loose-check API case by case.
	///
    class Bind : public Node, public Bindable
	{	WRD_CLASS_DECL(Bind, Node)
	public:
		wbool operator==(const This& rhs);
		wbool operator!=(const This& rhs);
		This& operator=(const This& rhs);

	public://	Bind:
		virtual wbool isBind() const;
        /// mostly, unbind is replacable to release() comletely.
        /// but some class(e.g. Refer) treat differently between unbind() and release().
		virtual Res& unbind();
		Id getItsId() const;
		using Bindable::canBind;
		virtual wbool canBind(const Class& cls) const;
		//		Node:
		virtual CStrong use(Msg& msg) const; 
		virtual Strong use(Msg& msg); 
		virtual const Origin& getOrigin() const; 
		virtual const Container& getNodes() const;

	public:	//	Thing:
		using Super::to;
		virtual Strong to(const Class& cls);
		virtual Res& assign(const Thing& it);

	protected://Bind:
		virtual Res& _bind(const Instance& it);
		virtual Instance& _get();
		//	TODO: const cast.
		//		Bind는 알다시피 World의 const를 구현하는 핵심 클래스다.
		//		Node& n = Bind(const T&..);
		//		n.to<T>(); // REJECT. return Bind(Null)
		//		T& cast = n.down<T>(); // REJECT. cast.isNull() == true.
		//		const T& cast = n.down<const T>(); // OK.
		//		Bind& cast1 = n.to<const T>(); // OK. cast1->isNull() != true
		//	위의 코드가 가능하도록 해야 한다.
		virtual Thing& _down(const Class& cls);
		Res& _assign(const This& rhs);

	private:
		Id _its_id; // id for binded one
	};
}
