#include "../ast/obj.hpp"
#include "../ast/func.hpp"
#include "../ast/scope.inl"
#include "../ast/slot.hpp"
#include "starter.hpp"

namespace namu {

    WRD_DEF_ME(starter)

    nbicontainer& me::subs() {
        static ndumMap inner;
        return inner;
    }

    wbool me::canRun(const ucontainable& args) const {
        return args.len() == 1 && args.begin()->isSub<node>();
    }

    str me::run(const ucontainable& args) {
        if(!canRun(args))
            return WRD_E("argument doesn't match to main func()"), str();

        node& pak = *args.begin();
        WRD_I("run a pack");
        node& main = _findMain(pak, narr());
        if(nul(main))
            return WRD_E("there is 0 or more than 2 main() found."), str();

        if(main.canRun(narr()))
            return pak.run("main");

        /* TODO: str[] args
        if(main.canRun(narr(k*/

        return WRD_E("couldn't run main func(). it doesn't match any argument"), str();
    }

    node& me::_findMain(node& pak, const ucontainable& args) {
        // TODO: now, only find to main() but I need to find main(argc, argv) case, too.
        node& ret = pak.sub("main", narr());
        if(nul(ret))
            WRD_E("could'nt find main().");

        return ret;
    }
}
