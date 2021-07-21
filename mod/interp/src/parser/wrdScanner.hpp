#pragma once

//extern wrd::sobj* root;
extern int yylineno;
extern char* yytext;

extern "C" {
    int yylex(YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner);
    void yyerror(YYLTYPE* loc, yyscan_t scanner, const char* msg);
    int yywrap(yyscan_t scanner);
}
