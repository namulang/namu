/* A Bison parser, made by GNU Bison 3.7.6.  */

/* Skeleton implementation for Bison GLR parsers in C

   Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C GLR parser skeleton written by Paul Hilfinger.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30706

/* Bison version string.  */
#define YYBISON_VERSION "3.7.6"

/* Skeleton name.  */
#define YYSKELETON_NAME "glr.c"

/* Pure parsers.  */
#define YYPURE 0






/* First part of user prologue.  */
#line 1 "wrdcBison.cpp"

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

#line 83 "wrdcBison.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "wrdcBison.h"

/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_tpack = 3,                      /* tpack  */
  YYSYMBOL_tswitch = 4,                    /* tswitch  */
  YYSYMBOL_tas = 5,                        /* tas  */
  YYSYMBOL_tfor = 6,                       /* tfor  */
  YYSYMBOL_tdef = 7,                       /* tdef  */
  YYSYMBOL_twith = 8,                      /* twith  */
  YYSYMBOL_tret = 9,                       /* tret  */
  YYSYMBOL_treturn = 10,                   /* treturn  */
  YYSYMBOL_tif = 11,                       /* tif  */
  YYSYMBOL_telse = 12,                     /* telse  */
  YYSYMBOL_telif = 13,                     /* telif  */
  YYSYMBOL_tfrom = 14,                     /* tfrom  */
  YYSYMBOL_tnext = 15,                     /* tnext  */
  YYSYMBOL_tprop = 16,                     /* tprop  */
  YYSYMBOL_timport = 17,                   /* timport  */
  YYSYMBOL_taka = 18,                      /* taka  */
  YYSYMBOL_tthis = 19,                     /* tthis  */
  YYSYMBOL_tnode = 20,                     /* tnode  */
  YYSYMBOL_tin = 21,                       /* tin  */
  YYSYMBOL_tindent = 22,                   /* tindent  */
  YYSYMBOL_tdedent = 23,                   /* tdedent  */
  YYSYMBOL_tnull = 24,                     /* tnull  */
  YYSYMBOL_teof = 25,                      /* teof  */
  YYSYMBOL_tnum = 26,                      /* tnum  */
  YYSYMBOL_tbool = 27,                     /* tbool  */
  YYSYMBOL_tchar = 28,                     /* tchar  */
  YYSYMBOL_tstr = 29,                      /* tstr  */
  YYSYMBOL_tfctor = 30,                    /* tfctor  */
  YYSYMBOL_tfdtor = 31,                    /* tfdtor  */
  YYSYMBOL_tfget = 32,                     /* tfget  */
  YYSYMBOL_tfset = 33,                     /* tfset  */
  YYSYMBOL_tfres = 34,                     /* tfres  */
  YYSYMBOL_tnormalId = 35,                 /* tnormalId  */
  YYSYMBOL_taccessedId = 36,               /* taccessedId  */
  YYSYMBOL_tconName = 37,                  /* tconName  */
  YYSYMBOL_teol = 38,                      /* teol  */
  YYSYMBOL_topDefAssign = 39,              /* topDefAssign  */
  YYSYMBOL_topMinusAssign = 40,            /* topMinusAssign  */
  YYSYMBOL_topSquareAssign = 41,           /* topSquareAssign  */
  YYSYMBOL_topDivideAssign = 42,           /* topDivideAssign  */
  YYSYMBOL_topModAssign = 43,              /* topModAssign  */
  YYSYMBOL_topPowAssign = 44,              /* topPowAssign  */
  YYSYMBOL_topLessEqual = 45,              /* topLessEqual  */
  YYSYMBOL_topMoreEqual = 46,              /* topMoreEqual  */
  YYSYMBOL_topEqual = 47,                  /* topEqual  */
  YYSYMBOL_topRefEqual = 48,               /* topRefEqual  */
  YYSYMBOL_topNotEqual = 49,               /* topNotEqual  */
  YYSYMBOL_topNotRefEqual = 50,            /* topNotRefEqual  */
  YYSYMBOL_topPlusAssign = 51,             /* topPlusAssign  */
  YYSYMBOL_topSeq = 52,                    /* topSeq  */
  YYSYMBOL_topSafeNavi = 53,               /* topSafeNavi  */
  YYSYMBOL_topUplus = 54,                  /* topUplus  */
  YYSYMBOL_topUminus = 55,                 /* topUminus  */
  YYSYMBOL_56_ = 56,                       /* '='  */
  YYSYMBOL_57_ = 57,                       /* '&'  */
  YYSYMBOL_58_ = 58,                       /* '|'  */
  YYSYMBOL_59_ = 59,                       /* '<'  */
  YYSYMBOL_60_ = 60,                       /* '>'  */
  YYSYMBOL_61_ = 61,                       /* '%'  */
  YYSYMBOL_62_ = 62,                       /* '^'  */
  YYSYMBOL_63_ = 63,                       /* '+'  */
  YYSYMBOL_64_ = 64,                       /* '-'  */
  YYSYMBOL_65_ = 65,                       /* '*'  */
  YYSYMBOL_66_ = 66,                       /* '/'  */
  YYSYMBOL_67_ = 67,                       /* '.'  */
  YYSYMBOL_68_ = 68,                       /* ','  */
  YYSYMBOL_69_ = 69,                       /* '('  */
  YYSYMBOL_70_ = 70,                       /* ')'  */
  YYSYMBOL_71_ = 71,                       /* '{'  */
  YYSYMBOL_72_ = 72,                       /* '}'  */
  YYSYMBOL_73_ = 73,                       /* '['  */
  YYSYMBOL_74_ = 74,                       /* ']'  */
  YYSYMBOL_75_ = 75,                       /* ';'  */
  YYSYMBOL_76_ = 76,                       /* '@'  */
  YYSYMBOL_77_ = 77,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 78,                  /* $accept  */
  YYSYMBOL_tid = 79,                       /* tid  */
  YYSYMBOL_telseBlock = 80,                /* telseBlock  */
  YYSYMBOL_telifBlock = 81,                /* telifBlock  */
  YYSYMBOL_telifBlocks = 82,               /* telifBlocks  */
  YYSYMBOL_tbranch = 83,                   /* tbranch  */
  YYSYMBOL_termFor = 84,                   /* termFor  */
  YYSYMBOL_tcaseExpr = 85,                 /* tcaseExpr  */
  YYSYMBOL_tcaseStmt = 86,                 /* tcaseStmt  */
  YYSYMBOL_tcaseIndentBlock = 87,          /* tcaseIndentBlock  */
  YYSYMBOL_tswitchExpr = 88,               /* tswitchExpr  */
  YYSYMBOL_termIf = 89,                    /* termIf  */
  YYSYMBOL_trhsIdExpr = 90,                /* trhsIdExpr  */
  YYSYMBOL_tdefBlockExpr = 91,             /* tdefBlockExpr  */
  YYSYMBOL_tdefexpr = 92,                  /* tdefexpr  */
  YYSYMBOL_tconNames = 93,                 /* tconNames  */
  YYSYMBOL_ttype = 94,                     /* ttype  */
  YYSYMBOL_tconAccess = 95,                /* tconAccess  */
  YYSYMBOL_takaStmt = 96,                  /* takaStmt  */
  YYSYMBOL_tcast = 97,                     /* tcast  */
  YYSYMBOL_treturnexpr = 98,               /* treturnexpr  */
  YYSYMBOL_trhsIds = 99,                   /* trhsIds  */
  YYSYMBOL_trhslist = 100,                 /* trhslist  */
  YYSYMBOL_tlhsId = 101,                   /* tlhsId  */
  YYSYMBOL_ttuple = 102,                   /* ttuple  */
  YYSYMBOL_ttuples = 103,                  /* ttuples  */
  YYSYMBOL_tmap = 104,                     /* tmap  */
  YYSYMBOL_tarray = 105,                   /* tarray  */
  YYSYMBOL_tseq = 106,                     /* tseq  */
  YYSYMBOL_taccess = 107,                  /* taccess  */
  YYSYMBOL_tpackAccess = 108,              /* tpackAccess  */
  YYSYMBOL_tsafeAccess = 109,              /* tsafeAccess  */
  YYSYMBOL_tparam = 110,                   /* tparam  */
  YYSYMBOL_tparams = 111,                  /* tparams  */
  YYSYMBOL_tfuncRhsList = 112,             /* tfuncRhsList  */
  YYSYMBOL_tpropexpr = 113,                /* tpropexpr  */
  YYSYMBOL_tpropIndentBlock = 114,         /* tpropIndentBlock  */
  YYSYMBOL_tpropBlock = 115,               /* tpropBlock  */
  YYSYMBOL_tgetsetFuncName = 116,          /* tgetsetFuncName  */
  YYSYMBOL_tgetsetList = 117,              /* tgetsetList  */
  YYSYMBOL_tgetsetterExpr = 118,           /* tgetsetterExpr  */
  YYSYMBOL_tgetsetterStmt = 119,           /* tgetsetterStmt  */
  YYSYMBOL_tdefOrigin = 120,               /* tdefOrigin  */
  YYSYMBOL_tfunclist = 121,                /* tfunclist  */
  YYSYMBOL_tfunc = 122,                    /* tfunc  */
  YYSYMBOL_tfuncBody = 123,                /* tfuncBody  */
  YYSYMBOL_tctorfunc = 124,                /* tctorfunc  */
  YYSYMBOL_tdtorfunc = 125,                /* tdtorfunc  */
  YYSYMBOL_tfuncCall = 126,                /* tfuncCall  */
  YYSYMBOL_texpr = 127,                    /* texpr  */
  YYSYMBOL_tblock = 128,                   /* tblock  */
  YYSYMBOL_tdefBlock = 129,                /* tdefBlock  */
  YYSYMBOL_tpackExpr = 130,                /* tpackExpr  */
  YYSYMBOL_timportExpr = 131,              /* timportExpr  */
  YYSYMBOL_tfileExpr = 132,                /* tfileExpr  */
  YYSYMBOL_tdefIndentBlock = 133,          /* tdefIndentBlock  */
  YYSYMBOL_tindentBlock = 134,             /* tindentBlock  */
  YYSYMBOL_tfile = 135                     /* tfile  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Default (constant) value used for initialization for null
   right-hand sides.  Unlike the standard yacc.c template, here we set
   the default value of $$ to a zeroed-out value.  Since the default
   value is undefined, this behavior is technically correct.  */
static YYSTYPE yyval_default;



#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif
#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YYFREE
# define YYFREE free
#endif
#ifndef YYMALLOC
# define YYMALLOC malloc
#endif
#ifndef YYREALLOC
# define YYREALLOC realloc
#endif

#ifdef __cplusplus
  typedef bool yybool;
# define yytrue true
# define yyfalse false
#else
  /* When we move to stdbool, get rid of the various casts to yybool.  */
  typedef signed char yybool;
# define yytrue 1
# define yyfalse 0
#endif

#ifndef YYSETJMP
# include <setjmp.h>
# define YYJMP_BUF jmp_buf
# define YYSETJMP(Env) setjmp (Env)
/* Pacify Clang and ICC.  */
# define YYLONGJMP(Env, Val)                    \
 do {                                           \
   longjmp (Env, Val);                          \
   YY_ASSERT (0);                               \
 } while (yyfalse)
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* The _Noreturn keyword of C11.  */
#ifndef _Noreturn
# if (defined __cplusplus \
      && ((201103 <= __cplusplus && !(__GNUC__ == 4 && __GNUC_MINOR__ == 7)) \
          || (defined _MSC_VER && 1900 <= _MSC_VER)))
#  define _Noreturn [[noreturn]]
# elif ((!defined __cplusplus || defined __clang__) \
        && (201112 <= (defined __STDC_VERSION__ ? __STDC_VERSION__ : 0) \
            || (!defined __STRICT_ANSI__ \
                && (__4 < __GNUC__ + (7 <= __GNUC_MINOR__) \
                    || (defined __apple_build_version__ \
                        ? 6000000 <= __apple_build_version__ \
                        : 3 < __clang_major__ + (5 <= __clang_minor__))))))
   /* _Noreturn works as-is.  */
# elif (2 < __GNUC__ + (8 <= __GNUC_MINOR__) || defined __clang__ \
        || 0x5110 <= __SUNPRO_C)
#  define _Noreturn __attribute__ ((__noreturn__))
# elif 1200 <= (defined _MSC_VER ? _MSC_VER : 0)
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  62
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1764

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  78
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  58
/* YYNRULES -- Number of rules.  */
#define YYNRULES  170
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  314
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule.  */
#define YYMAXRHS 6
/* YYMAXLEFT -- Maximum number of symbols to the left of a handle
   accessed by $0, $-1, etc., in any rule.  */
#define YYMAXLEFT 0

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   310

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    61,    57,     2,
      69,    70,    65,    63,    68,    64,    67,    66,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    77,    75,
      59,    56,    60,     2,    76,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    73,     2,    74,    62,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    71,    58,    72,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55
};

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    87,    87,    88,    91,    95,    98,   103,   109,   113,
     116,   121,   127,   135,   136,   139,   145,   153,   158,   161,
     164,   167,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   190,   191,   192,   193,   195,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   214,   215,   217,   220,
     225,   226,   228,   229,   230,   231,   232,   233,   234,   237,
     238,   239,   240,   241,   244,   245,   246,   247,   248,   249,
     252,   255,   258,   261,   266,   267,   270,   275,   278,   283,
     288,   289,   293,   299,   305,   310,   311,   314,   318,   323,
     330,   335,   340,   344,   345,   348,   349,   352,   353,   356,
     359,   364,   369,   376,   377,   378,   388,   391,   394,   397,
     401,   402,   403,   405,   410,   417,   418,   420,   421,   424,
     428,   431,   434,   437,   440,   445,   446,   449,   452,   455,
     458,   461,   466,   467,   470,   475,   480,   485,   486,   487,
     490,   496,   502,   507,   513,   521,   526,   529,   534,   535,
     536,   539,   540,   541,   544,   545,   546,   547,   550,   555,
     561
};
#endif

#define YYPACT_NINF (-181)
#define YYTABLE_NINF (-136)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      23,    10,   -21,   152,   108,    10,   -21,   -21,    24,  -181,
     245,   152,   291,  -181,  -181,  -181,    26,  -181,  -181,  -181,
    -181,   162,    33,  -181,  -181,  -181,  -181,  -181,   117,  -181,
      -2,    -8,  -181,    19,   849,   649,    35,  -181,    59,    68,
      12,    12,  -181,    -8,  -181,    98,  -181,    38,   849,    54,
      92,    82,   162,   122,   215,   130,   141,   538,   192,  -181,
    -181,   145,  -181,  -181,    23,   192,   849,   183,    31,    18,
    -181,    10,   849,   102,   849,  -181,  -181,  -181,  -181,  1691,
     849,   849,   686,   849,   343,  -181,  -181,  -181,   240,  -181,
    -181,  -181,    63,  -181,  -181,  -181,  -181,  -181,  -181,  -181,
    1016,   179,   849,   203,   849,   196,  -181,  -181,  -181,   -13,
    -181,    73,  1080,   199,   886,   192,  -181,  -181,   168,   171,
    -181,   575,  -181,   849,   849,  -181,  1107,  -181,  -181,  -181,
    -181,  -181,   304,    31,  -181,   849,  -181,    52,   275,   338,
      12,  -181,   205,   338,   849,   849,   849,   849,   849,   849,
     849,  1131,  1158,  1044,   202,   918,   -31,  -181,    91,   723,
    -181,    -8,   235,   849,   849,   849,   849,   849,   849,   849,
     283,  -181,  -181,   849,   849,   849,   849,   849,   849,   849,
     849,   849,   849,   287,   299,  -181,   849,   849,  -181,   849,
    -181,   372,   849,   406,  -181,  -181,  -181,   188,  -181,   211,
     760,  1182,  -181,  -181,  1209,  -181,  -181,    60,  1233,  1260,
    -181,  -181,   206,   440,   251,   849,  -181,  -181,   321,  -181,
    -181,   237,  -181,  1284,  1311,  1335,  1362,  1386,  1413,  1437,
    -181,   849,  -181,   849,  -181,   596,  -181,   299,   201,  1534,
    1551,  1567,  1585,  1602,  1464,   222,  -181,  1488,  1515,  1618,
    1636,   119,  1653,   505,   797,   149,   545,   239,  -181,  -181,
    -181,   -21,  -181,   993,  1209,  1209,  -181,   474,  -181,  -181,
    -181,  -181,  -181,  -181,   575,  -181,    31,  -181,   812,   338,
      12,   849,  -181,  -181,  1209,   942,  -181,   175,   273,  -181,
      12,  -181,  -181,  -181,  -181,  -181,    12,    85,  -181,   612,
    1209,  -181,  -181,  -181,  -181,  -181,  -181,  -181,  -181,   849,
    -181,  -181,  -181,  1209
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     2,     3,
       0,     0,     0,    79,   160,    78,     0,    96,    77,    71,
      70,     0,    69,    72,    73,   158,   159,   169,     0,    95,
     155,     0,     2,   163,     0,     0,     0,   113,     0,   156,
       0,     0,   135,     0,   111,     0,   110,     0,     0,    85,
     109,    84,     0,     0,     0,     0,     0,     0,     0,   141,
     142,     0,     1,   170,     0,     0,     0,     0,     0,   163,
     131,     0,     0,     0,     0,    23,    22,    25,    24,    28,
       0,     0,     0,     0,     0,    56,    26,    60,   122,    30,
      39,    31,     0,    29,    27,    57,    33,    32,    61,   114,
       0,     0,     0,     0,     0,     0,   144,   145,   109,     0,
     136,     0,    74,     0,     0,     0,   139,    87,   105,     0,
     106,     0,   143,     0,     0,   167,   165,   166,   140,    88,
     168,   138,   163,     0,   162,     0,   132,     0,     0,     0,
       0,    59,    21,     0,     0,     0,     0,     0,     0,     0,
       0,    35,    37,     0,    77,     0,     0,    98,     0,     0,
     146,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    36,    38,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   118,     0,     0,   115,     0,
      94,   122,     0,   122,   157,   112,    80,     0,    81,     0,
       0,    75,   137,   149,   147,   148,   150,     0,    90,    91,
     134,   153,     0,   163,     0,     0,    10,    58,     0,    20,
       6,    19,     8,    63,    64,    65,    66,    67,    62,    68,
      34,     0,   101,     0,   100,   114,    89,     0,    47,    49,
      50,    51,    52,    53,   102,   107,   108,    54,    55,    46,
      48,    44,    45,    40,    41,    42,    43,   103,   104,   125,
     126,   128,   121,     0,    92,    93,   116,   122,   119,    82,
      83,    76,   164,   152,     0,   161,     0,   133,     0,     0,
       0,     0,    18,     7,    97,     0,    99,     0,     0,   123,
       0,   127,    86,   117,   151,   154,     0,     0,    15,     0,
      11,     9,     4,     5,   120,   124,   130,   129,    14,     0,
      13,    17,    16,    12
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -181,     6,    95,   104,  -181,    32,  -181,  -181,    30,  -181,
    -181,  -181,    46,  -181,     8,  -181,     3,  -181,  -181,  -181,
     278,   -79,  -181,     0,   103,  -181,  -181,  -181,  -181,  -181,
    -181,  -181,    -3,  -181,   142,  -181,  -180,  -181,  -181,  -181,
     153,    51,  -181,    13,  -181,    17,  -181,  -181,   -36,    65,
    -181,  -181,  -181,  -181,   276,   -55,   -38,  -181
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    84,   219,   220,   221,   142,    85,   297,   298,   299,
      86,    87,   100,    13,    89,    49,    50,    90,    15,    91,
     205,   101,    37,    92,   157,   158,    93,    94,    95,    96,
      17,    97,    18,    45,   160,    19,   185,   287,   261,   290,
     288,   289,    20,    21,    22,    59,    23,    24,    98,   206,
     207,   212,    25,    26,    27,    70,    60,    28
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      16,    30,   106,   107,   156,    39,    12,    44,    14,    33,
      36,   266,    51,   268,   136,    31,    43,    46,   120,    40,
      41,    51,    32,     9,    58,    52,     1,    29,     2,    47,
       3,    51,   135,    66,    65,   141,     2,   189,     3,     4,
       5,   232,   -95,    51,    53,    29,   108,     4,    10,   102,
      55,    61,    51,     6,     7,   115,    67,    67,     8,     9,
     119,     6,     7,    11,    16,    54,     8,     9,    16,   116,
      12,   137,    14,   104,    12,   128,   134,   210,   138,   154,
      88,    53,   131,   272,    51,   273,   105,   293,    35,    57,
     214,   -95,    10,    54,   112,    68,    68,    52,   274,    11,
      10,   216,   217,   126,    35,   222,   195,    11,    29,   111,
      47,    51,   132,    51,   197,    43,   199,    62,   139,    54,
     143,   156,    34,    55,   161,   113,   151,   152,   153,   155,
      54,   114,   202,    16,   246,    54,   186,   140,    51,    12,
      55,   211,    63,    32,     9,   196,    38,   258,   191,    54,
     193,    52,   121,   309,   161,    64,   154,   117,   277,   233,
     201,    51,    57,   234,   236,   122,   109,   204,   110,   208,
     209,   169,   170,   171,   172,    69,   119,    35,   103,    57,
     129,   213,   179,   180,   181,   182,   183,    32,     9,   119,
     223,   224,   225,   226,   227,   228,   229,    29,   304,    47,
      55,   169,   170,   171,   172,   133,   161,   259,   260,   238,
     239,   240,   241,   242,   243,   244,   183,   192,    56,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   275,
      55,   194,   263,   264,    29,   265,    47,    -2,   267,    57,
      35,   301,   302,   218,   276,   161,   155,   189,    56,   190,
     118,     9,   307,   169,   170,   171,   172,   237,   308,   310,
     269,   279,   177,   178,   179,   180,   181,   182,   183,    57,
     -77,   198,   -77,   278,   291,   218,    16,   284,   162,   285,
      32,     9,    12,   270,   295,   163,   164,   165,   166,   167,
     168,    -2,   169,   170,   171,   172,   215,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,    -2,   161,
      29,   306,    47,   303,    48,    42,   282,   184,   245,     9,
     204,    11,   257,     9,   300,   283,    29,   143,    47,   312,
      48,   259,   260,   280,   281,   127,   286,   262,   305,   294,
     130,     0,    67,   161,   159,   300,     0,     0,     0,   163,
     164,   165,   166,   167,   168,   313,   169,   170,   171,   172,
      10,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,     0,     0,     0,     0,    55,   161,    29,     0,
      47,    68,    48,   163,   164,   165,   166,   167,   168,     0,
     169,   170,   171,   172,     0,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,     0,     0,     0,     0,
     162,   161,   159,     0,     0,    57,     0,   163,   164,   165,
     166,   167,   168,     0,   169,   170,   171,   172,     0,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
       0,     0,     0,     0,   162,   161,     0,     0,     0,   184,
       0,   163,   164,   165,   166,   167,   168,     0,   169,   170,
     171,   172,     0,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,     0,     0,     0,     0,    67,   161,
       0,     0,     0,   184,     0,   163,   164,   165,   166,   167,
     168,     0,   169,   170,   171,   172,     0,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,     0,     0,
     161,     0,   162,     0,     0,     0,     0,    68,     0,   163,
     164,   165,   166,   167,   168,     0,   169,   170,   171,   172,
       0,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,    71,     2,    72,     3,    73,   123,   124,    74,
     161,   184,     0,   125,     4,     0,     0,   169,   170,   171,
     172,     0,     0,     0,    75,    76,    77,    78,     6,     7,
     181,   182,   183,    79,     9,     0,     0,     0,     0,    71,
       2,    72,     3,    73,   123,   124,    74,     0,     0,     0,
     203,     4,    80,    81,     0,     0,     0,   169,   170,   171,
     172,    75,    76,    77,    78,     6,     7,    82,     0,    83,
      79,     9,   183,     0,    11,     0,    71,     2,    72,     3,
      73,     0,     0,    74,   296,     0,     0,     0,     4,    80,
      81,  -114,     0,  -135,  -114,   311,     0,     0,    75,    76,
      77,    78,     6,     7,    82,     0,    83,    79,     9,     0,
       0,    11,  -135,    71,     2,    72,     3,    73,     0,     0,
      74,     0,     0,     0,     0,     4,    80,    81,     0,     0,
       0,     0,     0,  -114,     0,    75,    76,    77,    78,     6,
       7,    82,     0,    83,    79,     9,     0,     0,    11,     0,
      71,     2,    72,     3,    73,     0,     0,    74,     0,     0,
       0,     0,     4,    80,    81,     0,     0,     0,     0,     0,
       0,     0,    75,    76,    77,    78,     6,     7,    82,    99,
      83,    79,     9,     0,     0,    11,     0,    71,     2,    72,
       3,    73,     0,     0,    74,     0,     0,     0,     0,     4,
      80,    81,     0,     0,     0,     0,     0,     0,     0,    75,
      76,    77,    78,     6,     7,    82,    42,    83,    79,     9,
       0,     0,    11,     0,    71,     2,    72,     3,    73,     0,
       0,    74,     0,     0,     0,     0,     4,    80,    81,     0,
       0,     0,     0,     0,     0,     0,    75,    76,    77,    78,
       6,     7,    82,   235,    83,    79,     9,     0,     0,    11,
       0,     0,   161,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    80,    81,    71,     2,    72,     3,
      73,     0,     0,    74,   296,     0,     0,     0,     4,    82,
       0,    83,   271,     0,     0,     0,    11,     0,    75,    76,
      77,    78,     6,     7,     0,     0,     0,    79,     9,   169,
     170,   171,   172,    71,     2,    72,     3,    73,     0,     0,
      74,     0,   181,   182,   183,     4,    80,    81,     0,     0,
       0,     0,     0,     0,     0,    75,    76,    77,    78,     6,
       7,    82,     0,    83,    79,     9,     0,     0,    11,     0,
      71,     2,    72,     3,    73,     0,     0,    74,     0,     0,
       0,     0,     4,    80,    81,     0,     0,     0,     0,     0,
       0,     0,    75,    76,    77,    78,     6,     7,    82,     0,
      83,    79,     9,   161,     0,    11,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      80,    81,     0,     0,     0,     0,     0,   161,     0,     0,
       0,     0,     0,     0,     0,    82,     0,   200,     0,     0,
       0,     0,    11,   163,   164,   165,   166,   167,   168,     0,
     169,   170,   171,   172,     0,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   187,   163,   164,   165,
     166,   167,   168,   231,   169,   170,   171,   172,   161,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
       0,     0,     0,     0,     0,     0,     0,   231,     0,     0,
       0,   161,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   163,   164,
     165,   166,   167,   168,     0,   169,   170,   171,   172,   161,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   163,   164,   165,   166,   167,   168,   292,   169,   170,
     171,   172,     0,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   187,   161,   188,     0,     0,   163,
     164,   165,   166,   167,   168,     0,   169,   170,   171,   172,
       0,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   161,     0,   230,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   163,   164,   165,   166,   167,
     168,     0,   169,   170,   171,   172,   161,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,     0,     0,
       0,     0,   163,   164,   165,   166,   167,   168,     0,   169,
     170,   171,   172,   161,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,     0,   163,   164,   165,   166,
     167,   168,     0,   169,   170,   171,   172,   161,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,     0,
       0,     0,     0,   163,   164,   165,   166,   167,   168,     0,
     169,   170,   171,   172,   161,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,     0,   163,   164,   165,
     166,   167,   168,     0,   169,   170,   171,   172,   161,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
       0,     0,     0,     0,   163,   164,   165,   166,   167,   168,
       0,   169,   170,   171,   172,   161,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,     0,   163,   164,
     165,   166,   167,   168,     0,   169,   170,   171,   172,   161,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,     0,     0,     0,     0,   163,   164,   165,   166,   167,
     168,     0,   169,   170,   171,   172,   161,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,     0,   163,
     164,   165,   166,   167,   168,     0,   169,   170,   171,   172,
     161,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,     0,     0,     0,     0,   163,   164,   165,   166,
     167,   168,     0,   169,   170,   171,   172,   161,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,     0,
     163,   164,   165,   166,   167,   168,     0,   169,   170,   171,
     172,   161,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,     0,     0,     0,     0,   163,   164,   165,
     166,   167,   168,     0,   169,   170,   171,   172,   161,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
       0,   163,   164,   165,   166,   167,   168,     0,   169,   170,
     171,   172,   161,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,     0,     0,     0,     0,   163,   164,
     165,   166,   167,   168,     0,   169,   170,   171,   172,   161,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,     0,   163,   164,   165,   166,   167,   168,     0,   169,
     170,   171,   172,   161,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,     0,     0,     0,     0,   163,
     164,   165,   166,   167,   168,     0,   169,   170,   171,   172,
     161,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,     0,   163,   164,   165,   166,   167,   168,   161,
     169,   170,   171,   172,     0,     0,     0,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   161,     0,     0,     0,
     163,   164,   165,   166,   167,   168,     0,   169,   170,   171,
     172,     0,   161,     0,   175,   176,   177,   178,   179,   180,
     181,   182,   183,     0,     0,     0,   169,   170,   171,   172,
     161,     0,     0,     0,     0,   177,   178,   179,   180,   181,
     182,   183,     0,   169,   170,   171,   172,   161,     0,     0,
       0,     0,   177,   178,   179,   180,   181,   182,   183,   169,
     170,   171,   172,   161,     0,     0,     0,     0,   177,   178,
     179,   180,   181,   182,   183,     0,     0,   169,   170,   171,
     172,   161,     0,     0,     0,     0,   177,   178,   179,   180,
     181,   182,   183,     0,   169,   170,   171,   172,   161,     0,
       0,     0,     0,   177,   178,   179,   180,   181,   182,   183,
     169,   170,   171,   172,     0,     0,     0,     0,     0,   177,
     178,   179,   180,   181,   182,   183,     0,     0,   169,   170,
     171,   172,     0,     0,     0,     0,     0,   177,   178,   179,
     180,   181,   182,   183,     0,   169,   170,   171,   172,   -28,
       0,     0,    -2,     0,     0,     0,   179,   180,   181,   182,
     183,     0,     0,     0,     0,     0,    -2,     0,    -2,     0,
      -2,   144,   145,   146,   147,   148,     0,     0,     0,     0,
       0,     0,   149,     0,     0,     0,     0,   150,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -28,     0,
      -2,     0,     0,     0,   -95
};

static const yytype_int16 yycheck[] =
{
       0,     1,    40,    41,    83,     5,     0,    10,     0,     3,
       4,   191,    12,   193,    69,     2,    10,    11,    54,     6,
       7,    21,    35,    36,    21,    12,     3,    35,     5,    37,
       7,    31,    14,    14,    31,    73,     5,    68,     7,    16,
      17,    72,    18,    43,    18,    35,    43,    16,    69,    14,
      38,    18,    52,    30,    31,    52,    38,    38,    35,    36,
      54,    30,    31,    76,    64,    67,    35,    36,    68,    52,
      64,    71,    64,    14,    68,    58,    68,   132,    72,    82,
      34,    18,    65,    23,    84,    25,    18,   267,    69,    77,
      38,    67,    69,    67,    48,    77,    77,    84,    38,    76,
      69,   139,   140,    57,    69,   143,   109,    76,    35,    71,
      37,   111,    66,   113,   111,   109,   113,     0,    72,    67,
      74,   200,    14,    38,     5,    71,    80,    81,    82,    83,
      67,    39,   115,   133,   170,    67,    73,    35,   138,   133,
      38,   133,    25,    35,    36,    72,     4,   183,   102,    67,
     104,   138,    22,    68,     5,    38,   159,    35,   213,    68,
     114,   161,    77,    72,   161,    24,    68,   121,    70,   123,
     124,    52,    53,    54,    55,    33,   170,    69,    36,    77,
      35,   135,    63,    64,    65,    66,    67,    35,    36,   183,
     144,   145,   146,   147,   148,   149,   150,    35,    23,    37,
      38,    52,    53,    54,    55,    22,     5,    32,    33,   163,
     164,   165,   166,   167,   168,   169,    67,    14,    56,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,    23,
      38,    35,   186,   187,    35,   189,    37,    69,   192,    77,
      69,   279,   280,    38,    38,     5,   200,    68,    56,    70,
      35,    36,   290,    52,    53,    54,    55,    22,   296,   297,
      72,   215,    61,    62,    63,    64,    65,    66,    67,    77,
      68,    72,    70,    22,   261,    38,   276,   231,    38,   233,
      35,    36,   276,    72,   276,    45,    46,    47,    48,    49,
      50,    69,    52,    53,    54,    55,    21,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    69,     5,
      35,    38,    37,   281,    39,    70,   221,    77,    35,    36,
     274,    76,    35,    36,   278,   221,    35,   281,    37,   299,
      39,    32,    33,    12,    13,    57,   233,   184,   287,   274,
      64,    -1,    38,     5,    69,   299,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,   309,    52,    53,    54,    55,
      69,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    -1,    -1,    -1,    -1,    38,     5,    35,    -1,
      37,    77,    39,    45,    46,    47,    48,    49,    50,    -1,
      52,    53,    54,    55,    -1,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    -1,    -1,    -1,    -1,
      38,     5,    69,    -1,    -1,    77,    -1,    45,    46,    47,
      48,    49,    50,    -1,    52,    53,    54,    55,    -1,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      -1,    -1,    -1,    -1,    38,     5,    -1,    -1,    -1,    77,
      -1,    45,    46,    47,    48,    49,    50,    -1,    52,    53,
      54,    55,    -1,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    -1,    -1,    -1,    -1,    38,     5,
      -1,    -1,    -1,    77,    -1,    45,    46,    47,    48,    49,
      50,    -1,    52,    53,    54,    55,    -1,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    -1,    -1,
       5,    -1,    38,    -1,    -1,    -1,    -1,    77,    -1,    45,
      46,    47,    48,    49,    50,    -1,    52,    53,    54,    55,
      -1,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,     4,     5,     6,     7,     8,     9,    10,    11,
       5,    77,    -1,    15,    16,    -1,    -1,    52,    53,    54,
      55,    -1,    -1,    -1,    26,    27,    28,    29,    30,    31,
      65,    66,    67,    35,    36,    -1,    -1,    -1,    -1,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      15,    16,    54,    55,    -1,    -1,    -1,    52,    53,    54,
      55,    26,    27,    28,    29,    30,    31,    69,    -1,    71,
      35,    36,    67,    -1,    76,    -1,     4,     5,     6,     7,
       8,    -1,    -1,    11,    12,    -1,    -1,    -1,    16,    54,
      55,    35,    -1,    37,    38,    23,    -1,    -1,    26,    27,
      28,    29,    30,    31,    69,    -1,    71,    35,    36,    -1,
      -1,    76,    56,     4,     5,     6,     7,     8,    -1,    -1,
      11,    -1,    -1,    -1,    -1,    16,    54,    55,    -1,    -1,
      -1,    -1,    -1,    77,    -1,    26,    27,    28,    29,    30,
      31,    69,    -1,    71,    35,    36,    -1,    -1,    76,    -1,
       4,     5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    16,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    26,    27,    28,    29,    30,    31,    69,    70,
      71,    35,    36,    -1,    -1,    76,    -1,     4,     5,     6,
       7,     8,    -1,    -1,    11,    -1,    -1,    -1,    -1,    16,
      54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,
      27,    28,    29,    30,    31,    69,    70,    71,    35,    36,
      -1,    -1,    76,    -1,     4,     5,     6,     7,     8,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    16,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    26,    27,    28,    29,
      30,    31,    69,    70,    71,    35,    36,    -1,    -1,    76,
      -1,    -1,     5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,     4,     5,     6,     7,
       8,    -1,    -1,    11,    12,    -1,    -1,    -1,    16,    69,
      -1,    71,    72,    -1,    -1,    -1,    76,    -1,    26,    27,
      28,    29,    30,    31,    -1,    -1,    -1,    35,    36,    52,
      53,    54,    55,     4,     5,     6,     7,     8,    -1,    -1,
      11,    -1,    65,    66,    67,    16,    54,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    27,    28,    29,    30,
      31,    69,    -1,    71,    35,    36,    -1,    -1,    76,    -1,
       4,     5,     6,     7,     8,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    16,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    26,    27,    28,    29,    30,    31,    69,    -1,
      71,    35,    36,     5,    -1,    76,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    55,    -1,    -1,    -1,    -1,    -1,     5,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    69,    -1,    71,    -1,    -1,
      -1,    -1,    76,    45,    46,    47,    48,    49,    50,    -1,
      52,    53,    54,    55,    -1,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    45,    46,    47,
      48,    49,    50,    75,    52,    53,    54,    55,     5,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,    -1,
      -1,     5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    46,
      47,    48,    49,    50,    -1,    52,    53,    54,    55,     5,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    45,    46,    47,    48,    49,    50,    74,    52,    53,
      54,    55,    -1,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,     5,    70,    -1,    -1,    45,
      46,    47,    48,    49,    50,    -1,    52,    53,    54,    55,
      -1,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,     5,    -1,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    -1,    52,    53,    54,    55,     5,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    -1,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    50,    -1,    52,
      53,    54,    55,     5,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    -1,    45,    46,    47,    48,
      49,    50,    -1,    52,    53,    54,    55,     5,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    45,    46,    47,    48,    49,    50,    -1,
      52,    53,    54,    55,     5,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    -1,    45,    46,    47,
      48,    49,    50,    -1,    52,    53,    54,    55,     5,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,    50,
      -1,    52,    53,    54,    55,     5,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    -1,    45,    46,
      47,    48,    49,    50,    -1,    52,    53,    54,    55,     5,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,    45,    46,    47,    48,    49,
      50,    -1,    52,    53,    54,    55,     5,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    -1,    45,
      46,    47,    48,    49,    50,    -1,    52,    53,    54,    55,
       5,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    -1,    -1,    -1,    -1,    45,    46,    47,    48,
      49,    50,    -1,    52,    53,    54,    55,     5,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    -1,
      45,    46,    47,    48,    49,    50,    -1,    52,    53,    54,
      55,     5,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    -1,    -1,    -1,    -1,    45,    46,    47,
      48,    49,    50,    -1,    52,    53,    54,    55,     5,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      -1,    45,    46,    47,    48,    49,    50,    -1,    52,    53,
      54,    55,     5,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    -1,    -1,    -1,    -1,    45,    46,
      47,    48,    49,    50,    -1,    52,    53,    54,    55,     5,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    -1,    45,    46,    47,    48,    49,    50,    -1,    52,
      53,    54,    55,     5,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    -1,    -1,    -1,    -1,    45,
      46,    47,    48,    49,    50,    -1,    52,    53,    54,    55,
       5,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    -1,    45,    46,    47,    48,    49,    50,     5,
      52,    53,    54,    55,    -1,    -1,    -1,    59,    60,    61,
      62,    63,    64,    65,    66,    67,     5,    -1,    -1,    -1,
      45,    46,    47,    48,    49,    50,    -1,    52,    53,    54,
      55,    -1,     5,    -1,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    -1,    -1,    -1,    52,    53,    54,    55,
       5,    -1,    -1,    -1,    -1,    61,    62,    63,    64,    65,
      66,    67,    -1,    52,    53,    54,    55,     5,    -1,    -1,
      -1,    -1,    61,    62,    63,    64,    65,    66,    67,    52,
      53,    54,    55,     5,    -1,    -1,    -1,    -1,    61,    62,
      63,    64,    65,    66,    67,    -1,    -1,    52,    53,    54,
      55,     5,    -1,    -1,    -1,    -1,    61,    62,    63,    64,
      65,    66,    67,    -1,    52,    53,    54,    55,     5,    -1,
      -1,    -1,    -1,    61,    62,    63,    64,    65,    66,    67,
      52,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,    61,
      62,    63,    64,    65,    66,    67,    -1,    -1,    52,    53,
      54,    55,    -1,    -1,    -1,    -1,    -1,    61,    62,    63,
      64,    65,    66,    67,    -1,    52,    53,    54,    55,    18,
      -1,    -1,    21,    -1,    -1,    -1,    63,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,    -1,    35,    -1,    37,    -1,
      39,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    51,    -1,    -1,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,
      69,    -1,    -1,    -1,    73
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     7,    16,    17,    30,    31,    35,    36,
      69,    76,    79,    91,    92,    96,   101,   108,   110,   113,
     120,   121,   122,   124,   125,   130,   131,   132,   135,    35,
     101,   121,    35,    79,    14,    69,    79,   100,   112,   101,
     121,   121,    70,    79,   110,   111,    79,    37,    39,    93,
      94,   101,   121,    18,    67,    38,    56,    77,    94,   123,
     134,    18,     0,    25,    38,    94,    14,    38,    77,   112,
     133,     4,     6,     8,    11,    26,    27,    28,    29,    35,
      54,    55,    69,    71,    79,    84,    88,    89,    90,    92,
      95,    97,   101,   104,   105,   106,   107,   109,   126,    70,
      90,    99,    14,   112,    14,    18,   134,   134,    94,    68,
      70,    71,    90,    71,    39,    94,   123,    35,    35,    79,
     126,    22,    24,     9,    10,    15,    90,    98,   123,    35,
     132,   123,    90,    22,    92,    14,   133,   101,    79,    90,
      35,   134,    83,    90,    40,    41,    42,    43,    44,    51,
      56,    90,    90,    90,   110,    90,    99,   102,   103,    69,
     112,     5,    38,    45,    46,    47,    48,    49,    50,    52,
      53,    54,    55,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    77,   114,    73,    68,    70,    68,
      70,    90,    14,    90,    35,   110,    72,    94,    72,    94,
      71,    90,   123,    15,    90,    98,   127,   128,    90,    90,
     133,    92,   129,    90,    38,    21,   134,   134,    38,    80,
      81,    82,   134,    90,    90,    90,    90,    90,    90,    90,
      70,    75,    72,    68,    72,    70,    94,    22,    90,    90,
      90,    90,    90,    90,    90,    35,   126,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    35,   126,    32,
      33,   116,   118,    90,    90,    90,   114,    90,   114,    72,
      72,    72,    23,    25,    38,    23,    38,   133,    22,    90,
      12,    13,    80,    81,    90,    90,   102,   115,   118,   119,
     117,   121,    74,   114,   127,    92,    12,    85,    86,    87,
      90,   134,   134,    83,    23,   119,    38,   134,   134,    68,
     134,    23,    86,    90
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    78,    79,    79,    80,    81,    82,    82,    83,    84,
      84,    85,    85,    86,    86,    87,    87,    88,    89,    89,
      89,    89,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    91,
      91,    91,    91,    91,    92,    92,    92,    92,    92,    92,
      93,    93,    93,    93,    94,    94,    95,    96,    96,    97,
      98,    98,    99,    99,   100,   101,   101,   102,   103,   103,
     104,   105,   106,   107,   107,   108,   108,   109,   109,   110,
     110,   111,   111,   112,   112,   112,   113,   113,   113,   113,
     114,   114,   114,   115,   115,   116,   116,   117,   117,   118,
     119,   120,   120,   120,   120,   121,   121,   122,   122,   122,
     122,   122,   123,   123,   124,   125,   126,   127,   127,   127,
     128,   128,   128,   129,   129,   130,   131,   131,   132,   132,
     132,   133,   133,   133,   134,   134,   134,   134,   135,   135,
     135
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     3,     3,     1,     2,     2,     5,
       3,     1,     3,     2,     2,     1,     2,     6,     4,     3,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     2,     2,     2,     2,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     1,     3,     2,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     3,     4,     5,     1,     1,     1,
       3,     3,     4,     4,     1,     1,     4,     3,     3,     3,
       2,     2,     3,     3,     3,     1,     1,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     1,     3,     1,     2,     3,     5,     6,     4,     5,
       4,     2,     0,     1,     2,     1,     1,     1,     0,     3,
       2,     3,     4,     6,     5,     2,     3,     4,     4,     3,
       3,     2,     1,     2,     3,     3,     2,     1,     1,     1,
       1,     3,     2,     1,     3,     2,     2,     4,     1,     1,
       1,     4,     2,     0,     4,     2,     2,     2,     3,     1,
       2
};


/* YYDPREC[RULE-NUM] -- Dynamic precedence of rule #RULE-NUM (0 if none).  */
static const yytype_int8 yydprec[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     1,     1,     0,     1,     1,     1,     1,     1,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     3,     3,     4,     4,     0,     0,
       0,     0,     5,     5,     5,     5,     5,     5,     5,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0
};

/* YYMERGER[RULE-NUM] -- Index of merging function for rule #RULE-NUM.  */
static const yytype_int8 yymerger[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0
};

/* YYIMMEDIATE[RULE-NUM] -- True iff rule #RULE-NUM is not to be deferred, as
   in the case of predicates.  */
static const yybool yyimmediate[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0
};

/* YYCONFLP[YYPACT[STATE-NUM]] -- Pointer into YYCONFL of start of
   list of conflicting reductions corresponding to action entry for
   state STATE-NUM in yytable.  0 means no conflicts.  The list in
   yyconfl is terminated by a rule number of 0.  */
static const yytype_int16 yyconflp[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     0,     0,     0,     0,    13,     3,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     0,
       0,     0,     0,     0,     0,    15,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   737,     9,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    11,
       0,     0,     0,     0,   777,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   739,   741,   743,   745,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   779,   781,   783,   785,     0,   591,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    83,     0,     0,
       0,     0,     0,   177,     0,    25,     0,     0,     0,     0,
       0,     0,     0,   593,   595,   597,   599,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     267,     0,   269,     0,     0,   513,     0,     0,    27,     0,
       0,     0,     0,     0,     0,    29,    31,    33,    35,    37,
      39,   695,    41,    43,    45,    47,     0,    49,    51,    53,
      55,    57,    59,    61,    63,    65,    67,    69,   797,   129,
       0,     0,     0,     0,     0,     0,     0,    71,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   131,     0,     0,     0,     0,     0,     0,   133,
     135,   137,   139,   141,   143,     0,   145,   147,   149,   151,
       0,   153,   155,   157,   159,   161,   163,   165,   167,   169,
     171,   173,     0,     0,     0,     0,     0,   271,     0,     0,
       0,   175,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     273,   319,     0,     0,     0,     0,     0,   275,   277,   279,
     281,   283,   285,     0,   287,   289,   291,   293,     0,   295,
     297,   299,   301,   303,   305,   307,   309,   311,   313,   315,
       0,     0,     0,     0,   321,   465,     0,     0,     0,   317,
       0,   323,   325,   327,   329,   331,   333,     0,   335,   337,
     339,   341,     0,   343,   345,   347,   349,   351,   353,   355,
     357,   359,   361,   363,     0,     0,     0,     0,   467,   799,
       0,     0,     0,   365,     0,   469,   471,   473,   475,   477,
     479,     0,   481,   483,   485,   487,     0,   489,   491,   493,
     495,   497,   499,   501,   503,   505,   507,   509,     0,     0,
     757,     0,   801,     0,     0,     0,     0,   511,     0,   803,
     805,   807,   809,   811,   813,     0,   815,   817,   819,   821,
       0,   823,   825,   827,   829,   831,   833,   835,   837,   839,
     841,   843,     0,     0,     0,     0,     0,     0,     0,     0,
     787,   845,     0,     0,     0,     0,     0,   759,   761,   763,
     765,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   789,   791,   793,
     795,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   585,     0,     0,   587,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   589,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   767,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   769,
     771,   773,   775,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    73,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    85,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    75,    77,    79,    81,   179,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    87,    89,    91,    93,    95,    97,     0,    99,
     101,   103,   105,   223,   107,   109,   111,   113,   115,   117,
     119,   121,   123,   125,   127,     0,   181,   183,   185,   187,
     189,   191,     0,   193,   195,   197,   199,   367,   201,   203,
     205,   207,   209,   211,   213,   215,   217,   219,   221,     0,
       0,     0,     0,   225,   227,   229,   231,   233,   235,     0,
     237,   239,   241,   243,     0,   245,   247,   249,   251,   253,
     255,   257,   259,   261,   263,   265,     0,     0,     0,     0,
       0,     0,     0,     0,   369,   371,   373,   375,   377,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   421,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   379,   381,
     383,   385,   387,   389,     0,   391,   393,   395,   397,   515,
     399,   401,   403,   405,   407,   409,   411,   413,   415,   417,
     419,     0,     0,     0,     0,   423,   425,   427,   429,   431,
     433,     0,   435,   437,   439,   441,   525,   443,   445,   447,
     449,   451,   453,   455,   457,   459,   461,   463,     0,     0,
       0,     0,     0,     0,     0,     0,   517,   519,   521,   523,
     535,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   527,   529,   531,   533,   545,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   537,   539,   541,
     543,   555,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   547,   549,   551,   553,   565,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   557,   559,
     561,   563,   575,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   567,   569,   571,   573,   651,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   577,
     579,   581,   583,   697,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   653,
     655,   657,   659,   661,   663,     0,   665,   667,   669,   671,
     707,   673,   675,   677,   679,   681,   683,   685,   687,   689,
     691,   693,     0,     0,     0,     0,     0,     0,     0,   601,
     699,   701,   703,   705,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   611,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   709,   711,   713,
     715,     0,   621,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   603,   605,   607,   609,
     631,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   613,   615,   617,   619,   641,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   623,
     625,   627,   629,   717,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   633,   635,   637,
     639,   727,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   643,   645,   647,   649,   747,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     719,   721,   723,   725,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   729,   731,
     733,   735,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   749,   751,   753,   755,    17,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    19,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    21,     0,
      23,     0,     0,     0,     0
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
static const short yyconfl[] =
{
       0,    69,     0,   163,     0,   163,     0,   163,     0,    85,
       0,    84,     0,   163,     0,   163,     0,    95,     0,    28,
       0,    95,     0,    28,     0,   122,     0,   122,     0,   122,
       0,   122,     0,   122,     0,   122,     0,   122,     0,   122,
       0,   122,     0,   122,     0,   122,     0,   122,     0,   122,
       0,   122,     0,   122,     0,   122,     0,   122,     0,   122,
       0,   122,     0,   122,     0,   122,     0,   122,     0,   122,
       0,   122,     0,    74,     0,    74,     0,    74,     0,    74,
       0,    74,     0,   105,     0,   165,     0,   165,     0,   165,
       0,   165,     0,   165,     0,   165,     0,   165,     0,   165,
       0,   165,     0,   165,     0,   165,     0,   165,     0,   165,
       0,   165,     0,   165,     0,   165,     0,   165,     0,   165,
       0,   165,     0,   165,     0,   165,     0,   165,     0,   163,
       0,   163,     0,   163,     0,   163,     0,   163,     0,   163,
       0,   163,     0,   163,     0,   163,     0,   163,     0,   163,
       0,   163,     0,   163,     0,   163,     0,   163,     0,   163,
       0,   163,     0,   163,     0,   163,     0,   163,     0,   163,
       0,   163,     0,   163,     0,   163,     0,    21,     0,    35,
       0,    35,     0,    35,     0,    35,     0,    35,     0,    35,
       0,    35,     0,    35,     0,    35,     0,    35,     0,    35,
       0,    35,     0,    35,     0,    35,     0,    35,     0,    35,
       0,    35,     0,    35,     0,    35,     0,    35,     0,    35,
       0,    35,     0,    37,     0,    37,     0,    37,     0,    37,
       0,    37,     0,    37,     0,    37,     0,    37,     0,    37,
       0,    37,     0,    37,     0,    37,     0,    37,     0,    37,
       0,    37,     0,    37,     0,    37,     0,    37,     0,    37,
       0,    37,     0,    37,     0,    37,     0,   111,     0,   111,
       0,   122,     0,   122,     0,   122,     0,   122,     0,   122,
       0,   122,     0,   122,     0,   122,     0,   122,     0,   122,
       0,   122,     0,   122,     0,   122,     0,   122,     0,   122,
       0,   122,     0,   122,     0,   122,     0,   122,     0,   122,
       0,   122,     0,   122,     0,   122,     0,   122,     0,   122,
       0,   122,     0,   122,     0,   122,     0,   122,     0,   122,
       0,   122,     0,   122,     0,   122,     0,   122,     0,   122,
       0,   122,     0,   122,     0,   122,     0,   122,     0,   122,
       0,   122,     0,   122,     0,   122,     0,   122,     0,   122,
       0,   122,     0,   122,     0,   122,     0,    75,     0,    75,
       0,    75,     0,    75,     0,    75,     0,    90,     0,    90,
       0,    90,     0,    90,     0,    90,     0,    90,     0,    90,
       0,    90,     0,    90,     0,    90,     0,    90,     0,    90,
       0,    90,     0,    90,     0,    90,     0,    90,     0,    90,
       0,    90,     0,    90,     0,    90,     0,    90,     0,    90,
       0,    91,     0,    91,     0,    91,     0,    91,     0,    91,
       0,    91,     0,    91,     0,    91,     0,    91,     0,    91,
       0,    91,     0,    91,     0,    91,     0,    91,     0,    91,
       0,    91,     0,    91,     0,    91,     0,    91,     0,    91,
       0,    91,     0,    91,     0,   163,     0,   163,     0,   163,
       0,   163,     0,   163,     0,   163,     0,   163,     0,   163,
       0,   163,     0,   163,     0,   163,     0,   163,     0,   163,
       0,   163,     0,   163,     0,   163,     0,   163,     0,   163,
       0,   163,     0,   163,     0,   163,     0,   163,     0,   163,
       0,   163,     0,    19,     0,    63,     0,    63,     0,    63,
       0,    63,     0,    63,     0,    64,     0,    64,     0,    64,
       0,    64,     0,    64,     0,    65,     0,    65,     0,    65,
       0,    65,     0,    65,     0,    66,     0,    66,     0,    66,
       0,    66,     0,    66,     0,    67,     0,    67,     0,    67,
       0,    67,     0,    67,     0,    62,     0,    62,     0,    62,
       0,    62,     0,    62,     0,    68,     0,    68,     0,    68,
       0,    68,     0,    68,     0,   135,     0,   135,     0,   135,
       0,    47,     0,    47,     0,    47,     0,    47,     0,    47,
       0,    49,     0,    49,     0,    49,     0,    49,     0,    49,
       0,    50,     0,    50,     0,    50,     0,    50,     0,    50,
       0,    51,     0,    51,     0,    51,     0,    51,     0,    51,
       0,    52,     0,    52,     0,    52,     0,    52,     0,    52,
       0,    53,     0,    53,     0,    53,     0,    53,     0,    53,
       0,   102,     0,   102,     0,   102,     0,   102,     0,   102,
       0,   102,     0,   102,     0,   102,     0,   102,     0,   102,
       0,   102,     0,   102,     0,   102,     0,   102,     0,   102,
       0,   102,     0,   102,     0,   102,     0,   102,     0,   102,
       0,   102,     0,   102,     0,   107,     0,    54,     0,    54,
       0,    54,     0,    54,     0,    54,     0,    55,     0,    55,
       0,    55,     0,    55,     0,    55,     0,    46,     0,    46,
       0,    46,     0,    46,     0,    46,     0,    48,     0,    48,
       0,    48,     0,    48,     0,    48,     0,    44,     0,    44,
       0,    44,     0,    44,     0,    44,     0,    45,     0,    45,
       0,    45,     0,    45,     0,    45,     0,    40,     0,    40,
       0,    40,     0,    40,     0,    40,     0,    41,     0,    41,
       0,    41,     0,    41,     0,    41,     0,    42,     0,    42,
       0,    42,     0,    42,     0,    42,     0,    43,     0,    43,
       0,    43,     0,    43,     0,    43,     0,   103,     0,   122,
       0,   122,     0,   122,     0,   122,     0,   122,     0,   122,
       0,   122,     0,   122,     0,   122,     0,   122,     0,   122,
       0,   122,     0,   122,     0,   122,     0,   122,     0,   122,
       0,   122,     0,   122,     0,   122,     0,   122,     0,   122,
       0,   122,     0,   122,     0,   122,     0
};



YYSTYPE yylval;

int yynerrs;
int yychar;

enum { YYENOMEM = -2 };

typedef enum { yyok, yyaccept, yyabort, yyerr } YYRESULTTAG;

#define YYCHK(YYE)                              \
  do {                                          \
    YYRESULTTAG yychk_flag = YYE;               \
    if (yychk_flag != yyok)                     \
      return yychk_flag;                        \
  } while (0)

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYMAXDEPTH * sizeof (GLRStackItem)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Minimum number of free items on the stack allowed after an
   allocation.  This is to allow allocation and initialization
   to be completed by functions that call yyexpandGLRStack before the
   stack is expanded, thus insuring that all necessary pointers get
   properly redirected to new data.  */
#define YYHEADROOM 2

#ifndef YYSTACKEXPANDABLE
#  define YYSTACKEXPANDABLE 1
#endif

#if YYSTACKEXPANDABLE
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyexpandGLRStack (Yystack);                       \
  } while (0)
#else
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyMemoryExhausted (Yystack);                      \
  } while (0)
#endif

/** State numbers. */
typedef int yy_state_t;

/** Rule numbers. */
typedef int yyRuleNum;

/** Item references. */
typedef short yyItemNum;

typedef struct yyGLRState yyGLRState;
typedef struct yyGLRStateSet yyGLRStateSet;
typedef struct yySemanticOption yySemanticOption;
typedef union yyGLRStackItem yyGLRStackItem;
typedef struct yyGLRStack yyGLRStack;

struct yyGLRState {
  /** Type tag: always true.  */
  yybool yyisState;
  /** Type tag for yysemantics.  If true, yysval applies, otherwise
   *  yyfirstVal applies.  */
  yybool yyresolved;
  /** Number of corresponding LALR(1) machine state.  */
  yy_state_t yylrState;
  /** Preceding state in this stack */
  yyGLRState* yypred;
  /** Source position of the last token produced by my symbol */
  YYPTRDIFF_T yyposn;
  union {
    /** First in a chain of alternative reductions producing the
     *  nonterminal corresponding to this state, threaded through
     *  yynext.  */
    yySemanticOption* yyfirstVal;
    /** Semantic value for this state.  */
    YYSTYPE yysval;
  } yysemantics;
};

struct yyGLRStateSet {
  yyGLRState** yystates;
  /** During nondeterministic operation, yylookaheadNeeds tracks which
   *  stacks have actually needed the current lookahead.  During deterministic
   *  operation, yylookaheadNeeds[0] is not maintained since it would merely
   *  duplicate yychar != YYEMPTY.  */
  yybool* yylookaheadNeeds;
  YYPTRDIFF_T yysize;
  YYPTRDIFF_T yycapacity;
};

struct yySemanticOption {
  /** Type tag: always false.  */
  yybool yyisState;
  /** Rule number for this reduction */
  yyRuleNum yyrule;
  /** The last RHS state in the list of states to be reduced.  */
  yyGLRState* yystate;
  /** The lookahead for this reduction.  */
  int yyrawchar;
  YYSTYPE yyval;
  /** Next sibling in chain of options.  To facilitate merging,
   *  options are chained in decreasing order by address.  */
  yySemanticOption* yynext;
};

/** Type of the items in the GLR stack.  The yyisState field
 *  indicates which item of the union is valid.  */
union yyGLRStackItem {
  yyGLRState yystate;
  yySemanticOption yyoption;
};

struct yyGLRStack {
  int yyerrState;


  YYJMP_BUF yyexception_buffer;
  yyGLRStackItem* yyitems;
  yyGLRStackItem* yynextFree;
  YYPTRDIFF_T yyspaceLeft;
  yyGLRState* yysplitPoint;
  yyGLRState* yylastDeleted;
  yyGLRStateSet yytops;
};

#if YYSTACKEXPANDABLE
static void yyexpandGLRStack (yyGLRStack* yystackp);
#endif

_Noreturn static void
yyFail (yyGLRStack* yystackp, const char* yymsg)
{
  if (yymsg != YY_NULLPTR)
    yyerror (yymsg);
  YYLONGJMP (yystackp->yyexception_buffer, 1);
}

_Noreturn static void
yyMemoryExhausted (yyGLRStack* yystackp)
{
  YYLONGJMP (yystackp->yyexception_buffer, 2);
}

/** Accessing symbol of state YYSTATE.  */
static inline yysymbol_kind_t
yy_accessing_symbol (yy_state_t yystate)
{
  return YY_CAST (yysymbol_kind_t, yystos[yystate]);
}

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "tpack", "tswitch",
  "tas", "tfor", "tdef", "twith", "tret", "treturn", "tif", "telse",
  "telif", "tfrom", "tnext", "tprop", "timport", "taka", "tthis", "tnode",
  "tin", "tindent", "tdedent", "tnull", "teof", "tnum", "tbool", "tchar",
  "tstr", "tfctor", "tfdtor", "tfget", "tfset", "tfres", "tnormalId",
  "taccessedId", "tconName", "teol", "topDefAssign", "topMinusAssign",
  "topSquareAssign", "topDivideAssign", "topModAssign", "topPowAssign",
  "topLessEqual", "topMoreEqual", "topEqual", "topRefEqual", "topNotEqual",
  "topNotRefEqual", "topPlusAssign", "topSeq", "topSafeNavi", "topUplus",
  "topUminus", "'='", "'&'", "'|'", "'<'", "'>'", "'%'", "'^'", "'+'",
  "'-'", "'*'", "'/'", "'.'", "','", "'('", "')'", "'{'", "'}'", "'['",
  "']'", "';'", "'@'", "':'", "$accept", "tid", "telseBlock", "telifBlock",
  "telifBlocks", "tbranch", "termFor", "tcaseExpr", "tcaseStmt",
  "tcaseIndentBlock", "tswitchExpr", "termIf", "trhsIdExpr",
  "tdefBlockExpr", "tdefexpr", "tconNames", "ttype", "tconAccess",
  "takaStmt", "tcast", "treturnexpr", "trhsIds", "trhslist", "tlhsId",
  "ttuple", "ttuples", "tmap", "tarray", "tseq", "taccess", "tpackAccess",
  "tsafeAccess", "tparam", "tparams", "tfuncRhsList", "tpropexpr",
  "tpropIndentBlock", "tpropBlock", "tgetsetFuncName", "tgetsetList",
  "tgetsetterExpr", "tgetsetterStmt", "tdefOrigin", "tfunclist", "tfunc",
  "tfuncBody", "tctorfunc", "tdtorfunc", "tfuncCall", "texpr", "tblock",
  "tdefBlock", "tpackExpr", "timportExpr", "tfileExpr", "tdefIndentBlock",
  "tindentBlock", "tfile", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#if YYDEBUG

# ifndef YYFPRINTF
#  define YYFPRINTF fprintf
# endif

# define YY_FPRINTF                             \
  YY_IGNORE_USELESS_CAST_BEGIN YY_FPRINTF_

# define YY_FPRINTF_(Args)                      \
  do {                                          \
    YYFPRINTF Args;                             \
    YY_IGNORE_USELESS_CAST_END                  \
  } while (0)

# define YY_DPRINTF                             \
  YY_IGNORE_USELESS_CAST_BEGIN YY_DPRINTF_

# define YY_DPRINTF_(Args)                      \
  do {                                          \
    if (yydebug)                                \
      YYFPRINTF Args;                           \
    YY_IGNORE_USELESS_CAST_END                  \
  } while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif



/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                  \
  do {                                                                  \
    if (yydebug)                                                        \
      {                                                                 \
        YY_FPRINTF ((stderr, "%s ", Title));                            \
        yy_symbol_print (stderr, Kind, Value);        \
        YY_FPRINTF ((stderr, "\n"));                                    \
      }                                                                 \
  } while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;

static void yypstack (yyGLRStack* yystackp, YYPTRDIFF_T yyk)
  YY_ATTRIBUTE_UNUSED;
static void yypdumpstack (yyGLRStack* yystackp)
  YY_ATTRIBUTE_UNUSED;

#else /* !YYDEBUG */

# define YY_DPRINTF(Args) do {} while (yyfalse)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)

#endif /* !YYDEBUG */



/** Fill in YYVSP[YYLOW1 .. YYLOW0-1] from the chain of states starting
 *  at YYVSP[YYLOW0].yystate.yypred.  Leaves YYVSP[YYLOW1].yystate.yypred
 *  containing the pointer to the next state in the chain.  */
static void yyfillin (yyGLRStackItem *, int, int) YY_ATTRIBUTE_UNUSED;
static void
yyfillin (yyGLRStackItem *yyvsp, int yylow0, int yylow1)
{
  int i;
  yyGLRState *s = yyvsp[yylow0].yystate.yypred;
  for (i = yylow0-1; i >= yylow1; i -= 1)
    {
#if YYDEBUG
      yyvsp[i].yystate.yylrState = s->yylrState;
#endif
      yyvsp[i].yystate.yyresolved = s->yyresolved;
      if (s->yyresolved)
        yyvsp[i].yystate.yysemantics.yysval = s->yysemantics.yysval;
      else
        /* The effect of using yysval or yyloc (in an immediate rule) is
         * undefined.  */
        yyvsp[i].yystate.yysemantics.yyfirstVal = YY_NULLPTR;
      s = yyvsp[i].yystate.yypred = s->yypred;
    }
}


/** If yychar is empty, fetch the next token.  */
static inline yysymbol_kind_t
yygetToken (int *yycharp)
{
  yysymbol_kind_t yytoken;
  if (*yycharp == YYEMPTY)
    {
      YY_DPRINTF ((stderr, "Reading a token\n"));
      *yycharp = yylex ();
    }
  if (*yycharp <= YYEOF)
    {
      *yycharp = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YY_DPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (*yycharp);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }
  return yytoken;
}

/* Do nothing if YYNORMAL or if *YYLOW <= YYLOW1.  Otherwise, fill in
 * YYVSP[YYLOW1 .. *YYLOW-1] as in yyfillin and set *YYLOW = YYLOW1.
 * For convenience, always return YYLOW1.  */
static inline int yyfill (yyGLRStackItem *, int *, int, yybool)
     YY_ATTRIBUTE_UNUSED;
static inline int
yyfill (yyGLRStackItem *yyvsp, int *yylow, int yylow1, yybool yynormal)
{
  if (!yynormal && yylow1 < *yylow)
    {
      yyfillin (yyvsp, *yylow, yylow1);
      *yylow = yylow1;
    }
  return yylow1;
}

/** Perform user action for rule number YYN, with RHS length YYRHSLEN,
 *  and top stack item YYVSP.  YYLVALP points to place to put semantic
 *  value ($$), and yylocp points to place for location information
 *  (@$).  Returns yyok for normal return, yyaccept for YYACCEPT,
 *  yyerr for YYERROR, yyabort for YYABORT.  */
static YYRESULTTAG
yyuserAction (yyRuleNum yyn, int yyrhslen, yyGLRStackItem* yyvsp,
              yyGLRStack* yystackp,
              YYSTYPE* yyvalp)
{
  yybool yynormal YY_ATTRIBUTE_UNUSED = yystackp->yysplitPoint == YY_NULLPTR;
  int yylow;
  YY_USE (yyvalp);
  YY_USE (yyrhslen);
# undef yyerrok
# define yyerrok (yystackp->yyerrState = 0)
# undef YYACCEPT
# define YYACCEPT return yyaccept
# undef YYABORT
# define YYABORT return yyabort
# undef YYERROR
# define YYERROR return yyerrok, yyerr
# undef YYRECOVERING
# define YYRECOVERING() (yystackp->yyerrState != 0)
# undef yyclearin
# define yyclearin (yychar = YYEMPTY)
# undef YYFILL
# define YYFILL(N) yyfill (yyvsp, &yylow, (N), yynormal)
# undef YYBACKUP
# define YYBACKUP(Token, Value)                                              \
  return yyerror (YY_("syntax error: cannot back up")),     \
         yyerrok, yyerr

  yylow = 1;
  if (yyrhslen == 0)
    *yyvalp = yyval_default;
  else
    *yyvalp = yyvsp[YYFILL (1-yyrhslen)].yystate.yysemantics.yysval;
  switch (yyn)
    {
  case 2: /* tid: tnormalId  */
#line 87 "wrdcBison.cpp"
                        { ((*yyvalp).strVal) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.strVal); }
#line 1901 "wrdcBison.tab.cpp"
    break;

  case 3: /* tid: taccessedId  */
#line 88 "wrdcBison.cpp"
                          { ((*yyvalp).strVal) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.strVal); }
#line 1907 "wrdcBison.tab.cpp"
    break;

  case 4: /* telseBlock: teol telse tindentBlock  */
#line 91 "wrdcBison.cpp"
                                      {
                ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node);
            }
#line 1915 "wrdcBison.tab.cpp"
    break;

  case 5: /* telifBlock: teol telif tbranch  */
#line 95 "wrdcBison.cpp"
                                 {
                ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node);
            }
#line 1923 "wrdcBison.tab.cpp"
    break;

  case 6: /* telifBlocks: telifBlock  */
#line 98 "wrdcBison.cpp"
                         {
                vector<Branch*>* ret = new vector<Branch*>;
                ret->push_back((Branch*) (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
                ((*yyvalp).nodes) = ret;
            }
#line 1933 "wrdcBison.tab.cpp"
    break;

  case 7: /* telifBlocks: telifBlocks telifBlock  */
#line 103 "wrdcBison.cpp"
                                     {
                vector<Branch*>* blk = (vector<Branch*>*) (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nodes);
                blk->push_back((Branch*) (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
                ((*yyvalp).nodes) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nodes);
            }
#line 1943 "wrdcBison.tab.cpp"
    break;

  case 8: /* tbranch: trhsIdExpr tindentBlock  */
#line 109 "wrdcBison.cpp"
                                      {
                ((*yyvalp).node) = new Branch((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node), (Container*) (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 1951 "wrdcBison.tab.cpp"
    break;

  case 9: /* termFor: tfor tid tin trhsIdExpr tindentBlock  */
#line 113 "wrdcBison.cpp"
                                                   {
                ((*yyvalp).node) = new For(new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.strVal)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node), (Container*) (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 1959 "wrdcBison.tab.cpp"
    break;

  case 10: /* termFor: tfor trhsIdExpr tindentBlock  */
#line 116 "wrdcBison.cpp"
                                           {
                ((*yyvalp).node) = new For((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node), (Container*) (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 1967 "wrdcBison.tab.cpp"
    break;

  case 11: /* tcaseExpr: trhsIdExpr  */
#line 121 "wrdcBison.cpp"
                         {
                Block* ret = new Block();
                if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node))
                    ret->add((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
                ((*yyvalp).node) = ret;
            }
#line 1978 "wrdcBison.tab.cpp"
    break;

  case 12: /* tcaseExpr: tcaseExpr ',' trhsIdExpr  */
#line 127 "wrdcBison.cpp"
                                       {
                Block* ret = (Block*) ((*yyvalp).node);
                if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node))
                    ret->add((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
                ((*yyvalp).node) = ret;
            }
#line 1989 "wrdcBison.tab.cpp"
    break;

  case 13: /* tcaseStmt: tcaseExpr tindentBlock  */
#line 135 "wrdcBison.cpp"
                                     { ((*yyvalp).node) = new CaseBlock((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 1995 "wrdcBison.tab.cpp"
    break;

  case 14: /* tcaseStmt: telse tindentBlock  */
#line 136 "wrdcBison.cpp"
                                 { ((*yyvalp).node) = new CaseBlock(new Str("else"), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2001 "wrdcBison.tab.cpp"
    break;

  case 15: /* tcaseIndentBlock: tcaseStmt  */
#line 139 "wrdcBison.cpp"
                             {
                Block* ret = new Block();
                if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node))
                    ret->add((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
                ((*yyvalp).node) = ret;
            }
#line 2012 "wrdcBison.tab.cpp"
    break;

  case 16: /* tcaseIndentBlock: tcaseIndentBlock tcaseStmt  */
#line 145 "wrdcBison.cpp"
                                         {
                Block* ret = (Block*) (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node);
                if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node))
                    ret->add((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
                ((*yyvalp).node) = ret;
            }
#line 2023 "wrdcBison.tab.cpp"
    break;

  case 17: /* tswitchExpr: tswitch tlhsId teol tindent tcaseIndentBlock tdedent  */
#line 153 "wrdcBison.cpp"
                                                                   {
                ((*yyvalp).node) = new SwitchExpr((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node));
            }
#line 2031 "wrdcBison.tab.cpp"
    break;

  case 18: /* termIf: tif tbranch telifBlocks telseBlock  */
#line 158 "wrdcBison.cpp"
                                                 {
                ((*yyvalp).node) = new If((Branch*) (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), (vector<Branch*>*) (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.nodes), (Block*) (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 2039 "wrdcBison.tab.cpp"
    break;

  case 19: /* termIf: tif tbranch telifBlocks  */
#line 161 "wrdcBison.cpp"
                                      {
                ((*yyvalp).node) = new If((Branch*) (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node), (vector<Branch*>*) (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.nodes), 0);
            }
#line 2047 "wrdcBison.tab.cpp"
    break;

  case 20: /* termIf: tif tbranch telseBlock  */
#line 164 "wrdcBison.cpp"
                                     {
                ((*yyvalp).node) = new If((Branch*) (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node), (Block*) (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 2055 "wrdcBison.tab.cpp"
    break;

  case 21: /* termIf: tif tbranch  */
#line 167 "wrdcBison.cpp"
                          {
                ((*yyvalp).node) = new If((Branch*) (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 2063 "wrdcBison.tab.cpp"
    break;

  case 22: /* trhsIdExpr: tbool  */
#line 176 "wrdcBison.cpp"
                    { ((*yyvalp).node) = new Bool((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.boolVal)); }
#line 2069 "wrdcBison.tab.cpp"
    break;

  case 23: /* trhsIdExpr: tnum  */
#line 177 "wrdcBison.cpp"
                   { ((*yyvalp).node) = new Float((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.floatVal)); }
#line 2075 "wrdcBison.tab.cpp"
    break;

  case 24: /* trhsIdExpr: tstr  */
#line 178 "wrdcBison.cpp"
                   { ((*yyvalp).node) = new Str((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.strVal)); }
#line 2081 "wrdcBison.tab.cpp"
    break;

  case 25: /* trhsIdExpr: tchar  */
#line 179 "wrdcBison.cpp"
                    { ((*yyvalp).node) = new Char((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.charVal)); }
#line 2087 "wrdcBison.tab.cpp"
    break;

  case 26: /* trhsIdExpr: tswitchExpr  */
#line 180 "wrdcBison.cpp"
                          { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2093 "wrdcBison.tab.cpp"
    break;

  case 27: /* trhsIdExpr: tarray  */
#line 181 "wrdcBison.cpp"
                     { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2099 "wrdcBison.tab.cpp"
    break;

  case 28: /* trhsIdExpr: tnormalId  */
#line 182 "wrdcBison.cpp"
                        { ((*yyvalp).node) = new Str((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.strVal)); }
#line 2105 "wrdcBison.tab.cpp"
    break;

  case 29: /* trhsIdExpr: tmap  */
#line 183 "wrdcBison.cpp"
                   { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2111 "wrdcBison.tab.cpp"
    break;

  case 30: /* trhsIdExpr: tdefexpr  */
#line 184 "wrdcBison.cpp"
                       { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2117 "wrdcBison.tab.cpp"
    break;

  case 31: /* trhsIdExpr: tcast  */
#line 185 "wrdcBison.cpp"
                             { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2123 "wrdcBison.tab.cpp"
    break;

  case 32: /* trhsIdExpr: tsafeAccess  */
#line 186 "wrdcBison.cpp"
                                   { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2129 "wrdcBison.tab.cpp"
    break;

  case 33: /* trhsIdExpr: taccess  */
#line 187 "wrdcBison.cpp"
                               { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2135 "wrdcBison.tab.cpp"
    break;

  case 34: /* trhsIdExpr: '(' trhsIdExpr ')'  */
#line 188 "wrdcBison.cpp"
                                 { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node); }
#line 2141 "wrdcBison.tab.cpp"
    break;

  case 35: /* trhsIdExpr: topUplus trhsIdExpr  */
#line 190 "wrdcBison.cpp"
                                           { ((*yyvalp).node) = new UPre(new Id("++"), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2147 "wrdcBison.tab.cpp"
    break;

  case 36: /* trhsIdExpr: trhsIdExpr topUplus  */
#line 191 "wrdcBison.cpp"
                                           { ((*yyvalp).node) = new UPost(new Id("++"), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node)); }
#line 2153 "wrdcBison.tab.cpp"
    break;

  case 37: /* trhsIdExpr: topUminus trhsIdExpr  */
#line 192 "wrdcBison.cpp"
                                            { ((*yyvalp).node) = new UPre(new Id("--"), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2159 "wrdcBison.tab.cpp"
    break;

  case 38: /* trhsIdExpr: trhsIdExpr topUminus  */
#line 193 "wrdcBison.cpp"
                                            { ((*yyvalp).node) = new UPost(new Id("--"), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node)); }
#line 2165 "wrdcBison.tab.cpp"
    break;

  case 39: /* trhsIdExpr: tconAccess  */
#line 195 "wrdcBison.cpp"
                                  { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2171 "wrdcBison.tab.cpp"
    break;

  case 40: /* trhsIdExpr: trhsIdExpr '+' trhsIdExpr  */
#line 197 "wrdcBison.cpp"
                                                 { ((*yyvalp).node) = new Plus((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2177 "wrdcBison.tab.cpp"
    break;

  case 41: /* trhsIdExpr: trhsIdExpr '-' trhsIdExpr  */
#line 198 "wrdcBison.cpp"
                                                 { ((*yyvalp).node) = new Minus((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2183 "wrdcBison.tab.cpp"
    break;

  case 42: /* trhsIdExpr: trhsIdExpr '*' trhsIdExpr  */
#line 199 "wrdcBison.cpp"
                                                 { ((*yyvalp).node) = new Square((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2189 "wrdcBison.tab.cpp"
    break;

  case 43: /* trhsIdExpr: trhsIdExpr '/' trhsIdExpr  */
#line 200 "wrdcBison.cpp"
                                                 { ((*yyvalp).node) = new Divide((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2195 "wrdcBison.tab.cpp"
    break;

  case 44: /* trhsIdExpr: trhsIdExpr '%' trhsIdExpr  */
#line 201 "wrdcBison.cpp"
                                                 { ((*yyvalp).node) = new Moduler((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2201 "wrdcBison.tab.cpp"
    break;

  case 45: /* trhsIdExpr: trhsIdExpr '^' trhsIdExpr  */
#line 202 "wrdcBison.cpp"
                                                 { ((*yyvalp).node) = new Power((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2207 "wrdcBison.tab.cpp"
    break;

  case 46: /* trhsIdExpr: trhsIdExpr '<' trhsIdExpr  */
#line 203 "wrdcBison.cpp"
                                                 { ((*yyvalp).node) = new Less((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2213 "wrdcBison.tab.cpp"
    break;

  case 47: /* trhsIdExpr: trhsIdExpr topLessEqual trhsIdExpr  */
#line 204 "wrdcBison.cpp"
                                                          { ((*yyvalp).node) = new LessEqual((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2219 "wrdcBison.tab.cpp"
    break;

  case 48: /* trhsIdExpr: trhsIdExpr '>' trhsIdExpr  */
#line 205 "wrdcBison.cpp"
                                                 { ((*yyvalp).node) = new More((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2225 "wrdcBison.tab.cpp"
    break;

  case 49: /* trhsIdExpr: trhsIdExpr topMoreEqual trhsIdExpr  */
#line 206 "wrdcBison.cpp"
                                                          { ((*yyvalp).node) = new MoreEqual((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2231 "wrdcBison.tab.cpp"
    break;

  case 50: /* trhsIdExpr: trhsIdExpr topEqual trhsIdExpr  */
#line 207 "wrdcBison.cpp"
                                                      { ((*yyvalp).node) = new Equal((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2237 "wrdcBison.tab.cpp"
    break;

  case 51: /* trhsIdExpr: trhsIdExpr topRefEqual trhsIdExpr  */
#line 208 "wrdcBison.cpp"
                                                         { ((*yyvalp).node) = new RefEqual((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2243 "wrdcBison.tab.cpp"
    break;

  case 52: /* trhsIdExpr: trhsIdExpr topNotEqual trhsIdExpr  */
#line 209 "wrdcBison.cpp"
                                                         { ((*yyvalp).node) = new NotEqual((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2249 "wrdcBison.tab.cpp"
    break;

  case 53: /* trhsIdExpr: trhsIdExpr topNotRefEqual trhsIdExpr  */
#line 210 "wrdcBison.cpp"
                                                            { ((*yyvalp).node) = new NotRefEqual((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2255 "wrdcBison.tab.cpp"
    break;

  case 54: /* trhsIdExpr: trhsIdExpr '&' trhsIdExpr  */
#line 211 "wrdcBison.cpp"
                                                 { ((*yyvalp).node) = new And((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2261 "wrdcBison.tab.cpp"
    break;

  case 55: /* trhsIdExpr: trhsIdExpr '|' trhsIdExpr  */
#line 212 "wrdcBison.cpp"
                                                 { ((*yyvalp).node) = new Or((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2267 "wrdcBison.tab.cpp"
    break;

  case 56: /* trhsIdExpr: termFor  */
#line 214 "wrdcBison.cpp"
                               { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2273 "wrdcBison.tab.cpp"
    break;

  case 57: /* trhsIdExpr: tseq  */
#line 215 "wrdcBison.cpp"
                            { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2279 "wrdcBison.tab.cpp"
    break;

  case 58: /* trhsIdExpr: twith tnormalId tindentBlock  */
#line 217 "wrdcBison.cpp"
                                           {
                ((*yyvalp).node) = new With(new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.strVal)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 2287 "wrdcBison.tab.cpp"
    break;

  case 59: /* trhsIdExpr: twith tindentBlock  */
#line 220 "wrdcBison.cpp"
                                 {
                ((*yyvalp).node) = new With(0, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 2295 "wrdcBison.tab.cpp"
    break;

  case 60: /* trhsIdExpr: termIf  */
#line 225 "wrdcBison.cpp"
                     { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2301 "wrdcBison.tab.cpp"
    break;

  case 61: /* trhsIdExpr: tfuncCall  */
#line 226 "wrdcBison.cpp"
                        { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2307 "wrdcBison.tab.cpp"
    break;

  case 62: /* trhsIdExpr: tnormalId topPlusAssign trhsIdExpr  */
#line 228 "wrdcBison.cpp"
                                                          { ((*yyvalp).node) = new PlusAssign(new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.strVal)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2313 "wrdcBison.tab.cpp"
    break;

  case 63: /* trhsIdExpr: tnormalId topMinusAssign trhsIdExpr  */
#line 229 "wrdcBison.cpp"
                                                           { ((*yyvalp).node) = new MinusAssign(new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.strVal)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2319 "wrdcBison.tab.cpp"
    break;

  case 64: /* trhsIdExpr: tnormalId topSquareAssign trhsIdExpr  */
#line 230 "wrdcBison.cpp"
                                                            { ((*yyvalp).node) = new SquareAssign(new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.strVal)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2325 "wrdcBison.tab.cpp"
    break;

  case 65: /* trhsIdExpr: tnormalId topDivideAssign trhsIdExpr  */
#line 231 "wrdcBison.cpp"
                                                            { ((*yyvalp).node) = new DivideAssign(new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.strVal)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2331 "wrdcBison.tab.cpp"
    break;

  case 66: /* trhsIdExpr: tnormalId topModAssign trhsIdExpr  */
#line 232 "wrdcBison.cpp"
                                                         { ((*yyvalp).node) = new ModulerAssign(new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.strVal)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2337 "wrdcBison.tab.cpp"
    break;

  case 67: /* trhsIdExpr: tnormalId topPowAssign trhsIdExpr  */
#line 233 "wrdcBison.cpp"
                                                         { ((*yyvalp).node) = new PowAssign(new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.strVal)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2343 "wrdcBison.tab.cpp"
    break;

  case 68: /* trhsIdExpr: tnormalId '=' trhsIdExpr  */
#line 234 "wrdcBison.cpp"
                                                { ((*yyvalp).node) = new Assign(new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.strVal)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2349 "wrdcBison.tab.cpp"
    break;

  case 69: /* tdefBlockExpr: tfunc  */
#line 237 "wrdcBison.cpp"
                      { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2355 "wrdcBison.tab.cpp"
    break;

  case 70: /* tdefBlockExpr: tdefOrigin  */
#line 238 "wrdcBison.cpp"
                             { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2361 "wrdcBison.tab.cpp"
    break;

  case 71: /* tdefBlockExpr: tpropexpr  */
#line 239 "wrdcBison.cpp"
                            { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2367 "wrdcBison.tab.cpp"
    break;

  case 72: /* tdefBlockExpr: tctorfunc  */
#line 240 "wrdcBison.cpp"
                            { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2373 "wrdcBison.tab.cpp"
    break;

  case 73: /* tdefBlockExpr: tdtorfunc  */
#line 241 "wrdcBison.cpp"
                            { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2379 "wrdcBison.tab.cpp"
    break;

  case 74: /* tdefexpr: tid topDefAssign trhsIdExpr  */
#line 244 "wrdcBison.cpp"
                                          { ((*yyvalp).node) = new DefAssign(new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.strVal)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2385 "wrdcBison.tab.cpp"
    break;

  case 75: /* tdefexpr: tid ttype topDefAssign trhsIdExpr  */
#line 245 "wrdcBison.cpp"
                                                { ((*yyvalp).node) = new DefAssign(new Param((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.strVal))), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2391 "wrdcBison.tab.cpp"
    break;

  case 76: /* tdefexpr: tid ttype topDefAssign '{' '}'  */
#line 246 "wrdcBison.cpp"
                                             { ((*yyvalp).node) = new DefAssign(new Param((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.node), new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.strVal))), new Array()); }
#line 2397 "wrdcBison.tab.cpp"
    break;

  case 77: /* tdefexpr: tparam  */
#line 247 "wrdcBison.cpp"
                     { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2403 "wrdcBison.tab.cpp"
    break;

  case 78: /* tdefexpr: takaStmt  */
#line 248 "wrdcBison.cpp"
                       { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2409 "wrdcBison.tab.cpp"
    break;

  case 79: /* tdefexpr: tdefBlockExpr  */
#line 249 "wrdcBison.cpp"
                            { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2415 "wrdcBison.tab.cpp"
    break;

  case 80: /* tconNames: tconName '{' '}'  */
#line 252 "wrdcBison.cpp"
                               {
                ((*yyvalp).node) = new Origin(new Id(string((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.strVal)) + "{}"));
            }
#line 2423 "wrdcBison.tab.cpp"
    break;

  case 81: /* tconNames: tconNames '{' '}'  */
#line 255 "wrdcBison.cpp"
                                {
                ((*yyvalp).node) = new Origin(new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node)->print() + "{}"));
            }
#line 2431 "wrdcBison.tab.cpp"
    break;

  case 82: /* tconNames: tconName '{' ttype '}'  */
#line 258 "wrdcBison.cpp"
                                     {
                ((*yyvalp).node) = new MapOrigin(new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.strVal)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node));
            }
#line 2439 "wrdcBison.tab.cpp"
    break;

  case 83: /* tconNames: tconNames '{' ttype '}'  */
#line 261 "wrdcBison.cpp"
                                      {
                ((*yyvalp).node) = new MapOrigin((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node));
            }
#line 2447 "wrdcBison.tab.cpp"
    break;

  case 84: /* ttype: tlhsId  */
#line 266 "wrdcBison.cpp"
                     { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2453 "wrdcBison.tab.cpp"
    break;

  case 85: /* ttype: tconNames  */
#line 267 "wrdcBison.cpp"
                        { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2459 "wrdcBison.tab.cpp"
    break;

  case 86: /* tconAccess: tlhsId '[' trhsIdExpr ']'  */
#line 270 "wrdcBison.cpp"
                                        {
                ((*yyvalp).node) = new ContainerAccess((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node));
            }
#line 2467 "wrdcBison.tab.cpp"
    break;

  case 87: /* takaStmt: tlhsId taka tnormalId  */
#line 275 "wrdcBison.cpp"
                                    {
                ((*yyvalp).node) = new AkaStmt((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.strVal)));
            }
#line 2475 "wrdcBison.tab.cpp"
    break;

  case 88: /* takaStmt: tfunc taka tnormalId  */
#line 278 "wrdcBison.cpp"
                                   {
                ((*yyvalp).node) = new AkaStmt((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.strVal)));
            }
#line 2483 "wrdcBison.tab.cpp"
    break;

  case 89: /* tcast: trhsIdExpr tas ttype  */
#line 283 "wrdcBison.cpp"
                                   {
                ((*yyvalp).node) = new Cast((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node));
            }
#line 2491 "wrdcBison.tab.cpp"
    break;

  case 90: /* treturnexpr: tret trhsIdExpr  */
#line 288 "wrdcBison.cpp"
                              { ((*yyvalp).node) = new Return("ret", (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2497 "wrdcBison.tab.cpp"
    break;

  case 91: /* treturnexpr: treturn trhsIdExpr  */
#line 289 "wrdcBison.cpp"
                                 { ((*yyvalp).node) = new Return("return", (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2503 "wrdcBison.tab.cpp"
    break;

  case 92: /* trhsIds: trhsIdExpr ',' trhsIdExpr  */
#line 293 "wrdcBison.cpp"
                                        {
                Args* ret = new Args();
                ret->add((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node));
                ret->add((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
                ((*yyvalp).node) = ret;
            }
#line 2514 "wrdcBison.tab.cpp"
    break;

  case 93: /* trhsIds: trhsIds ',' trhsIdExpr  */
#line 299 "wrdcBison.cpp"
                                     {
                Args* ret = (Args*) (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node);
                ret->add((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
                ((*yyvalp).node) = ret;
            }
#line 2524 "wrdcBison.tab.cpp"
    break;

  case 94: /* trhslist: '(' trhsIds ')'  */
#line 305 "wrdcBison.cpp"
                              { //  " "를 쓰면 안된다.
                ((*yyvalp).node) = new List((Args*) (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node));
            }
#line 2532 "wrdcBison.tab.cpp"
    break;

  case 95: /* tlhsId: tnormalId  */
#line 310 "wrdcBison.cpp"
                        { ((*yyvalp).node) = new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.strVal)); }
#line 2538 "wrdcBison.tab.cpp"
    break;

  case 96: /* tlhsId: tpackAccess  */
#line 311 "wrdcBison.cpp"
                          { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2544 "wrdcBison.tab.cpp"
    break;

  case 97: /* ttuple: trhsIdExpr ';' trhsIdExpr  */
#line 314 "wrdcBison.cpp"
                                        {
                ((*yyvalp).node) = new Tuple((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 2552 "wrdcBison.tab.cpp"
    break;

  case 98: /* ttuples: ttuple  */
#line 318 "wrdcBison.cpp"
                     {
                Args* ret = new Args();
                ret->add((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
                ((*yyvalp).node) = ret;
            }
#line 2562 "wrdcBison.tab.cpp"
    break;

  case 99: /* ttuples: ttuples ',' ttuple  */
#line 323 "wrdcBison.cpp"
                                 {
                Args* ret = (Args*) (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node);
                ret->add((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
                ((*yyvalp).node) = ret;
            }
#line 2572 "wrdcBison.tab.cpp"
    break;

  case 100: /* tmap: '{' ttuples '}'  */
#line 330 "wrdcBison.cpp"
                              {
                ((*yyvalp).node) = new Array((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node));
            }
#line 2580 "wrdcBison.tab.cpp"
    break;

  case 101: /* tarray: '{' trhsIds '}'  */
#line 335 "wrdcBison.cpp"
                              {
                ((*yyvalp).node) = new Array((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node));
            }
#line 2588 "wrdcBison.tab.cpp"
    break;

  case 102: /* tseq: trhsIdExpr topSeq trhsIdExpr  */
#line 340 "wrdcBison.cpp"
                                           {
                ((*yyvalp).node) = new Sequence((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 2596 "wrdcBison.tab.cpp"
    break;

  case 103: /* taccess: trhsIdExpr '.' tnormalId  */
#line 344 "wrdcBison.cpp"
                                       { ((*yyvalp).node) = new Access((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.strVal))); }
#line 2602 "wrdcBison.tab.cpp"
    break;

  case 104: /* taccess: trhsIdExpr '.' tfuncCall  */
#line 345 "wrdcBison.cpp"
                                       { ((*yyvalp).node) = new Access((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2608 "wrdcBison.tab.cpp"
    break;

  case 105: /* tpackAccess: tlhsId '.' tnormalId  */
#line 348 "wrdcBison.cpp"
                                   { ((*yyvalp).node) = new Access((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.strVal))); }
#line 2614 "wrdcBison.tab.cpp"
    break;

  case 106: /* tpackAccess: tlhsId '.' tfuncCall  */
#line 349 "wrdcBison.cpp"
                                   { ((*yyvalp).node) = new Access((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2620 "wrdcBison.tab.cpp"
    break;

  case 107: /* tsafeAccess: trhsIdExpr topSafeNavi tnormalId  */
#line 352 "wrdcBison.cpp"
                                               { ((*yyvalp).node) = new SafeAccess((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.strVal))); }
#line 2626 "wrdcBison.tab.cpp"
    break;

  case 108: /* tsafeAccess: trhsIdExpr topSafeNavi tfuncCall  */
#line 353 "wrdcBison.cpp"
                                               { ((*yyvalp).node) = new SafeAccess((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2632 "wrdcBison.tab.cpp"
    break;

  case 109: /* tparam: tid ttype  */
#line 356 "wrdcBison.cpp"
                        {
                ((*yyvalp).node) = new Param((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node), new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.strVal)));
            }
#line 2640 "wrdcBison.tab.cpp"
    break;

  case 110: /* tparam: '@' tid  */
#line 359 "wrdcBison.cpp"
                      {
                ((*yyvalp).node) = new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.strVal));
            }
#line 2648 "wrdcBison.tab.cpp"
    break;

  case 111: /* tparams: tparam  */
#line 364 "wrdcBison.cpp"
                     {
                Args* ret = new Args();
                ret->add((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
                ((*yyvalp).node) = ret;
            }
#line 2658 "wrdcBison.tab.cpp"
    break;

  case 112: /* tparams: tparams ',' tparam  */
#line 369 "wrdcBison.cpp"
                                 {
                Args* ret = (Args*) (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node);
                ret->add((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
                ((*yyvalp).node) = ret;
            }
#line 2668 "wrdcBison.tab.cpp"
    break;

  case 113: /* tfuncRhsList: trhslist  */
#line 376 "wrdcBison.cpp"
                       { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2674 "wrdcBison.tab.cpp"
    break;

  case 114: /* tfuncRhsList: '(' ')'  */
#line 377 "wrdcBison.cpp"
                      { ((*yyvalp).node) = new List(); }
#line 2680 "wrdcBison.tab.cpp"
    break;

  case 115: /* tfuncRhsList: '(' trhsIdExpr ')'  */
#line 378 "wrdcBison.cpp"
                                 {
                List* ret = new List();
                Args* args = new Args();
                args->add((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node));
                ret->add(args);
                ((*yyvalp).node) = ret;
            }
#line 2692 "wrdcBison.tab.cpp"
    break;

  case 116: /* tpropexpr: tprop tid tfrom trhsIdExpr tpropIndentBlock  */
#line 388 "wrdcBison.cpp"
                                                          {
                ((*yyvalp).node) = new Prop(new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.strVal)), 0, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 2700 "wrdcBison.tab.cpp"
    break;

  case 117: /* tpropexpr: tprop tid tfuncRhsList tfrom trhsIdExpr tpropIndentBlock  */
#line 391 "wrdcBison.cpp"
                                                                       {
                ((*yyvalp).node) = new Prop(new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.strVal)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 2708 "wrdcBison.tab.cpp"
    break;

  case 118: /* tpropexpr: tprop tfrom trhsIdExpr tpropIndentBlock  */
#line 394 "wrdcBison.cpp"
                                                      {
                ((*yyvalp).node) = new Prop(0, 0, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 2716 "wrdcBison.tab.cpp"
    break;

  case 119: /* tpropexpr: tprop tfuncRhsList tfrom trhsIdExpr tpropIndentBlock  */
#line 397 "wrdcBison.cpp"
                                                                   {
                ((*yyvalp).node) = new Prop(0, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 2724 "wrdcBison.tab.cpp"
    break;

  case 120: /* tpropIndentBlock: teol tindent tpropBlock tdedent  */
#line 401 "wrdcBison.cpp"
                                                  { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node); }
#line 2730 "wrdcBison.tab.cpp"
    break;

  case 121: /* tpropIndentBlock: ':' tgetsetterExpr  */
#line 402 "wrdcBison.cpp"
                                 { ((*yyvalp).node) = new InlineStmt((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 2736 "wrdcBison.tab.cpp"
    break;

  case 122: /* tpropIndentBlock: %empty  */
#line 403 "wrdcBison.cpp"
              { ((*yyvalp).node) = 0; }
#line 2742 "wrdcBison.tab.cpp"
    break;

  case 123: /* tpropBlock: tgetsetterStmt  */
#line 405 "wrdcBison.cpp"
                             {
                Block* ret = new Block();
                ret->add((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
                ((*yyvalp).node) = ret;
            }
#line 2752 "wrdcBison.tab.cpp"
    break;

  case 124: /* tpropBlock: tpropBlock tgetsetterStmt  */
#line 410 "wrdcBison.cpp"
                                        {
                Block* ret = (Block*) (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node);
                ret->add((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
                ((*yyvalp).node) = ret;
            }
#line 2762 "wrdcBison.tab.cpp"
    break;

  case 125: /* tgetsetFuncName: tfget  */
#line 417 "wrdcBison.cpp"
                        { ((*yyvalp).node) = new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.strVal)); }
#line 2768 "wrdcBison.tab.cpp"
    break;

  case 126: /* tgetsetFuncName: tfset  */
#line 418 "wrdcBison.cpp"
                    { ((*yyvalp).node) = new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.strVal)); }
#line 2774 "wrdcBison.tab.cpp"
    break;

  case 127: /* tgetsetList: tfunclist  */
#line 420 "wrdcBison.cpp"
                        { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2780 "wrdcBison.tab.cpp"
    break;

  case 128: /* tgetsetList: %empty  */
#line 421 "wrdcBison.cpp"
              { ((*yyvalp).node) = 0; }
#line 2786 "wrdcBison.tab.cpp"
    break;

  case 129: /* tgetsetterExpr: tgetsetFuncName tgetsetList tindentBlock  */
#line 424 "wrdcBison.cpp"
                                                         {
                ((*yyvalp).node) = new Func(0, 0, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node), 0, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 2794 "wrdcBison.tab.cpp"
    break;

  case 130: /* tgetsetterStmt: tgetsetterExpr teol  */
#line 428 "wrdcBison.cpp"
                                    { ((*yyvalp).node) = new Stmt((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node)); }
#line 2800 "wrdcBison.tab.cpp"
    break;

  case 131: /* tdefOrigin: tdef tid tdefIndentBlock  */
#line 431 "wrdcBison.cpp"
                                       {
                ((*yyvalp).node) = new Def(new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.strVal)), 0, 0, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 2808 "wrdcBison.tab.cpp"
    break;

  case 132: /* tdefOrigin: tdef tid tfuncRhsList tdefIndentBlock  */
#line 434 "wrdcBison.cpp"
                                                    {
                ((*yyvalp).node) = new Def(new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.strVal)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node), 0, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 2816 "wrdcBison.tab.cpp"
    break;

  case 133: /* tdefOrigin: tdef tid tfuncRhsList tfrom trhsIdExpr tdefIndentBlock  */
#line 437 "wrdcBison.cpp"
                                                                     {
                ((*yyvalp).node) = new Def(new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval.strVal)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 2824 "wrdcBison.tab.cpp"
    break;

  case 134: /* tdefOrigin: tdef tid tfrom trhsIdExpr tdefIndentBlock  */
#line 440 "wrdcBison.cpp"
                                                        {
                ((*yyvalp).node) = new Def(new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.strVal)), 0, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 2832 "wrdcBison.tab.cpp"
    break;

  case 135: /* tfunclist: '(' ')'  */
#line 445 "wrdcBison.cpp"
                      { ((*yyvalp).node) = 0; }
#line 2838 "wrdcBison.tab.cpp"
    break;

  case 136: /* tfunclist: '(' tparams ')'  */
#line 446 "wrdcBison.cpp"
                              { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node); }
#line 2844 "wrdcBison.tab.cpp"
    break;

  case 137: /* tfunc: tid tfunclist ttype tfuncBody  */
#line 449 "wrdcBison.cpp"
                                            {
                ((*yyvalp).node) = new Func(0, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node), new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval.strVal)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), 0, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 2852 "wrdcBison.tab.cpp"
    break;

  case 138: /* tfunc: tas tfunclist ttype tfuncBody  */
#line 452 "wrdcBison.cpp"
                                            {
                ((*yyvalp).node) = new Func(0, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node), new Id("as"), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), 0, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 2860 "wrdcBison.tab.cpp"
    break;

  case 139: /* tfunc: tid tfunclist tfuncBody  */
#line 455 "wrdcBison.cpp"
                                      {
                ((*yyvalp).node) = new Func(0, 0, new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.strVal)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node), 0, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 2868 "wrdcBison.tab.cpp"
    break;

  case 140: /* tfunc: tfunclist ttype tfuncBody  */
#line 458 "wrdcBison.cpp"
                                        {
                ((*yyvalp).node) = new Func(0, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node), new Id(""), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), 0, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 2876 "wrdcBison.tab.cpp"
    break;

  case 141: /* tfunc: tfunclist tfuncBody  */
#line 461 "wrdcBison.cpp"
                                  {
                ((*yyvalp).node) = new Func(0, 0, new Id(""), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node), 0, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 2884 "wrdcBison.tab.cpp"
    break;

  case 142: /* tfuncBody: tindentBlock  */
#line 466 "wrdcBison.cpp"
                           { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2890 "wrdcBison.tab.cpp"
    break;

  case 143: /* tfuncBody: '=' tnull  */
#line 467 "wrdcBison.cpp"
                        { ((*yyvalp).node) = new Str(" = null"); }
#line 2896 "wrdcBison.tab.cpp"
    break;

  case 144: /* tctorfunc: tfctor tfunclist tindentBlock  */
#line 470 "wrdcBison.cpp"
                                            {
                ((*yyvalp).node) = new Func(0, 0, new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.strVal)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node), 0, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 2904 "wrdcBison.tab.cpp"
    break;

  case 145: /* tdtorfunc: tfdtor tfunclist tindentBlock  */
#line 475 "wrdcBison.cpp"
                                            {
                ((*yyvalp).node) = new Func(0, 0, new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.strVal)), (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node), 0, (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 2912 "wrdcBison.tab.cpp"
    break;

  case 146: /* tfuncCall: tid tfuncRhsList  */
#line 480 "wrdcBison.cpp"
                               {
                ((*yyvalp).node) = new FuncCall(new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.strVal)), (List*) (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 2920 "wrdcBison.tab.cpp"
    break;

  case 147: /* texpr: trhsIdExpr  */
#line 485 "wrdcBison.cpp"
                         { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2926 "wrdcBison.tab.cpp"
    break;

  case 148: /* texpr: treturnexpr  */
#line 486 "wrdcBison.cpp"
                          { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 2932 "wrdcBison.tab.cpp"
    break;

  case 149: /* texpr: tnext  */
#line 487 "wrdcBison.cpp"
                    { ((*yyvalp).node) = new Next(); }
#line 2938 "wrdcBison.tab.cpp"
    break;

  case 150: /* tblock: texpr  */
#line 490 "wrdcBison.cpp"
                    {
                Block* ret = new Block();
                if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node))
                    ret->add((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
                ((*yyvalp).node) = ret;
            }
#line 2949 "wrdcBison.tab.cpp"
    break;

  case 151: /* tblock: tblock teol texpr  */
#line 496 "wrdcBison.cpp"
                                {
                Block* ret = (Block*) (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node);
                if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node))
                    ret->add((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
                ((*yyvalp).node) = ret;
            }
#line 2960 "wrdcBison.tab.cpp"
    break;

  case 152: /* tblock: tblock teof  */
#line 502 "wrdcBison.cpp"
                          {
                ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node);
            }
#line 2968 "wrdcBison.tab.cpp"
    break;

  case 153: /* tdefBlock: tdefexpr  */
#line 507 "wrdcBison.cpp"
                       {
                Block* ret = new Block();
                if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node))
                    ret->add(new Stmt((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)));
                ((*yyvalp).node) = ret;
            }
#line 2979 "wrdcBison.tab.cpp"
    break;

  case 154: /* tdefBlock: tdefBlock teol tdefexpr  */
#line 513 "wrdcBison.cpp"
                                      {
                Block* ret = (Block*) (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node);
                if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node))
                    ret->add(new Stmt((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)));
                ((*yyvalp).node) = ret;
            }
#line 2990 "wrdcBison.tab.cpp"
    break;

  case 155: /* tpackExpr: tpack tlhsId  */
#line 521 "wrdcBison.cpp"
                           {
                ((*yyvalp).node) = new PackStmt((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 2998 "wrdcBison.tab.cpp"
    break;

  case 156: /* timportExpr: timport tlhsId  */
#line 526 "wrdcBison.cpp"
                             {
                ((*yyvalp).node) = new ImportStmt((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node));
            }
#line 3006 "wrdcBison.tab.cpp"
    break;

  case 157: /* timportExpr: timport tlhsId taka tnormalId  */
#line 529 "wrdcBison.cpp"
                                            {
                ((*yyvalp).node) = new ImportStmt(new AkaStmt((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node), new Id((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.strVal))));
            }
#line 3014 "wrdcBison.tab.cpp"
    break;

  case 158: /* tfileExpr: tpackExpr  */
#line 534 "wrdcBison.cpp"
                      { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 3020 "wrdcBison.tab.cpp"
    break;

  case 159: /* tfileExpr: timportExpr  */
#line 535 "wrdcBison.cpp"
                          { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 3026 "wrdcBison.tab.cpp"
    break;

  case 160: /* tfileExpr: tdefexpr  */
#line 536 "wrdcBison.cpp"
                       { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node); }
#line 3032 "wrdcBison.tab.cpp"
    break;

  case 161: /* tdefIndentBlock: teol tindent tdefBlock tdedent  */
#line 539 "wrdcBison.cpp"
                                                { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node); }
#line 3038 "wrdcBison.tab.cpp"
    break;

  case 162: /* tdefIndentBlock: ':' tdefexpr  */
#line 540 "wrdcBison.cpp"
                           { ((*yyvalp).node) = new InlineStmt((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 3044 "wrdcBison.tab.cpp"
    break;

  case 163: /* tdefIndentBlock: %empty  */
#line 541 "wrdcBison.cpp"
              { ((*yyvalp).node) = 0; }
#line 3050 "wrdcBison.tab.cpp"
    break;

  case 164: /* tindentBlock: teol tindent tblock tdedent  */
#line 544 "wrdcBison.cpp"
                                          { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node); }
#line 3056 "wrdcBison.tab.cpp"
    break;

  case 165: /* tindentBlock: ':' trhsIdExpr  */
#line 545 "wrdcBison.cpp"
                             { ((*yyvalp).node) = new InlineStmt((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 3062 "wrdcBison.tab.cpp"
    break;

  case 166: /* tindentBlock: ':' treturnexpr  */
#line 546 "wrdcBison.cpp"
                              { ((*yyvalp).node) = new InlineStmt((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)); }
#line 3068 "wrdcBison.tab.cpp"
    break;

  case 167: /* tindentBlock: ':' tnext  */
#line 547 "wrdcBison.cpp"
                        { ((*yyvalp).node) = new InlineStmt(new Next()); }
#line 3074 "wrdcBison.tab.cpp"
    break;

  case 168: /* tfile: tfile teol tfileExpr  */
#line 550 "wrdcBison.cpp"
                                   {
                File* ret = (File*) (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval.node);
                ret->add(new Stmt((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)));
                ((*yyvalp).node) = ret;
            }
#line 3084 "wrdcBison.tab.cpp"
    break;

  case 169: /* tfile: tfileExpr  */
#line 555 "wrdcBison.cpp"
                        {
                parsed = new File();
                if ((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node))
                    parsed->add(new Stmt((YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (0)].yystate.yysemantics.yysval.node)));
                ((*yyvalp).node) = parsed;
            }
#line 3095 "wrdcBison.tab.cpp"
    break;

  case 170: /* tfile: tfile teof  */
#line 561 "wrdcBison.cpp"
                         { ((*yyvalp).node) = (YY_CAST (yyGLRStackItem const *, yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval.node); }
#line 3101 "wrdcBison.tab.cpp"
    break;


#line 3105 "wrdcBison.tab.cpp"

      default: break;
    }

  return yyok;
# undef yyerrok
# undef YYABORT
# undef YYACCEPT
# undef YYERROR
# undef YYBACKUP
# undef yyclearin
# undef YYRECOVERING
}


static void
yyuserMerge (int yyn, YYSTYPE* yy0, YYSTYPE* yy1)
{
  YY_USE (yy0);
  YY_USE (yy1);

  switch (yyn)
    {

      default: break;
    }
}

                              /* Bison grammar-table manipulation.  */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}

/** Number of symbols composing the right hand side of rule #RULE.  */
static inline int
yyrhsLength (yyRuleNum yyrule)
{
  return yyr2[yyrule];
}

static void
yydestroyGLRState (char const *yymsg, yyGLRState *yys)
{
  if (yys->yyresolved)
    yydestruct (yymsg, yy_accessing_symbol (yys->yylrState),
                &yys->yysemantics.yysval);
  else
    {
#if YYDEBUG
      if (yydebug)
        {
          if (yys->yysemantics.yyfirstVal)
            YY_FPRINTF ((stderr, "%s unresolved", yymsg));
          else
            YY_FPRINTF ((stderr, "%s incomplete", yymsg));
          YY_SYMBOL_PRINT ("", yy_accessing_symbol (yys->yylrState), YY_NULLPTR, &yys->yyloc);
        }
#endif

      if (yys->yysemantics.yyfirstVal)
        {
          yySemanticOption *yyoption = yys->yysemantics.yyfirstVal;
          yyGLRState *yyrh;
          int yyn;
          for (yyrh = yyoption->yystate, yyn = yyrhsLength (yyoption->yyrule);
               yyn > 0;
               yyrh = yyrh->yypred, yyn -= 1)
            yydestroyGLRState (yymsg, yyrh);
        }
    }
}

/** Left-hand-side symbol for rule #YYRULE.  */
static inline yysymbol_kind_t
yylhsNonterm (yyRuleNum yyrule)
{
  return YY_CAST (yysymbol_kind_t, yyr1[yyrule]);
}

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

/** True iff LR state YYSTATE has only a default reduction (regardless
 *  of token).  */
static inline yybool
yyisDefaultedState (yy_state_t yystate)
{
  return yypact_value_is_default (yypact[yystate]);
}

/** The default reduction for YYSTATE, assuming it has one.  */
static inline yyRuleNum
yydefaultAction (yy_state_t yystate)
{
  return yydefact[yystate];
}

#define yytable_value_is_error(Yyn) \
  0

/** The action to take in YYSTATE on seeing YYTOKEN.
 *  Result R means
 *    R < 0:  Reduce on rule -R.
 *    R = 0:  Error.
 *    R > 0:  Shift to state R.
 *  Set *YYCONFLICTS to a pointer into yyconfl to a 0-terminated list
 *  of conflicting reductions.
 */
static inline int
yygetLRActions (yy_state_t yystate, yysymbol_kind_t yytoken, const short** yyconflicts)
{
  int yyindex = yypact[yystate] + yytoken;
  if (yytoken == YYSYMBOL_YYerror)
    {
      // This is the error token.
      *yyconflicts = yyconfl;
      return 0;
    }
  else if (yyisDefaultedState (yystate)
           || yyindex < 0 || YYLAST < yyindex || yycheck[yyindex] != yytoken)
    {
      *yyconflicts = yyconfl;
      return -yydefact[yystate];
    }
  else if (! yytable_value_is_error (yytable[yyindex]))
    {
      *yyconflicts = yyconfl + yyconflp[yyindex];
      return yytable[yyindex];
    }
  else
    {
      *yyconflicts = yyconfl + yyconflp[yyindex];
      return 0;
    }
}

/** Compute post-reduction state.
 * \param yystate   the current state
 * \param yysym     the nonterminal to push on the stack
 */
static inline yy_state_t
yyLRgotoState (yy_state_t yystate, yysymbol_kind_t yysym)
{
  int yyr = yypgoto[yysym - YYNTOKENS] + yystate;
  if (0 <= yyr && yyr <= YYLAST && yycheck[yyr] == yystate)
    return yytable[yyr];
  else
    return yydefgoto[yysym - YYNTOKENS];
}

static inline yybool
yyisShiftAction (int yyaction)
{
  return 0 < yyaction;
}

static inline yybool
yyisErrorAction (int yyaction)
{
  return yyaction == 0;
}

                                /* GLRStates */

/** Return a fresh GLRStackItem in YYSTACKP.  The item is an LR state
 *  if YYISSTATE, and otherwise a semantic option.  Callers should call
 *  YY_RESERVE_GLRSTACK afterwards to make sure there is sufficient
 *  headroom.  */

static inline yyGLRStackItem*
yynewGLRStackItem (yyGLRStack* yystackp, yybool yyisState)
{
  yyGLRStackItem* yynewItem = yystackp->yynextFree;
  yystackp->yyspaceLeft -= 1;
  yystackp->yynextFree += 1;
  yynewItem->yystate.yyisState = yyisState;
  return yynewItem;
}

/** Add a new semantic action that will execute the action for rule
 *  YYRULE on the semantic values in YYRHS to the list of
 *  alternative actions for YYSTATE.  Assumes that YYRHS comes from
 *  stack #YYK of *YYSTACKP. */
static void
yyaddDeferredAction (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yyGLRState* yystate,
                     yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yySemanticOption* yynewOption =
    &yynewGLRStackItem (yystackp, yyfalse)->yyoption;
  YY_ASSERT (!yynewOption->yyisState);
  yynewOption->yystate = yyrhs;
  yynewOption->yyrule = yyrule;
  if (yystackp->yytops.yylookaheadNeeds[yyk])
    {
      yynewOption->yyrawchar = yychar;
      yynewOption->yyval = yylval;
    }
  else
    yynewOption->yyrawchar = YYEMPTY;
  yynewOption->yynext = yystate->yysemantics.yyfirstVal;
  yystate->yysemantics.yyfirstVal = yynewOption;

  YY_RESERVE_GLRSTACK (yystackp);
}

                                /* GLRStacks */

/** Initialize YYSET to a singleton set containing an empty stack.  */
static yybool
yyinitStateSet (yyGLRStateSet* yyset)
{
  yyset->yysize = 1;
  yyset->yycapacity = 16;
  yyset->yystates
    = YY_CAST (yyGLRState**,
               YYMALLOC (YY_CAST (YYSIZE_T, yyset->yycapacity)
                         * sizeof yyset->yystates[0]));
  if (! yyset->yystates)
    return yyfalse;
  yyset->yystates[0] = YY_NULLPTR;
  yyset->yylookaheadNeeds
    = YY_CAST (yybool*,
               YYMALLOC (YY_CAST (YYSIZE_T, yyset->yycapacity)
                         * sizeof yyset->yylookaheadNeeds[0]));
  if (! yyset->yylookaheadNeeds)
    {
      YYFREE (yyset->yystates);
      return yyfalse;
    }
  memset (yyset->yylookaheadNeeds,
          0,
          YY_CAST (YYSIZE_T, yyset->yycapacity) * sizeof yyset->yylookaheadNeeds[0]);
  return yytrue;
}

static void yyfreeStateSet (yyGLRStateSet* yyset)
{
  YYFREE (yyset->yystates);
  YYFREE (yyset->yylookaheadNeeds);
}

/** Initialize *YYSTACKP to a single empty stack, with total maximum
 *  capacity for all stacks of YYSIZE.  */
static yybool
yyinitGLRStack (yyGLRStack* yystackp, YYPTRDIFF_T yysize)
{
  yystackp->yyerrState = 0;
  yynerrs = 0;
  yystackp->yyspaceLeft = yysize;
  yystackp->yyitems
    = YY_CAST (yyGLRStackItem*,
               YYMALLOC (YY_CAST (YYSIZE_T, yysize)
                         * sizeof yystackp->yynextFree[0]));
  if (!yystackp->yyitems)
    return yyfalse;
  yystackp->yynextFree = yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULLPTR;
  yystackp->yylastDeleted = YY_NULLPTR;
  return yyinitStateSet (&yystackp->yytops);
}


#if YYSTACKEXPANDABLE
# define YYRELOC(YYFROMITEMS, YYTOITEMS, YYX, YYTYPE)                   \
  &((YYTOITEMS)                                                         \
    - ((YYFROMITEMS) - YY_REINTERPRET_CAST (yyGLRStackItem*, (YYX))))->YYTYPE

/** If *YYSTACKP is expandable, extend it.  WARNING: Pointers into the
    stack from outside should be considered invalid after this call.
    We always expand when there are 1 or fewer items left AFTER an
    allocation, so that we can avoid having external pointers exist
    across an allocation.  */
static void
yyexpandGLRStack (yyGLRStack* yystackp)
{
  yyGLRStackItem* yynewItems;
  yyGLRStackItem* yyp0, *yyp1;
  YYPTRDIFF_T yynewSize;
  YYPTRDIFF_T yyn;
  YYPTRDIFF_T yysize = yystackp->yynextFree - yystackp->yyitems;
  if (YYMAXDEPTH - YYHEADROOM < yysize)
    yyMemoryExhausted (yystackp);
  yynewSize = 2*yysize;
  if (YYMAXDEPTH < yynewSize)
    yynewSize = YYMAXDEPTH;
  yynewItems
    = YY_CAST (yyGLRStackItem*,
               YYMALLOC (YY_CAST (YYSIZE_T, yynewSize)
                         * sizeof yynewItems[0]));
  if (! yynewItems)
    yyMemoryExhausted (yystackp);
  for (yyp0 = yystackp->yyitems, yyp1 = yynewItems, yyn = yysize;
       0 < yyn;
       yyn -= 1, yyp0 += 1, yyp1 += 1)
    {
      *yyp1 = *yyp0;
      if (*YY_REINTERPRET_CAST (yybool *, yyp0))
        {
          yyGLRState* yys0 = &yyp0->yystate;
          yyGLRState* yys1 = &yyp1->yystate;
          if (yys0->yypred != YY_NULLPTR)
            yys1->yypred =
              YYRELOC (yyp0, yyp1, yys0->yypred, yystate);
          if (! yys0->yyresolved && yys0->yysemantics.yyfirstVal != YY_NULLPTR)
            yys1->yysemantics.yyfirstVal =
              YYRELOC (yyp0, yyp1, yys0->yysemantics.yyfirstVal, yyoption);
        }
      else
        {
          yySemanticOption* yyv0 = &yyp0->yyoption;
          yySemanticOption* yyv1 = &yyp1->yyoption;
          if (yyv0->yystate != YY_NULLPTR)
            yyv1->yystate = YYRELOC (yyp0, yyp1, yyv0->yystate, yystate);
          if (yyv0->yynext != YY_NULLPTR)
            yyv1->yynext = YYRELOC (yyp0, yyp1, yyv0->yynext, yyoption);
        }
    }
  if (yystackp->yysplitPoint != YY_NULLPTR)
    yystackp->yysplitPoint = YYRELOC (yystackp->yyitems, yynewItems,
                                      yystackp->yysplitPoint, yystate);

  for (yyn = 0; yyn < yystackp->yytops.yysize; yyn += 1)
    if (yystackp->yytops.yystates[yyn] != YY_NULLPTR)
      yystackp->yytops.yystates[yyn] =
        YYRELOC (yystackp->yyitems, yynewItems,
                 yystackp->yytops.yystates[yyn], yystate);
  YYFREE (yystackp->yyitems);
  yystackp->yyitems = yynewItems;
  yystackp->yynextFree = yynewItems + yysize;
  yystackp->yyspaceLeft = yynewSize - yysize;
}
#endif

static void
yyfreeGLRStack (yyGLRStack* yystackp)
{
  YYFREE (yystackp->yyitems);
  yyfreeStateSet (&yystackp->yytops);
}

/** Assuming that YYS is a GLRState somewhere on *YYSTACKP, update the
 *  splitpoint of *YYSTACKP, if needed, so that it is at least as deep as
 *  YYS.  */
static inline void
yyupdateSplit (yyGLRStack* yystackp, yyGLRState* yys)
{
  if (yystackp->yysplitPoint != YY_NULLPTR && yystackp->yysplitPoint > yys)
    yystackp->yysplitPoint = yys;
}

/** Invalidate stack #YYK in *YYSTACKP.  */
static inline void
yymarkStackDeleted (yyGLRStack* yystackp, YYPTRDIFF_T yyk)
{
  if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
    yystackp->yylastDeleted = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yystates[yyk] = YY_NULLPTR;
}

/** Undelete the last stack in *YYSTACKP that was marked as deleted.  Can
    only be done once after a deletion, and only when all other stacks have
    been deleted.  */
static void
yyundeleteLastStack (yyGLRStack* yystackp)
{
  if (yystackp->yylastDeleted == YY_NULLPTR || yystackp->yytops.yysize != 0)
    return;
  yystackp->yytops.yystates[0] = yystackp->yylastDeleted;
  yystackp->yytops.yysize = 1;
  YY_DPRINTF ((stderr, "Restoring last deleted stack as stack #0.\n"));
  yystackp->yylastDeleted = YY_NULLPTR;
}

static inline void
yyremoveDeletes (yyGLRStack* yystackp)
{
  YYPTRDIFF_T yyi, yyj;
  yyi = yyj = 0;
  while (yyj < yystackp->yytops.yysize)
    {
      if (yystackp->yytops.yystates[yyi] == YY_NULLPTR)
        {
          if (yyi == yyj)
            YY_DPRINTF ((stderr, "Removing dead stacks.\n"));
          yystackp->yytops.yysize -= 1;
        }
      else
        {
          yystackp->yytops.yystates[yyj] = yystackp->yytops.yystates[yyi];
          /* In the current implementation, it's unnecessary to copy
             yystackp->yytops.yylookaheadNeeds[yyi] since, after
             yyremoveDeletes returns, the parser immediately either enters
             deterministic operation or shifts a token.  However, it doesn't
             hurt, and the code might evolve to need it.  */
          yystackp->yytops.yylookaheadNeeds[yyj] =
            yystackp->yytops.yylookaheadNeeds[yyi];
          if (yyj != yyi)
            YY_DPRINTF ((stderr, "Rename stack %ld -> %ld.\n",
                        YY_CAST (long, yyi), YY_CAST (long, yyj)));
          yyj += 1;
        }
      yyi += 1;
    }
}

/** Shift to a new state on stack #YYK of *YYSTACKP, corresponding to LR
 * state YYLRSTATE, at input position YYPOSN, with (resolved) semantic
 * value *YYVALP and source location *YYLOCP.  */
static inline void
yyglrShift (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yy_state_t yylrState,
            YYPTRDIFF_T yyposn,
            YYSTYPE* yyvalp)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yytrue;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yysval = *yyvalp;
  yystackp->yytops.yystates[yyk] = yynewState;

  YY_RESERVE_GLRSTACK (yystackp);
}

/** Shift stack #YYK of *YYSTACKP, to a new state corresponding to LR
 *  state YYLRSTATE, at input position YYPOSN, with the (unresolved)
 *  semantic value of YYRHS under the action for YYRULE.  */
static inline void
yyglrShiftDefer (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yy_state_t yylrState,
                 YYPTRDIFF_T yyposn, yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;
  YY_ASSERT (yynewState->yyisState);

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yyfalse;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yyfirstVal = YY_NULLPTR;
  yystackp->yytops.yystates[yyk] = yynewState;

  /* Invokes YY_RESERVE_GLRSTACK.  */
  yyaddDeferredAction (yystackp, yyk, yynewState, yyrhs, yyrule);
}

#if !YYDEBUG
# define YY_REDUCE_PRINT(Args)
#else
# define YY_REDUCE_PRINT(Args)          \
  do {                                  \
    if (yydebug)                        \
      yy_reduce_print Args;             \
  } while (0)

/*----------------------------------------------------------------------.
| Report that stack #YYK of *YYSTACKP is going to be reduced by YYRULE. |
`----------------------------------------------------------------------*/

static inline void
yy_reduce_print (yybool yynormal, yyGLRStackItem* yyvsp, YYPTRDIFF_T yyk,
                 yyRuleNum yyrule)
{
  int yynrhs = yyrhsLength (yyrule);
  int yyi;
  YY_FPRINTF ((stderr, "Reducing stack %ld by rule %d (line %d):\n",
               YY_CAST (long, yyk), yyrule - 1, yyrline[yyrule]));
  if (! yynormal)
    yyfillin (yyvsp, 1, -yynrhs);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YY_FPRINTF ((stderr, "   $%d = ", yyi + 1));
      yy_symbol_print (stderr,
                       yy_accessing_symbol (yyvsp[yyi - yynrhs + 1].yystate.yylrState),
                       &yyvsp[yyi - yynrhs + 1].yystate.yysemantics.yysval                       );
      if (!yyvsp[yyi - yynrhs + 1].yystate.yyresolved)
        YY_FPRINTF ((stderr, " (unresolved)"));
      YY_FPRINTF ((stderr, "\n"));
    }
}
#endif

/** Pop the symbols consumed by reduction #YYRULE from the top of stack
 *  #YYK of *YYSTACKP, and perform the appropriate semantic action on their
 *  semantic values.  Assumes that all ambiguities in semantic values
 *  have been previously resolved.  Set *YYVALP to the resulting value,
 *  and *YYLOCP to the computed location (if any).  Return value is as
 *  for userAction.  */
static inline YYRESULTTAG
yydoAction (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yyRuleNum yyrule,
            YYSTYPE* yyvalp)
{
  int yynrhs = yyrhsLength (yyrule);

  if (yystackp->yysplitPoint == YY_NULLPTR)
    {
      /* Standard special case: single stack.  */
      yyGLRStackItem* yyrhs
        = YY_REINTERPRET_CAST (yyGLRStackItem*, yystackp->yytops.yystates[yyk]);
      YY_ASSERT (yyk == 0);
      yystackp->yynextFree -= yynrhs;
      yystackp->yyspaceLeft += yynrhs;
      yystackp->yytops.yystates[0] = & yystackp->yynextFree[-1].yystate;
      YY_REDUCE_PRINT ((yytrue, yyrhs, yyk, yyrule));
      return yyuserAction (yyrule, yynrhs, yyrhs, yystackp,
                           yyvalp);
    }
  else
    {
      yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
      yyGLRState* yys = yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred
        = yystackp->yytops.yystates[yyk];
      int yyi;
      for (yyi = 0; yyi < yynrhs; yyi += 1)
        {
          yys = yys->yypred;
          YY_ASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yystackp->yytops.yystates[yyk] = yys;
      YY_REDUCE_PRINT ((yyfalse, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1, yyk, yyrule));
      return yyuserAction (yyrule, yynrhs, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, yyvalp);
    }
}

/** Pop items off stack #YYK of *YYSTACKP according to grammar rule YYRULE,
 *  and push back on the resulting nonterminal symbol.  Perform the
 *  semantic action associated with YYRULE and store its value with the
 *  newly pushed state, if YYFORCEEVAL or if *YYSTACKP is currently
 *  unambiguous.  Otherwise, store the deferred semantic action with
 *  the new state.  If the new state would have an identical input
 *  position, LR state, and predecessor to an existing state on the stack,
 *  it is identified with that existing state, eliminating stack #YYK from
 *  *YYSTACKP.  In this case, the semantic value is
 *  added to the options for the existing state's semantic value.
 */
static inline YYRESULTTAG
yyglrReduce (yyGLRStack* yystackp, YYPTRDIFF_T yyk, yyRuleNum yyrule,
             yybool yyforceEval)
{
  YYPTRDIFF_T yyposn = yystackp->yytops.yystates[yyk]->yyposn;

  if (yyforceEval || yystackp->yysplitPoint == YY_NULLPTR)
    {
      YYSTYPE yysval;

      YYRESULTTAG yyflag = yydoAction (yystackp, yyk, yyrule, &yysval);
      if (yyflag == yyerr && yystackp->yysplitPoint != YY_NULLPTR)
        YY_DPRINTF ((stderr,
                     "Parse on stack %ld rejected by rule %d (line %d).\n",
                     YY_CAST (long, yyk), yyrule - 1, yyrline[yyrule - 1]));
      if (yyflag != yyok)
        return yyflag;
      YY_SYMBOL_PRINT ("-> $$ =", yylhsNonterm (yyrule), &yysval, &yyloc);
      yyglrShift (yystackp, yyk,
                  yyLRgotoState (yystackp->yytops.yystates[yyk]->yylrState,
                                 yylhsNonterm (yyrule)),
                  yyposn, &yysval);
    }
  else
    {
      YYPTRDIFF_T yyi;
      int yyn;
      yyGLRState* yys, *yys0 = yystackp->yytops.yystates[yyk];
      yy_state_t yynewLRState;

      for (yys = yystackp->yytops.yystates[yyk], yyn = yyrhsLength (yyrule);
           0 < yyn; yyn -= 1)
        {
          yys = yys->yypred;
          YY_ASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yynewLRState = yyLRgotoState (yys->yylrState, yylhsNonterm (yyrule));
      YY_DPRINTF ((stderr,
                   "Reduced stack %ld by rule %d (line %d); action deferred.  "
                   "Now in state %d.\n",
                   YY_CAST (long, yyk), yyrule - 1, yyrline[yyrule - 1],
                   yynewLRState));
      for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
        if (yyi != yyk && yystackp->yytops.yystates[yyi] != YY_NULLPTR)
          {
            yyGLRState *yysplit = yystackp->yysplitPoint;
            yyGLRState *yyp = yystackp->yytops.yystates[yyi];
            while (yyp != yys && yyp != yysplit && yyp->yyposn >= yyposn)
              {
                if (yyp->yylrState == yynewLRState && yyp->yypred == yys)
                  {
                    yyaddDeferredAction (yystackp, yyk, yyp, yys0, yyrule);
                    yymarkStackDeleted (yystackp, yyk);
                    YY_DPRINTF ((stderr, "Merging stack %ld into stack %ld.\n",
                                 YY_CAST (long, yyk), YY_CAST (long, yyi)));
                    return yyok;
                  }
                yyp = yyp->yypred;
              }
          }
      yystackp->yytops.yystates[yyk] = yys;
      yyglrShiftDefer (yystackp, yyk, yynewLRState, yyposn, yys0, yyrule);
    }
  return yyok;
}

static YYPTRDIFF_T
yysplitStack (yyGLRStack* yystackp, YYPTRDIFF_T yyk)
{
  if (yystackp->yysplitPoint == YY_NULLPTR)
    {
      YY_ASSERT (yyk == 0);
      yystackp->yysplitPoint = yystackp->yytops.yystates[yyk];
    }
  if (yystackp->yytops.yycapacity <= yystackp->yytops.yysize)
    {
      YYPTRDIFF_T state_size = YYSIZEOF (yystackp->yytops.yystates[0]);
      YYPTRDIFF_T half_max_capacity = YYSIZE_MAXIMUM / 2 / state_size;
      if (half_max_capacity < yystackp->yytops.yycapacity)
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yycapacity *= 2;

      {
        yyGLRState** yynewStates
          = YY_CAST (yyGLRState**,
                     YYREALLOC (yystackp->yytops.yystates,
                                (YY_CAST (YYSIZE_T, yystackp->yytops.yycapacity)
                                 * sizeof yynewStates[0])));
        if (yynewStates == YY_NULLPTR)
          yyMemoryExhausted (yystackp);
        yystackp->yytops.yystates = yynewStates;
      }

      {
        yybool* yynewLookaheadNeeds
          = YY_CAST (yybool*,
                     YYREALLOC (yystackp->yytops.yylookaheadNeeds,
                                (YY_CAST (YYSIZE_T, yystackp->yytops.yycapacity)
                                 * sizeof yynewLookaheadNeeds[0])));
        if (yynewLookaheadNeeds == YY_NULLPTR)
          yyMemoryExhausted (yystackp);
        yystackp->yytops.yylookaheadNeeds = yynewLookaheadNeeds;
      }
    }
  yystackp->yytops.yystates[yystackp->yytops.yysize]
    = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yylookaheadNeeds[yystackp->yytops.yysize]
    = yystackp->yytops.yylookaheadNeeds[yyk];
  yystackp->yytops.yysize += 1;
  return yystackp->yytops.yysize - 1;
}

/** True iff YYY0 and YYY1 represent identical options at the top level.
 *  That is, they represent the same rule applied to RHS symbols
 *  that produce the same terminal symbols.  */
static yybool
yyidenticalOptions (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  if (yyy0->yyrule == yyy1->yyrule)
    {
      yyGLRState *yys0, *yys1;
      int yyn;
      for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
           yyn = yyrhsLength (yyy0->yyrule);
           yyn > 0;
           yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
        if (yys0->yyposn != yys1->yyposn)
          return yyfalse;
      return yytrue;
    }
  else
    return yyfalse;
}

/** Assuming identicalOptions (YYY0,YYY1), destructively merge the
 *  alternative semantic values for the RHS-symbols of YYY1 and YYY0.  */
static void
yymergeOptionSets (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  yyGLRState *yys0, *yys1;
  int yyn;
  for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
       yyn = yyrhsLength (yyy0->yyrule);
       0 < yyn;
       yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
    {
      if (yys0 == yys1)
        break;
      else if (yys0->yyresolved)
        {
          yys1->yyresolved = yytrue;
          yys1->yysemantics.yysval = yys0->yysemantics.yysval;
        }
      else if (yys1->yyresolved)
        {
          yys0->yyresolved = yytrue;
          yys0->yysemantics.yysval = yys1->yysemantics.yysval;
        }
      else
        {
          yySemanticOption** yyz0p = &yys0->yysemantics.yyfirstVal;
          yySemanticOption* yyz1 = yys1->yysemantics.yyfirstVal;
          while (yytrue)
            {
              if (yyz1 == *yyz0p || yyz1 == YY_NULLPTR)
                break;
              else if (*yyz0p == YY_NULLPTR)
                {
                  *yyz0p = yyz1;
                  break;
                }
              else if (*yyz0p < yyz1)
                {
                  yySemanticOption* yyz = *yyz0p;
                  *yyz0p = yyz1;
                  yyz1 = yyz1->yynext;
                  (*yyz0p)->yynext = yyz;
                }
              yyz0p = &(*yyz0p)->yynext;
            }
          yys1->yysemantics.yyfirstVal = yys0->yysemantics.yyfirstVal;
        }
    }
}

/** Y0 and Y1 represent two possible actions to take in a given
 *  parsing state; return 0 if no combination is possible,
 *  1 if user-mergeable, 2 if Y0 is preferred, 3 if Y1 is preferred.  */
static int
yypreference (yySemanticOption* y0, yySemanticOption* y1)
{
  yyRuleNum r0 = y0->yyrule, r1 = y1->yyrule;
  int p0 = yydprec[r0], p1 = yydprec[r1];

  if (p0 == p1)
    {
      if (yymerger[r0] == 0 || yymerger[r0] != yymerger[r1])
        return 0;
      else
        return 1;
    }
  if (p0 == 0 || p1 == 0)
    return 0;
  if (p0 < p1)
    return 3;
  if (p1 < p0)
    return 2;
  return 0;
}

static YYRESULTTAG yyresolveValue (yyGLRState* yys,
                                   yyGLRStack* yystackp);


/** Resolve the previous YYN states starting at and including state YYS
 *  on *YYSTACKP. If result != yyok, some states may have been left
 *  unresolved possibly with empty semantic option chains.  Regardless
 *  of whether result = yyok, each state has been left with consistent
 *  data so that yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveStates (yyGLRState* yys, int yyn,
                 yyGLRStack* yystackp)
{
  if (0 < yyn)
    {
      YY_ASSERT (yys->yypred);
      YYCHK (yyresolveStates (yys->yypred, yyn-1, yystackp));
      if (! yys->yyresolved)
        YYCHK (yyresolveValue (yys, yystackp));
    }
  return yyok;
}

/** Resolve the states for the RHS of YYOPT on *YYSTACKP, perform its
 *  user action, and return the semantic value and location in *YYVALP
 *  and *YYLOCP.  Regardless of whether result = yyok, all RHS states
 *  have been destroyed (assuming the user action destroys all RHS
 *  semantic values if invoked).  */
static YYRESULTTAG
yyresolveAction (yySemanticOption* yyopt, yyGLRStack* yystackp,
                 YYSTYPE* yyvalp)
{
  yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
  int yynrhs = yyrhsLength (yyopt->yyrule);
  YYRESULTTAG yyflag =
    yyresolveStates (yyopt->yystate, yynrhs, yystackp);
  if (yyflag != yyok)
    {
      yyGLRState *yys;
      for (yys = yyopt->yystate; yynrhs > 0; yys = yys->yypred, yynrhs -= 1)
        yydestroyGLRState ("Cleanup: popping", yys);
      return yyflag;
    }

  yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred = yyopt->yystate;
  {
    int yychar_current = yychar;
    YYSTYPE yylval_current = yylval;
    yychar = yyopt->yyrawchar;
    yylval = yyopt->yyval;
    yyflag = yyuserAction (yyopt->yyrule, yynrhs,
                           yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, yyvalp);
    yychar = yychar_current;
    yylval = yylval_current;
  }
  return yyflag;
}

#if YYDEBUG
static void
yyreportTree (yySemanticOption* yyx, int yyindent)
{
  int yynrhs = yyrhsLength (yyx->yyrule);
  int yyi;
  yyGLRState* yys;
  yyGLRState* yystates[1 + YYMAXRHS];
  yyGLRState yyleftmost_state;

  for (yyi = yynrhs, yys = yyx->yystate; 0 < yyi; yyi -= 1, yys = yys->yypred)
    yystates[yyi] = yys;
  if (yys == YY_NULLPTR)
    {
      yyleftmost_state.yyposn = 0;
      yystates[0] = &yyleftmost_state;
    }
  else
    yystates[0] = yys;

  if (yyx->yystate->yyposn < yys->yyposn + 1)
    YY_FPRINTF ((stderr, "%*s%s -> <Rule %d, empty>\n",
                 yyindent, "", yysymbol_name (yylhsNonterm (yyx->yyrule)),
                 yyx->yyrule - 1));
  else
    YY_FPRINTF ((stderr, "%*s%s -> <Rule %d, tokens %ld .. %ld>\n",
                 yyindent, "", yysymbol_name (yylhsNonterm (yyx->yyrule)),
                 yyx->yyrule - 1, YY_CAST (long, yys->yyposn + 1),
                 YY_CAST (long, yyx->yystate->yyposn)));
  for (yyi = 1; yyi <= yynrhs; yyi += 1)
    {
      if (yystates[yyi]->yyresolved)
        {
          if (yystates[yyi-1]->yyposn+1 > yystates[yyi]->yyposn)
            YY_FPRINTF ((stderr, "%*s%s <empty>\n", yyindent+2, "",
                         yysymbol_name (yy_accessing_symbol (yystates[yyi]->yylrState))));
          else
            YY_FPRINTF ((stderr, "%*s%s <tokens %ld .. %ld>\n", yyindent+2, "",
                         yysymbol_name (yy_accessing_symbol (yystates[yyi]->yylrState)),
                         YY_CAST (long, yystates[yyi-1]->yyposn + 1),
                         YY_CAST (long, yystates[yyi]->yyposn)));
        }
      else
        yyreportTree (yystates[yyi]->yysemantics.yyfirstVal, yyindent+2);
    }
}
#endif

static YYRESULTTAG
yyreportAmbiguity (yySemanticOption* yyx0,
                   yySemanticOption* yyx1)
{
  YY_USE (yyx0);
  YY_USE (yyx1);

#if YYDEBUG
  YY_FPRINTF ((stderr, "Ambiguity detected.\n"));
  YY_FPRINTF ((stderr, "Option 1,\n"));
  yyreportTree (yyx0, 2);
  YY_FPRINTF ((stderr, "\nOption 2,\n"));
  yyreportTree (yyx1, 2);
  YY_FPRINTF ((stderr, "\n"));
#endif

  yyerror (YY_("syntax is ambiguous"));
  return yyabort;
}

/** Resolve the ambiguity represented in state YYS in *YYSTACKP,
 *  perform the indicated actions, and set the semantic value of YYS.
 *  If result != yyok, the chain of semantic options in YYS has been
 *  cleared instead or it has been left unmodified except that
 *  redundant options may have been removed.  Regardless of whether
 *  result = yyok, YYS has been left with consistent data so that
 *  yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveValue (yyGLRState* yys, yyGLRStack* yystackp)
{
  yySemanticOption* yyoptionList = yys->yysemantics.yyfirstVal;
  yySemanticOption* yybest = yyoptionList;
  yySemanticOption** yypp;
  yybool yymerge = yyfalse;
  YYSTYPE yysval;
  YYRESULTTAG yyflag;

  for (yypp = &yyoptionList->yynext; *yypp != YY_NULLPTR; )
    {
      yySemanticOption* yyp = *yypp;

      if (yyidenticalOptions (yybest, yyp))
        {
          yymergeOptionSets (yybest, yyp);
          *yypp = yyp->yynext;
        }
      else
        {
          switch (yypreference (yybest, yyp))
            {
            case 0:
              return yyreportAmbiguity (yybest, yyp);
              break;
            case 1:
              yymerge = yytrue;
              break;
            case 2:
              break;
            case 3:
              yybest = yyp;
              yymerge = yyfalse;
              break;
            default:
              /* This cannot happen so it is not worth a YY_ASSERT (yyfalse),
                 but some compilers complain if the default case is
                 omitted.  */
              break;
            }
          yypp = &yyp->yynext;
        }
    }

  if (yymerge)
    {
      yySemanticOption* yyp;
      int yyprec = yydprec[yybest->yyrule];
      yyflag = yyresolveAction (yybest, yystackp, &yysval);
      if (yyflag == yyok)
        for (yyp = yybest->yynext; yyp != YY_NULLPTR; yyp = yyp->yynext)
          {
            if (yyprec == yydprec[yyp->yyrule])
              {
                YYSTYPE yysval_other;
                yyflag = yyresolveAction (yyp, yystackp, &yysval_other);
                if (yyflag != yyok)
                  {
                    yydestruct ("Cleanup: discarding incompletely merged value for",
                                yy_accessing_symbol (yys->yylrState),
                                &yysval);
                    break;
                  }
                yyuserMerge (yymerger[yyp->yyrule], &yysval, &yysval_other);
              }
          }
    }
  else
    yyflag = yyresolveAction (yybest, yystackp, &yysval);

  if (yyflag == yyok)
    {
      yys->yyresolved = yytrue;
      yys->yysemantics.yysval = yysval;
    }
  else
    yys->yysemantics.yyfirstVal = YY_NULLPTR;
  return yyflag;
}

static YYRESULTTAG
yyresolveStack (yyGLRStack* yystackp)
{
  if (yystackp->yysplitPoint != YY_NULLPTR)
    {
      yyGLRState* yys;
      int yyn;

      for (yyn = 0, yys = yystackp->yytops.yystates[0];
           yys != yystackp->yysplitPoint;
           yys = yys->yypred, yyn += 1)
        continue;
      YYCHK (yyresolveStates (yystackp->yytops.yystates[0], yyn, yystackp
                             ));
    }
  return yyok;
}

static void
yycompressStack (yyGLRStack* yystackp)
{
  yyGLRState* yyp, *yyq, *yyr;

  if (yystackp->yytops.yysize != 1 || yystackp->yysplitPoint == YY_NULLPTR)
    return;

  for (yyp = yystackp->yytops.yystates[0], yyq = yyp->yypred, yyr = YY_NULLPTR;
       yyp != yystackp->yysplitPoint;
       yyr = yyp, yyp = yyq, yyq = yyp->yypred)
    yyp->yypred = yyr;

  yystackp->yyspaceLeft += yystackp->yynextFree - yystackp->yyitems;
  yystackp->yynextFree = YY_REINTERPRET_CAST (yyGLRStackItem*, yystackp->yysplitPoint) + 1;
  yystackp->yyspaceLeft -= yystackp->yynextFree - yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULLPTR;
  yystackp->yylastDeleted = YY_NULLPTR;

  while (yyr != YY_NULLPTR)
    {
      yystackp->yynextFree->yystate = *yyr;
      yyr = yyr->yypred;
      yystackp->yynextFree->yystate.yypred = &yystackp->yynextFree[-1].yystate;
      yystackp->yytops.yystates[0] = &yystackp->yynextFree->yystate;
      yystackp->yynextFree += 1;
      yystackp->yyspaceLeft -= 1;
    }
}

static YYRESULTTAG
yyprocessOneStack (yyGLRStack* yystackp, YYPTRDIFF_T yyk,
                   YYPTRDIFF_T yyposn)
{
  while (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
    {
      yy_state_t yystate = yystackp->yytops.yystates[yyk]->yylrState;
      YY_DPRINTF ((stderr, "Stack %ld Entering state %d\n",
                   YY_CAST (long, yyk), yystate));

      YY_ASSERT (yystate != YYFINAL);

      if (yyisDefaultedState (yystate))
        {
          YYRESULTTAG yyflag;
          yyRuleNum yyrule = yydefaultAction (yystate);
          if (yyrule == 0)
            {
              YY_DPRINTF ((stderr, "Stack %ld dies.\n", YY_CAST (long, yyk)));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          yyflag = yyglrReduce (yystackp, yyk, yyrule, yyimmediate[yyrule]);
          if (yyflag == yyerr)
            {
              YY_DPRINTF ((stderr,
                           "Stack %ld dies "
                           "(predicate failure or explicit user error).\n",
                           YY_CAST (long, yyk)));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          if (yyflag != yyok)
            return yyflag;
        }
      else
        {
          yysymbol_kind_t yytoken = yygetToken (&yychar);
          const short* yyconflicts;
          const int yyaction = yygetLRActions (yystate, yytoken, &yyconflicts);
          yystackp->yytops.yylookaheadNeeds[yyk] = yytrue;

          for (/* nothing */; *yyconflicts; yyconflicts += 1)
            {
              YYRESULTTAG yyflag;
              YYPTRDIFF_T yynewStack = yysplitStack (yystackp, yyk);
              YY_DPRINTF ((stderr, "Splitting off stack %ld from %ld.\n",
                           YY_CAST (long, yynewStack), YY_CAST (long, yyk)));
              yyflag = yyglrReduce (yystackp, yynewStack,
                                    *yyconflicts,
                                    yyimmediate[*yyconflicts]);
              if (yyflag == yyok)
                YYCHK (yyprocessOneStack (yystackp, yynewStack,
                                          yyposn));
              else if (yyflag == yyerr)
                {
                  YY_DPRINTF ((stderr, "Stack %ld dies.\n", YY_CAST (long, yynewStack)));
                  yymarkStackDeleted (yystackp, yynewStack);
                }
              else
                return yyflag;
            }

          if (yyisShiftAction (yyaction))
            break;
          else if (yyisErrorAction (yyaction))
            {
              YY_DPRINTF ((stderr, "Stack %ld dies.\n", YY_CAST (long, yyk)));
              yymarkStackDeleted (yystackp, yyk);
              break;
            }
          else
            {
              YYRESULTTAG yyflag = yyglrReduce (yystackp, yyk, -yyaction,
                                                yyimmediate[-yyaction]);
              if (yyflag == yyerr)
                {
                  YY_DPRINTF ((stderr,
                               "Stack %ld dies "
                               "(predicate failure or explicit user error).\n",
                               YY_CAST (long, yyk)));
                  yymarkStackDeleted (yystackp, yyk);
                  break;
                }
              else if (yyflag != yyok)
                return yyflag;
            }
        }
    }
  return yyok;
}






static void
yyreportSyntaxError (yyGLRStack* yystackp)
{
  if (yystackp->yyerrState != 0)
    return;
  yyerror (YY_("syntax error"));
  yynerrs += 1;
}

/* Recover from a syntax error on *YYSTACKP, assuming that *YYSTACKP->YYTOKENP,
   yylval, and yylloc are the syntactic category, semantic value, and location
   of the lookahead.  */
static void
yyrecoverSyntaxError (yyGLRStack* yystackp)
{
  if (yystackp->yyerrState == 3)
    /* We just shifted the error token and (perhaps) took some
       reductions.  Skip tokens until we can proceed.  */
    while (yytrue)
      {
        yysymbol_kind_t yytoken;
        int yyj;
        if (yychar == YYEOF)
          yyFail (yystackp, YY_NULLPTR);
        if (yychar != YYEMPTY)
          {
            yytoken = YYTRANSLATE (yychar);
            yydestruct ("Error: discarding",
                        yytoken, &yylval);
            yychar = YYEMPTY;
          }
        yytoken = yygetToken (&yychar);
        yyj = yypact[yystackp->yytops.yystates[0]->yylrState];
        if (yypact_value_is_default (yyj))
          return;
        yyj += yytoken;
        if (yyj < 0 || YYLAST < yyj || yycheck[yyj] != yytoken)
          {
            if (yydefact[yystackp->yytops.yystates[0]->yylrState] != 0)
              return;
          }
        else if (! yytable_value_is_error (yytable[yyj]))
          return;
      }

  /* Reduce to one stack.  */
  {
    YYPTRDIFF_T yyk;
    for (yyk = 0; yyk < yystackp->yytops.yysize; yyk += 1)
      if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
        break;
    if (yyk >= yystackp->yytops.yysize)
      yyFail (yystackp, YY_NULLPTR);
    for (yyk += 1; yyk < yystackp->yytops.yysize; yyk += 1)
      yymarkStackDeleted (yystackp, yyk);
    yyremoveDeletes (yystackp);
    yycompressStack (yystackp);
  }

  /* Pop stack until we find a state that shifts the error token.  */
  yystackp->yyerrState = 3;
  while (yystackp->yytops.yystates[0] != YY_NULLPTR)
    {
      yyGLRState *yys = yystackp->yytops.yystates[0];
      int yyj = yypact[yys->yylrState];
      if (! yypact_value_is_default (yyj))
        {
          yyj += YYSYMBOL_YYerror;
          if (0 <= yyj && yyj <= YYLAST && yycheck[yyj] == YYSYMBOL_YYerror
              && yyisShiftAction (yytable[yyj]))
            {
              /* Shift the error token.  */
              int yyaction = yytable[yyj];
              YY_SYMBOL_PRINT ("Shifting", yy_accessing_symbol (yyaction),
                               &yylval, &yyerrloc);
              yyglrShift (yystackp, 0, yyaction,
                          yys->yyposn, &yylval);
              yys = yystackp->yytops.yystates[0];
              break;
            }
        }
      if (yys->yypred != YY_NULLPTR)
        yydestroyGLRState ("Error: popping", yys);
      yystackp->yytops.yystates[0] = yys->yypred;
      yystackp->yynextFree -= 1;
      yystackp->yyspaceLeft += 1;
    }
  if (yystackp->yytops.yystates[0] == YY_NULLPTR)
    yyFail (yystackp, YY_NULLPTR);
}

#define YYCHK1(YYE)                                                          \
  do {                                                                       \
    switch (YYE) {                                                           \
    case yyok:                                                               \
      break;                                                                 \
    case yyabort:                                                            \
      goto yyabortlab;                                                       \
    case yyaccept:                                                           \
      goto yyacceptlab;                                                      \
    case yyerr:                                                              \
      goto yyuser_error;                                                     \
    default:                                                                 \
      goto yybuglab;                                                         \
    }                                                                        \
  } while (0)

/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
  int yyresult;
  yyGLRStack yystack;
  yyGLRStack* const yystackp = &yystack;
  YYPTRDIFF_T yyposn;

  YY_DPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY;
  yylval = yyval_default;

  if (! yyinitGLRStack (yystackp, YYINITDEPTH))
    goto yyexhaustedlab;
  switch (YYSETJMP (yystack.yyexception_buffer))
    {
    case 0: break;
    case 1: goto yyabortlab;
    case 2: goto yyexhaustedlab;
    default: goto yybuglab;
    }
  yyglrShift (&yystack, 0, 0, 0, &yylval);
  yyposn = 0;

  while (yytrue)
    {
      /* For efficiency, we have two loops, the first of which is
         specialized to deterministic operation (single stack, no
         potential ambiguity).  */
      /* Standard mode. */
      while (yytrue)
        {
          yy_state_t yystate = yystack.yytops.yystates[0]->yylrState;
          YY_DPRINTF ((stderr, "Entering state %d\n", yystate));
          if (yystate == YYFINAL)
            goto yyacceptlab;
          if (yyisDefaultedState (yystate))
            {
              yyRuleNum yyrule = yydefaultAction (yystate);
              if (yyrule == 0)
                {
                  yyreportSyntaxError (&yystack);
                  goto yyuser_error;
                }
              YYCHK1 (yyglrReduce (&yystack, 0, yyrule, yytrue));
            }
          else
            {
              yysymbol_kind_t yytoken = yygetToken (&yychar);
              const short* yyconflicts;
              int yyaction = yygetLRActions (yystate, yytoken, &yyconflicts);
              if (*yyconflicts)
                /* Enter nondeterministic mode.  */
                break;
              if (yyisShiftAction (yyaction))
                {
                  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
                  yychar = YYEMPTY;
                  yyposn += 1;
                  yyglrShift (&yystack, 0, yyaction, yyposn, &yylval);
                  if (0 < yystack.yyerrState)
                    yystack.yyerrState -= 1;
                }
              else if (yyisErrorAction (yyaction))
                {
                  /* Issue an error message unless the scanner already
                     did. */
                  if (yychar != YYerror)
                    yyreportSyntaxError (&yystack);
                  goto yyuser_error;
                }
              else
                YYCHK1 (yyglrReduce (&yystack, 0, -yyaction, yytrue));
            }
        }

      /* Nondeterministic mode. */
      while (yytrue)
        {
          yysymbol_kind_t yytoken_to_shift;
          YYPTRDIFF_T yys;

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            yystackp->yytops.yylookaheadNeeds[yys] = yychar != YYEMPTY;

          /* yyprocessOneStack returns one of three things:

              - An error flag.  If the caller is yyprocessOneStack, it
                immediately returns as well.  When the caller is finally
                yyparse, it jumps to an error label via YYCHK1.

              - yyok, but yyprocessOneStack has invoked yymarkStackDeleted
                (&yystack, yys), which sets the top state of yys to NULL.  Thus,
                yyparse's following invocation of yyremoveDeletes will remove
                the stack.

              - yyok, when ready to shift a token.

             Except in the first case, yyparse will invoke yyremoveDeletes and
             then shift the next token onto all remaining stacks.  This
             synchronization of the shift (that is, after all preceding
             reductions on all stacks) helps prevent double destructor calls
             on yylval in the event of memory exhaustion.  */

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            YYCHK1 (yyprocessOneStack (&yystack, yys, yyposn));
          yyremoveDeletes (&yystack);
          if (yystack.yytops.yysize == 0)
            {
              yyundeleteLastStack (&yystack);
              if (yystack.yytops.yysize == 0)
                yyFail (&yystack, YY_("syntax error"));
              YYCHK1 (yyresolveStack (&yystack));
              YY_DPRINTF ((stderr, "Returning to deterministic operation.\n"));
              yyreportSyntaxError (&yystack);
              goto yyuser_error;
            }

          /* If any yyglrShift call fails, it will fail after shifting.  Thus,
             a copy of yylval will already be on stack 0 in the event of a
             failure in the following loop.  Thus, yychar is set to YYEMPTY
             before the loop to make sure the user destructor for yylval isn't
             called twice.  */
          yytoken_to_shift = YYTRANSLATE (yychar);
          yychar = YYEMPTY;
          yyposn += 1;
          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            {
              yy_state_t yystate = yystack.yytops.yystates[yys]->yylrState;
              const short* yyconflicts;
              int yyaction = yygetLRActions (yystate, yytoken_to_shift,
                              &yyconflicts);
              /* Note that yyconflicts were handled by yyprocessOneStack.  */
              YY_DPRINTF ((stderr, "On stack %ld, ", YY_CAST (long, yys)));
              YY_SYMBOL_PRINT ("shifting", yytoken_to_shift, &yylval, &yylloc);
              yyglrShift (&yystack, yys, yyaction, yyposn,
                          &yylval);
              YY_DPRINTF ((stderr, "Stack %ld now in state #%d\n",
                           YY_CAST (long, yys),
                           yystack.yytops.yystates[yys]->yylrState));
            }

          if (yystack.yytops.yysize == 1)
            {
              YYCHK1 (yyresolveStack (&yystack));
              YY_DPRINTF ((stderr, "Returning to deterministic operation.\n"));
              yycompressStack (&yystack);
              break;
            }
        }
      continue;
    yyuser_error:
      yyrecoverSyntaxError (&yystack);
      yyposn = yystack.yytops.yystates[0]->yyposn;
    }

 yyacceptlab:
  yyresult = 0;
  goto yyreturn;

 yybuglab:
  YY_ASSERT (yyfalse);
  goto yyabortlab;

 yyabortlab:
  yyresult = 1;
  goto yyreturn;

 yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;

 yyreturn:
  if (yychar != YYEMPTY)
    yydestruct ("Cleanup: discarding lookahead",
                YYTRANSLATE (yychar), &yylval);

  /* If the stack is well-formed, pop the stack until it is empty,
     destroying its entries as we go.  But free the stack regardless
     of whether it is well-formed.  */
  if (yystack.yyitems)
    {
      yyGLRState** yystates = yystack.yytops.yystates;
      if (yystates)
        {
          YYPTRDIFF_T yysize = yystack.yytops.yysize;
          YYPTRDIFF_T yyk;
          for (yyk = 0; yyk < yysize; yyk += 1)
            if (yystates[yyk])
              {
                while (yystates[yyk])
                  {
                    yyGLRState *yys = yystates[yyk];
                    if (yys->yypred != YY_NULLPTR)
                      yydestroyGLRState ("Cleanup: popping", yys);
                    yystates[yyk] = yys->yypred;
                    yystack.yynextFree -= 1;
                    yystack.yyspaceLeft += 1;
                  }
                break;
              }
        }
      yyfreeGLRStack (&yystack);
    }

  return yyresult;
}

/* DEBUGGING ONLY */
#if YYDEBUG
static void
yy_yypstack (yyGLRState* yys)
{
  if (yys->yypred)
    {
      yy_yypstack (yys->yypred);
      YY_FPRINTF ((stderr, " -> "));
    }
  YY_FPRINTF ((stderr, "%d@%ld", yys->yylrState, YY_CAST (long, yys->yyposn)));
}

static void
yypstates (yyGLRState* yyst)
{
  if (yyst == YY_NULLPTR)
    YY_FPRINTF ((stderr, "<null>"));
  else
    yy_yypstack (yyst);
  YY_FPRINTF ((stderr, "\n"));
}

static void
yypstack (yyGLRStack* yystackp, YYPTRDIFF_T yyk)
{
  yypstates (yystackp->yytops.yystates[yyk]);
}

static void
yypdumpstack (yyGLRStack* yystackp)
{
#define YYINDEX(YYX)                                                    \
  YY_CAST (long,                                                        \
           ((YYX)                                                       \
            ? YY_REINTERPRET_CAST (yyGLRStackItem*, (YYX)) - yystackp->yyitems \
            : -1))

  yyGLRStackItem* yyp;
  for (yyp = yystackp->yyitems; yyp < yystackp->yynextFree; yyp += 1)
    {
      YY_FPRINTF ((stderr, "%3ld. ",
                   YY_CAST (long, yyp - yystackp->yyitems)));
      if (*YY_REINTERPRET_CAST (yybool *, yyp))
        {
          YY_ASSERT (yyp->yystate.yyisState);
          YY_ASSERT (yyp->yyoption.yyisState);
          YY_FPRINTF ((stderr, "Res: %d, LR State: %d, posn: %ld, pred: %ld",
                       yyp->yystate.yyresolved, yyp->yystate.yylrState,
                       YY_CAST (long, yyp->yystate.yyposn),
                       YYINDEX (yyp->yystate.yypred)));
          if (! yyp->yystate.yyresolved)
            YY_FPRINTF ((stderr, ", firstVal: %ld",
                         YYINDEX (yyp->yystate.yysemantics.yyfirstVal)));
        }
      else
        {
          YY_ASSERT (!yyp->yystate.yyisState);
          YY_ASSERT (!yyp->yyoption.yyisState);
          YY_FPRINTF ((stderr, "Option. rule: %d, state: %ld, next: %ld",
                       yyp->yyoption.yyrule - 1,
                       YYINDEX (yyp->yyoption.yystate),
                       YYINDEX (yyp->yyoption.yynext)));
        }
      YY_FPRINTF ((stderr, "\n"));
    }

  YY_FPRINTF ((stderr, "Tops:"));
  {
    YYPTRDIFF_T yyi;
    for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
      YY_FPRINTF ((stderr, "%ld: %ld; ", YY_CAST (long, yyi),
                   YYINDEX (yystackp->yytops.yystates[yyi])));
    YY_FPRINTF ((stderr, "\n"));
  }
#undef YYINDEX
}
#endif

#undef yylval
#undef yychar
#undef yynerrs




