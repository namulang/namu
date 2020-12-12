#include "Type.hpp"

namespace wrd { namespace meta {
    WRD_DEF_THIS(Type)

    wbool This::operator==(const This& rhs) const { return &getName() == &rhs.getName(); }
    wbool This::operator!=(const This& rhs) const { return !operator==(rhs); }

    const Types& This::getLeafs() const {
		//TODO: change to range based for loop.
		return nulr<Types>();
    }

    wbool This::init() {
        //	pre:
		//		Caution for not refering metaclass and binding inside of this:
		//			while this func is called, a structuring for metaclass doesn't finished.
		//			so if you call funcs using metaclass (in)directly, that calling makes
		//			crash or infinite loop.
		//			please you make sure not to use those APIs.
		//
		//		Object class should not initialize explicitly:
        //      	or This makes recursive call.
        //			Because if we make a instance of TType<Object>, it triggers Type::init inside of it.
        if(isInit()) return true;

        //  main:
		_setInit(true);
        WRD_I("init %s type's meta info.", getName().c_str());
        //        get Supers info from Super:
        //                at this point TType<Super> is instantiated, and "Super" also is all of this sequences.
        Type& super = const_cast<Type&>(getSuper());
        super.init();
        //        constructing SuperType:
        Types& mySupers = _getSupers();
        mySupers = super._getSupers();
        mySupers.push_back(&super);
        //        notify to super:
        super._getSubs().push_back(this);
        return true;
    }

    wbool This::rel() {
        // TODO:
        _setInit(false);
        return true;
    }

    wbool This::isSuper(const Type& it) const {
        //  checking class hierarchy algorithm:
        //        Use the "Tier" of the class hierarchy info to check it.
        //        "Tier" means that how this class are inherited far from the Root class, that is, Object.
        //        So, if the "this" is a super of given object "it", its "tier"th super class
        //        would must be the class of "this".
        if(nil(it)) return false;
        const Types& its = it.getSupers();
        wcnt myTier = getSupers().size(),
             itsTier = its.size();
        if(myTier > itsTier) return false;


        //  main:
        const Type& target = itsTier == myTier ? it :
            (const Type&) *its[myTier];

        return *this == target;	// operator== is virtual func.
    }
}}
