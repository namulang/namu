%code top {
/*  ============================================================================================
    |                                          PROLOGUE                                        |
    ============================================================================================  */
    #include <iostream>
    #include <sstream>
    using std::cout;
    #include "../loweventer.hpp"
    #include "../../../builtin.hpp"
    using namespace namu;

    #define YYLLOC_DEFAULT(Current, Rhs, N) \
        do { \
          if(N) { \
              (Current).start = YYRHSLOC (Rhs, 1).start; \
              (Current).end = YYRHSLOC (Rhs, N).end; \
          } else { \
              (Current).start.row = (Current).end.row = YYRHSLOC (Rhs, 0).end.row; \
              (Current).start.col = (Current).end.col = YYRHSLOC (Rhs, 0).end.col; \
          } \
          EVENTER.onSrcArea(Current); \
        } while(0)

    #define EVENTER (*yyget_extra(scanner))
}

/*  ============================================================================================
    |                                          C++ DECLS                                       |
    ============================================================================================  */

%code requires {
    #include "../../../ast/point.hpp"
    #include "../../../ast/args.hpp"
    #include "../defBlock.hpp"

    typedef void* yyscan_t;

    namespace namu {
        class node;
        class obj;
        class immutableTactic;
        template <typename K, typename V, typename TACTIC> class tnmap;
        typedef tnmap<std::string, node, immutableTactic> scope;
        typedef tstr<node> str;
        template <typename T, typename WRP> class tnarr;
        typedef tnarr<node> narr;
    }

    struct lloc : public namu::area {
        int colcnt;

        void rel() {
            colcnt = 0;
            namu::area::rel();
        }
    };
}

%code provides {
    extern int yylineno;
    extern char* yytext;
    namespace namu {
        class loweventer;
    }

    extern "C" {
        int yylex(YYSTYPE* val, YYLTYPE* loc, yyscan_t scanner);
        void yyset_lineno(int linenumber, yyscan_t scanner);
        namu::loweventer* yyget_extra(yyscan_t scanner);
        char* yyget_text(yyscan_t scanner);
        void yyerror(YYLTYPE* loc, yyscan_t scanner, const char* msg);
    }

    void _onEndParse(yyscan_t scanner);
}

/*  ============================================================================================
    |                                         BISON FLAGS                                      |
    ============================================================================================  */

%union {
    namu::nchar asChar;
    int asInt;
    std::string* asStr;
    bool asBool;
    float asFlt;
    namu::node* asNode;
    namu::obj* asObj;
    namu::narr* asNarr;
    namu::scope* asScope;
    namu::defBlock* asDefBlock;
    namu::args* asArgs;
}

%define api.pure
%define parse.error custom
%glr-parser
%locations

%lex-param {yyscan_t scanner}
%parse-param {yyscan_t scanner}
%define api.location.type {lloc}
%expect 4
%require "3.8.1"

/*  ============================================================================================
    |                                        BISON SYMBOLS                                     |
    ============================================================================================  */

%start compilation-unit

// mode:
%token SCAN_AGAIN SCAN_EXIT SCAN_MODE_NORMAL SCAN_MODE_INDENT SCAN_MODE_INDENT_IGNORE SCAN_MODE_END

// terminal:
//  reserved-keyword:
//      use prefix '_' on some tokens for windows compatibility.
//      branch:
%token IF _ELSE_ RET NEXT BREAK
//      check:
%token _IN_ IS
//      loop:
%token _WHILE_ FOR
//      define:
%token DEF WITH AS ENUM ONLY GET SET END
//  predefined-type:
%token VOID INT STR BOOL FLT NUL BYTE CHAR ME SUPER IT CTOR PACK 
//  valueless-token:
%token NEWLINE INDENT DEDENT ENDOFFILE DOUBLE_MINUS DOUBLE_PLUS DOUBLE_DOT ARROW TAB ASSIGN DEFASSIGN
%token OPEN_CLOSE_SQUARE_BRACKET GE LE EQ NE LOGICAL_AND LOGICAL_OR LSHIFT RSHIFT
%token ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN OR_ASSIGN AND_ASSIGN XOR_ASSIGN
//  value-holding-token:
%token <asChar> CHARVAL
%token <asInt> INTVAL
%token <asFlt> FLTVAL
%token <asBool> BOOLVAL
%token <asStr> NAME STRVAL

// nonterminal:
//  basic component:
%type <asInt> delimiter
%type <asNode> compilation-unit unary postfix primary
%type <asStr> visibility
//      expr:
//          inline:
%type <asNode> expr-line expr-line1 expr-line2 expr-line3 expr-line4 expr-line5 expr-line6 expr-line7 expr-line8 expr-line9
//          compound:
%type <asNode> expr-compound block indentblock
%type <asDefBlock> indentDefBlock defblock declBlock indentDeclBlock
//      stmt:
%type <asNode> allstmt stmt decl-stmt def-stmt def-stmt-no-visibility def-stmt-visibility
%type <asNarr> allstmt-chain def-stmt-chain
//      access:
%type <asNode> access call-access
//      func:
%type <asNode> func-call
//      tuple:
%type <asArgs> tuple tuple-items
%type <asArgs> func-call-tuple func-call-tuple-items
%type <asNode> func-call-tuple-item
%type <asNarr> params param-items
//      type:
%type <asNode> type
%type <asArgs> typenames typeparams
//  keyword:
//      branch:
%type <asNode> if ret next break
%type <asNode> matching matchers matcher-item
%type <asNarr> matcher-equal-rhs
//      loop
%type <asNode> while for
//      define:
//          value:
%type <asNode> def-prop-inline def-prop-value def-prop-without-value def-prop-accessor def-prop-accessor-item
%type <asNarr> def-prop-accessor-items
%type <asNode> def-prop-compound
//          func:
%type <asNode> abstract-func def-func getter get setter set end
%type <asNode> lambda lambda-default lambda-deduction
//          obj:
%type <asNode> def-obj def-obj-default def-obj-default-generic
//              container:
%type <asNode> def-array-value
//              with:
%type <asNode> with-inline with-compound
//  predefined-type:
%type <asObj> pack

/*  ============================================================================================
    |                                     OPERATOR PRECEDENCE                                  |
    ============================================================================================  */
%precedence IF
%precedence _ELSE_
%precedence ':'
%precedence ';'






/*  ============================================================================================
    |                                           RULES                                          |
    ============================================================================================  */
%%

// basic component:
delimiter: NEWLINE { $$ = 0; }
         | ';' { $$ = 0; }
compilation-unit: pack defblock {
                tstr<obj> pak(*$1);
                tstr<defBlock> lifeBlock($2);
                EVENTER.onCompilationUnit(*pak, *lifeBlock);
                _onEndParse(scanner);
              }

// basic component:
unary: postfix { $$ = $1; }
     | DOUBLE_PLUS unary { $$ = EVENTER.onUnaryDoublePlus(*$2); }
     | DOUBLE_MINUS unary { $$ = EVENTER.onUnaryDoubleMinus(*$2); }
     | '+' unary { $$ = $2; }
     | '-' unary { $$ = EVENTER.onUnaryMinus(*$2); }
     | '!' unary { $$ = EVENTER.onUnaryNot(*$2); }
     | '~' unary { $$ = EVENTER.onUnaryBitwiseNot(*$2); }

postfix: primary { $$ = $1; }
       | postfix DOUBLE_MINUS { $$ = EVENTER.onUnaryPostfixDoubleMinus(*$1); }
       | postfix DOUBLE_PLUS { $$ = EVENTER.onUnaryPostfixDoublePlus(*$1); }
       | postfix '.' access { $$ = EVENTER.onGet(*$1, *$3); }
       | postfix '.' func-call {
        $$ = EVENTER.onFillFromOfFuncCall(*$1, $3->cast<runExpr>());
     } | func-call { $$ = $1; }
       | postfix '[' expr-line ']' { $$ = EVENTER.onGetElem(*$1, *$3); }

primary: INTVAL { $$ = EVENTER.onPrimitive<nInt>($1); }
       | STRVAL {
        $$ = EVENTER.onPrimitive<nStr>(*$1);
        free($1);
     } | FLTVAL { $$ = EVENTER.onPrimitive<nFlt>($1); }
       | BOOLVAL { $$ = EVENTER.onPrimitive<nBool>($1); }
       | CHARVAL { $$ = EVENTER.onPrimitive<nChar>($1); }
       | tuple { $$ = EVENTER.onParanthesisAsTuple(*$1); }
       | NUL {
        // ??
     } | def-array-value { $$ = $1; }
       | func-access { $$ = $1; }
       | access { $$ = $1; }
visibility: '_' '+' {
            // ??
        } | '+' '_' {
            // ??
        } | '_' {
            // ??
        } | '+' {
            // ??
        } | %empty {
            // ??
        }
//  expr:
//      inline:
expr-line: expr-line9 { $$ = $1; }
expr-line9: expr-line8 { $$ = $1; }
          | expr-line9 LOGICAL_OR expr-line8 { $$ = EVENTER.onOr(*$1, *$3); }
          | expr-line9 LOGICAL_AND expr-line8 { $$ = EVENTER.onAnd(*$1, *$3); }
expr-line8: expr-line7 { $$ = $1; }
          | expr-line8 LSHIFT expr-line7 { $$ = EVENTER.onLShift(*$1, *$3); }
          | expr-line8 RSHIFT expr-line7 { $$ = EVENTER.onRShift(*$1, *$3); }
expr-line7: expr-line6 { $$ = $1; }
          | expr-line7 '>' expr-line6 { $$ = EVENTER.onGt(*$1, *$3); }
          | expr-line7 '<' expr-line6 { $$ = EVENTER.onLt(*$1, *$3); }
          | expr-line7 GE expr-line6 { $$ = EVENTER.onGe(*$1, *$3); }
          | expr-line7 LE expr-line6 { $$ = EVENTER.onLe(*$1, *$3); }
          | expr-line7 EQ expr-line6 { $$ = EVENTER.onEq(*$1, *$3); }
          | expr-line7 NE expr-line6 { $$ = EVENTER.onNe(*$1, *$3); }
expr-line6: expr-line5 { $$ = $1; }
          | expr-line6 '|' expr-line5 { $$ = EVENTER.onBitwiseOr(*$1, *$3); }
          | expr-line6 IS type {
            // ??
        } | expr-line6 _IN_ expr-line5 {
            // ??
        }
expr-line5: expr-line4 { $$ = $1; }
          | expr-line5 '^' expr-line4 { $$ = EVENTER.onBitwiseXor(*$1, *$3); }
expr-line4: expr-line3 { $$ = $1; }
          | expr-line4 '&' expr-line3 { $$ = EVENTER.onBitwiseAnd(*$1, *$3); }
expr-line3: expr-line2 { $$ = $1; }
          | expr-line3 '+' expr-line2 { $$ = EVENTER.onAdd(*$1, *$3); }
          | expr-line3 '-' expr-line2 { $$ = EVENTER.onSub(*$1, *$3); }
expr-line2: expr-line1 { $$ = $1; }
          | expr-line2 '*' expr-line1 { $$ = EVENTER.onMul(*$1, *$3); }
          | expr-line2 '/' expr-line1 { $$ = EVENTER.onDiv(*$1, *$3); }
          | expr-line2 '%' expr-line1 { $$ = EVENTER.onMod(*$1, *$3); }
expr-line1: unary { $$ = $1; }
          | expr-line1 AS type { $$ = EVENTER.onAs(*$1, *$3); }
          | unary DOUBLE_DOT unary { $$ = EVENTER.onDefSeq(*$1, *$3); }
//      compound:
expr-compound: if { $$ = $1; }
             | expr-line9 ASSIGN expr-compound { $$ = EVENTER.onAssign(*$1, *$3); }
             | for { $$ = $1; }
             | while { $$ = $1; }
             | end { $$ = $1; }

block: allstmt { $$ = EVENTER.onBlock(*$1); }
     | block allstmt { $$ = EVENTER.onBlock($1->cast<blockExpr>(), *$2); }

indentblock: NEWLINE INDENT block DEDENT { $$ = $3; }
           | ':' allstmt-chain {
            // ??
         } | ':' ';' {
            // ??
         }

indentDefBlock: NEWLINE INDENT defblock DEDENT { $$ = $3; }
              | ':' def-stmt-chain {
                // ??
            } | ':' ';' {
                // ??
            }

defblock: def-stmt { $$ = EVENTER.onDefBlock(); }
        | defblock def-stmt {
        str lifeStmt($2);
        $$ = EVENTER.onDefBlock(*$1, *lifeStmt);
      }

declBlock: decl-stmt {
            // ??
       } | declBlock decl-stmt {
            // ??
       }
indentDeclBlock: NEWLINE INDENT declBlock DEDENT {
                // ??
             } | ':' allstmt-chain {
                // TODO: allstmt should be declstmt.
                // for preventing reduce/reduce conflict, I need to declare allstmt on here rule.
                // ??
             }

//  stmt:
allstmt: stmt { $$ = $1; }
       | def-stmt-no-visibility { $$ = $1; }
       | def-stmt-visibility { $$ = $1; }
stmt: expr-line delimiter { $$ = $1; }
    | ret { $$ = $1; }
    | break { $$ = $1; }
    | next { $$ = $1; }
    | expr-compound { $$ = $1; }
    | matching { $$ = $1; }
    | expr-line9 ASSIGN expr-line delimiter { $$ = EVENTER.onAssign(*$1, *$3); }
    | expr-line9 ADD_ASSIGN expr-line9 delimiter { $$ = EVENTER.onAddAssign(*$1, *$3); }
    | expr-line9 SUB_ASSIGN expr-line9 delimiter { $$ = EVENTER.onSubAssign(*$1, *$3); }
    | expr-line9 MUL_ASSIGN expr-line9 delimiter { $$ = EVENTER.onMulAssign(*$1, *$3); }
    | expr-line9 DIV_ASSIGN expr-line9 delimiter { $$ = EVENTER.onDivAssign(*$1, *$3); }
    | expr-line9 MOD_ASSIGN expr-line9 delimiter { $$ = EVENTER.onModAssign(*$1, *$3); }

decl-stmt: access delimiter {
            // ??
       }

def-stmt: def-stmt-no-visibility { $$ = $1; }
        | visibility def-stmt-visibility {
            // TODO:
            $$ = $2;
      }
def-stmt-no-visibility: with-inline delimiter { $$ = $1; }
                      | with-compound { $$ = $1; }
                      | def-obj { $$ = $1; }
def-stmt-visibility: def-prop-inline delimiter { $$ = $1; }
                   | def-func { $$ = $1; }
                   | abstract-func { $$ = $1; }
                   | def-prop-compound { $$ = $1; }

allstmt-chain: allstmt {
                // ??
           } | allstmt-chain ';' allstmt {
                // ??
           }
def-stmt-chain: def-stmt {
                // ??
           } | def-stmt-chain ';' def-stmt {
                // ??
           }

//  access:
access: call-access { $$ = $1; }
      | type { $$ = $1; }
call-access: type params { $$ = EVENTER.onCallAccess(*$1, *$2); }

//  func:
func-call: type func-call-tuple {
        tstr<narr> argsLife($2);
        str typeLife($1);
        $$ = EVENTER.onRunExpr(*typeLife, *argsLife);
      }

//  tuple:
tuple: '(' tuple-items ')' { $$ = $2; }
     | '(' ')' { $$ = EVENTER.onTuple(); }
tuple-items: expr-line { $$ = EVENTER.onTuple(*$1); }
           | tuple-items ',' expr-line { $$ = EVENTER.onTuple(*$1, *$3); }
func-call-tuple: '(' func-call-tuple-items ')' { $$ = $2; }
               | '(' ')' { $$ = EVENTER.onFuncCallTuple(); }
func-call-tuple-item: expr-line { $$ = $1; }
                    | lambda {
                        // ??
                  }
func-call-tuple-items: func-call-tuple-item {
                        $$ = EVENTER.onFuncCallTuple(*$1);
                   } | func-call-tuple-items ',' func-call-tuple-item {
                        $$ = EVENTER.onFuncCallTuple(*$1, *$3);
                   }
params: '(' VOID ')' { $$ = EVENTER.onParams(); }
      | '(' param-items ')' { $$ = $2; }
param-items: def-prop-without-value {
            $$ = EVENTER.onParams($1->cast<defPropExpr>());
         } | param-items ',' def-prop-without-value {
            $$ = EVENTER.onParams(*$1, $3->cast<defPropExpr>());
         }
args: '(' ')' {
        // ??
  } | '(' args-items ')' {
        // ??
  }
args-items: NAME {
            // ??
        } | args-items NAME {
            // ??
        }

//  type:
type: VOID { $$ = EVENTER.onPrimitive<nVoid>(); }
    | INT { $$ = EVENTER.onPrimitive<nInt>(); }
    | BYTE { $$ = EVENTER.onPrimitive<nByte>(); }
    | CHAR { $$ = EVENTER.onPrimitive<nChar>(); }
    | STR { $$ = EVENTER.onPrimitive<nStr>(); }
    | BOOL { $$ = EVENTER.onPrimitive<nBool>(); }
    | FLT { $$ = EVENTER.onPrimitive<nFlt>(); }
    | NAME {
        $$ = EVENTER.onGet(*$1);
        free($1);
  } | type OPEN_CLOSE_SQUARE_BRACKET { $$ = EVENTER.onGetArray(*$1); }
    | NAME typeparams {
        tstr<args> argsLife($2);
        $$ = EVENTER.onGetGeneric(*$1, *argsLife);
        free($1);
  }

typeparams: '<' typenames '>' { $$ = $2; }
typenames: type { $$ = EVENTER.onTypeNames(*$1); }
         | typenames ',' type { $$ = EVENTER.onTypeNames(*$1, *$3); }

//  keyword:
//      branch:
if: IF expr-line indentblock {
    $$ = EVENTER.onIf(*$2, $3->cast<blockExpr>());
} | IF expr-line indentblock _ELSE_ indentblock {
    $$ = EVENTER.onIf(*$2, $3->cast<blockExpr>(), $5->cast<blockExpr>());
} | IF expr-line indentblock _ELSE_ if {
    $$ = EVENTER.onIf(*$2, $3->cast<blockExpr>(), $5->cast<ifExpr>());
}

ret: RET delimiter { $$ = EVENTER.onRet(); }
   | RET expr-line delimiter { $$ = EVENTER.onRet(*$2); }
   | RET expr-compound { $$ = EVENTER.onRet(*$2); }

next: NEXT delimiter { $$ = EVENTER.onNext(); }

break: BREAK delimiter { $$ = EVENTER.onBreak(); }
     | BREAK expr-line delimiter { $$ = EVENTER.onBreak(*$2); }
     | BREAK expr-compound { $$ = EVENTER.onBreak(*$2); }

matching: expr-line NEWLINE INDENT matchers DEDENT {
            // ??
      }
matchers: matcher-item {
            // ??
      } | matchers matcher-item {
            // ??
      }
matcher-item: _IN_ expr-line5 indentblock {
                // ??
          } | IS type indentblock {
                // ??
          } | matcher-equal-rhs indentblock {
                // ??
          } | '>' expr-line6 indentblock {
                // ??
          } | '<' expr-line6 indentblock {
                // ??
          } | GE expr-line6 indentblock {
                // ??
          } | LE expr-line6 indentblock {
                // ??
          } | EQ expr-line6 indentblock {
                // ??
          } | NE expr-line6 indentblock {
                // ??
          }
matcher-equal-rhs: expr-line {
                    // ??
               } | matcher-equal-rhs ',' expr-line {
                    // ??
               }

//      loop:
while: _WHILE_ expr-line indentblock {
     $$ = EVENTER.onWhile(*$2, $3->cast<blockExpr>());
   }

for: FOR NAME _IN_ expr-line indentblock {
    $$ = EVENTER.onFor(std::string(*$2), *$4, $5->cast<blockExpr>());
    free($2);
 }

//      define:
//          value:
def-prop-inline: def-prop-without-value { $$ = $1; }
              | def-prop-value { $$ = $1; }
def-prop-without-value: NAME type { // exp means 'explicitly'
                        $$ = EVENTER.onDefVar(*$1, *$2);
                        free($1);
                   }
def-prop-value: NAME DEFASSIGN expr-line {
              $$ = EVENTER.onDefAssign(*$1, *$3);
              free($1);
          }
def-prop-accessor: NEWLINE INDENT def-prop-accessor-items DEDENT {
                    // ??
              }
def-prop-accessor-item: getter { $$ = $1; }
                      | setter { $$ = $1; }
def-prop-accessor-items: def-prop-accessor-item {
                        // ??
                    } | def-prop-accessor-items def-prop-accessor-item {
                        // ??
                    }

def-prop-compound: NAME DEFASSIGN expr-compound {
                    $$ = EVENTER.onDefAssign(*$1, *$3);
                    free($1);
               } | def-prop-inline def-prop-accessor {
                    // ??
               }

//          func:
abstract-func: call-access type {
                str accessLife(*$1);
                $$ = EVENTER.onAbstractFunc(accessLife->cast<getExpr>(), *$2);
           } | type '(' ')' type {
                $$ = EVENTER.onAbstractFunc(*$1, *$4);
           }

def-func: abstract-func indentblock {
        $$ = EVENTER.onFunc($1->cast<mgdFunc>(), $2->cast<blockExpr>());
     }

getter: get indentblock {
        // ??
    }
get: GET {
    // ??
 } | '_' GET {
    // ??
 }

setter: set indentblock {
    // ??
 }
set: SET {
    // ??
 } | '_' SET {
    // ??
 }

end: END indentblock {
    // ??
 }

lambda: lambda-default {
        // ??
    } | lambda-deduction {
        // ??
    }
lambda-default: args type indentblock {
                // checks tuple that it's NAME.
                // ??
            } | params type indentblock {
                // ??
            }
lambda-deduction: args indentblock {
                // ??
                // checks tuple that it's NAME.
              } | params indentblock {
                // ??
              }

//          obj:
def-obj: def-obj-default { $$ = $1; }
       | def-obj-default-generic { $$ = $1; }
def-obj-default: DEF NAME indentDefBlock {
                $$ = EVENTER.onDefObj(std::string(*$2), *$3);
                free($2);
             }
def-obj-default-generic: DEF NAME typeparams indentDefBlock {
                        tstr<args> argsLife($3);
                        $$ = EVENTER.onDefObjGeneric(*$2, *argsLife, *$4);
                        free($2);
                     }

//              container:
def-array-value: '{' tuple-items '}' { $$ = EVENTER.onDefArray(*$2); }

//              with:
with-inline: WITH expr-line {
            // ??
         }

with-compound: with-inline indentblock {
                // ??
           } | with-inline ONLY indentDeclBlock {
                // ??
           }

//  predefined-type:
pack: PACK postfix delimiter { $$ = EVENTER.onPack(*$2); }
    | %empty { $$ = EVENTER.onPack(); }


%%

/*  ============================================================================================
    |                                         EPILOGUE                                         |
    ============================================================================================  */

static std::string traceErr(const yypcontext_t* ctx, yyscan_t scanner) {
    constexpr nint TOKEN_MAX = 5;
    yysymbol_kind_t tokens[TOKEN_MAX];
    ncnt expected = yypcontext_expected_tokens(ctx, tokens, TOKEN_MAX);
    if(expected <= 0)
        return "nothing";

    std::stringstream ss;
    ss << "'" << yysymbol_name(tokens[0]) << "'";
    for(int n=1; n < expected ;n++)
        ss << ", '" << yysymbol_name(tokens[n]) << "'";
    return ss.str();

    // TODO: high quality error trace..
}

// when bison claims that it can't parse any further, this func will be called.
// it means that error recovery has been failed already.
static int yyreport_syntax_error(const yypcontext_t* ctx, yyscan_t scanner) {
    yysymbol_kind_t symbol = yypcontext_token(ctx);

    if(symbol != YYSYMBOL_YYUNDEF) {
        EVENTER.onSrcArea(*yypcontext_location(ctx));
        EVENTER.onParseErr(traceErr(ctx, scanner), yysymbol_name(symbol));
    }

    _onEndParse(scanner);
    return 0;
}

void _onEndParse(yyscan_t scanner) {
    EVENTER.onEndParse();
    yyset_lineno(0, scanner);
}

// errors except syntax will come here. for instance, when available memory doesn't exist.
void yyerror(YYLTYPE* loc, yyscan_t scanner, const char* msg) {
    EVENTER.onErr(errCode::MSG, msg);
}
