%top {
/*  ============================================================================================
    |                                          PROLOGUE                                        |
    ============================================================================================  */

#include "lowparser.hpp"
#include "../loweventer.hpp"
#include <iostream>
#include <functional>

#define YY_DECL int yylexOrigin(YYSTYPE* yylval_param, YYLTYPE* yylloc_param, yyscan_t yyscanner)
#define YY_USER_ACTION yylloc->first_line = yylloc->last_line = yyget_lineno(yyscanner); \
                       yylloc->first_column = yylloc->colcnt; yylloc->last_column = yylloc->colcnt+yyleng-1; \
                       yylloc->colcnt += yyleng;
}

/*  ============================================================================================
    |                                      FLEX DEFINITIONS                                    |
    ============================================================================================  */

%option reentrant bison-bridge bison-locations
%option extra-type="wrd::loweventer*"
%option yylineno



/*  ============================================================================================
    |                                           RULES                                          |
    ============================================================================================  */
%%

";" { return yytext[0]; }
if { return IF; }
[ \t]+ ;
\n {
    yylloc->colcnt = 0;
    return NEWLINE;
}

[[:digit:]]+ {
    yylval->nint = atoi(yytext);
    return INT;
}

<<EOF>> {
    std::cout << "---EOF!\n";
    yylloc->colcnt = 0;
    return ENDOFFILE;
}

%%
/*  ============================================================================================
    |                                         EPILOGUE                                         |
    ============================================================================================  */

int yywrap(yyscan_t scanner) {
    // TODO:
    return 1;
}

int yylex(YYSTYPE* yylval_param, YYLTYPE* yylloc_param, yyscan_t yyscanner) {
    wrd::loweventer* eventer = yyget_extra(yyscanner);
    if(!eventer->isInit()) // init: tokenScanable
        eventer->setScan<wrd::indentScan>();

    int tok;
    do
        tok = eventer->onScan(*eventer, yylval_param, yylloc_param, yyscanner);
    while(tok == SCAN_AGAIN);

    return tok;
}
