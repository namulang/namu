#include "type.hpp"

namespace namu {
    WRD_DEF_ME(type)

    wbool me::operator==(const me& rhs) const {
#if WRD_BUILD_PLATFORM == WRD_TYPE_WINDOWS
        return getName() == rhs.getName();
#else
        return &getName() == &rhs.getName();
#endif
    }

    wbool me::operator!=(const me& rhs) const { return !operator==(rhs); }

    const types& me::getLeafs() const {
        types* leafs = *_onGetLeafs();
        if(!leafs) {
            // TODO: search & extract all derive classes.
            leafs = new types();
            _setLeafs(leafs);

            _findLeafs(*this, *leafs);
        }

        return *leafs;
    }

    void me::_findLeafs(const type& cls, types& tray) const {
        for(const type* sub : cls.getSubs()) {
            if(sub->getSubs().size() == 0)
                tray.push_back(const_cast<type*>(sub));

            _findLeafs(*sub, tray);
        }
    }

    wbool me::init() {
        // pre:
        //  Caution for not refering metaclass and binding inside of this:
        //  while this func is called, a structuring for metaclass doesn't finished.
        //  so if you call funcs using metaclass (in)directly, that calling makes
        //  crash or infinite loop.
        //  please you make sure not to use those APIs.
        //
        // Object class should not initialize explicitly:
        //  or me makes recursive call. Because if we make a instance of TType<Object>,
        //  it triggers Type::init inside of it.
        if(isInit()) return false;

        // main:
        //  setting init flag first is important:
        //      when we construct structure between super and subs,
        //      we need to assign ptr of static variable. but can't gaurantee that this ptr is
        //      belonged to static memory. so we're going to use get() static func.
        //      when static variable at get() func was not initialized before, its constructor
        //      will leds us to here, however nothing serius happen because init flag was set
        //      to true.
        _setInit(true);
        //  get Supers info from Super:
        //      at this point TType<Super> is instantiated, and "Super" also is all of this
        //      sequences.
        type& super = const_cast<type&>(getSuper());
        super.init();
        //        constructing SuperType:
        types& mySupers = _getSupers();
        mySupers = super._getSupers();
        mySupers.push_back(&super);
        // post:
        //  notify to super:
        super._onAddSubClass(*this);
        return _logInitOk(true);
    }

    void me::_onAddSubClass(const me& subClass) {
        _getSubs().push_back(&subClass._getStatic());
    }

    wbool me::rel() {
        // TODO:
        _setInit(false);
        return true;
    }

    wbool me::isSuper(const type& it) const {
        //  checking class hierarchy algorithm:
        //        Use the "Tier" of the class hierarchy info to check it.
        //        "Tier" means that how this class are inherited far from the Root class, that is, Object.
        //        So, if the "this" is a super of given object "it", its "tier"th super class
        //        would must be the class of "this".
        if(nul(it)) return false;
        const types& its = it.getSupers();
        wcnt myTier = getSupers().size(),
             itsTier = its.size();
        if(myTier > itsTier) return false;


        //  main:
        const type& target = itsTier == myTier ? it :
            (const type&) *its[myTier];

        return *this == target; // operator== is virtual func.
    }

    wbool me::_logInitOk(wbool res) {
        if(!res) {
            WRD_E("couldn't init meta of %s class.", getName().c_str());
            return res;
        }

        return res;
    }

    const types& me::getSubs() const {
        return (const_cast<me*>(this))->_getSubs();
    }
    const types& me::getSupers() const {
        return (const_cast<me*>(this))->_getSupers();
    }

    void me::_setInit(wbool newState) {
        const wbool& res = isInit();
        wbool& isInit = const_cast<wbool&>(res);

        isInit = newState;
    }

    void me::_setLeafs(types* newLeafs) const {
        types** leafs = _onGetLeafs();
        if(*leafs == newLeafs) return;

        if(*leafs)
            delete *leafs;

        *leafs = newLeafs;
    }
}
