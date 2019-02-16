#include "Class.hpp"
#include "Classes.hpp"
#include "../memory/TStrong.hpp"
#include "../base/Thing.hpp"

namespace wrd
{
#define THIS Class
	//	we can't put WRD_CLASS_DEF here. it'll generates TClass<TClass<TClass<....> infinitely.
	WRD_CLASS_DEF(THIS)

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

    wbool THIS::isSuper(const Class& it) const
    {
        //  checking class hierarchy algorithm:
        //        Use the "Tier" of the class hierarchy info to check it.
        //        "Tier" means that how this class are inherited far from the Root class, that is, Object.
        //        So, if the "this" is a super of given object "it", its "tier"th super class
        //        would must be the class of "this".
        if(it.isNull()) return false;
        const Classes& its = it.getSupers();
        wcnt    my_tier = getSupers().getLen(),
                its_tier = its.getLen();
        if(my_tier > its_tier) return false;


        //  main:
        const Class& target = its_tier == my_tier ? it :
            static_cast<const Class&>(its[my_tier]);

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
