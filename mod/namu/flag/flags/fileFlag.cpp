#include "fileFlag.hpp"
#include <fstream>
#include <sstream>

namespace namu {
    WRD_DEF_ME(fileFlag)

    wbool me::_onTake(const args& tray, cli& c, interpreter& ip) const {
        std::vector<string> buf;

        for(const auto& filePath : tray) {
            std::ifstream fout(filePath);
            std::stringstream buffer;
            buffer << fout.rdbuf();

            buf.push_back(buffer.str());
        }

        ip.setSrcSupply(*new bufferSrcSupply(buf));
        return true;
    };
}
