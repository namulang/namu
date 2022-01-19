#include "parser.hpp"
#include "bison/lowscanner.hpp"

YY_DECL;

namespace wrd {

    WRD_DEF_ME(parser)

    tstr<narr> me::parse(const wchar* script) {
        WRD_I("parse starts.");

        yyscan_t scanner;
        yylex_init_extra(&_eventer, &scanner);

        YY_BUFFER_STATE bufState = yy_scan_string((wchar*) script, scanner); // +2 is for space of END_OF_BUFFER, nullptr.
        if(!bufState) {
            _eventer.getReport()->add(new err(err::ERR, 11, "bufState")).log();
            return str();
        }
        yy_switch_to_buffer(bufState, scanner);

#if YYDEBUG
        yyset_debug(1, scanner); // For Flex (no longer a global, but rather a member of yyguts_t)
        yydebug = 1;             // For Bison (still global, even in a reentrant parser)
#endif

        int res = yyparse(scanner);
        if(res) {
            _eventer.getReport()->add(new err(err::WARN, 12, res)).log();
            return str();
        }

        yy_delete_buffer(bufState, scanner);
        yylex_destroy(scanner);
        _eventer.prepareParse();
        return _eventer.getTray();
    }

    void me::rel() {
        _eventer.rel();
    }
}
