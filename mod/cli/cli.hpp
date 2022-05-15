#pragma once

#include "option/options.hpp"

namespace wrd {
    struct cli {
        const options& getOptions() const;

        void run(args& a) {
            interpreter ip;

            for(const auto& op : getOptions()) {
                op->take(ip, *this, a);
                if(a.size() <= 0)
                    break;
            }

            errReport rpt;
            ip.setReport(rpt)
              .interpret();

            if(!ip.isVerified())
                return;

            starter s;
            str res = s.run(narr(ip.getPack()));
            if(res)
                std::cout << "end successfully.\n";
        }
    };
}
