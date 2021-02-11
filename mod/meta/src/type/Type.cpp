#include "Type.hpp"

namespace wrd {
    WRD_DEF_THIS(Type)

    wbool This::operator==(This& rhs) { return &getName() == &rhs.getName(); }
    wbool This::operator!=(This& rhs) { return !operator==(rhs); }

    Types& This::getLeafs() {
        //TODO: change to range based for loop.
        return nulOf<Types>();
    }

    wbool This::init() {
        //  pre:
        //      Caution for not refering metaclass and binding inside of this:
        //          while this func is called, a structuring for metaclass doesn't finished.
        //          so if you call funcs using metaclass (in)directly, that calling makes
        //          crash or infinite loop.
        //          please you make sure not to use those APIs.
        //
        //      Object class should not initialize explicitly:
        //          or This makes recursive call. Because if we make a instance of TType<Object>,
        //          it triggers Type::init inside of it.
        if(isInit()) return true;

        //  main:
        //      setting init flag first is important:
        //          when we construct structure between super and subs,
        //          we need to assign ptr of static variable. but can't gaurantee that this ptr is
        //          belonged to static memory. so we're going to use get() static func.
        //          when static variable at get() func was not initialized before, its constructor
        //          will leds us to here, however nothing serius happen because init flag was set
        //          to true.
        _setInit(true);
        WRD_I("initializing %s type's meta info...", getName().c_str());
        //      get Supers info from Super:
        //          at this point TType<Super> is instantiated, and "Super" also is all of this
        //          sequences.
        Type& super = getSuper();
        super.init();
        //        constructing SuperType:
        Types& mySupers = getSupers();
        mySupers = super.getSupers();
        mySupers.push_back(&super);
        //        notify to super:
        super.getSubs().push_back(&_getStatic());
        return _logInitOk(true);
    }

    wbool This::rel() {
        // TODO:
        _setInit(false);
        return true;
    }

    wbool This::isSuper(Type& it) {
        //  checking class hierarchy algorithm:
        //        Use the "Tier" of the class hierarchy info to check it.
        //        "Tier" means that how this class are inherited far from the Root class, that is, Object.
        //        So, if the "this" is a super of given object "it", its "tier"th super class
        //        would must be the class of "this".
        if(nul(it)) return false;
        Types& its = it.getSupers();
        wcnt myTier = getSupers().size(),
             itsTier = its.size();
        if(myTier > itsTier) return false;


        //  main:
        Type& target = itsTier == myTier ? it :
            (Type&) *its[myTier];

        return *this == target; // operator== is virtual func.
    }

    wbool This::_logInitOk(wbool res) {
        if(!res) {
            WRD_E("couldn't init meta of %s class.", getName().c_str());
            return res;
        }

#define _FUNC(func) WRD_DI("\t  ." #func "=%s", func ? "true" : "false");
        WRD_EACH(_FUNC, isTemplate(), isAbstract())
#undef _FUNC

        WRD_DI("... %s class init completed.", getName().c_str());
        return res;
    }
}
