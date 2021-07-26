#include "interpreter.hpp"
#include "wrdScanner.hpp"

namespace wrd {

    WRD_DEF_ME(interpreter)

    wbool me::test(const wchar* msg) {
        yyscan_t scanner;
        yylex_init(&scanner);

        //TODO: read from file: yyset_in(input_file, scanner);
        std::string str(msg);
        YY_BUFFER_STATE buffer = yy_scan_buffer((wchar*) str.c_str(), str.size() + 2, scanner); // + 2 for marking END_OF_BUFFER, nullptr.
        if (buffer == nullptr) {
            return WRD_E("buffer == null"), false;
        }

        // TODO: provide API to manipulate these variable
        yyset_debug(1, scanner); // For Flex (no longer a global, but rather a member of yyguts_t)
#if YYDEBUG
        yydebug = 1;             // For Bison (still global, even in a reentrant parser)
#endif

        int ret = yyparse(scanner);

        yylex_destroy(scanner);
        return ret == 0;
    }
}
