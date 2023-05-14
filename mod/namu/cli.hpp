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
            str res = s.run(args((baseObj&) ip.getSubPack()));

#ifdef __EMSCRIPTEN__
            // I don't know the detail reason but if user doesn't put '\n' at the
            // end, the line won't be printed.
            std::cout << "\n";
#endif
            if(res && !rpt) {
                return _finish(ip, 0);
            }

            return _finish(ip, -1);
        }

    private:
        nint _finish(interpreter& ip, nint ret) {
            stream& strm = logger::get()["consoleStream"];
            nbool prev = strm.isEnable();

            strm.setEnable(true);
            ip.log();
            strm.setEnable(prev);
            return ret;
        }
    };
}
