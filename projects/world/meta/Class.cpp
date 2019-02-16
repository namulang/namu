#include "Class.hpp"
#include "Classes.hpp"
#include "../memory/TStrong.hpp"
#include "../base/Thing.hpp"

namespace wrd
{
#define THIS Class
	//	we can't put WRD_CLASS_DEF here. it'll generates TClass<TClass<TClass<....> infinitely.
	
	///	@remark	Class returning result of getClass() with itself.
	///			if this func always returns metaclass no matter of what This type is,
	///			users need to care about getting meta of metaclass on calling getClass().
	///			for example,
	///				Thing& thing1 = ...; // let's assume that got from outside.
	///				Object obj;
	///
	///				wbool compare = obj.isSub(thing1.getClass()); // user intend to get class of Thing.
	///				// however, value 'compare' will definitely be false if
	///				// thing was actually a retrived one by calling Thing.getClass() before.
	///
	///				// because Class::getClass() will return TClass<TClass<T> >,
	///				// that stmt will be translated that checks object vs TClass<T>.
	///
	///			so basically, when you want to get Class of Class of Class,that is Meta of Meta class, you should wrap given type T with TClass class template.
	///			e.g) TClass<Class>
	const Class& THIS::getClass() const { return This::getClassStatic(); }
	TStrong<THIS> THIS::clone() const { return TStrong<This>(_clone().down<This>()); }
	WRD_LAZY_METHOD(const Class&, THIS::getClassStatic, WRD_VOID(), TClass<This>)

	Res& THIS::onInitNodes(Container& tray)
	{
		//	TODO:
		return wasgood;
	}

	TStrong<Instance> THIS::_clone() const { return TCloner<This>::clone(*this); }
    wbool THIS::operator==(const This& rhs) const { return &getName() == &rhs.getName(); }
    wbool THIS::operator!=(const This& rhs) const { return ! operator==(rhs); }

    const Classes& THIS::getLeafs() const
    {
		//TODO: change to range based for loop.
		static Classes inner;
		return inner;
    }

	const Array& THIS::getVars() const
	{
		static Array inner;
		return inner;
	}

    Res& THIS::init()
    {
        //	pre:
		//		Caution for not refering metaclass and binding inside of this:
		//			while this func is called, a structuring for metaclass doesn't finished.
		//			so if you call funcs using metaclass (in)directly, that calling makes
		//			crash or infinite loop.
		//			please you make sure not to use those APIs.
		//
		//		Object class should not initialize explicitly:
        //      	or This makes recursive call.
        //			Because if we make a instance of TClass<Object>, it triggers Class::init inside of it.
		if( ! Classer::_isPreloaded())
			return Classer::_preload(*this), wasntinit;
        if(isInit()) return wascancel;

        //  main:
        //        get Supers info from Super:
        //                at this point TClass<Super> is instantiated, and "Super" also is all of this sequences.
        Class& super = const_cast<Class&>(getSuper());
        super.init();
        //        constructing SuperClass:
        Classes& my_supers = _getSupers();
        my_supers = super._getSupers();
        my_supers.push(super);
        //        notify to super:
        if(super._getSubs().push(*this) == wrongidx)
            return wascancel;

        return wasgood;
    }

    wbool THIS::isSuperCls(const Class& it) const
    {
        //  checking class hierarchy algorithm:
        //        Use the "Tier" of the class hierarchy info to check it.
        //        "Tier" means that how this class are inherited far from the Root class, that is, Object.
        //        So, if the "this" is a super of given object "it", its "tier"th super class
        //        would must be the class of "this".
        if(it.isNull()) return false;
        Classes& its = (Classes&) it.getSupers();
        wcnt    my_tier = getSupers().getLen(),
                its_tier = its.getLen();
        if(my_tier > its_tier) return false;


        //  main:
        const Class& target = its_tier == my_tier ? it :
            (const Class&) its._arr[my_tier]._get();

        return *this == target;	// operator== is virtual func. 
    }

    Classes& THIS::_getSupers() { return const_cast<Classes&>(getSupers()); }
    Classes& THIS::_getSubs() { return const_cast<Classes&>(getSubs()); }

    Res& THIS::_initNodes()
    {
        _getNodes() = getSupers()[0].getNodes(); // getSupers()[0] is parent class.
        return wasgood;
	}
}
