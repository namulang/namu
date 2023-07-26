#pragma once

#include "flag/flags.hpp"

namespace namu {

    struct cli {
        const flags& getFlags() const;

        nbool run(flagArgs& a) {
            _res = -1;
            interpreter ip;
            errReport rpt;
            ip.setReport(rpt);

            for(const auto& op : getFlags()) {
                op->take(ip, *this, a);

                if(a.size() <= 0)
                    break;
            }

            ip.interpret();

            if(!ip.isVerified())
                return _finish(ip);

            starter s;
            str res = s.run(args((baseObj&) ip.getSubPack()));
            _res = 0;
            if(res && res->isSub<nInt>())
                _res = res->cast<nint>();

#ifdef __EMSCRIPTEN__
            // I don't know the detail reason but if user doesn't put '\n' at the
            // end, the line won't be printed.
            std::cout << "\n";
#endif
            if(rpt) // has an err
                _res = -1;
            return _finish(ip);
        }

        nint getRes() const {
            return _res;
        }

    private:
        nint _finish(interpreter& ip) {
            stream& strm = logger::get()["consoleStream"];
            nbool prev = strm.isEnable();

            strm.setEnable(true);
            ip.log();
            strm.setEnable(prev);
            return _res;
        }

    private:
        nint _res;
    };
}
