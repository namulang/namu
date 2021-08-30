#include "parser.hpp"
#include "lowscanner.hpp"

namespace wrd {

    WRD_DEF_ME(parser)

    str me::parseBuffer(const std::string& buffer) {
        yyscan_t scanner;
        yylex_init_extra(this, &scanner);

        YY_BUFFER_STATE bufState = yy_scan_buffer((wchar*) buffer.c_str(), buffer.size() + 2, scanner); // +2 is for space of END_OF_BUFFER, nullptr.
        if(!bufState)
            return WRD_E("bufState == nullptr"), str();

#if YYDEBUG
        yyset_debug(1, scanner); // For Flex (no longer a global, but rather a member of yyguts_t)
        yydebug = 1;             // For Bison (still global, even in a reentrant parser)
#endif

        int res = yyparse(this, scanner);
        // TODO: handle ret.

        yylex_destroy(scanner);
        str ret = getRootBinder();

		rel();
		return ret;
    }
}
