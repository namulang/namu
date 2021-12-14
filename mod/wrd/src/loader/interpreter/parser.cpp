#include "parser.hpp"
#include "lowstate.hpp"
#include "lowscanner.hpp"

namespace wrd {

    WRD_DEF_ME(parser)

    str me::parse(const wchar* script) {
        yyscan_t scanner;
        lowstate state;
        yylex_init_extra(&state, &scanner);

        YY_BUFFER_STATE bufState = yy_scan_string((wchar*) script, scanner); // +2 is for space of END_OF_BUFFER, nullptr.
        if(!bufState)
            return WRD_E("bufState == nullptr"), str();

#if YYDEBUG
        yyset_debug(1, scanner); // For Flex (no longer a global, but rather a member of yyguts_t)
        yydebug = 1;             // For Bison (still global, even in a reentrant parser)
#endif

        int res = yyparse(scanner);
        // TODO: handle ret.

        yylex_destroy(scanner);
        rel();
        return state.root;
    }

    void me::rel() {
        _report.bind(dummyErrReport::singletone);
    }

}
