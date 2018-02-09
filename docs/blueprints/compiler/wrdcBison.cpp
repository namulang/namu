%{
#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include "node.hpp"

int yylex();
extern int yylineno;
extern char* yytext;
namespace wrd {
    const char* getName(int type);
}

void yyerror(const char* s)
{
    cout << Node::clr(Node::RED) << "error " << yylineno << Node::clr(Node::WHITE) << ": " << s << ", " << yytext << "\n";
    //asm("int3");
}
%}

%glr-parser
%union {
    int typeId;
    int intVal;
    float floatVal;
    bool boolVal;
    char charVal;
    const char* strVal;
    Node* node;
}

%verbose
%start tfile

%token tfor tdef twith tret tretfun tretif tretwith tretfor tif telse telif tfrom tagain tprop timport taka tthis tme tgot tnode tnull tsuper tout tin

%token <intVal> tinteger teof
%token <floatVal> tfloat
%token <boolVal> tbool
%token <charVal> tchar
%token <strVal> tstr
%token <strVal> tidentifier tfuncname
%token teol topDefAssign topPlusAssign topMinusAssign topSquareAssign topDivideAssign topModAssign topPowAssign
%type <node> tstmt tlhsexpr/*only lhs*/ texpr trhsexpr tcast targs ttlist tblock tfile tfunc tvalue tassign tdefAssign tplusAssign tminusAssign tsquareAssign tdivideAssign tmodAssign tpowAssign

%printer { fprintf(yyo, "%s[%d]", wrd::getName($$), $$); } tinteger;
%printer { fprintf(yyo, "%s", $$); } tidentifier;

// 우선순위: 밑으로 갈수록 높음.
//  결합 순서 정의:
//      정해주지 않으면 모호성 오류 나온다.
//      left: 왼쪽 결합.
//      right: 오른쪽 결합.
%left ":=" '=' "+=" "-=" "/=" "*=" "%=" "^="
%left '%' '^'
%left '+' '-'
%left '*' '/'

%%

tvalue      : tinteger {
                $$ = new Int($1);
            }
            | tbool {
                $$ = new Bool($1);
            }
            | tfloat {
                $$ = new Float($1);
            }
            | tstr {
                $$ = new Str($1);
            }
            | tchar {
                $$ = new Char($1);
            }
            | tidentifier {
                $$ = new Id($1);
            }
            ;

trhsexpr    : tvalue {
                $$ = $1;
            }
            | ttlist {
                $$ = $1;
            }
            | trhsexpr '+' trhsexpr {
                $$ = new Plus($1, $3);
            }
            | trhsexpr '-' trhsexpr {
                $$ = new Minus($1, $3);
            }
            | trhsexpr '*' trhsexpr {
                $$ = new Square($1, $3);
            }
            | trhsexpr '/' trhsexpr {
                $$ = new Divide($1, $3);
            }
            | trhsexpr '%' trhsexpr {
                $$ = new Moduler($1, $3);
            }
            | trhsexpr '^' trhsexpr {
                $$ = new Power($1, $3);
            }
            | tcast { $$ = $1; }
            | tfor tidentifier tin texpr tblock {
                $$ = new For(new Id($2), $4, (Container*) $5);
            }
            | tfunc { $$ = $1; }
            | tassign { $$ = $1; }
            ;

tlhsexpr    : tdefAssign { $$ = $1; }
            | tplusAssign { $$ = $1; }
            | tminusAssign { $$ = $1; }
            | tsquareAssign { $$ = $1; }
            | tdivideAssign { $$ = $1; }
            | tmodAssign { $$ = $1; }
            | tpowAssign { $$ = $1; }
            //| tidentifier tlist {}
            ;

texpr       : trhsexpr { $$ = $1; }
            | tlhsexpr { $$ = $1; }

tassign     : tidentifier '=' texpr {
                $$ = new Assign(new Id($1), $3);
            }
            ;

tdefAssign  : tidentifier topDefAssign texpr {
                $$ = new DefAssign(new Id($1), $3);
            }
            ;

tplusAssign : tidentifier topPlusAssign texpr {
                $$ = new PlusAssign(new Id($1), $3);
            }
            ;

tminusAssign : tidentifier topMinusAssign texpr {
                $$ = new MinusAssign(new Id($1), $3);
            }
            ;

tsquareAssign : tidentifier topSquareAssign texpr {
                $$ = new SquareAssign(new Id($1), $3);
            }
            ;

tdivideAssign : tidentifier topDivideAssign texpr {
                $$ = new DivideAssign(new Id($1), $3);
            }
            ;

tmodAssign : tidentifier topModAssign texpr {
                $$ = new ModulerAssign(new Id($1), $3);
            }
            ;

tpowAssign : tidentifier topPowAssign texpr {
                $$ = new PowAssign(new Id($1), $3);
            }
            ;

tcast       : tidentifier texpr {
                $$ = new Cast(new Id($1), $2);
            }
            ;

/*tarr        : topen_bracket targs tclose_bracket { if (IS_DEBUG) cout << "[]"; }
             | topen_bracket tclose_bracket { if (IS_DEBUG) cout << "[]"; }
            ;*/



targs       : texpr {
                Args* ret = new Args();
                ret->add($1);
                $$ = ret;
            }
            | targs ',' texpr {
                Args* ret = (Args*) $1;
                ret->add($3);
                $$ = ret;
            }
            ;

ttlist      : '(' targs ')' { //  " "를 쓰면 안된다.
                $$ = new TypeList((Args*) $2);
            }
            | '(' ')' {
                $$ = new TypeList();
            }
            ;

tfunc       : tfuncname ttlist {
                $$ = new Func($1, (TypeList*) $2);
            }
            ;

tstmt       : texpr teol {
                $$ = new Stmt($1);
            }
            | teol {
                $$ = new Stmt(new Str(""));
            }
            | texpr teof {
                $$ = new Stmt($1);
            }

            ;

tblock      : tstmt {
                Block* ret = new Block();
                if ($1)
                    ret->add($1);
                $$ = ret;
            }
            | tblock tstmt {
                Block* ret = (Block*) $1;
                if ($2)
                    ret->add($2);
                $$ = ret;
            }
            ;

tfile       : tblock teof {
                Block* blk = (Block*) $1;
                File* ret = new File(blk);
                cout << ret->print();
                $$ = ret;
            }
            ;
