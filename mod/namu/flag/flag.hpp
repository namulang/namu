#pragma once

#include "args.hpp"
#include "../common.hpp"
#include <regex>

namespace namu {

    struct cli;
    class flag : public instance, public clonable {
        WRD(ADT(flag, instance))

    public:
        virtual const nchar* getName() const = 0;
        virtual const nchar* getDescription() const = 0;

        /// @return how many argument taken by this flag.
        virtual nbool take(interpreter& ip, cli& c, args& a) const;

    protected:
        void _delArgs(args& a, std::vector<int> indices) const {
            // remove del in reverse order.
            for(auto e=indices.rbegin(); e != indices.rend() ;++e)
                a.erase(a.begin() + *e);
        }

        virtual const nchar* _getRegExpr() const = 0;
        virtual nbool _onTake(const args& tray, cli& c, interpreter& ip) const = 0;
    };

    typedef std::vector<tstr<flag>> flags;
}
