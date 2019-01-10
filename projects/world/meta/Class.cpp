#include "Class.hpp"
#include "Classes.hpp"
#include "../memory/TStrong.hpp"
#include "../base/Thing.hpp"

namespace wrd
{
#define THIS Class
	//	we can't put WRD_CLASS_DEF here. it'll generates TClass<TClass<TClass<....> infinitely.
	const Class& THIS::getClass() const { return *this; }
	TStrong<THIS> THIS::clone() const { return TStrong<This>(_clone().down<This>()); }
    wbool THIS::operator==(const This& rhs) const { return &getName() == &rhs.getName(); }
    wbool THIS::operator!=(const This& rhs) const { return &getName() != &rhs.getName(); }

    const Classes& THIS::getLeafs() const
    {
        static Classes inner;
        //    TODO:
		return inner;
    }

	const Array& THIS::getVars() const
	{
		static Array inner;
		return inner;
	}

	wbool THIS::isInit() const { /*TODO: */ return false; }

    Res& THIS::init()
    {
		/* TODO: impl Array
        //    pre:
        //        exception:
        WRD_IS_SUPER(init())

        //    main:
        //        Object class should not initialize explicitly:
        //            or This makes recursive call.
        //            Because if we make a instance of TClass<Object>, it triggers Class::init inside of it.
        if(&getName() == &TClass<Thing>::getNameStatic())
            return wasgood;

        //  main:
        //        get Supers info from Super:
        //                at this point TClass<Super> is instantiated, and "Super" also is all of this sequences.
        Class& super = const_cast<Class&>(getSuper());
        super.init();
        //        constructing SuperClass:
        Classes& my_supers = _getSupers();
        my_supers = super._getSupers();
        my_supers.push(&super);
        //        notify to super:
        if(super._getSubs().push(*this) != wrongidx)
            return wascancel;
		*/
        return wasgood;
    }

    wbool THIS::isSuper(const Class& it) const
    {	/* TODO: impl Array
        //  checking class hierarchy algorithm:
        //        Use the "Tier" of the class hierarchy info to check it.
        //        "Tier" means that how this class are inherited far from the Root class, that is, Object.
        //        So, if the "this" is a super of given object "it", its "tier"th super class
        //        would must be the class of "this".
        if(it.isNull()) return false;
        const Classes& its = it.getSupers();
        wcnt    my_tier = getClass().getSupers().size(),
                its_tier = its_supers.size();
        if(my_tier > its_tier) return false;


        //  main:
        const ClassBase& target = its_tier == my_tier ? it :
            static_cast<const Class&>(its[my_tier]);

        return getClass() == target;//  Remember. We're using Class as "Monostate".
		*/
		return false;
    }

    Classes& THIS::_getSupers() { return const_cast<Classes&>(getSupers()); }
    Classes& THIS::_getSubs() { return const_cast<Classes&>(getSubs()); }

    Res& THIS::_initNodes()
    {
        _getNodes() = getSupers()[0].getNodes(); // getSupers()[0]은 바로 위의 부모클래스.
        return wasgood;
	}
	
	TStrong<Instance> THIS::_clone() const { return TCloner<This>::clone(*this); }
}
