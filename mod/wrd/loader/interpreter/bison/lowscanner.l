%top {
/*  ============================================================================================
    |                                          PROLOGUE                                        |
    ============================================================================================  */

#include "lowparser.hpp"
#include "../loweventer.hpp"
#include <iostream>
#include <functional>
#ifdef WRD_BUILD_PLATFORM_IS_WINDOWS
#   define YY_NO_UNISTD_H 1
#endif
namespace {
    static constexpr int TAB_WIDTH = 4;
}

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
%option nounistd


/*  ============================================================================================
    |                                           STATE                                          |
    ============================================================================================  */

%x stateComment


/*  ============================================================================================
    |                                           RULES                                          |
    ============================================================================================  */

/* reusable pattern: */

/* actual-pattern: */
%%

[%*+-/\(\.\,] { return yyget_extra(yyscanner)->onIgnoreIndent(yytext[0]); }
[\)] { return yytext[0]; }
\-\- {
    WRD_E("DOUBLE_MINUS");
    return DOUBLE_MINUS;
}
\-> { return ARROW; }
\+\+ { return DOUBLE_PLUS; }
\= { return ASSIGN; }
":=" { return DEFASSIGN; }
[ ]+ ;
\t {
    yylloc->start.col = (yylloc->start.col + TAB_WIDTH) & ~(TAB_WIDTH-1);
    yylloc->colcnt = (yylloc->colcnt + TAB_WIDTH) & ~(TAB_WIDTH-1);
}

\n {
    yylloc->colcnt = yylloc->start.col = yylloc->end.col= 0;
    yyget_extra(yyscanner)->onNewLine();
    return NEWLINE;
}

if { return IF; }
void { return VOIDTYPE; }
int { return INTTYPE; }
str { return STRTYPE; }
bool { return BOOLTYPE; }
char { return CHARTYPE; }
flt { return FLTTYPE; }
null { return NULTYPE; }
pack { return PACK; }
aka { return AKA; }
return { return RETURN; }
as { return AS; }

[[:digit:]]+ {
    yylval->asInt = atoi(yytext);
    WRD_DI("scanner: INTVAL=%s", yytext);
    return INTVAL;
}

[[:digit:]]+\.[[:digit:]]+ {
    yylval->asFlt = std::stod(yytext);
    WRD_DI("scanner: FLTVAL=%f", yylval->asFlt);
    return FLTVAL;
}

true {
    yylval->asBool = true;
    WRD_DI("scanner: BOOLVAL=true");
    return BOOLVAL;
}

false {
    yylval->asBool = false;
    WRD_DI("scanner: BOOLVAL=false");
    return BOOLVAL;
}

[a-zA-Z0-9_]+ {
    yylval->asStr = strdup(yytext);
    WRD_DI("scanner: NAME=%s", yytext);
    return NAME;
}

\'([^\r\f\n\'])\' {
    yylval->asChar = yytext[1];
    WRD_DI("scanner: CHARVAR='%c'", yytext[0]);
    return CHARVAR;
}

\"([^\r\f\n\"]*)\" {
    int len = strlen(yytext) - 2; // without double-quotes
    yylval->asStr = new char[len+1];
    strncpy(yylval->asStr, yytext+1, len);
    yylval->asStr[len] = '\0';
    WRD_DI("scanner: STRVAL=\"%s\"", yylval->asStr);
    return STRVAL;
}

<<EOF>> {
    WRD_DI("scanner: ENDOFFILE");
    yylloc->colcnt = 0;
    return ENDOFFILE;
}

\/\/[^\n]* {}

\/\* {
    BEGIN(yyget_extra(yyscanner)->pushState(stateComment));
}

<stateComment>"*/" {
    BEGIN(yyget_extra(yyscanner)->popState());
}
<stateComment>. {}

. {
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
