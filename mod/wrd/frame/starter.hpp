#pragma once

#include "frame.hpp"
#include "../builtin/container/native/tndumMap.hpp"

namespace wrd {

    class starter : public node {
        WRD(CLASS(starter, node))

    public:
        starter() {}

    public:
        // node:
        nbicontainer& subs() override {
            static ndumMap inner;
            return inner;
        }

        wbool canRun(const ucontainable& args) const override {
            return args.len() == 1 && args.begin()->isSub<node>();
        }

        str run(const ucontainable& args) override {
            if(!canRun(args))
                return WRD_E("argument doesn't match to main func()"), str();

            node& pak = *args.begin();
            node& main = _findMain(pak, args);
            if(nul(main))
                return WRD_E("there is 0 or more than 2 main() found."), str();

            if(main.canRun(narr()))
                return pak.run("main", narr());

            /* TODO: str[] args
            if(main.canRun(narr(k*/

            return WRD_E("couldn't run main func(). it doesn't match any argument"), str();
        }

    private:
        node& _findMain(node& pak, const ucontainable& args) {
            node& ret = pak.sub("main", narr());
            if(nul(ret))
                WRD_E("could'nt find main().");

            return ret;
        }
    };

}
