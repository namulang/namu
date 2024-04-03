#include "errPassFilter.hpp"

namespace namu {
    NAMU(DEF_ME(errPassFilter))

    std::string me::filt(logLv::level lv, const nchar* tag, const std::string& msg) const {
        if(lv > logLv::ERR) return "";
        return msg;
    }
}
