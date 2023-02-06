#pragma once

#include "flag/flags.hpp"

namespace namu {
    struct cli {
        const flags& getFlags() const;

        nbool run(flagArgs& a) {
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
            str res = s.run(args(ip.getSubPack()));
            if(res && !rpt) {
                return _finish(ip, 0);
            }

            return _finish(ip, -1);
        }

    private:
        nint _finish(interpreter& ip, nint ret) {
            ip.log();
            return ret;
        }
    };
}
