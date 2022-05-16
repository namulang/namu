#include "parser.hpp"
#include "bison/lowscanner.hpp"
#include "../../ast/pack.hpp"

YY_DECL;

namespace wrd {

    WRD_DEF_ME(parser)

    me& me::setPack(const pack& pak) {
        _eventer.getPack().bind(pak);
        return *this;
    }

	pack& me::getPack() {
		return *_eventer.getPack();
	}

	node& me::getSubPack() {
		return *_eventer.getSubPack();
	}

    str me::parse(const wchar* script) {
        WRD_I("parse starts.");
        _eventer.prepareParse();

        yyscan_t scanner;
        yylex_init_extra(&_eventer, &scanner);

        YY_BUFFER_STATE bufState = yy_scan_string((wchar*) script, scanner); // +2 is for space of END_OF_BUFFER, nullptr.
        if(!bufState) {
            _eventer.getReport()->add(new err(err::ERR, errCode::IS_NULL, "bufState")).log();
            return str();
        }
        yy_switch_to_buffer(bufState, scanner);

#if YYDEBUG
        //yyset_debug(1, scanner); // For Flex (no longer a global, but rather a member of yyguts_t)
        //yydebug = 1;             // For Bison (still global, even in a reentrant parser)
#endif

        int res = yyparse(scanner);
        if(res) {
            _eventer.getReport()->add(new err(err::WARN, errCode::PARSING_HAS_ERR, res)).log();
            return str();
        }

        yy_delete_buffer(bufState, scanner);
        yylex_destroy(scanner);
        return _eventer.getSubPack();
    }

    void me::rel() {
        _eventer.rel();
    }
}
