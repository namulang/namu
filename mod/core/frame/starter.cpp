#include "../ast/obj.hpp"
#include "../ast/func.hpp"
#include "../ast/scope.inl"
#include "../ast/slot.hpp"
#include "starter.hpp"

namespace namu {

    NAMU_DEF_ME(starter)

    nbicontainer& me::subs() {
        static ndumMap inner;
        return inner;
    }

    nbool me::canRun(const args& a) const {
        return a.len() == 1 && a.begin()->isSub<node>();
    }

    str me::run(const args& a) {
        if(!canRun(a))
            return NAMU_E("argument doesn't match to main func()"), str();

        node& pak = *a.begin();
        NAMU_I("run a pack");
        node& main = _findMain(pak, args());
        if(nul(main))
            return NAMU_E("there is 0 or more than 2 main() found."), str();

        if(main.canRun(narr()))
            return pak.run("main");

        /* TODO: str[] args
        if(main.canRun(narr(k*/

        return NAMU_E("couldn't run main func(). it doesn't match any argument"), str();
    }

    node& me::_findMain(node& pak, const args& a) {
        // TODO: now, only find to main() but I need to find main(argc, argv) case, too.
        node& ret = pak.sub("main", a);
        if(nul(ret))
            NAMU_E("could'nt find main().");

        return ret;
    }
}
