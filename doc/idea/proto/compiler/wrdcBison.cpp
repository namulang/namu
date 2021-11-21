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

%token tpack tfor tdef twith tret treturn tif telse telif tfrom tnext tprop timport taka tthis tnode tout tin tindent tdedent

%token <intVal> teof
%token <floatVal> tnum
%token <boolVal> tbool
%token <charVal> tchar
%token <strVal> tstr tfctor tfdtor tfget tfset tfres tfwarn tferr

%token <strVal> tnormalId taccessedId tconName tdeckId
%type <strVal> tid

%token teol topDefAssign topMinusAssign topSquareAssign topDivideAssign topModAssign topPowAssign topLessEqual topMoreEqual topEqual topRefEqual topNotEqual topNotRefEqual topPlusAssign topSeq topSafeNavi topRedirect topUplus topUminus

%type <node> tblock tindentBlock temptiableIndentBlock
%type <node> tstmt tcast tfile tfuncCall telseBlock telifBlock tbranch termIf termFor tseq tarray ttype tmap taccess tconAccess treturnexpr ttuple ttuples tparam tparams tsafeAccess tconNames


%type <node> trhsexpr trhslist tfuncRhsList tlhslist trhsIdExpr trhsListExpr tlhsId trhsIds tdefId tdefIds tdeflist toutableId tlhslistElem

%type <node> timportStmt tpackStmt tpackStmts tpackBlocks

%type <node> tfunc tctorfunc tdtorfunc tfunclist tfuncleft tfuncright

%type <node> tdefOrigin tdefIndentBlock tdefexpr tdefStmt tdefBlock tdefOriginStmt

%type <nodes> telifBlocks

%type <node> tgetsetterStmt tgetsetterExpr tpropexpr tpropIndentBlock tpropBlock tgetsetList tgetsetFuncName

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

tbranch     : trhsexpr tindentBlock {
                $$ = new Branch($1, (Container*) $2);
            }

termFor     : tfor tid tin trhsIdExpr tindentBlock {
                $$ = new For(new Id($2), $4, (Container*) $5);
            }
            | tfor trhsIdExpr tindentBlock {
                $$ = new For($2, (Container*) $3);
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
            | tarray { $$ = $1; }
            | tmap { $$ = $1; }
            | ttype %dprec 1 { $$ = $1; }
            | tdefexpr { $$ = $1; }
            | tcast %dprec 1 { $$ = $1; }
            | tsafeAccess { $$ = $1; }
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

            | twith tnormalId tindentBlock {
                $$ = new With(new Id($2), $3);
            }
            | twith tindentBlock {
                $$ = new With(0, $2);
            }
            ;

            | termIf { $$ = $1; }
            | tfuncCall { $$ = $1; }

            | tnormalId topPlusAssign trhsIdExpr %dprec 5 { $$ = new PlusAssign(new Id($1), $3); }
            | tnormalId topMinusAssign trhsIdExpr %dprec 5 { $$ = new MinusAssign(new Id($1), $3); }
            | tnormalId topSquareAssign trhsIdExpr %dprec 5 { $$ = new SquareAssign(new Id($1), $3); }
            | tnormalId topDivideAssign trhsIdExpr %dprec 5 { $$ = new DivideAssign(new Id($1), $3); }
            | tnormalId topModAssign trhsIdExpr %dprec 5 { $$ = new ModulerAssign(new Id($1), $3); }
            | tnormalId topPowAssign trhsIdExpr %dprec 5 { $$ = new PowAssign(new Id($1), $3); }
            | tnormalId '=' trhsIdExpr %dprec 5 { $$ = new Assign(new Id($1), $3); }
            ;


trhsListExpr: trhslist { $$ = $1; } // tlhslist --> can be trhslist.
            | trhsListExpr '+' trhsListExpr %dprec 2 { $$ = new Plus($1, $3); }
            | trhsListExpr '-' trhsListExpr %dprec 2 { $$ = new Minus($1, $3); }
            | trhsListExpr '*' trhsListExpr %dprec 2 { $$ = new Square($1, $3); }
            | trhsListExpr '/' trhsListExpr %dprec 2 { $$ = new Divide($1, $3); }
            | trhsListExpr '%' trhsListExpr %dprec 2 { $$ = new Moduler($1, $3); }
            | trhsListExpr '^' trhsListExpr %dprec 2 { $$ = new Power($1, $3); }
            | trhsListExpr '<' trhsListExpr %dprec 2 { $$ = new Less($1, $3); }
            | trhsListExpr topLessEqual trhsListExpr %dprec 2 { $$ = new LessEqual($1, $3); }
            | trhsListExpr '>' trhsListExpr %dprec 2 { $$ = new More($1, $3); }
            | trhsListExpr topMoreEqual trhsListExpr %dprec 2 { $$ = new MoreEqual($1, $3); }
            | trhsListExpr topEqual trhsListExpr %dprec 2 { $$ = new Equal($1, $3); }
            | trhsListExpr topRefEqual trhsListExpr %dprec 2 { $$ = new RefEqual($1, $3); }
            | trhsListExpr topNotEqual trhsListExpr %dprec 2 { $$ = new NotEqual($1, $3); }
            | trhsListExpr topNotRefEqual trhsListExpr %dprec 2 { $$ = new NotRefEqual($1, $3); }
            | trhsListExpr '&' trhsListExpr %dprec 3 { $$ = new And($1, $3); }
            | trhsListExpr '|' trhsListExpr %dprec 3 { $$ = new Or($1, $3); }

            | tlhslist '=' trhsListExpr { $$ = new Assign($1, $3); }
            | tlhslist topPlusAssign trhsListExpr { $$ = new PlusAssign($1, $3); }
            | tlhslist topMinusAssign trhsListExpr { $$ = new MinusAssign($1, $3); }
            | tlhslist topSquareAssign trhsListExpr { $$ = new SquareAssign($1, $3); }
            | tlhslist topDivideAssign trhsListExpr { $$ = new DivideAssign($1, $3); }
            | tlhslist topModAssign trhsListExpr { $$ = new ModulerAssign($1, $3); }
            | tlhslist topPowAssign trhsListExpr { $$ = new PowAssign($1, $3); }
            ;

trhsexpr    : trhsIdExpr { $$ = $1; }
            | trhsListExpr { $$ = $1; }
            ;



toutableId  : tid { $$ = new Id($1); }
            | tout tid { $$ = new Out(new Id($2)); }
            ;

tdefexpr    : tdeflist topDefAssign trhsListExpr { $$ = new DefAssign($1, $3); }
            | toutableId topDefAssign trhsIdExpr { $$ = new DefAssign($1, $3); }
            | tdefOrigin { $$ = $1; }
            | tfunc { $$ = $1; }
            | tpropexpr { $$ = $1; }
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
            | tconNames { $$ = $1; }
            ;

tconAccess  : tnormalId '[' trhsIdExpr ']' {
                $$ = new ContainerAccess(new Id($1), $3);
            }
            ;

tcast       : ttype trhsIdExpr {
                $$ = new Cast($1, $2);
            }
            ;


treturnexpr : tret trhsexpr { $$ = new Return("ret", $2); }
            | treturn trhsexpr { $$ = new Return("return", $2); }
            ;


trhsIds     : trhsexpr ',' trhsexpr {
                Args* ret = new Args();
                ret->add($1);
                ret->add($3);
                $$ = ret;
            }
            | trhsIds ',' trhsexpr {
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
            | taccess { $$ = $1; }
            | tlhslist { $$ = $1; }
            ;
tlhslistElem: tlhsId {
                Args* ret = new Args();
                ret->add($1);
                $$ = ret;
            }
            | tlhslistElem ',' tlhsId {
                Args* ret = (Args*) $1;
                ret->add($3);
                $$ = ret;
            }
            | tlhslistElem ',' tlhslist {
                Args* ret = (Args*) $1;
                ret->add($3);
                $$ = ret;
            }
            ;
tlhslist    : '(' tlhslistElem ')' {
                $$ = new List((Args*) $2);
            }
            ;

tdefId      : toutableId { $$ = $1; }
            | tdeflist { $$ = $1; }
            ;
tdefIds     : tdefId {
                Args* ret = new Args();
                ret->add($1);
                $$ = ret;
            }
            | tdefIds ',' tdefId {
                Args* ret = (Args*) $1;
                ret->add($3);
                $$ = ret;
            }
            ;
tdeflist    : '(' tdefIds ')' {
                $$ = new List((Args*) $2);
            }
            ;




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

tmap        : '{' ttuples '}' {
                $$ = new Array($2);
            }
            ;

tarray      : '{' trhsIds '}' {
                $$ = new Array($2);
            }
            ;

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
            | tdeckId {
                $$ = new Param(new Id($1), new Id($1));
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
            | '(' trhsexpr ')' {
                List* ret = new List();
                Args* args = new Args();
                args->add($2);
                ret->add(args);
                $$ = ret;
            }
            ;


tpropexpr   : tprop tid tfrom trhsexpr tpropIndentBlock {
                $$ = new Prop(new Id($2), 0, $4, $5);
            }
            | tprop tid tfuncRhsList tfrom trhsexpr tpropIndentBlock {
                $$ = new Prop(new Id($2), $3, $5, $6);
            }
            | tprop tfrom trhsexpr tpropIndentBlock {
                $$ = new Prop(0, 0, $3, $4);
            }
            | tprop tfuncRhsList tfrom trhsexpr tpropIndentBlock {
                $$ = new Prop(0, $2, $4, $5);
            }
            ;
tpropIndentBlock: teol tindent tpropBlock tdedent { $$ = $3; }
            | ':' tgetsetterExpr { $$ = new InlineStmt($2); }
            | { $$ = 0; }
            ;
tpropBlock  : tgetsetterStmt {
                Block* ret = new Block();
                ret->add($1);
                $$ = ret;
            }
            | tpropBlock tgetsetterStmt {
                Block* ret = (Block*) $1;
                ret->add($2);
                $$ = ret;
            }
            ;

tgetsetFuncName : tfget { $$ = new Id($1); }
            | tfset { $$ = new Id($1); }
            ;
tgetsetList : tfunclist { $$ = $1; }
            | { $$ = 0; }
            ;

temptiableIndentBlock: tindentBlock { $$ = $1; }
            | { $$ = 0; }
            ;

tgetsetterExpr: tgetsetFuncName tgetsetList temptiableIndentBlock {
                $$ = new Func(0, 0, $1, $2, 0, $3);
            }
            | tfuncleft tgetsetFuncName tgetsetList temptiableIndentBlock {
                $$ = new Func($1, 0, $2, $3, 0, $4);
            }
            | tgetsetFuncName tgetsetList tfuncright temptiableIndentBlock {
                $$ = new Func(0, 0, $1, $2, $3, $4);
            }
            ;
tgetsetterStmt: tgetsetterExpr teol { $$ = new Stmt($1); }
            ;

tdefOrigin  : tdef tid tdefIndentBlock {
                $$ = new Def(new Id($2), 0, 0, $3);
            }
            | tdef tid tfuncRhsList tdefIndentBlock {
                $$ = new Def(new Id($2), $3, 0, $4);
            }
            | tdef tid tfuncRhsList tfrom trhsexpr tdefIndentBlock {
                $$ = new Def(new Id($2), $3, $5, $6);
            }
            | tdef tid tfrom trhsexpr tdefIndentBlock {
                $$ = new Def(new Id($2), 0, $4, $5);
            }
            ;
tdefOriginStmt: tdefOrigin teol { $$ = new Stmt($1); }
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

tfunc       : ttype tid tfunclist temptiableIndentBlock {
                $$ = new Func(0, $1, new Id($2), $3, 0, $4);
            }
            | tfuncleft ttype tid tfunclist temptiableIndentBlock {
                $$ = new Func($1, $2, new Id($3), $4, 0, $5);
            }
            | ttype tid tfunclist tfuncright temptiableIndentBlock {
                $$ = new Func(0, $1, new Id($2), $3, $4, $5);
            }
            | tferr tfunclist temptiableIndentBlock {
                $$ = new Func(0, 0, new Id($1), $2, 0, $3);
            }
            | tfwarn tfunclist temptiableIndentBlock {
                $$ = new Func(0, 0, new Id($1), $2, 0, $3);
            }
            | tfres tfunclist temptiableIndentBlock {
                $$ = new Func(0, 0, new Id($1), $2, 0, $3);
            }
            ;

tctorfunc   : tfctor tfunclist temptiableIndentBlock {
                $$ = new Func(0, 0, new Id($1), $2, 0, $3);
            }
            ;

tdtorfunc   : tfdtor tfunclist temptiableIndentBlock {
                $$ = new Func(0, 0, new Id($1), $2, 0, $3);
            }
            ;

tfuncCall   : tid tfuncRhsList {
                $$ = new FuncCall(new Id($1), (List*) $2);
            }
            | ttype tfuncRhsList {
                $$ = new FuncCall($1, $2);
            }
            ;

tdefStmt    : tdefexpr teol { $$ = new Stmt($1); }
            | teol { $$ = new Stmt(new Str("")); }
            | tctorfunc teol { $$ = new Stmt($1); }
            | tdtorfunc teol { $$ = new Stmt($1); }
            ;

tstmt       : trhsexpr teol { $$ = new Stmt($1); }
            | treturnexpr teol { $$ = new Stmt($1); }
            | tnext teol { $$ = new Stmt(new Next()); }
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

tpackStmt   : tpack taccess teol {
                  Block* ret = new Block();
                  if ($2)
                     ret->add($2);
                  $$ = ret;
            }

timportStmt : timport taccess teol {
                $$ = new ImportStmt($2);
            }
            | timport tnormalId teol {
                $$ = new ImportStmt(new Id($2));
            }
            ;
tpackStmts  : tpackStmt { $$ = $1; }
            | timportStmt { $$ = $1; }
            ;
tpackBlocks : tpackStmts {
                Block* block = new Block();
                if ($1)
                    block->add($1);
                $$ = block;
            }
            | tpackBlocks tpackStmts {
                if ($2)
                    ((Block*) $1)->add($2);
                $$ = $1;
            }
            ;


tdefIndentBlock: teol tindent tdefBlock tdedent { $$ = $3; }
            | ':' tdefexpr { $$ = new InlineStmt($2); }
            | ':' tctorfunc { $$ = new InlineStmt($2); }
            | ':' tdtorfunc { $$ = new InlineStmt($2); }
            | { $$ = 0; }
            ;

tindentBlock: teol tindent tblock tdedent { $$ = $3; }
            | ':' trhsexpr { $$ = new InlineStmt($2); }
            | ':' treturnexpr { $$ = new InlineStmt($2); }
            | ':' tnext { $$ = new InlineStmt(new Next()); }
            ;

tfile       : tfile tdefOriginStmt {
                File* ret = (File*) $1;
                ret->add($2);
                $$ = ret;
            }
            | tpackBlocks {
                parsed = new File();
                parsed->setHeader($1);
                $$ = parsed;
            }
            | tdefOriginStmt {
                parsed = new File();
                parsed->add($1);
                $$ = parsed;
            }
            | teol {
                $$ = parsed = new File();
            }
            | tfile teol { $$ = $1; }
            | tfile teof { $$ = $1; }
            ;
