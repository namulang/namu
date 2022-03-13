%top {
/*  ============================================================================================
    |                                          PROLOGUE                                        |
    ============================================================================================  */

#include "lowparser.hpp"
#include "../loweventer.hpp"
#include <iostream>
#include <functional>

#define YY_DECL int yylexOrigin(YYSTYPE* yylval_param, YYLTYPE* yylloc_param, yyscan_t yyscanner)
#define YY_USER_ACTION yylloc->start.row = yylloc->end.row = yyget_lineno(yyscanner); \
                       yylloc->start.col = yylloc->colcnt; yylloc->end.col = yylloc->colcnt+yyleng-1; \
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

/* reusable pattern: */

/* actual-pattern: */
%%

[*+-/\(\.\,] { return yyget_extra(yyscanner)->onIgnoreIndent(yytext[0]); }
[\)] { return yytext[0]; }
\-\- {
    WRD_E("DOUBLE_MINUS");
    return DOUBLE_MINUS;
}
\-> { return ARROW; }
\+\+ { return DOUBLE_PLUS; }
[ \t]+ ;
\n {
    yylloc->colcnt = yylloc->start.col = yylloc->end.col= 0;
    yyget_extra(yyscanner)->onNewLine();
    return NEWLINE;
}

if { return IF; }
void { return VOID; }
int { return INT; }
str { return STR; }
bool { return BOOL; }
char { return CHAR; }
flt { return FLT; }
null { return NUL; }
pack { return PACK; }
aka { return AKA; }
return { return RETURN; }

[[:digit:]]+ {
    yylval->asInt = atoi(yytext);
    WRD_DI("scanner: INTVAL=%s", yytext);
    return INTVAL;
}

[[:alpha:]]+[[:alnum:]]* {
    yylval->asStr = strdup(yytext);
    WRD_DI("scanner: NAME=%s", yytext);
    return NAME;
}

\'[^\r\f\n\']\' {
    yylval->asChar = yytext[0];
    WRD_DI("scanner: CHARVAR='%c'", yytext[0]);
    return CHARVAR;
}

\"[^\r\f\n\"]*\" {
    yylval->asStr = strdup(yytext);
    WRD_DI("scanner: STRVAL=\"%s\"", yytext);
    return STRVAL;
}

<<EOF>> {
    WRD_DI("scanner: ENDOFFILE");
    yylloc->colcnt = 0;
    return ENDOFFILE;
}

<*>. {
    return yyget_extra(yyscanner)->onScanUnexpected(yytext);
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
    while(tok == SCAN_AGAIN ||
          tok == SCAN_MODE_INDENT ||
          tok == SCAN_MODE_NORMAL);

    return tok;
}
