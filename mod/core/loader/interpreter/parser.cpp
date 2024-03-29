#include "parser.hpp"
#include "bison/lowscanner.hpp"
#include "../../ast/slot.hpp"
#include "../../frame/thread.hpp"

YY_DECL;

namespace namu {

    NAMU_DEF_ME(parser)

    me& me::setSlot(const slot& tray) {
        _eventer.getSlot().bind(tray);
        return *this;
    }

    slot& me::getSlot() {
        return *_eventer.getSlot();
    }

    obj& me::getSubPack() {
        return *_eventer.getSubPack();
    }

    tstr<obj> me::parse(const nchar* script) {
        if(nul(thread::get())) {
            _eventer.getReport()->add(err::newErr(errCode::NO_THREAD));
            return tstr<obj>();
        }

        NAMU_I("parse starts.");
        _eventer.prepareParse();

        yyscan_t scanner;
        yylex_init_extra(&_eventer, &scanner);

        YY_BUFFER_STATE bufState = yy_scan_string((nchar*) script, scanner); // +2 is for space of END_OF_BUFFER, nullptr.
        if(!bufState) {
            _eventer.getReport()->add(err::newErr(errCode::IS_NULL, "bufState")).log();
            return tstr<obj>();
        }

        // fix Flex Bug here:
        //  when yy_scan_string get called, it returns bufState after malloc it.
        //  but some variables wasn't initialized. yy_bs_lineno(used to calculate
        //  current cursor position) is one of them.
        bufState->yy_bs_lineno = bufState->yy_bs_column = 0;
        yy_switch_to_buffer(bufState, scanner);

#if YYDEBUG
        //yyset_debug(1, scanner); // For Flex (no longer a global, but rather a member of yyguts_t)
        //yydebug = 1;             // For Bison (still global, even in a reentrant parser)
#endif

        int res = yyparse(scanner);
        if(res) {
            _eventer.getReport()->add(err::newWarn(errCode::PARSING_HAS_ERR, res)).log();
            return tstr<obj>();
        }

        yy_delete_buffer(bufState, scanner);
        yylex_destroy(scanner);
        return _eventer.getSubPack();
    }

    void me::rel() {
        _eventer.rel();
    }

    me::parser() { me::rel(); }

    me& me::setReport(errReport& report) {
        _eventer.getReport().bind(report);
        return *this;
    }
}
