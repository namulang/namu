#pragma once

#include "flagArgs.hpp"
#include "../common.hpp"
#include <regex>

namespace namu {

    struct cli;
    class flag : public instance, public clonable {
        NAMU(ADT(flag, instance))

    public:
        virtual const nchar* getName() const = 0;
        virtual const nchar* getDescription() const = 0;

        /// @return how many argument taken by this flag.
        virtual nbool take(interpreter& ip, cli& c, flagArgs& a) const;

    protected:
        void _delArgs(flagArgs& a, std::vector<int> indices) const {
            // remove del in reverse order.
            for(auto e=indices.rbegin(); e != indices.rend() ;++e)
                a.erase(a.begin() + *e);
        }

        virtual const nchar* _getRegExpr() const = 0;
        virtual nbool _onTake(const flagArgs& tray, cli& c, interpreter& ip) const = 0;
    };

    typedef std::vector<tstr<flag>> flags;
}
