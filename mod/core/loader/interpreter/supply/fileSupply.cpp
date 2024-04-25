#include "fileSupply.hpp"
#include "../parser.hpp"

namespace namu {
    NAMU(DEF_ME(fileSupply))

    me::fileSupply(const std::string& newPath):  _path(newPath) {}

    void* me::onSupplySrc(parser& ps, void* scanner) const {
        static std::string dummy;
        std::ifstream fout(_path);
        if(fout.fail())
            // there is no file.
            return ps.getReport().add(err::newErr(errCode::FILE_NOT_OPEN, _path.c_str())), nullptr;

        std::stringstream buffer;
        buffer << fout.rdbuf();
        return _scanString(ps, buffer.str().c_str(), scanner);
    }
}
