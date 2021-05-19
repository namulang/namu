#include "swrd.hpp"
#include <fstream>
#include "flex.hpp"

namespace wrd {

    namespace {
        std::string _fileName;
    }

    WRD_DEF_ME(swrd)

    tstr<sobj> me::interp(const wchar* script) {
        YY_BUFFER_STATE buffer = yy_scan_string(script);
        tstr<sobj> ret = _runParser();
        yy_delete_buffer(buffer);
        return ret;
    }
    tstr<sobj> me::interp(const std::string& script) {
        return interp(script.c_str());
    }
    tstr<sobj> me::interpFile(const wchar* path) {
        yyin = fopen(path, "r");
        if(!yyin)
            return WRD_E("invalid file path %s.", path), tstr<sobj>();

        _fileName = _extractFileName(path);
        WRD_I("interpreting file '%s'...", _fileName.c_str());
        return _runParser();
    }
    tstr<sobj> me::interpFile(const std::string& path) {
        return interpFile(path.c_str());
    }

    tstr<sobj> me::_runParser() {
        int res = yyparse();
        if(res)
            return WRD_E("interpretion has been failed. res=%d", res), tstr<sobj>();
        if(!root)
            WRD_E("nothing interpreted.");

        return tstr<sobj>(root);
    }

    const std::string& me::getFileName() {
        return _fileName;
    }

    std::string me::_extractFileName(const std::string& path) {
        size_t atSlash = path.find_last_of("\\/");
        if(atSlash < 0) return "";

        return path.substr(atSlash + 1);
    }
}
