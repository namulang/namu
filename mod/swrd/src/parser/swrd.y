%{
#pragma once
#include "../common.hpp"
#include "../interp/smallWorld.hpp"

namespace wrd { namespace swrd {
    class obj;
}}

using namespace wrd::swrd;

int yylex();
extern wrd::swrd::obj* root;
extern int yylineno;
extern char* yytext;

void yyerror(const char* s);

%}

%glr-parser
%union {
    int intVal;
    float floatVal;
    bool boolVal;
    char charVal;
    const char* strVal;
    wrd::swrd::obj* obj;
}

%verbose
%start tfile

%token tdef tprop tnode tin tindent tdedent

%token <intVal> teof
%token <floatVal> tnum
%token <boolVal> tbool
%token <charVal> tokChar
%token <strVal> tokStr
%token <strVal> tid tcontainerName
%token teol
%type <obj> tfile tarray
%type <obj> trhsexpr trhsIds
%type <obj> tdefOrigin tdefIndentBlock tdefexpr tdefStmt tdefBlock tdefOriginStmt

// 우선순위: 밑으로 갈수록 높음.
//  결합 순서 정의:
//      정해주지 않으면 모호성 오류 나온다.
//      left: 왼쪽 결합.
//      right: 오른쪽 결합.
%right '=' topDefAssign

%%

// trhsexpr과 tlhsexpr:
//  tlhsexpr은 할당이 가능한 변수. lvalue.
//  trhsexpr은 값을 나타내는 모든 표현식.
//  따라서 범주상으로 보았을때 trhsexpr 은 tlhsexpr을 포함한다. 더 크다는 얘기다.
trhsexpr    : tbool {
                $$ = new terminalObj($1);
                WRD_DI("trhsexpr(%x) <-- %s", $$, $1 ? "true" : "false");
            }
            | tnum {
                $$ = new terminalObj($1);
                WRD_DI("trhsexpr(%x) <-- %d", $$, $1);
            }
            | tokStr {
                $$ = new terminalObj($1);
                WRD_DI("trhsexpr(%x) <-- '%s'", $$, $1);
            }
            | tokChar {
                $$ = new terminalObj($1);
                WRD_DI("trhsexpr(%x) <-- tokChar(%c)", $$, $1);
            }
            | tarray {
                $$ = $1;
                WRD_DI("trhsexpr(%x) <-- tarray(%x)", $$, $1);
            }
            ;

tdefexpr    : tid topDefAssign trhsexpr {
                $3->setName($1);
                $$ = $3;
                WRD_DI("tdefexpr(%x) <-- %s := trhsexpr(%x)", $$, $1, $3);
            }
            | tdefOrigin {
                $$ = $1;
                WRD_DI("tdefexpr(%x) <-- tdefOrigin(%x)", $$, $1);
            }
            ;

trhsIds     : trhsexpr ',' trhsexpr {
                $$ = new obj();
                $$->add(*$1);
                $1->add(*$3);
                WRD_DI("trhsIds(%x) <-- trhsexpr(%x) , trhsexpr(%x)", $$, $1, $3);
            }
            | trhsIds ',' trhsexpr {
                $$ = $1;
                $$->add(*$3);
                WRD_DI("rhsIds(%x) <-- trhsIds(%x) , trhsexpr(%x)", $$, $1, $3);
            }
            ;

tarray      : '{' trhsIds '}' {
                $$ = $2;
                WRD_DI("tarray(%x) <-- { trhsIds(%x) }", $$, $2);
            }
            ;

tdefIndentBlock: teol tindent tdefBlock tdedent {
                $$ = $3;
                WRD_DI("tdefIndentBlock(%x) <-- \\n \\t tdefBlock(%x) -\\t", $$, $3);
            }
            | ':' tdefexpr {
                $$ = $2;
                WRD_DI("tdefIndentBlock(%x) <-- : tdefexpr(%x)", $$, $2);
            }
            | { $$ = 0; }
            ;

tdefOrigin  : tdef tid tdefIndentBlock {
                $3->setName($2);
                $$ = $3;
                WRD_DI("tdefOrigin(%x) <-- def %s tdefIndentBlock(%x)", $$, $2, $3);
            }
            ;

tdefOriginStmt: tdefOrigin teol {
                $$ = $1;
                WRD_DI("tdefOriginStmt(%x) <-- tdefOrigin(%x) \\n", $$, $1);
            }
            ;

tdefStmt    : tdefexpr teol {
                $$ = $1;
                WRD_DI("tdefStmt(%x) <-- tdefexpr(%x) \\n", $$, $1);
            }
            | teol {
                WRD_DI("tdefStmt(null) <-- \\n");
            }
            ;

tdefBlock   : tdefStmt {
                $$ = new obj();
                $$->add(*$1);
                WRD_DI("tdefBlock(%x) <-- tdefStmt(%x)", $$, $1);
            }
            | tdefBlock tdefStmt {
                $$ = $1;
                $$->add(*$2);
                WRD_DI("tdefBlock(%x) <-- tdefBlock(%x) tdefStmt(%x)", $$, $1, $2);
            }
            ;

tfile       : tfile tdefOriginStmt {
                $$ = $1;
                $$->add(*$2);
                WRD_DI("tfile(%x) <-- tfile(%x), tdefOriginStmt(%x)", $$, $1, $2);
            }
            | tdefOriginStmt {
                const std::string& name = wrd::swrd::smallWorld::getFileName();
                $$ = root = new obj(name);
                wrd::id id = $1->getId();
                $$->add(*$1);
                WRD_DI("$1 = %x, %d.%d.%d", $1, id.tagN, id.chkN, id.serial);
                WRD_DI("tfile(%s %x) <-- tdefOriginStmt(%x)", name.c_str(), $$, $1);
            }
            | teol {
                $$ = root = new obj();
                WRD_DI("tfile(%x) <-- \\n", $$);
            }
            | tfile teol {
                $$ = $1;
                WRD_DI("tfile(%x) <-- \\n", $$);
            }
            | tfile teof {
                $$ = $1;
                WRD_DI("tfile(%x) <-- EndOfFile", $$);
            }
            ;
