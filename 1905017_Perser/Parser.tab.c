/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IF = 258,
     ELSE = 259,
     FOR = 260,
     WHILE = 261,
     DO = 262,
     BREAK = 263,
     INT = 264,
     CHAR = 265,
     FLOAT = 266,
     DOUBLE = 267,
     VOID = 268,
     RETURN = 269,
     SWITCH = 270,
     CASE = 271,
     DEFAULT = 272,
     CONTINUE = 273,
     ADDOP = 274,
     MULOP = 275,
     RELOP = 276,
     LOGICOP = 277,
     INCOP = 278,
     DECOP = 279,
     ASSIGNOP = 280,
     NOT = 281,
     LPAREN = 282,
     RPAREN = 283,
     LCURL = 284,
     RCURL = 285,
     LSQUARE = 286,
     RSQUARE = 287,
     COMMA = 288,
     SEMICOLON = 289,
     CONST_INT = 290,
     CONST_FLOAT = 291,
     CONST_CHAR = 292,
     ID = 293,
     LOWER_THAN_ELSE = 294,
     PRINTLN = 295
   };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define FOR 260
#define WHILE 261
#define DO 262
#define BREAK 263
#define INT 264
#define CHAR 265
#define FLOAT 266
#define DOUBLE 267
#define VOID 268
#define RETURN 269
#define SWITCH 270
#define CASE 271
#define DEFAULT 272
#define CONTINUE 273
#define ADDOP 274
#define MULOP 275
#define RELOP 276
#define LOGICOP 277
#define INCOP 278
#define DECOP 279
#define ASSIGNOP 280
#define NOT 281
#define LPAREN 282
#define RPAREN 283
#define LCURL 284
#define RCURL 285
#define LSQUARE 286
#define RSQUARE 287
#define COMMA 288
#define SEMICOLON 289
#define CONST_INT 290
#define CONST_FLOAT 291
#define CONST_CHAR 292
#define ID 293
#define LOWER_THAN_ELSE 294
#define PRINTLN 295




/* Copy the first part of user declarations.  */
#line 1 "Parser.y"

  #include <bits/stdc++.h>
  #include "symbolTable.h"
  using namespace std;


  int yyparse(void);
  int yylex(void);
  extern FILE *yyin;
  extern int yylineno;
  symbolTable st=symbolTable(30);

  //int errorCount=0;
  //ofstream errorOut;
  ofstream parseTree;

  void dfs(symbolInfo* symbol){
    if(symbol->childList.size()==0) 
      {
        parseTree << symbol->getType() + " "+ symbol->getName() + "<Line: "<< symbol->getStartLine() <<"-"<<symbol->getEndLine()<<">"<<endl;
        return;
      }

    parseTree << symbol->getType() + " "+ symbol->getName() + "<Line: " << symbol->getStartLine()<<"-"<<symbol->getEndLine()<<">"<<endl;

    for(int i=0;i<symbol->childList.size();i++){
      dfs(symbol->childList[i]);
    }    

  }

  void yyerror(const char* s){
		
  }



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 38 "Parser.y"
{
  symbolInfo* symbol;
}
/* Line 193 of yacc.c.  */
#line 217 "Parser.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 230 "Parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   172

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNRULES -- Number of states.  */
#define YYNSTATES  119

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   295

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    23,
      29,    36,    42,    47,    51,    54,    56,    60,    63,    67,
      69,    71,    73,    77,    84,    86,    91,    93,    96,    98,
     100,   102,   110,   117,   125,   131,   137,   141,   143,   146,
     148,   153,   155,   159,   161,   165,   167,   171,   173,   177,
     179,   183,   186,   189,   191,   193,   198,   202,   204,   206,
     209,   212,   214,   215,   219
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      42,     0,    -1,    43,    -1,    43,    44,    -1,    44,    -1,
      49,    -1,    45,    -1,    46,    -1,    50,    38,    27,    47,
      28,    34,    -1,    50,    38,    27,    28,    34,    -1,    50,
      38,    27,    47,    28,    48,    -1,    50,    38,    27,    28,
      48,    -1,    47,    33,    50,    38,    -1,    47,    33,    50,
      -1,    50,    38,    -1,    50,    -1,    29,    52,    30,    -1,
      29,    30,    -1,    50,    51,    34,    -1,     9,    -1,    11,
      -1,    13,    -1,    51,    33,    38,    -1,    51,    33,    38,
      31,    35,    32,    -1,    38,    -1,    38,    31,    35,    32,
      -1,    53,    -1,    52,    53,    -1,    49,    -1,    54,    -1,
      48,    -1,     5,    27,    54,    54,    56,    28,    53,    -1,
       3,    27,    56,    28,    53,    39,    -1,     3,    27,    56,
      28,    53,     4,    53,    -1,     6,    27,    56,    28,    53,
      -1,    40,    27,    38,    28,    34,    -1,    14,    56,    34,
      -1,    34,    -1,    56,    34,    -1,    38,    -1,    38,    31,
      56,    32,    -1,    57,    -1,    55,    25,    57,    -1,    58,
      -1,    58,    22,    58,    -1,    59,    -1,    59,    21,    59,
      -1,    60,    -1,    59,    19,    60,    -1,    61,    -1,    60,
      20,    61,    -1,    19,    61,    -1,    26,    61,    -1,    62,
      -1,    55,    -1,    38,    27,    63,    28,    -1,    27,    56,
      28,    -1,    35,    -1,    36,    -1,    55,    23,    -1,    55,
      24,    -1,    64,    -1,    -1,    64,    33,    57,    -1,    57,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    58,    58,    65,    70,    77,    81,    85,    91,   100,
     110,   119,   130,   137,   143,   148,   154,   160,   167,   175,
     179,   183,   189,   195,   204,   208,   217,   221,   228,   232,
     236,   240,   250,   259,   269,   277,   285,   293,   297,   304,
     308,   317,   321,   329,   333,   341,   345,   353,   357,   365,
     369,   377,   382,   387,   393,   397,   404,   410,   414,   418,
     423,   430,   434,   440,   446
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "FOR", "WHILE", "DO",
  "BREAK", "INT", "CHAR", "FLOAT", "DOUBLE", "VOID", "RETURN", "SWITCH",
  "CASE", "DEFAULT", "CONTINUE", "ADDOP", "MULOP", "RELOP", "LOGICOP",
  "INCOP", "DECOP", "ASSIGNOP", "NOT", "LPAREN", "RPAREN", "LCURL",
  "RCURL", "LSQUARE", "RSQUARE", "COMMA", "SEMICOLON", "CONST_INT",
  "CONST_FLOAT", "CONST_CHAR", "ID", "LOWER_THAN_ELSE", "PRINTLN",
  "$accept", "start", "program", "unit", "func_declaration",
  "func_definition", "parameter_list", "compound_statement",
  "var_declaration", "type_specifier", "declaration_list", "statements",
  "statement", "expression_statement", "variable", "expression",
  "logic_expression", "rel_expression", "simple_expression", "term",
  "unary_expression", "factor", "argument_list", "arguments", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    44,    44,    45,    45,
      46,    46,    47,    47,    47,    47,    48,    48,    49,    50,
      50,    50,    51,    51,    51,    51,    52,    52,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    54,    54,    55,
      55,    56,    56,    57,    57,    58,    58,    59,    59,    60,
      60,    61,    61,    61,    62,    62,    62,    62,    62,    62,
      62,    63,    63,    64,    64
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       6,     5,     4,     3,     2,     1,     3,     2,     3,     1,
       1,     1,     3,     6,     1,     4,     1,     2,     1,     1,
       1,     7,     6,     7,     5,     5,     3,     1,     2,     1,
       4,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     2,     2,     1,     1,     4,     3,     1,     1,     2,
       2,     1,     0,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    19,    20,    21,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    24,     0,     0,     0,     0,    18,     0,
       0,    15,     0,    22,     0,     9,    11,     0,     0,    14,
      25,     0,     0,     0,     0,     0,     0,     0,     0,    17,
      37,    57,    58,    39,     0,    30,    28,     0,     0,    26,
      29,    54,     0,    41,    43,    45,    47,    49,    53,     8,
      10,    13,     0,     0,     0,     0,     0,    54,    51,    52,
       0,    62,     0,     0,    24,    16,    27,    59,    60,     0,
      38,     0,     0,     0,     0,    12,    23,     0,     0,     0,
      36,    56,    64,     0,    61,     0,     0,    42,    44,    48,
      46,    50,     0,     0,     0,    55,     0,    40,     0,     0,
       0,    34,    63,    35,     0,    32,     0,    33,    31
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,    20,    45,    46,    47,
      14,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    93,    94
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -70
static const yytype_int8 yypact[] =
{
      75,   -70,   -70,   -70,     5,    75,   -70,   -70,   -70,   -70,
     -13,   -70,   -70,    -8,   -17,     2,     3,    20,   -70,    -2,
      26,    41,    55,    60,    63,   -70,   -70,    31,    75,   -70,
     -70,    65,    82,    84,    87,   121,   121,   121,   121,   -70,
     -70,   -70,   -70,    54,    88,   -70,   -70,    79,    99,   -70,
     -70,    71,    85,   -70,    94,    43,   100,   -70,   -70,   -70,
     -70,    86,    89,   121,   117,   121,    93,    83,   -70,   -70,
      95,   121,   121,    92,    91,   -70,   -70,   -70,   -70,   121,
     -70,   121,   121,   121,   121,   -70,   -70,   103,   117,   104,
     -70,   -70,   -70,   110,   108,   113,   114,   -70,   -70,   100,
     127,   -70,    15,   121,    15,   -70,   121,   -70,   115,     0,
     122,   -70,   -70,   -70,    15,   -70,    15,   -70,   -70
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -70,   -70,   -70,   149,   -70,   -70,   -70,    -5,    78,    52,
     -70,   -70,   -41,   -52,   -36,   -32,   -69,    77,    80,    90,
     -28,   -70,   -70,   -70
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      67,    67,    92,    66,   114,    11,    70,    76,    68,    69,
      97,     1,    88,     2,    26,     3,    17,    18,    32,    15,
      33,    34,    60,    16,     1,    13,     2,    24,     3,    35,
      19,    87,    25,    89,    36,    67,   103,   112,    22,   115,
      95,    37,    38,    67,    24,    67,    67,    67,    67,    40,
      41,    42,    10,    43,    27,    44,   101,    10,    23,    28,
      24,   109,    82,   111,    83,    59,    32,    21,    33,    34,
      67,   110,     1,   117,     2,   118,     3,    35,     9,    29,
      61,    71,    36,     9,     1,    72,     2,    30,     3,    37,
      38,    31,    24,    39,    77,    78,    79,    40,    41,    42,
      62,    43,    32,    44,    33,    34,    77,    78,     1,    63,
       2,    64,     3,    35,    65,    73,    81,    74,    36,    80,
      84,    86,    16,    91,    85,    37,    38,    90,    24,    75,
      96,   102,   104,    40,    41,    42,    36,    43,   105,    44,
      36,   106,   108,    37,    38,   107,    82,    37,    38,   113,
     116,    40,    41,    42,    12,    43,    41,    42,    98,    43,
       0,     0,     0,   100,     0,     0,     0,     0,     0,     0,
       0,     0,    99
};

static const yytype_int8 yycheck[] =
{
      36,    37,    71,    35,     4,     0,    38,    48,    36,    37,
      79,     9,    64,    11,    19,    13,    33,    34,     3,    27,
       5,     6,    27,    31,     9,    38,    11,    29,    13,    14,
      28,    63,    34,    65,    19,    71,    88,   106,    35,    39,
      72,    26,    27,    79,    29,    81,    82,    83,    84,    34,
      35,    36,     0,    38,    28,    40,    84,     5,    38,    33,
      29,   102,    19,   104,    21,    34,     3,    15,     5,     6,
     106,   103,     9,   114,    11,   116,    13,    14,     0,    38,
      28,    27,    19,     5,     9,    31,    11,    32,    13,    26,
      27,    31,    29,    30,    23,    24,    25,    34,    35,    36,
      35,    38,     3,    40,     5,     6,    23,    24,     9,    27,
      11,    27,    13,    14,    27,    27,    22,    38,    19,    34,
      20,    32,    31,    28,    38,    26,    27,    34,    29,    30,
      38,    28,    28,    34,    35,    36,    19,    38,    28,    40,
      19,    33,    28,    26,    27,    32,    19,    26,    27,    34,
      28,    34,    35,    36,     5,    38,    35,    36,    81,    38,
      -1,    -1,    -1,    83,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    11,    13,    42,    43,    44,    45,    46,    49,
      50,     0,    44,    38,    51,    27,    31,    33,    34,    28,
      47,    50,    35,    38,    29,    34,    48,    28,    33,    38,
      32,    31,     3,     5,     6,    14,    19,    26,    27,    30,
      34,    35,    36,    38,    40,    48,    49,    50,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    34,
      48,    50,    35,    27,    27,    27,    56,    55,    61,    61,
      56,    27,    31,    27,    38,    30,    53,    23,    24,    25,
      34,    22,    19,    21,    20,    38,    32,    56,    54,    56,
      34,    28,    57,    63,    64,    56,    38,    57,    58,    60,
      59,    61,    28,    54,    28,    28,    33,    32,    28,    53,
      56,    53,    57,    34,     4,    39,    28,    53,    53
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 58 "Parser.y"
    {
   (yyval.symbol)=new symbolInfo("program","start",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
   (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
   dfs((yyval.symbol));
;}
    break;

  case 3:
#line 65 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("program unit","program",(yyvsp[(1) - (2)].symbol)->getStartLine(),(yyvsp[(2) - (2)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (2)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (2)].symbol));
;}
    break;

  case 4:
#line 70 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("unit","program",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
;}
    break;

  case 5:
#line 77 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("var_declaration","unit",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)-> childList.push_back((yyvsp[(1) - (1)].symbol));
;}
    break;

  case 6:
#line 81 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("func_declaration","unit",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)-> childList.push_back((yyvsp[(1) - (1)].symbol));
;}
    break;

  case 7:
#line 85 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("func_definition","unit",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)-> childList.push_back((yyvsp[(1) - (1)].symbol));
;}
    break;

  case 8:
#line 91 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("type_specifier ID LPAREN parameter_list RPAREN SEMICOLON","func_declaration",(yyvsp[(1) - (6)].symbol)->getStartLine(),(yyvsp[(6) - (6)].symbol)->getEndLine());
  (yyval.symbol)-> childList.push_back((yyvsp[(1) - (6)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(2) - (6)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(3) - (6)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(4) - (6)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(5) - (6)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(6) - (6)].symbol));
;}
    break;

  case 9:
#line 100 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("type_specifier ID LPAREN RPAREN SEMICOLON","func_declaration",(yyvsp[(1) - (5)].symbol)->getStartLine(),(yyvsp[(5) - (5)].symbol)->getEndLine());
  (yyval.symbol)-> childList.push_back((yyvsp[(1) - (5)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(2) - (5)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(3) - (5)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(4) - (5)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(5) - (5)].symbol)); 
;}
    break;

  case 10:
#line 110 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("type_specifier ID LPAREN parameter_list RPAREN compound_statement","func_definition",(yyvsp[(1) - (6)].symbol)->getStartLine(),(yyvsp[(6) - (6)].symbol)->getEndLine());
  (yyval.symbol)-> childList.push_back((yyvsp[(1) - (6)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(2) - (6)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(3) - (6)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(4) - (6)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(5) - (6)].symbol)); 
  (yyval.symbol)->childList.push_back((yyvsp[(6) - (6)].symbol));
;}
    break;

  case 11:
#line 119 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("type_specifier ID LPAREN RPAREN compound_statement","func_definition",(yyvsp[(1) - (5)].symbol)->getStartLine(),(yyvsp[(5) - (5)].symbol)->getEndLine());
  (yyval.symbol)-> childList.push_back((yyvsp[(1) - (5)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(2) - (5)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(3) - (5)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(4) - (5)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(5) - (5)].symbol)); 
  
;}
    break;

  case 12:
#line 130 "Parser.y"
    {
 (yyval.symbol) = new symbolInfo("parameter_list COMMA type_specifier ID","parameter_list",(yyvsp[(1) - (4)].symbol)->getStartLine(),(yyvsp[(4) - (4)].symbol)->getEndLine());
 (yyval.symbol)->childList.push_back((yyvsp[(1) - (4)].symbol));
 (yyval.symbol)->childList.push_back((yyvsp[(2) - (4)].symbol));
 (yyval.symbol)->childList.push_back((yyvsp[(3) - (4)].symbol));
 (yyval.symbol)->childList.push_back((yyvsp[(4) - (4)].symbol));
;}
    break;

  case 13:
#line 137 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("parameter_list COMMA type_specifier","parameter_list",(yyvsp[(1) - (3)].symbol)->getStartLine(),(yyvsp[(3) - (3)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (3)].symbol));
;}
    break;

  case 14:
#line 143 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("type_specifier ID","parameter_list",(yyvsp[(1) - (2)].symbol)->getStartLine(),(yyvsp[(2) - (2)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (2)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (2)].symbol));
;}
    break;

  case 15:
#line 148 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("type_specifier","parameter_list",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
;}
    break;

  case 16:
#line 154 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("LCURL statements RCURL","compound_statement",(yyvsp[(1) - (3)].symbol)->getStartLine(),(yyvsp[(3) - (3)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (3)].symbol));
;}
    break;

  case 17:
#line 160 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("LCURL RCURL","compound_statement",(yyvsp[(1) - (2)].symbol)->getStartLine(),(yyvsp[(2) - (2)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (2)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (2)].symbol));
;}
    break;

  case 18:
#line 167 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("type_specifier declaration_list SEMICOLON","var_declaration",(yyvsp[(1) - (3)].symbol)->getStartLine(),(yyvsp[(3) - (3)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (3)].symbol));
;}
    break;

  case 19:
#line 175 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("INT","type_specifier",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
;}
    break;

  case 20:
#line 179 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("FLOAT","type_specifier",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
;}
    break;

  case 21:
#line 183 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("VOID","type_specifier",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
;}
    break;

  case 22:
#line 189 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("declaration_list COMMA ID", "declaration_list",(yyvsp[(1) - (3)].symbol)->getStartLine(),(yyvsp[(3) - (3)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (3)].symbol));
;}
    break;

  case 23:
#line 195 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("declaration_list COMMA ID LSQUARE CONST_INT RSQUARE", "declaration_list",(yyvsp[(1) - (6)].symbol)->getStartLine(),(yyvsp[(6) - (6)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (6)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (6)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (6)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(4) - (6)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(5) - (6)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(6) - (6)].symbol));
;}
    break;

  case 24:
#line 204 "Parser.y"
    {
  (yyval.symbol)= new symbolInfo("ID","declaration_list",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
;}
    break;

  case 25:
#line 208 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("ID LSQUARE CONST_INT RSQUARE","declaration_list",(yyvsp[(1) - (4)].symbol)->getStartLine(),(yyvsp[(4) - (4)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (4)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (4)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (4)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(4) - (4)].symbol));
;}
    break;

  case 26:
#line 217 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("statement","statements",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
;}
    break;

  case 27:
#line 221 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("statements statment","statements",(yyvsp[(1) - (2)].symbol)->getStartLine(),(yyvsp[(2) - (2)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (2)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (2)].symbol));
;}
    break;

  case 28:
#line 228 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("var_declaration","statement",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
;}
    break;

  case 29:
#line 232 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("expression_statement","statement",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
;}
    break;

  case 30:
#line 236 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("compound_statement","statement",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
;}
    break;

  case 31:
#line 240 "Parser.y"
    {
  (yyval.symbol)= new symbolInfo("FOR LPAREN expression_statement expression_statement expression RPAREN statement","statement",(yyvsp[(1) - (7)].symbol)->getStartLine(),(yyvsp[(7) - (7)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (7)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (7)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (7)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(4) - (7)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(5) - (7)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(6) - (7)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(7) - (7)].symbol));
;}
    break;

  case 32:
#line 250 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("IF LPAREN expression RPAREN statement LOWER_THAN_ELSE","statement",(yyvsp[(1) - (6)].symbol)->getStartLine(),(yyvsp[(6) - (6)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (6)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (6)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (6)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(4) - (6)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(5) - (6)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(6) - (6)].symbol));
;}
    break;

  case 33:
#line 259 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("IF LPAREN expression RPAREN statement ELSE statement","statement",(yyvsp[(1) - (7)].symbol)->getStartLine(),(yyvsp[(7) - (7)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (7)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (7)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (7)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(4) - (7)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(5) - (7)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(6) - (7)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(7) - (7)].symbol));
;}
    break;

  case 34:
#line 269 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("WHILE LPAREN expression RPAREN statement","statement",(yyvsp[(1) - (5)].symbol)->getStartLine(),(yyvsp[(5) - (5)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (5)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (5)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (5)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(4) - (5)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(5) - (5)].symbol));
;}
    break;

  case 35:
#line 277 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("PRINTLN LPAREN ID RPAREN SEMICOLON","statement",(yyvsp[(1) - (5)].symbol)->getStartLine(),(yyvsp[(5) - (5)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (5)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (5)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (5)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(4) - (5)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(5) - (5)].symbol));
;}
    break;

  case 36:
#line 285 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("RETURN expression SEMICOLON","statement",(yyvsp[(1) - (3)].symbol)->getStartLine(),(yyvsp[(3) - (3)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (3)].symbol));
;}
    break;

  case 37:
#line 293 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("SEMICOLON","expression_statement",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
;}
    break;

  case 38:
#line 297 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("expression SEMICOLON","expression_statement",(yyvsp[(1) - (2)].symbol)->getStartLine(),(yyvsp[(2) - (2)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (2)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (2)].symbol));
;}
    break;

  case 39:
#line 304 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("ID","variable",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
;}
    break;

  case 40:
#line 308 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("ID LSQUARE expression RSQUARE","variable",(yyvsp[(1) - (4)].symbol)->getStartLine(),(yyvsp[(4) - (4)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (4)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (4)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (4)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(4) - (4)].symbol));
;}
    break;

  case 41:
#line 317 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("logic_expression","expression",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
;}
    break;

  case 42:
#line 321 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("variable ASSIGNOP logic_expression","expression",(yyvsp[(1) - (3)].symbol)->getStartLine(),(yyvsp[(3) - (3)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (3)].symbol));
;}
    break;

  case 43:
#line 329 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("rel_expression","logic_expression",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
;}
    break;

  case 44:
#line 333 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("rel_expression LOGICOP rel_expression","logic_expression",(yyvsp[(1) - (3)].symbol)->getStartLine(),(yyvsp[(3) - (3)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (3)].symbol));
;}
    break;

  case 45:
#line 341 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("simple_expression","rel_expression",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
;}
    break;

  case 46:
#line 345 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("simple_expression RELOP simple_expression","rel_expression",(yyvsp[(1) - (3)].symbol)->getStartLine(),(yyvsp[(3) - (3)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (3)].symbol));
;}
    break;

  case 47:
#line 353 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("term","simple_expression",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
;}
    break;

  case 48:
#line 357 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("rsimple_expression ADDOP term","simple_expression",(yyvsp[(1) - (3)].symbol)->getStartLine(),(yyvsp[(3) - (3)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (3)].symbol));
;}
    break;

  case 49:
#line 365 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("unary_expression","term",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
;}
    break;

  case 50:
#line 369 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("term MULOP unary_expression","term",(yyvsp[(1) - (3)].symbol)->getStartLine(),(yyvsp[(3) - (3)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (3)].symbol));
;}
    break;

  case 51:
#line 377 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("ADDOP unary_expression","unary_expression",(yyvsp[(1) - (2)].symbol)->getStartLine(),(yyvsp[(2) - (2)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (2)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (2)].symbol));
;}
    break;

  case 52:
#line 382 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("NOT unary_expression","unary_expression",(yyvsp[(1) - (2)].symbol)->getStartLine(),(yyvsp[(2) - (2)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (2)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (2)].symbol));
;}
    break;

  case 53:
#line 387 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("factor","unary_expression",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
;}
    break;

  case 54:
#line 393 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("variable","factor",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
;}
    break;

  case 55:
#line 397 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("ID LPAREN argument_list RPAREN","factor",(yyvsp[(1) - (4)].symbol)->getStartLine(),(yyvsp[(4) - (4)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (4)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (4)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (4)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(4) - (4)].symbol));
;}
    break;

  case 56:
#line 404 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("LPAREN expression RPAREN","factor",(yyvsp[(1) - (3)].symbol)->getStartLine(),(yyvsp[(3) - (3)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (3)].symbol));
;}
    break;

  case 57:
#line 410 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("CONST_INT","factor",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
;}
    break;

  case 58:
#line 414 "Parser.y"
    {
 (yyval.symbol)=new symbolInfo("CONST_FLOAT","factor",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol)); 
;}
    break;

  case 59:
#line 418 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("variable INCOP","factor",(yyvsp[(1) - (2)].symbol)->getStartLine(),(yyvsp[(2) - (2)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (2)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (2)].symbol));
;}
    break;

  case 60:
#line 423 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("variable DECOP","factor",(yyvsp[(1) - (2)].symbol)->getStartLine(),(yyvsp[(2) - (2)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (2)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (2)].symbol));
;}
    break;

  case 61:
#line 430 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("arguments","argument_list",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
;}
    break;

  case 62:
#line 434 "Parser.y"
    {
  /*$$=new symbolInfo("","arguments",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);*/
;}
    break;

  case 63:
#line 440 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("arguments COMMA logic_expression","arguments",(yyvsp[(1) - (3)].symbol)->getStartLine(),(yyvsp[(3) - (3)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (3)].symbol));
;}
    break;

  case 64:
#line 446 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("logic_expression","arguments",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
;}
    break;


/* Line 1267 of yacc.c.  */
#line 2143 "Parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 451 "Parser.y"


int main(int argc,char *argv[]){
    if(argc != 2){
        cout<<"Please provide input file name and try again."<<endl;
        return 0;
    }
    FILE *fin = freopen(argv[1], "r", stdin);
    if(fin == nullptr){
        cout<<"Can't open specified file."<<endl;
        return 0;
    }
	cout<<argv[1]<<" opened successfully."<<endl;
	
    //errorOut.open("error.txt");
    freopen("log.txt", "w", stdout);
    // if we don't init the yyin, it will use stdin(console)
    yyin = fin;

    yylineno = 1; // line number starts from 1

    // start scanning the file here
	yyparse();

    fclose(yyin);
    return 0;
}
