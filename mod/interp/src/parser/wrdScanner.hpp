#pragma once

//extern wrd::sobj* root;
extern int yylineno;
extern char* yytext;

int yylex();
void yyerror(const char* msg);
