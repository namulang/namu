%{
#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include "wrdcNode.hpp"
using namespace std;

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
    void* nodes;
}

%verbose
%start tfile

%token tfor tdef twith tret tretfun tretif tretwith tretfor tif telse telif tfrom tagain tprop timport taka tthis tnode tout tin tindent tdedent
%token tfctor tfdtor tfres tfwarn tferr
%token tand tor

%token <intVal> tinteger teof
%token <floatVal> tfloat
%token <boolVal> tbool
%token <charVal> tchar
%token <strVal> tstr

%token <strVal> tnormalId taccessedId taccessedFuncname tnormalFuncname
%type <strVal> tid tfuncname

%token teol topDefAssign topMinusAssign topSquareAssign topDivideAssign topModAssign topPowAssign topLessEqual topMoreEqual topEqual topRefEqual topNotEqual topNotRefEqual topPlusAssign topSeq topSafeNavi topRedirect


%type <node> tstmt tlhsexpr/*only lhs*/ trhsexpr tcast trhsargs tlhsargs tblock tindentBlock tfile tfuncCall telseBlock telifBlock tbranch termIf tseq tarray ttype tmap taccess treturn tlhslist trhslist ttuple ttuples tparam tparams tsafeAccess

%type <node> timportStmt

%type <node> tfunc tctorfunc tdtorfunc tfunclist tfuncleft tfuncright

%type <node> tdefOrigin tdefIndentBlock tdefexpr tdefStmt tdefBlock

%type <nodes> telifBlocks

// 우선순위: 밑으로 갈수록 높음.
//  결합 순서 정의:
//      정해주지 않으면 모호성 오류 나온다.
//      left: 왼쪽 결합.
//      right: 오른쪽 결합.
%left ":=" '=' "+=" "-=" "/=" "*=" "%=" "^="
%left '&' '|'
%left '<' '>' topMoreEqual topLessEqual topEqual topRefEqual topNotEqual topNotRefEqual
%left '%' '^'
%left '+' '-'
%left '*' '/'
%left '.'

%%

tid         : tnormalId { $$ = $1; }
            | taccessedId { $$ = $1; }
            ;

tfuncname   : tnormalFuncname { $$ = $1; }
            | taccessedFuncname { $$ = $1; }
            ;

telseBlock  : teol telse teol tindentBlock {
                $$ = $4;
            }

telifBlock  : teol telif tbranch {
                $$ = $3;
            }
telifBlocks : telifBlock {
                vector<Branch*>* ret = new vector<Branch*>;
                ret->push_back((Branch*) $1);
                $$ = ret;
            }
            | telifBlocks telifBlock {
                vector<Branch*>* blk = (vector<Branch*>*) $1;
                blk->push_back((Branch*) $2);
                $$ = $1;
            }

tbranch     : trhsexpr teol tindentBlock {
                $$ = new Branch($1, (Container*) $3);
            }

termIf      : tif tbranch telifBlocks telseBlock {
                $$ = new If((Branch*) $2, (vector<Branch*>*) $3, (Block*) $4);
            }
            | tif tbranch telifBlocks {
                $$ = new If((Branch*) $2, (vector<Branch*>*) $3, 0);
            }
            | tif tbranch telseBlock {
                $$ = new If((Branch*) $2, (Block*) $3);
            }
            | tif tbranch {
                $$ = new If((Branch*) $2);
            }
            ;

// trhsexpr과 tlhsexpr:
//  tlhsexpr은 할당이 가능한 변수. lvalue.
//  trhsexpr은 값을 나타내는 모든 표현식.
//  따라서 범주상으로 보았을때 trhsexpr 은 tlhsexpr을 포함한다. 더 크다는 얘기다.
trhsexpr    : tinteger { $$ = new Int($1); }
            | tbool { $$ = new Bool($1); }
            | tfloat { $$ = new Float($1); }
            | tstr { $$ = new Str($1); }
            | tchar { $$ = new Char($1); }
            | tseq { $$ = $1; }
            | tarray { $$ = $1; }
            | tmap { $$ = $1; }
            | tlhsexpr { $$ = $1; }
            | tdefexpr { $$ = $1; }
            | tcast %dprec 1 { $$ = $1; }
            | taccess { $$ = $1; }
            | tsafeAccess { $$ = $1; }
            | trhsexpr '+' trhsexpr %dprec 2 {
                $$ = new Plus($1, $3);
            }
            | trhsexpr '-' trhsexpr %dprec 2 {
                $$ = new Minus($1, $3);
            }
            | trhsexpr '*' trhsexpr %dprec 2 {
                $$ = new Square($1, $3);
            }
            | trhsexpr '/' trhsexpr %dprec 2 {
                $$ = new Divide($1, $3);
            }
            | trhsexpr '%' trhsexpr %dprec 2 {
                $$ = new Moduler($1, $3);
            }
            | trhsexpr '^' trhsexpr %dprec 2 {
                $$ = new Power($1, $3);
            }
            | trhsexpr '<' trhsexpr %dprec 2 {
                $$ = new Less($1, $3);
            }
            | trhsexpr topLessEqual trhsexpr %dprec 2 {
                $$ = new LessEqual($1, $3);
            }
            | trhsexpr '>' trhsexpr %dprec 2 {
                $$ = new More($1, $3);
            }
            | trhsexpr topMoreEqual trhsexpr %dprec 2 {
                $$ = new MoreEqual($1, $3);
            }
            | trhsexpr topEqual trhsexpr %dprec 2 {
                $$ = new Equal($1, $3);
            }
            | trhsexpr topRefEqual trhsexpr %dprec 2 {
                $$ = new RefEqual($1, $3);
            }
            | trhsexpr topNotEqual trhsexpr %dprec 2 {
                $$ = new NotEqual($1, $3);
            }
            | trhsexpr topNotRefEqual trhsexpr %dprec 2 {
                $$ = new NotRefEqual($1, $3);
            }
            | trhsexpr '&' trhsexpr %dprec 3 { $$ = new And($1, $3); }
            | trhsexpr '|' trhsexpr %dprec 3 { $$ = new Or($1, $3); }

            | tfor tid tin trhsexpr teol tindentBlock {
                $$ = new For(new Id($2), $4, (Container*) $6);
            }

            | twith tnormalId teol tindentBlock {
                $$ = new With(new Id($2), $4);
            }
            | twith teol tindentBlock {
                $$ = new With(0, $3);
            }
            ;

            | termIf { $$ = $1; }
            | tfuncCall { $$ = $1; }
            ;

tdefexpr    : tlhslist topDefAssign trhslist { $$ = new DefAssign($1, $3); }
            | tid topDefAssign trhsexpr { $$ = new DefAssign(new Id($1), $3); }
            | tdefOrigin { $$ = $1; }
            | tfunc { $$ = $1; }
            ;

tlhsexpr    : tid { $$ = new Id($1); }
            | tlhslist '=' trhslist { $$ = new Assign($1, $3); }
            | tlhslist topPlusAssign trhslist { $$ = new PlusAssign($1, $3); }
            | tlhslist topMinusAssign trhslist { $$ = new MinusAssign($1, $3); }
            | tlhslist topSquareAssign trhslist { $$ = new SquareAssign($1, $3); }
            | tlhslist topDivideAssign trhslist { $$ = new DivideAssign($1, $3); }
            | tlhslist topModAssign trhslist { $$ = new ModulerAssign($1, $3); }
            | tlhslist topPowAssign trhslist { $$ = new PowAssign($1, $3); }

            | tlhsexpr topPlusAssign trhsexpr { $$ = new PlusAssign($1, $3); }
            | tlhsexpr topMinusAssign trhsexpr { $$ = new MinusAssign($1, $3); }
            | tlhsexpr topSquareAssign trhsexpr { $$ = new SquareAssign($1, $3); }
            | tlhsexpr topDivideAssign trhsexpr { $$ = new DivideAssign($1, $3); }
            | tlhsexpr topModAssign trhsexpr { $$ = new ModulerAssign($1, $3); }
            | tlhsexpr topPowAssign trhsexpr { $$ = new PowAssign($1, $3); }
            | tlhsexpr '=' trhsexpr { $$ = new Assign($1, $3); }
            ;

ttype       : tnormalId {
                  cout << "--------ttype(normalId=" << $1 << "\n";
                  $$ = new Id($1);
              }
            | ttype '[' ']' {
                  cout << "--------ttype[]=" << $1->print() << "\n";
                $$ = new Origin($1->print() + "[]");
            }
            | ttype '[' ttype ']' {
                cout << "--------ttype[ttype]\n";
                $$ = new MapOrigin($1, $3);
            }
            ;

tcast       : ttype trhsexpr {
                $$ = new Cast($1, $2);
            }
            ;


treturn     : tret trhsexpr { $$ = new Return("ret", $2); }
            | tretfun trhsexpr { $$ = new Return("retfun", $2); }
            | tretif trhsexpr { $$ = new Return("retif", $2); }
            | tretwith trhsexpr { $$ = new Return("retwith", $2); }
            | tretfor trhsexpr { $$ = new Return("retfor", $2); }
            ;


tlhsargs    : tlhsexpr {
                Args* ret = new Args();
                ret->add($1);
                $$ = ret;
            }
            | tlhsargs ',' tlhsexpr {
                Args* ret = (Args*) $1;
                ret->add($3);
                $$ = ret;
            }

trhsargs    : trhsexpr {
                Args* ret = new Args();
                ret->add($1);
                $$ = ret;
            }
            | trhsargs ',' trhsexpr {
                Args* ret = (Args*) $1;
                ret->add($3);
                $$ = ret;
            }
            ;

trhslist    : '(' trhsargs ')' { //  " "를 쓰면 안된다.
                $$ = new List((Args*) $2);
            }
            | '(' ')' {
                $$ = new List();
            }
            ;

tlhslist    : '(' tlhsargs ')' {
                $$ = new List((Args*) $2);
            }

ttuple      : trhsexpr ':' trhsexpr {
                $$ = new Tuple($1, $3);
            }

ttuples     : ttuple {
                Args* ret = new Args();
                ret->add($1);
                $$ = ret;
            }
            | ttuples ',' ttuple {
                Args* ret = (Args*) $1;
                ret->add($3);
                $$ = ret;
            }
            ;

tmap        : '[' ttuples ']' {
                $$ = new Array($2);
            }

tarray      : '[' trhsargs ']' {
                $$ = new Array($2);
            }

tseq        : trhsexpr topSeq trhsexpr {
                $$ = new Sequence($1, $3);
            }

taccess     : trhsexpr '.' tnormalId { $$ = new Access($1, new Id($3)); }
            | trhsexpr '.' tfuncCall { $$ = new Access($1, $3); }
            ;

tsafeAccess : trhsexpr topSafeNavi tnormalId { $$ = new SafeAccess($1, new Id($3)); }
            | trhsexpr topSafeNavi tfuncCall { $$ = new SafeAccess($1, $3); }
            ;

tparam      : ttype tid {
                $$ = new Param($1, new Id($2));
            }

tparams     : tparam {
                Args* ret = new Args();
                ret->add($1);
                $$ = ret;
            }
            | tparams tparam {
                Args* ret = (Args*) $1;
                ret->add($2);
                $$ = ret;
            }
            ;

tdefOrigin  : tdef tid teol tdefIndentBlock {
                $$ = new Def($2, 0, $4);
            }
            | tdef tid tfrom tnormalId teol tdefIndentBlock {
                $$ = new Def($2, new Id($4), $6);
            }
            ;

tfunclist   : '(' ')' { $$ = 0; }
            | '(' tparams ')' { $$ = $2; }
            ;

tfuncleft   : topRedirect { $$ = new Redirect(); }
            | tid topRedirect { $$ = new Redirect(new Id($1)); }
            | tlhslist topRedirect { $$ = new Redirect($1); }
            ;

tfuncright  : topRedirect { $$ = new Redirect(); }
            | topRedirect tid { $$ = new Redirect(new Id($2)); }
            | topRedirect tlhslist { $$ = new Redirect($2); }
            ;

tfunc       : ttype tfuncname tfunclist teol tindentBlock {
                $$ = new Func(0, $1, $2, $3, 0, $5);
            }
            | tfuncleft ttype tfuncname tfunclist teol tindentBlock {
                $$ = new Func($1, $2, $3, $4, 0, $6);
            }
            | ttype tfuncname tfunclist tfuncright teol tindentBlock {
                $$ = new Func(0, $1, $2, $3, $4, $6);
            }
            | tferr tfunclist teol tindentBlock {
                $$ = new Func(0, new Id(""), "@err", $2, 0, $4);
            }
            | tfwarn tfunclist teol tindentBlock {
                $$ = new Func(0, new Id(""), "@war", $2, 0, $4);
            }
            | tfres tfunclist teol tindentBlock {
                $$ = new Func(0, new Id(""), "@res", $2, 0, $4);
            }
            ;

tctorfunc   : tfctor tfunclist teol tindentBlock {
                $$ = new Func(0, new Id(""), "@ctor", $2, 0, $4);
            }
            ;

tdtorfunc   : tfdtor tfunclist teol tindentBlock {
                $$ = new Func(0, new Id(""), "@dtor", $2, 0, $4);
            }
            ;

tfuncCall   : tnormalFuncname trhslist {
                $$ = new FuncCall($1, (List*) $2);
            }
            ;

tdefStmt    : tdefexpr teol { $$ = new Stmt($1); }
            | teol { $$ = new Stmt(new Str("")); }
            | tctorfunc teol { $$ = $1; }
            | tdtorfunc teol { $$ = $1; }
            ;

tstmt       : trhsexpr teol { $$ = new Stmt($1); }
            | treturn teol { $$ = new Stmt($1); }
            | tagain teol { $$ = new Again(); }
            | trhsexpr teof { $$ = new Stmt($1); }
            | teol { $$ = new Stmt(new Str("")); }
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

tdefBlock   : tdefStmt {
                Block* ret = new Block();
                if ($1)
                    ret->add($1);
                $$ = ret;
            }
            | tdefBlock tdefStmt {
                Block* ret = (Block*) $1;
                if ($2)
                    ret->add($2);
                $$ = ret;
            }
            ;


timportStmt : timport taccess teol {
                $$ = new ImportStmt($2);
            }
            | timport tnormalId teol {
                $$ = new ImportStmt(new Id($2));
            }
            ;


tdefIndentBlock: tindent tdefBlock tdedent { $$ = $2; }

tindentBlock: tindent tblock tdedent { $$ = $2; }

tfile       : tfile tdefOrigin {
                File* ret = (File*) $1;
                ret->add($2);
                $$ = ret;
            }
            | timportStmt {
                File* ret = new File();
                ret->add($1);
                $$ = ret;
            }
            | tfile timportStmt {
                File* ret = (File*) $1;
                ret->add($2);
                $$ = ret;
            }
            | tdefOrigin {
                File* ret = new File();
                ret->add($1);
                $$ = $1;
            }
            | teol {}
            | tfile teol { $$ = $1; }
            | tfile teof {
                cout << $1->print();
                $$ = $1;
            }
            ;
