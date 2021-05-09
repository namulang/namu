#include "smallWorld.hpp"
#include <fstream>
#include "flex.hpp"

namespace wrd { namespace swrd {

    namespace {
        std::string _fileName;
    }

    WRD_DEF_ME(smallWorld)

    tstr<obj> me::interp(const wchar* script) {
        YY_BUFFER_STATE buffer = yy_scan_string(script);
        tstr<obj> ret = _runParser();
        yy_delete_buffer(buffer);
        return ret;
    }
    tstr<obj> me::interp(const std::string& script) {
        return interp(script.c_str());
    }
    tstr<obj> me::interpFile(const wchar* path) {
        yyin = fopen(path, "r");
        if(!yyin)
            return WRD_E("invalid file path %s.", path), tstr<obj>();

        _fileName = _extractFileName(path);
        WRD_I("interpreting file '%s'...", _fileName.c_str());
        return _runParser();
    }
    tstr<obj> me::interpFile(const std::string& path) {
        return interpFile(path.c_str());
    }

    tstr<obj> me::_runParser() {
        int res = yyparse();
        if(res)
            return WRD_E("interpretion has been failed. res=%d", res), tstr<obj>();
        if(!root)
            WRD_E("nothing interpreted.");

        return tstr<obj>(root);
    }

    const std::string& me::getFileName() {
        return _fileName;
    }

    std::string me::_extractFileName(const std::string& path) {
        size_t atSlash = path.find_last_of("\\/");
        if(atSlash < 0) return "";

        return path.substr(atSlash + 1);
    }
}}
