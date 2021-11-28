/* A Bison parser, made by GNU Bison 3.7.6.  */

/* Skeleton interface for Bison GLR parsers in C

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

#ifndef YY_YY_WRDCBISON_H_INCLUDED
# define YY_YY_WRDCBISON_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    tpack = 258,                   /* tpack  */
    tswitch = 259,                 /* tswitch  */
    tas = 260,                     /* tas  */
    tfor = 261,                    /* tfor  */
    tdef = 262,                    /* tdef  */
    twith = 263,                   /* twith  */
    tret = 264,                    /* tret  */
    treturn = 265,                 /* treturn  */
    tif = 266,                     /* tif  */
    telse = 267,                   /* telse  */
    telif = 268,                   /* telif  */
    tfrom = 269,                   /* tfrom  */
    tnext = 270,                   /* tnext  */
    tprop = 271,                   /* tprop  */
    timport = 272,                 /* timport  */
    taka = 273,                    /* taka  */
    tthis = 274,                   /* tthis  */
    tnode = 275,                   /* tnode  */
    tin = 276,                     /* tin  */
    tindent = 277,                 /* tindent  */
    tdedent = 278,                 /* tdedent  */
    tnull = 279,                   /* tnull  */
    teof = 280,                    /* teof  */
    tnum = 281,                    /* tnum  */
    tbool = 282,                   /* tbool  */
    tchar = 283,                   /* tchar  */
    tstr = 284,                    /* tstr  */
    tfctor = 285,                  /* tfctor  */
    tfdtor = 286,                  /* tfdtor  */
    tfget = 287,                   /* tfget  */
    tfset = 288,                   /* tfset  */
    tfres = 289,                   /* tfres  */
    tnormalId = 290,               /* tnormalId  */
    taccessedId = 291,             /* taccessedId  */
    tconName = 292,                /* tconName  */
    teol = 293,                    /* teol  */
    topDefAssign = 294,            /* topDefAssign  */
    topMinusAssign = 295,          /* topMinusAssign  */
    topSquareAssign = 296,         /* topSquareAssign  */
    topDivideAssign = 297,         /* topDivideAssign  */
    topModAssign = 298,            /* topModAssign  */
    topPowAssign = 299,            /* topPowAssign  */
    topLessEqual = 300,            /* topLessEqual  */
    topMoreEqual = 301,            /* topMoreEqual  */
    topEqual = 302,                /* topEqual  */
    topRefEqual = 303,             /* topRefEqual  */
    topNotEqual = 304,             /* topNotEqual  */
    topNotRefEqual = 305,          /* topNotRefEqual  */
    topPlusAssign = 306,           /* topPlusAssign  */
    topSeq = 307,                  /* topSeq  */
    topSafeNavi = 308,             /* topSafeNavi  */
    topUplus = 309,                /* topUplus  */
    topUminus = 310                /* topUminus  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 27 "wrdcBison.cpp"

    int typeId;
    int intVal;
    float floatVal;
    bool boolVal;
    char charVal;
    const char* strVal;
    Node* node;
    void* nodes;

#line 125 "wrdcBison.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_WRDCBISON_H_INCLUDED  */
