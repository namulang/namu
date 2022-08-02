#pragma once

#include "flag/flags.hpp"

namespace namu {
    struct cli {
        const flags& getFlags() const;

        wbool run(args& a) {
            interpreter ip;

            for(const auto& op : getFlags()) {
                op->take(ip, *this, a);

                if(a.size() <= 0)
                    break;
            }

            errReport rpt;
            ip.setReport(rpt)
              .interpret();

            if(!ip.isVerified())
                return _finish(ip, -1);

            starter s;
            str res = s.run(narr(ip.getSlot()));
            if(res && !rpt) {
                return _finish(ip, 0);
            }

            return _finish(ip, -1);
        }

    private:
        wint _finish(interpreter& ip, wint ret) {
            ip.log();
            return ret;
        }
    };
}
