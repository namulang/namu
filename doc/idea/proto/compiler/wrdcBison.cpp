%{
#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>
#include "wrdcNode.hpp"
using namespace std;

int yylex();
File* parsed = 0;
extern int yylineno;
extern char* yytext;
Node::Color Node::over = Node::NONE;
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

%token tpack tswitch tas tfor tdef twith tret treturn tif telse telif tfrom tnext timport taka tthis tnode tin tindent tdedent tnull

%token <intVal> teof
%token <floatVal> tnum
%token <boolVal> tbool
%token <charVal> tchar
%token <strVal> tstr tfctor tfdtor tfget tfset tfres

%token <strVal> tnormalId taccessedId tconName
%type <strVal> tid

%token teol topDefAssign topMinusAssign topSquareAssign topDivideAssign topModAssign topPowAssign topLessEqual topMoreEqual topEqual topRefEqual topNotEqual topNotRefEqual topPlusAssign topSeq topSafeNavi topUplus topUminus

%type <node> tblock tindentBlock
%type <node> texpr tcast tfile tfuncCall telseBlock telifBlock tbranch termIf termFor tseq tarray ttype tmap taccess tconAccess treturnexpr ttuple ttuples tparam tparams tnameOnlyParams tsafeAccess tconNames


%type <node> tfuncRhsList trhsIdExpr tlhsId trhsIds trhslist

%type <node> timportExpr tpackExpr tfileExpr tpackAccess takaStmt

%type <node> tfunc tfuncHeader tctorfunc tdtorfunc tfunclist tfuncNameOnlyList tfuncAllList

%type <node> tdefOrigin tdefIndentBlock tdefexpr tdefvar tdefStmt tdefBlock tdefBlockExpr

%type <nodes> telifBlocks

%type <node> tcaseIndentBlock tswitchExpr tcaseExpr tcaseStmt

%type <node> tpropexpr propBlock tpropindentBlock

// 우선순위: 밑으로 갈수록 높음.
//  결합 순서 정의:
//      정해주지 않으면 모호성 오류 나온다.
//      left: 왼쪽 결합.
//      right: 오른쪽 결합.
%right '=' topPlusAssign topDivideAssign topModAssign topPowAssign topSquareAssign topMinusAssign topDefAssign
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

telseBlock  : teol telse tindentBlock {
                $$ = $3;
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

tbranch     : trhsIdExpr tindentBlock {
                $$ = new Branch($1, (Container*) $2);
            }

termFor     : tfor tid tin trhsIdExpr tindentBlock {
                $$ = new For(new Id($2), $4, (Container*) $5);
            }
            | tfor trhsIdExpr tindentBlock {
                $$ = new For($2, (Container*) $3);
            }
            ;

tcaseExpr   : trhsIdExpr {
                Args* args = new Args();
                args->add($1);
                $$ = args;
            }
            | tcaseExpr ',' trhsIdExpr {
                Args* args = (Args*) $1;
                args->add($3);
                $$ = args;
            }
            ;

tcaseStmt   : tcaseExpr tindentBlock teol { $$ = new CaseBlock($1, $2); }
            | telse tindentBlock teol {
                Args* args = new Args();
                args->add(new Str("else"));
                $$ = new CaseBlock(args, $2);
            }
            ;

tcaseIndentBlock : tcaseStmt {
                Block* ret = new Block();
                if ($1)
                    ret->add($1);
                $$ = ret;
            }
            | tcaseIndentBlock tcaseStmt {
                Block* ret = (Block*) $1;
                if ($2)
                    ret->add($2);
                $$ = ret;
            }
            ;

tswitchExpr : tswitch tlhsId teol tindent tcaseIndentBlock tdedent {
                $$ = new SwitchExpr($2, $5);
            }
            ;

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
trhsIdExpr  : tbool { $$ = new Bool($1); }
            | tnum { $$ = new Float($1); }
            | tstr { $$ = new Str($1); }
            | tchar { $$ = new Char($1); }
            | tswitchExpr { $$ = $1; }
            | tarray { $$ = $1; }
            | ttype %dprec 8 { $$ = $1; }
            | tmap { $$ = $1; }
            | tdefexpr { $$ = $1; }
            | tcast %dprec 1 { $$ = $1; }
            | '(' trhsIdExpr ')' { $$ = $2; }

            | topUplus trhsIdExpr %dprec 1 { $$ = new UPre(new Id("++"), $2); }
            | trhsIdExpr topUplus %dprec 1 { $$ = new UPost(new Id("++"), $1); }
            | topUminus trhsIdExpr %dprec 1 { $$ = new UPre(new Id("--"), $2); }
            | trhsIdExpr topUminus %dprec 1 { $$ = new UPost(new Id("--"), $1); }

            | tconAccess %dprec 1 { $$ = $1; }

            | trhsIdExpr '+' trhsIdExpr %dprec 2 { $$ = new Plus($1, $3); }
            | trhsIdExpr '-' trhsIdExpr %dprec 2 { $$ = new Minus($1, $3); }
            | trhsIdExpr '*' trhsIdExpr %dprec 2 { $$ = new Square($1, $3); }
            | trhsIdExpr '/' trhsIdExpr %dprec 2 { $$ = new Divide($1, $3); }
            | trhsIdExpr '%' trhsIdExpr %dprec 2 { $$ = new Moduler($1, $3); }
            | trhsIdExpr '^' trhsIdExpr %dprec 2 { $$ = new Power($1, $3); }
            | trhsIdExpr '<' trhsIdExpr %dprec 2 { $$ = new Less($1, $3); }
            | trhsIdExpr topLessEqual trhsIdExpr %dprec 2 { $$ = new LessEqual($1, $3); }
            | trhsIdExpr '>' trhsIdExpr %dprec 2 { $$ = new More($1, $3); }
            | trhsIdExpr topMoreEqual trhsIdExpr %dprec 2 { $$ = new MoreEqual($1, $3); }
            | trhsIdExpr topEqual trhsIdExpr %dprec 2 { $$ = new Equal($1, $3); }
            | trhsIdExpr topRefEqual trhsIdExpr %dprec 2 { $$ = new RefEqual($1, $3); }
            | trhsIdExpr topNotEqual trhsIdExpr %dprec 2 { $$ = new NotEqual($1, $3); }
            | trhsIdExpr topNotRefEqual trhsIdExpr %dprec 2 { $$ = new NotRefEqual($1, $3); }
            | trhsIdExpr '&' trhsIdExpr %dprec 3 { $$ = new And($1, $3); }
            | trhsIdExpr '|' trhsIdExpr %dprec 3 { $$ = new Or($1, $3); }

            | termFor %dprec 4 { $$ = $1; }
            | tseq %dprec 4 { $$ = $1; }

            | twith taccess tindentBlock {
                $$ = new With($2, $3);
            }
            | twith tindentBlock {
                $$ = new With(0, $2);
            }
            ;

            | termIf { $$ = $1; }
            | tfuncCall { $$ = $1; }

            | trhsIdExpr topPlusAssign trhsIdExpr %dprec 5 { $$ = new PlusAssign($1, $3); }
            | trhsIdExpr topMinusAssign trhsIdExpr %dprec 5 { $$ = new MinusAssign($1, $3); }
            | trhsIdExpr topSquareAssign trhsIdExpr %dprec 5 { $$ = new SquareAssign($1, $3); }
            | trhsIdExpr topDivideAssign trhsIdExpr %dprec 5 { $$ = new DivideAssign($1, $3); }
            | trhsIdExpr topModAssign trhsIdExpr %dprec 5 { $$ = new ModulerAssign($1, $3); }
            | trhsIdExpr topPowAssign trhsIdExpr %dprec 5 { $$ = new PowAssign($1, $3); }
            | trhsIdExpr '=' trhsIdExpr %dprec 5 { $$ = new Assign($1, $3); }
            ;

tdefBlockExpr:  tfunc { $$ = $1; }
             | tdefOrigin { $$ = $1; }
             | tpropexpr { $$ = $1; }
             | tctorfunc { $$ = $1; }
             | tdtorfunc { $$ = $1; }
             ;

tdefvar     : tid topDefAssign trhsIdExpr { $$ = new DefAssign(new Id($1), $3); }
            | tid ttype topDefAssign trhsIdExpr { $$ = new DefAssign(new Param($2, new Id($1)), $4); }
            | tid ttype topDefAssign '{' '}' { $$ = new DefAssign(new Param($2, new Id($1)), new Array()); }
            | tparam { $$ = $1; }

tdefexpr    : takaStmt { $$ = $1; }
            | tdefBlockExpr { $$ = $1; }
            ;

tconNames   : tconName '{' '}' {
                $$ = new Origin(new Id(string($1) + "{}"));
            }
            | tconNames '{' '}' {
                $$ = new Origin(new Id($1->print() + "{}"));
            }
            | tconName '{' ttype '}' {
                $$ = new MapOrigin(new Id($1), $3);
            }
            | tconNames '{' ttype '}' {
                $$ = new MapOrigin($1, $3);
            }
            ;

ttype       : tlhsId { $$ = $1; }
ttype       : tlhsId '?' { $$ = new NullableType($1); }
            | tconNames { $$ = $1; }
            | tconNames '?' { $$ = new NullableType($1); }
            ;

tconAccess  : tlhsId '[' trhsIdExpr ']' {
                $$ = new ContainerAccess($1, $3);
            }
            ;

takaStmt    : tlhsId taka tnormalId {
                $$ = new AkaStmt($1, new Id($3));
            }
            ;

tcast       : trhsIdExpr tas ttype {
                $$ = new Cast($3, $1);
            }
            ;

treturnexpr : tret trhsIdExpr { $$ = new Return("ret", $2); }
            | tret { $$ = new Return("ret", nullptr); }
            | treturn trhsIdExpr { $$ = new Return("return", $2); }
            | treturn { $$ = new Return("return", nullptr); }
            ;


trhsIds     : trhsIdExpr ',' trhsIdExpr {
                Args* ret = new Args();
                ret->add($1);
                ret->add($3);
                $$ = ret;
            }
            | trhsIds ',' trhsIdExpr {
                Args* ret = (Args*) $1;
                ret->add($3);
                $$ = ret;
            }
            ;
trhslist    : '(' trhsIds ')' { //  " "를 쓰면 안된다.
                $$ = new List((Args*) $2);
            }
            ;

tlhsId      : tnormalId { $$ = new Id($1); }
            | tpackAccess { $$ = $1; }
            ;

ttuple      : trhsIdExpr ';' trhsIdExpr {
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

tmap        : '{' ttuples '}' {
                $$ = new Array($2);
            }
            ;

tarray      : '{' trhsIds '}' {
                $$ = new Array($2);
            }
            ;

tseq        : trhsIdExpr topSeq trhsIdExpr {
                $$ = new Sequence($1, $3);
            }

taccess     : trhsIdExpr '.' tnormalId { $$ = new Access($1, new Id($3)); }
            | trhsIdExpr '.' tfuncCall { $$ = new Access($1, $3); }
            ;

tpackAccess : tlhsId '.' tnormalId { $$ = new Access($1, new Id($3)); }
            | tlhsId '.' tfuncCall { $$ = new Access($1, $3); }
            ;

tsafeAccess : trhsIdExpr topSafeNavi tnormalId { $$ = new SafeAccess($1, new Id($3)); }
            | trhsIdExpr topSafeNavi tfuncCall { $$ = new SafeAccess($1, $3); }
            ;

tparam      : tid ttype {
                $$ = new Param($2, new Id($1));
            }
            | '@' tid {
                $$ = new Id($2);
            }
            ;

tnameOnlyParams : tid {
                Args* ret = new Args();
                ret->add(new Param(nullptr, new Id($1)));
                $$ = ret;
            }
            | tnameOnlyParams ',' tid {
                Args* ret = (Args*) $1;
                ret->add(new Param(nullptr, new Id($3)));
                $$ = ret;
            }
            ;

tparams     : tparam {
                Args* ret = new Args();
                ret->add($1);
                $$ = ret;
            }
            | tparams ',' tparam {
                Args* ret = (Args*) $1;
                ret->add($3);
                $$ = ret;
            }
            ;

tfuncRhsList: trhslist { $$ = $1; }
            | '(' ')' { $$ = new List(); }
            | '(' trhsIdExpr ')' {
                List* ret = new List();
                Args* args = new Args();
                args->add($2);
                ret->add(args);
                $$ = ret;
            }
            ;


propBlock   : tfunc teol {
                Block* blk = new Block();
                blk->add($1);
                $$ = blk;
            }
            | propBlock tfunc teol {
                Block* blk = (Block*) $1;
                blk->add($2);
                $$ = blk;
            }
            ;

tpropindentBlock: teol tindent propBlock tdedent { $$ = $3; }

tpropexpr   : tdefvar tpropindentBlock {
                $$ = new Prop($1, $2);
            }
            | tdefvar { $$ = $1; }
            ;

tdefOrigin  : tdef tid tdefIndentBlock {
                $$ = new Def(new Id($2), 0, 0, $3);
            }
            | tdef tid tfuncRhsList tdefIndentBlock {
                $$ = new Def(new Id($2), $3, 0, $4);
            }
            | tdef tid tfuncRhsList tfrom trhsIdExpr tdefIndentBlock {
                $$ = new Def(new Id($2), $3, $5, $6);
            }
            | tdef tid tfrom trhsIdExpr tdefIndentBlock {
                $$ = new Def(new Id($2), 0, $4, $5);
            }
            ;

tfunclist   : '(' ')' { $$ = 0; }
            | '(' tparams ')' { $$ = $2; }
            ;

tfuncNameOnlyList : '(' tnameOnlyParams ')' { $$ = $2; }

tfuncAllList : tfunclist { $$ = $1; }
            | tfuncNameOnlyList { $$ = $1; }
            ;

tfuncHeader : tid tfuncAllList ttype {
                $$ = new Func($3, new Id($1), $2, 0);
            }
            | tas tfuncAllList ttype {
                $$ = new Func($3, new Id("as"), $2, 0);
            }
            | tid tfuncAllList {
                $$ = new Func(0, new Id($1), $2, 0);
            }
            | tfuncAllList ttype {
                $$ = new Func($2, new Id(""), $1, 0);
            }
            | tfuncAllList {
                $$ = new Func(0, new Id(""), $1, 0);
            }
            ;

tfunc       : tfuncHeader tindentBlock {
                Func* fun = (Func*) $1;
                fun->has($2);
                $$ = fun;
            }
            | tfuncHeader taka tnormalId tindentBlock {
                Func* fun = (Func*) $1;
                fun->add("aka", new Id($3));
                fun->has($4);
                cout << "===================== $4=" << $4->print() << "\n";
                cout << "===================== $4=" << fun->has()->print() << "\n";
                $$ = fun;
            }
            | tfuncHeader '=' tnull {
                Func* fun = (Func*) $1;
                fun->has(new Str(" = null"));
                $$ = fun;
            }
            | tfuncHeader '=' tnull taka tnormalId {
                Func* fun = (Func*) $1;
                fun->has(new Str(" = null"));
                fun->add("aka", new Id($5));
                $$ = fun;
            }
            ;

tctorfunc   : tfctor tfunclist tindentBlock {
                $$ = new Func(0, new Id($1), $2, $3);
            }
            ;

tdtorfunc   : tfdtor tfunclist tindentBlock {
                $$ = new Func(0, new Id($1), $2, $3);
            }
            ;

tfuncCall   : tid tfuncRhsList {
                $$ = new FuncCall(new Id($1), (List*) $2);
            }
            ;

texpr       : trhsIdExpr { $$ = $1; }
            | treturnexpr { $$ = $1; }
            | tnext { $$ = new Next(); }
            ;

tblock      : texpr teol {
                Block* ret = new Block();
                if ($1)
                    ret->add(new Stmt($1));
                $$ = ret;
            }
            | tblock texpr teol {
                Block* ret = (Block*) $1;
                if ($2)
                    ret->add(new Stmt($2));
                $$ = ret;
            }
            ;

tdefStmt    : tdefexpr teol {
                  $$ = new Stmt($1);
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

tpackExpr   : tpack tpackAccess {
                $$ = new PackStmt($2);
            }
            ;

timportExpr : timport tlhsId {
                $$ = new ImportStmt($2);
            }
            | timport tlhsId taka tnormalId {
                $$ = new ImportStmt(new AkaStmt($2, new Id($4)));
            }
            ;

tfileExpr   : tpackExpr { $$ = $1; }
            | timportExpr { $$ = $1; }
            | tdefexpr { $$ = $1; }
            ;

tdefIndentBlock: teol tindent tdefBlock tdedent { $$ = $3; }
            | ':' tdefexpr { $$ = new InlineStmt($2); }
            | ':' tdefexpr teol { $$ = new InlineStmt($2); }
            | { $$ = new Str("\n"); }
            ;

tindentBlock: teol tindent tblock tdedent { $$ = $3; }
            | ':' trhsIdExpr teol { $$ = new InlineStmt($2); }
            | ':' trhsIdExpr { $$ = new InlineStmt($2); }
            | ':' treturnexpr teol { $$ = new InlineStmt($2); }
            | ':' treturnexpr { $$ = new InlineStmt($2); }
            | ':' tnext teol { $$ = new InlineStmt(new Next()); }
            | ':' tnext { $$ = new InlineStmt(new Next()); }
            ;

tfile       : tfile tfileExpr teol {
                File* ret = (File*) $1;
                ret->add($2);
                $$ = ret;
            }
            | tfileExpr teol {
                parsed = new File();
                if ($1)
                    parsed->add($1);
                $$ = parsed;
            }
            | tfile teof { $$ = $1; }
            ;
