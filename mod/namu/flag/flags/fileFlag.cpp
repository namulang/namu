#include "fileFlag.hpp"
#include <fstream>
#include <sstream>

namespace namu {
    NAMU_DEF_ME(fileFlag)

    const nchar* me::getName() const {
        return "<filePath>";
    }

    const nchar* me::getDescription() const {
        return R"DESC(
    file path of namu language script file.
    extension of file should be end with 'nm'.
    wildcard and the question mark aren't allowed.)DESC";
    }

    const nchar* me::_getRegExpr() const {
        return "[\\\\\\w\\.\\/:\\-\\(\\)\\d]+\\.nm$";
    }

    nbool me::_onTake(const flagArgs& tray, cli& c, interpreter& ip) const {
        std::vector<string> buf;

        for(const auto& filePath : tray) {
            std::ifstream fout(filePath);
            if(fout.fail()) { // there is no file.
                ip.getReport().add(err::newErr(errCode::FILE_NOT_OPEN, filePath.c_str()));
                continue;
            }

            std::stringstream buffer;
            buffer << fout.rdbuf();

            buf.push_back(buffer.str());
        }

        ip.setSrcSupply(*new bufferSrcSupply(buf));
        return true;
    };
}
