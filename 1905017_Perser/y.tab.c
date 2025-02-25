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
     LOWER_THAN_ELSE = 293,
     ID = 294
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
#define LOWER_THAN_ELSE 293
#define ID 294




/* Copy the first part of user declarations.  */
#line 1 "Parser.y"

  #include <bits/stdc++.h>
  #include "symbolTable.h"
  using namespace std;


  int yyparse(void);
  int yylex(void);
  extern FILE *yyin;
  extern int yylineno;
  bool isErrorHasOccured=false;
  int extraInt=0;

  symbolTable st=symbolTable(30);
  
  int errorCount = 0;
  ofstream errorFile;
  vector<symbolInfo*>* functionParamList = NULL;
  int paramDeclineNo;
  ofstream parseTree;

  /*void dfs(symbolInfo* symbol){
    if(symbol->childList.size()==0) 
      {
        parseTree << symbol->getType() + " "+ symbol->getName() + "<Line: "<< symbol->getStartLine() <<"-"<<symbol->getEndLine()<<">"<<endl;
        return;
      }

    parseTree << symbol->getType() + " "+ symbol->getName() + "<Line: " << symbol->getStartLine()<<"-"<<symbol->getEndLine()<<">"<<endl;

    for(int i=0;i<symbol->childList.size();i++){
      dfs(symbol->childList[i]);
    }    

  }*/

  void dfs(symbolInfo* symbol,int space){
    parseTree << symbol->getType() +" : " + symbol->getName();
    if(symbol->childList.size()==0){
      parseTree << "\t" <<"<Line: "<<symbol->getStartLine()<<">"<<endl;
    }
    else {
      parseTree << " \t" << "<Line: "<<symbol->getStartLine()<<"-"<<symbol->getEndLine()<<">"<<endl;
    }

    for(int i=0; i<symbol->childList.size();i++){
        for(int j=0;j<space;j++){
          parseTree<<" ";
        }
        dfs(symbol->childList[i],space+1);
    }
  }

  void yyerror(const char* s){
		
  }

  void debuggerFlag(){
    cout<<"The debuggerFlag is here ------------------------------------------------"<<endl;
  }

  void writeErrorFile(string str, int n=-1){
    int lineNo;
    if(n==-1){
      lineNo=yylineno;
    }else{
      lineNo=n;
    }
    
    //Line# 20: Redefinition of parameter 'a'
    string s="Line# "+to_string(lineNo)+": "+str;
    //string s="Error at line "+ to_string(lineNo) +": "+str+"\n";
    //errorFile<<"Error at line "<<n<<": "<<str<<"\n"<<endl;
    errorFile<<s<<endl;
    //cout<<s<<endl;
    errorCount++;
  }

  void writeLogFile(string str1,string str2){
    cout<<str1<<" : "<<str2<<endl;
  }

  void declareFuncParamList(vector<symbolInfo*>* &symbolList, int lineNo=yylineno){
    if(symbolList == NULL){
      return;
    }

    for(symbolInfo* si : *symbolList){
      string dataType=si->getDataTypeOrReturnType();
      string name = si->getName();
      int lineno = yylineno;

      if(dataType == "void"){
        writeErrorFile("Function parameter cannot be void");
        continue;
      }

      if(st.insert(name,"ID")){
        symbolInfo* info=st.LookUp(name);
        info->setDataTypeOrReturnType(dataType);
        continue;
      }

      //writeErrorFile("Multiple declaration of "+name+" in parameter",lineNo);
      writeErrorFile((string)"Redefinition of parameter '"+(string)name+(string)"'",lineNo);

    }
    symbolList->clear();
  }




  void declareFunction(string funcName, string returnType, vector<symbolInfo*>* paramList= NULL , int lineNo=yylineno){
    bool isInserted = st.insert(funcName, "FUNCTION");

    symbolInfo* si = st.LookUp(funcName);

    if(isInserted){
      si->setIsVariableOrFunction(2);
      si->setDataTypeOrReturnType(returnType);

      if(paramList != NULL){
        for(symbolInfo* para : *paramList){
          si->parameters.push_back({para->getDataTypeOrReturnType(),para->getName()});
        }
      }
    }
    else{
      if(si->getIsVariableOrFunction()== 2){
        writeErrorFile((string)"redeclaration of '"+(string)funcName+(string)"'", lineNo);
        return ;
      }
    }
  }

  bool checkVoidFunction(symbolInfo *a, symbolInfo *b){
    if(a->getDataTypeOrReturnType()=="void" || b->getDataTypeOrReturnType()=="void"){
      writeErrorFile("Void cannot be used in expression ");
      return true;
    }
    return false;
  }

  string typeCasting(symbolInfo *a, symbolInfo *b){
    if(a->getDataTypeOrReturnType() == b->getDataTypeOrReturnType()){
      return a->getDataTypeOrReturnType();
    }

    if(a->getDataTypeOrReturnType()=="int" && b->getDataTypeOrReturnType()=="float"){
      return "float";
    }

    if(a->getDataTypeOrReturnType()=="float" && b->getDataTypeOrReturnType()=="int"){
      return "float";
    }

    if(a->getDataTypeOrReturnType()=="void")
      return b->getDataTypeOrReturnType();
    else 
      return a->getDataTypeOrReturnType();
  }

  void defineFunction(string functionName, string returnType, int lineNo=yylineno, vector<symbolInfo*>* parameterList=NULL){
    symbolInfo* info= st.LookUp(functionName);

    if(info == NULL){
      st.insert(functionName,"FUNCTION");
      info = st.LookUp(functionName);
    }else{
      if(info->getIsVariableOrFunction() == 2){
        if(info->getDataTypeOrReturnType() != returnType){
          writeErrorFile((string)"Conflicting types for '"+(string)functionName+(string)"'",lineNo);
          return;
        }

        vector<pair<string,string>> paramsInDefine = info->parameters;

        int paramCount=0;
        if(parameterList==NULL) paramCount=0;
        else paramCount=parameterList->size();

        if(paramsInDefine.size()!= paramCount){
          //writeErrorFile("Numbers of arguments doesnt match declaration of function "+functionName,lineNo);
          writeErrorFile((string)"Conflicting types for '"+(string)functionName+(string)"'",lineNo);
          return;
        } 
        if(parameterList != NULL){

          vector<symbolInfo*> paramList= *parameterList;
          for(int i=0;i<paramsInDefine.size();i++){

            if(paramsInDefine[i].first != paramList[i]->getDataTypeOrReturnType()){
              writeErrorFile((string)"Conflicting argument types for '"+(string)functionName+(string)"'",lineNo);
              return;
            }
          }
        }
      }else{
        if(info->getIsVariableOrFunction()==1)
          writeErrorFile((string)"'"+(string)functionName+(string)"' redeclared as different kind of symbol");
        return;
      }
    }

    if(info->getIsVariableOrFunction() == 3){
      writeErrorFile((string)"redefinition of '"+(string)functionName+(string)"'",lineNo);
      return;
    }


    info->setIsVariableOrFunction(3);
    info->setReturnType(returnType);
    info->parameters=vector<pair<string,string>> ();

    if(parameterList != NULL){
      for(symbolInfo* si : *parameterList){

        /*for(auto x: info->parameters){
          if(x.second == si->getName()){
            writeErrorFile("Redefinition of parameter "+si->getName());
            return;
          }
        }*/
        info->parameters.push_back({si->getDataTypeOrReturnType(), si->getName()});
      }
    }
  }

  void callFunction(symbolInfo* &func, vector<symbolInfo*>* args=NULL){
    string funcName=func->getName();
    symbolInfo* info=st.LookUp(funcName);

    if(info==NULL){
      writeErrorFile((string)"Undeclared function '"+(string)funcName+(string)"'");
      return;
    }

    if(!info->isItFunction()){
      writeErrorFile((string)"'"+(string)funcName+(string)"' is not a function");
      return;
    }
    func->setDataTypeOrReturnType(info->getDataTypeOrReturnType());

    if(info->getIsVariableOrFunction() != 3){
      writeErrorFile((string)"Function '"+(string)funcName+(string)"' is not defined");
      return;
    }

    vector<pair<string,string>> params=info->parameters;

    int paramCount=0;
    if(args == NULL ) paramCount=0;
    else paramCount=args->size();

    if(params.size() != paramCount){
      //writeErrorFile("Total number of arguments mismatch in function "+funcName);
      if(params.size()> paramCount){
        writeErrorFile((string)"Too few arguments to function '"+(string)funcName+(string)"'");
      }
      else{
        writeErrorFile((string)"Too many arguments to function '"+(string)funcName+(string)"'");
      }
      return;
    } 

    if(args != NULL){
      vector<symbolInfo*> argList= *args;

      bool isOkay=true;
      
      for(int i=0;i<params.size();i++){
        if(params[i].first != argList[i]->getDataTypeOrReturnType()){
          //writeErrorFile(to_string(i+1)+"th argument mismatch in function "+funcName);
          isOkay=false;
          //debuggerFlag();
          //cout<<params[i].first<<"   "<<argList[i]->getDataTypeOrReturnType()<<endl;
          writeErrorFile((string)"Type mismatch for argument "+(string)to_string(i+1)+(string)" of '"+(string)funcName+(string)"'");
        }
      }
      if(!isOkay) return;
    }
  }


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
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
#line 286 "Parser.y"
{
  symbolInfo* symbol;
}
/* Line 193 of yacc.c.  */
#line 463 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 476 "y.tab.c"

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
#define YYLAST   148

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  74
/* YYNRULES -- Number of states.  */
#define YYNSTATES  128

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

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
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    23,
      29,    30,    38,    39,    46,    47,    48,    57,    62,    66,
      69,    71,    72,    77,    78,    82,    86,    87,    92,    94,
      96,    98,   102,   109,   111,   116,   118,   121,   123,   125,
     127,   135,   141,   149,   155,   159,   161,   164,   165,   169,
     171,   176,   178,   182,   184,   188,   190,   194,   196,   200,
     202,   206,   209,   212,   214,   216,   221,   225,   227,   229,
     232,   235,   237,   238,   242
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      41,     0,    -1,    42,    -1,    42,    43,    -1,    43,    -1,
      54,    -1,    44,    -1,    45,    -1,    56,    39,    27,    50,
      28,    34,    -1,    56,    39,    27,    28,    34,    -1,    -1,
      56,    39,    27,    50,    28,    46,    51,    -1,    -1,    56,
      39,    27,    28,    47,    51,    -1,    -1,    -1,    56,    39,
      27,     1,    48,    28,    49,    51,    -1,    50,    33,    56,
      39,    -1,    50,    33,    56,    -1,    56,    39,    -1,    56,
      -1,    -1,    29,    52,    58,    30,    -1,    -1,    29,    53,
      30,    -1,    56,    57,    34,    -1,    -1,    56,     1,    55,
      34,    -1,     9,    -1,    11,    -1,    13,    -1,    57,    33,
      39,    -1,    57,    33,    39,    31,    35,    32,    -1,    39,
      -1,    39,    31,    35,    32,    -1,    59,    -1,    58,    59,
      -1,    54,    -1,    60,    -1,    51,    -1,     5,    27,    60,
      60,    63,    28,    59,    -1,     3,    27,    63,    28,    59,
      -1,     3,    27,    63,    28,    59,     4,    59,    -1,     6,
      27,    63,    28,    59,    -1,    14,    63,    34,    -1,    34,
      -1,    63,    34,    -1,    -1,     1,    61,    34,    -1,    39,
      -1,    39,    31,    63,    32,    -1,    64,    -1,    62,    25,
      64,    -1,    65,    -1,    65,    22,    65,    -1,    66,    -1,
      66,    21,    66,    -1,    67,    -1,    66,    19,    67,    -1,
      68,    -1,    67,    20,    68,    -1,    19,    68,    -1,    26,
      68,    -1,    69,    -1,    62,    -1,    39,    27,    70,    28,
      -1,    27,    63,    28,    -1,    35,    -1,    36,    -1,    62,
      23,    -1,    62,    24,    -1,    71,    -1,    -1,    71,    33,
      64,    -1,    64,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   307,   307,   320,   327,   336,   343,   350,   358,   372,
     386,   386,   397,   397,   408,   414,   408,   431,   446,   460,
     471,   480,   480,   493,   493,   504,   539,   539,   558,   565,
     572,   581,   591,   605,   611,   624,   632,   643,   651,   658,
     665,   678,   691,   705,   718,   730,   739,   749,   749,   766,
     789,   820,   828,   857,   865,   881,   889,   902,   911,   939,
     947,   990,  1000,  1010,  1022,  1030,  1054,  1064,  1072,  1080,
    1089,  1100,  1109,  1115,  1129
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
  "CONST_FLOAT", "CONST_CHAR", "LOWER_THAN_ELSE", "ID", "$accept", "start",
  "program", "unit", "func_declaration", "func_definition", "@1", "@2",
  "@3", "@4", "parameter_list", "compound_statement", "@5", "@6",
  "var_declaration", "@7", "type_specifier", "declaration_list",
  "statements", "statement", "expression_statement", "@8", "variable",
  "expression", "logic_expression", "rel_expression", "simple_expression",
  "term", "unary_expression", "factor", "argument_list", "arguments", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    43,    44,    44,
      46,    45,    47,    45,    48,    49,    45,    50,    50,    50,
      50,    52,    51,    53,    51,    54,    55,    54,    56,    56,
      56,    57,    57,    57,    57,    58,    58,    59,    59,    59,
      59,    59,    59,    59,    59,    60,    60,    61,    60,    62,
      62,    63,    63,    64,    64,    65,    65,    66,    66,    67,
      67,    68,    68,    68,    69,    69,    69,    69,    69,    69,
      69,    70,    70,    71,    71
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       0,     7,     0,     6,     0,     0,     8,     4,     3,     2,
       1,     0,     4,     0,     3,     3,     0,     4,     1,     1,
       1,     3,     6,     1,     4,     1,     2,     1,     1,     1,
       7,     5,     7,     5,     3,     1,     2,     0,     3,     1,
       4,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     2,     2,     1,     1,     4,     3,     1,     1,     2,
       2,     1,     0,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    28,    29,    30,     0,     2,     4,     6,     7,     5,
       0,     1,     3,    26,    33,     0,     0,     0,     0,     0,
      25,    27,    14,    12,     0,    20,     0,    31,     0,     9,
       0,    10,     0,    19,    34,     0,    15,    21,    13,     8,
       0,    18,     0,     0,     0,     0,    11,    17,    32,    16,
      47,     0,     0,     0,     0,     0,     0,     0,    45,    67,
      68,    49,    39,    37,     0,     0,    35,    38,    64,     0,
      51,    53,    55,    57,    59,    63,    24,     0,     0,     0,
       0,     0,    64,    61,    62,     0,    72,     0,    33,    22,
      36,    69,    70,     0,    46,     0,     0,     0,     0,    48,
       0,     0,     0,    44,    66,    74,     0,    71,     0,    52,
      54,    58,    56,    60,     0,     0,     0,    65,     0,    50,
      41,     0,    43,    73,     0,     0,    42,    40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,     8,    40,    30,    28,    43,
      24,    62,    44,    45,    63,    16,    64,    15,    65,    66,
      67,    77,    68,    69,    70,    71,    72,    73,    74,    75,
     106,   107
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -82
static const yytype_int16 yypact[] =
{
     100,   -82,   -82,   -82,    17,   100,   -82,   -82,   -82,   -82,
       9,   -82,   -82,   -82,    54,    -9,    -2,    73,    22,    -6,
     -82,   -82,   -82,    18,   -13,     5,    26,    29,    38,   -82,
      39,    37,   100,   -82,   -82,    41,   -82,    57,   -82,   -82,
      39,    66,    76,    39,   101,    86,   -82,   -82,   -82,   -82,
     -82,    91,    92,    95,    53,    53,    53,    53,   -82,   -82,
     -82,    90,   -82,   -82,    10,    64,   -82,   -82,    72,    89,
     -82,   102,    -5,   105,   -82,   -82,   -82,    97,    53,    20,
      53,    98,    11,   -82,   -82,   106,    53,    53,   107,   -82,
     -82,   -82,   -82,    53,   -82,    53,    53,    53,    53,   -82,
     111,    20,   113,   -82,   -82,   -82,   114,    93,   112,   -82,
     -82,   105,   110,   -82,   101,    53,   101,   -82,    53,   -82,
     129,   115,   -82,   -82,   101,   101,   -82,   -82
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -82,   -82,   -82,   140,   -82,   -82,   -82,   -82,   -82,   -82,
     -82,   -21,   -82,   -82,    23,   -82,    13,   -82,   -82,   -63,
     -75,   -82,   -55,   -51,   -81,    51,    50,    52,   -48,   -82,
     -82,   -82
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -24
static const yytype_int8 yytable[] =
{
      82,    82,    90,    81,   101,   105,    85,    83,    84,    38,
      13,    13,   109,    10,    96,    31,    97,    11,    10,    46,
      32,    50,    49,     9,    19,    20,   115,   100,     9,   102,
      25,    82,    21,    27,    91,    92,   108,   123,    82,    55,
      82,    82,    82,    82,    33,    41,    56,    57,    14,    88,
     113,   120,    29,   122,    58,    59,    60,    26,    34,    61,
      35,   126,   127,    82,   121,    50,    36,    51,    37,    52,
      53,    39,    55,     1,    22,     2,    42,     3,    54,    56,
      57,    17,     1,    55,     2,    18,     3,   -23,    59,    60,
      56,    57,    61,    37,    89,    91,    92,    93,    58,    59,
      60,    23,    50,    61,    51,    47,    52,    53,    48,     1,
       1,     2,     2,     3,     3,    54,    76,    86,    78,    79,
      55,    87,    80,    94,    95,    98,   118,    56,    57,    96,
      37,    99,   103,   124,   104,    58,    59,    60,    18,   114,
      61,   116,   117,   125,   119,    12,   110,   112,   111
};

static const yytype_uint8 yycheck[] =
{
      55,    56,    65,    54,    79,    86,    57,    55,    56,    30,
       1,     1,    93,     0,    19,    28,    21,     0,     5,    40,
      33,     1,    43,     0,    33,    34,   101,    78,     5,    80,
      17,    86,    34,    39,    23,    24,    87,   118,    93,    19,
      95,    96,    97,    98,    39,    32,    26,    27,    39,    39,
      98,   114,    34,   116,    34,    35,    36,    35,    32,    39,
      31,   124,   125,   118,   115,     1,    28,     3,    29,     5,
       6,    34,    19,     9,     1,    11,    35,    13,    14,    26,
      27,    27,     9,    19,    11,    31,    13,    30,    35,    36,
      26,    27,    39,    29,    30,    23,    24,    25,    34,    35,
      36,    28,     1,    39,     3,    39,     5,     6,    32,     9,
       9,    11,    11,    13,    13,    14,    30,    27,    27,    27,
      19,    31,    27,    34,    22,    20,    33,    26,    27,    19,
      29,    34,    34,     4,    28,    34,    35,    36,    31,    28,
      39,    28,    28,    28,    32,     5,    95,    97,    96
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    11,    13,    41,    42,    43,    44,    45,    54,
      56,     0,    43,     1,    39,    57,    55,    27,    31,    33,
      34,    34,     1,    28,    50,    56,    35,    39,    48,    34,
      47,    28,    33,    39,    32,    31,    28,    29,    51,    34,
      46,    56,    35,    49,    52,    53,    51,    39,    32,    51,
       1,     3,     5,     6,    14,    19,    26,    27,    34,    35,
      36,    39,    51,    54,    56,    58,    59,    60,    62,    63,
      64,    65,    66,    67,    68,    69,    30,    61,    27,    27,
      27,    63,    62,    68,    68,    63,    27,    31,    39,    30,
      59,    23,    24,    25,    34,    22,    19,    21,    20,    34,
      63,    60,    63,    34,    28,    64,    70,    71,    63,    64,
      65,    67,    66,    68,    28,    60,    28,    28,    33,    32,
      59,    63,    59,    64,     4,    28,    59,    59
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
#line 307 "Parser.y"
    {
   (yyval.symbol)=new symbolInfo("program","start",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
   (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
   writeLogFile("start","program");
   st.printAllScopeTable();
   st.exitScope();
   cout<<"Total Lines: "<<yylineno<<endl;
   cout<<"Total Errors; "<<errorCount<<endl;
   //parseTree<<"it has opened"<<endl;
   dfs((yyval.symbol),1);
}
    break;

  case 3:
#line 320 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("program unit","program",(yyvsp[(1) - (2)].symbol)->getStartLine(),(yyvsp[(2) - (2)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (2)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (2)].symbol));
  writeLogFile("program","program unit");
  (yyval.symbol)->necessaryList=(yyvsp[(1) - (2)].symbol)->necessaryList;
}
    break;

  case 4:
#line 327 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("unit","program",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
  writeLogFile("program","unit");
  (yyval.symbol)->necessaryList=(yyvsp[(1) - (1)].symbol)->necessaryList;
}
    break;

  case 5:
#line 336 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("var_declaration","unit",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)-> childList.push_back((yyvsp[(1) - (1)].symbol));
  (yyval.symbol)->necessaryList=(yyvsp[(1) - (1)].symbol)->necessaryList;
  writeLogFile("unit","var_declaration");
  
}
    break;

  case 6:
#line 343 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("func_declaration","unit",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)-> childList.push_back((yyvsp[(1) - (1)].symbol));
  (yyval.symbol)->necessaryList=(yyvsp[(1) - (1)].symbol)->necessaryList;
  writeLogFile("unit","func_declaration");
  
}
    break;

  case 7:
#line 350 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("func_definition","unit",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)-> childList.push_back((yyvsp[(1) - (1)].symbol));
  (yyval.symbol)->necessaryList=(yyvsp[(1) - (1)].symbol)->necessaryList;
  writeLogFile("unit","func_definition");
}
    break;

  case 8:
#line 358 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("type_specifier ID LPAREN parameter_list RPAREN SEMICOLON","func_declaration",(yyvsp[(1) - (6)].symbol)->getStartLine(),(yyvsp[(6) - (6)].symbol)->getEndLine());
  (yyval.symbol)-> childList.push_back((yyvsp[(1) - (6)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(2) - (6)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(3) - (6)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(4) - (6)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(5) - (6)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(6) - (6)].symbol));

  declareFunction((yyvsp[(2) - (6)].symbol)->getName(),(yyvsp[(1) - (6)].symbol)->getDataTypeOrReturnType(),&((yyvsp[(4) - (6)].symbol)->necessaryList));

  writeLogFile("func_declaration","type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
  
}
    break;

  case 9:
#line 372 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("type_specifier ID LPAREN RPAREN SEMICOLON","func_declaration",(yyvsp[(1) - (5)].symbol)->getStartLine(),(yyvsp[(5) - (5)].symbol)->getEndLine());
  (yyval.symbol)-> childList.push_back((yyvsp[(1) - (5)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(2) - (5)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(3) - (5)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(4) - (5)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(5) - (5)].symbol));

  declareFunction((yyvsp[(2) - (5)].symbol)->getName(),(yyvsp[(1) - (5)].symbol)->getDataTypeOrReturnType()); 
  writeLogFile("func_declaration","type_specifier ID LPAREN RPAREN SEMICOLON");
  
}
    break;

  case 10:
#line 386 "Parser.y"
    {defineFunction((yyvsp[(2) - (5)].symbol)->getName(),(yyvsp[(1) - (5)].symbol)->getDataTypeOrReturnType(),yylineno,&((yyvsp[(4) - (5)].symbol)->necessaryList));}
    break;

  case 11:
#line 386 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("type_specifier ID LPAREN parameter_list RPAREN compound_statement","func_definition",(yyvsp[(1) - (7)].symbol)->getStartLine(),(yyvsp[(7) - (7)].symbol)->getEndLine());
  (yyval.symbol)-> childList.push_back((yyvsp[(1) - (7)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(2) - (7)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(3) - (7)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(4) - (7)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(5) - (7)].symbol)); 
  (yyval.symbol)->childList.push_back((yyvsp[(7) - (7)].symbol));
  writeLogFile("func_definition","type_specifier ID LPAREN parameter_list RPAREN compound_statement");

}
    break;

  case 12:
#line 397 "Parser.y"
    {defineFunction((yyvsp[(2) - (4)].symbol)->getName(),(yyvsp[(1) - (4)].symbol)->getDataTypeOrReturnType(),yylineno);}
    break;

  case 13:
#line 397 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("type_specifier ID LPAREN RPAREN compound_statement","func_definition",(yyvsp[(1) - (6)].symbol)->getStartLine(),(yyvsp[(6) - (6)].symbol)->getEndLine());
  (yyval.symbol)-> childList.push_back((yyvsp[(1) - (6)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(2) - (6)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(3) - (6)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(4) - (6)].symbol));
  (yyval.symbol)-> childList.push_back((yyvsp[(6) - (6)].symbol)); 
  writeLogFile("func_definition","type_specifier ID LPAREN RPAREN compound_statement");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
  
}
    break;

  case 14:
#line 408 "Parser.y"
    {
  if(!isErrorHasOccured){
    isErrorHasOccured=true;
    writeErrorFile("Syntax error at parameter list of function definition",yylineno);
    cout<<"Error at line no "<<yylineno<<" :syntax error"<<endl;
    //functionParamList.clear();
  }}
    break;

  case 15:
#line 414 "Parser.y"
    {isErrorHasOccured=false;}
    break;

  case 16:
#line 414 "Parser.y"
    {

    writeLogFile("func_definition","type_specifier ID LPAREN parameter_list RPAREN compound_statement");

    (yyval.symbol)=new symbolInfo("type_specifier ID LPAREN parameter_list RPAREN compound_statement","func_definition",(yyvsp[(1) - (8)].symbol)->getStartLine(),(yyvsp[(8) - (8)].symbol)->getEndLine());

    (yyval.symbol)->childList.push_back((yyvsp[(1) - (8)].symbol));
    (yyval.symbol)->childList.push_back((yyvsp[(2) - (8)].symbol));
    (yyval.symbol)->childList.push_back((yyvsp[(3) - (8)].symbol));
    (yyval.symbol)->childList.push_back(new symbolInfo("error","parameter_list",(yyvsp[(3) - (8)].symbol)->getEndLine(),(yyvsp[(6) - (8)].symbol)->getStartLine()));
    (yyval.symbol)->childList.push_back((yyvsp[(6) - (8)].symbol));
    (yyval.symbol)->childList.push_back((yyvsp[(8) - (8)].symbol));

    isErrorHasOccured=false;
  }
    break;

  case 17:
#line 431 "Parser.y"
    {
 (yyval.symbol) = new symbolInfo("parameter_list COMMA type_specifier ID","parameter_list",(yyvsp[(1) - (4)].symbol)->getStartLine(),(yyvsp[(4) - (4)].symbol)->getEndLine());
 (yyval.symbol)->childList.push_back((yyvsp[(1) - (4)].symbol));
 (yyval.symbol)->childList.push_back((yyvsp[(2) - (4)].symbol));
 (yyval.symbol)->childList.push_back((yyvsp[(3) - (4)].symbol));
 (yyval.symbol)->childList.push_back((yyvsp[(4) - (4)].symbol));

 (yyvsp[(1) - (4)].symbol)->necessaryList.push_back(new symbolInfo((yyvsp[(4) - (4)].symbol)->getName(),"",(yyvsp[(3) - (4)].symbol)->getDataTypeOrReturnType()));
 (yyval.symbol)->necessaryList=(yyvsp[(1) - (4)].symbol)->necessaryList; 

 functionParamList = &((yyvsp[(1) - (4)].symbol)->necessaryList);
 paramDeclineNo=yylineno;
 writeLogFile("parameter_list","parameter_list COMMA type_specifier ID");
 
}
    break;

  case 18:
#line 446 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("parameter_list COMMA type_specifier","parameter_list",(yyvsp[(1) - (3)].symbol)->getStartLine(),(yyvsp[(3) - (3)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (3)].symbol));

  (yyvsp[(1) - (3)].symbol)->necessaryList.push_back(new symbolInfo((yyvsp[(3) - (3)].symbol)->getName(),"",(yyvsp[(3) - (3)].symbol)->getDataTypeOrReturnType()));
  (yyval.symbol)->necessaryList=(yyvsp[(1) - (3)].symbol)->necessaryList;

  functionParamList = &((yyvsp[(1) - (3)].symbol)->necessaryList);
  paramDeclineNo=yylineno;
  writeLogFile("parameter_list","parameter_list COMMA type_specifier");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
    break;

  case 19:
#line 460 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("type_specifier ID","parameter_list",(yyvsp[(1) - (2)].symbol)->getStartLine(),(yyvsp[(2) - (2)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (2)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (2)].symbol));

  (yyval.symbol)->necessaryList.push_back(new symbolInfo((yyvsp[(2) - (2)].symbol)->getName(),"",(yyvsp[(1) - (2)].symbol)->getDataTypeOrReturnType()));
  
  functionParamList = &((yyval.symbol)->necessaryList);
  paramDeclineNo=yylineno;
  writeLogFile("parameter_list","type_specifier ID");
}
    break;

  case 20:
#line 471 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("type_specifier","parameter_list",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
  (yyval.symbol)->necessaryList.push_back(new symbolInfo((yyvsp[(1) - (1)].symbol)->getName(),"",(yyvsp[(1) - (1)].symbol)->getDataTypeOrReturnType()));
  //$$->necessaryList.push_back($1);
  writeLogFile("parameter_list","type_specifier");
}
    break;

  case 21:
#line 480 "Parser.y"
    {st.EnterScope(); st.printAllScopeTable();  declareFuncParamList(functionParamList, paramDeclineNo);}
    break;

  case 22:
#line 480 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("LCURL statements RCURL","compound_statement",(yyvsp[(1) - (4)].symbol)->getStartLine(),(yyvsp[(4) - (4)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (4)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (4)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(4) - (4)].symbol));
  (yyval.symbol)->necessaryList=(yyvsp[(1) - (4)].symbol)->necessaryList;

  
  st.printAllScopeTable();
  st.exitScope();
  writeLogFile("compound_statement","LCURL statements RCURL");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
    break;

  case 23:
#line 493 "Parser.y"
    {st.EnterScope();}
    break;

  case 24:
#line 493 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("LCURL RCURL","compound_statement",(yyvsp[(1) - (3)].symbol)->getStartLine(),(yyvsp[(3) - (3)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (3)].symbol));
  st.printAllScopeTable();
  st.exitScope();
  writeLogFile("compound_statement","LCURL RCURL");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
    break;

  case 25:
#line 504 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("type_specifier declaration_list SEMICOLON","var_declaration",(yyvsp[(1) - (3)].symbol)->getStartLine(),(yyvsp[(3) - (3)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (3)].symbol));
  
  for(symbolInfo* si : (yyvsp[(2) - (3)].symbol)->necessaryList){
    if((yyvsp[(1) - (3)].symbol)->getDataTypeOrReturnType() == "void"){
      writeErrorFile((string)"Variable or field '"+(string)si->getName()+(string)"' declared void");
    }

    bool isInserted = st.insert(si->getName(),si->getType());

    
    if(!isInserted){
      if(si->getIsVariableOrFunction()!=1)
        writeErrorFile((string)"'"+(string)si->getName()+(string)"' redeclared as different kind of symbol");

      symbolInfo* temp=st.LookUp(si->getName());
      if(si->getIsVariableOrFunction()==1 && si->getDataTypeOrReturnType() != temp->getDataTypeOrReturnType()){
        writeErrorFile((string)"Conflicting types for'"+(string)si->getName()+(string)"'");
      }
    }else{
      symbolInfo* temp = st.LookUp(si->getName());
      temp->setDataTypeOrReturnType((yyvsp[(1) - (3)].symbol)->getDataTypeOrReturnType());

      if(si->isItArray()){
          temp->sizeOfArray=si->sizeOfArray;
      }
    }
  }

  writeLogFile("var_declaration","type_specifier declaration_list SEMICOLON");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
    break;

  case 26:
#line 539 "Parser.y"
    {
  if(!isErrorHasOccured){
    isErrorHasOccured=true;
    cout<<"Error at line no "<<yylineno<<" : syntax error"<<endl;
    writeErrorFile("Syntax error at declaration list of variable declaration",yylineno);
    writeLogFile("var_declaration","type_specifier declaration_list SEMICOLON");
    extraInt=yylineno;
  }
}
    break;

  case 27:
#line 547 "Parser.y"
    {
    (yyval.symbol)=new symbolInfo("type_specifier declaration_list SEMICOLON","var_declaration",(yyvsp[(1) - (4)].symbol)->getStartLine(),(yyvsp[(4) - (4)].symbol)->getEndLine());
    (yyval.symbol)->childList.push_back((yyvsp[(1) - (4)].symbol));
    (yyval.symbol)->childList.push_back(new symbolInfo("error","declaration_list",extraInt,extraInt));
    (yyval.symbol)->childList.push_back((yyvsp[(4) - (4)].symbol));

    isErrorHasOccured=false;
    extraInt=0;
}
    break;

  case 28:
#line 558 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("INT","type_specifier",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
  (yyval.symbol)->setDataTypeOrReturnType("int");
  writeLogFile("type_specifier","INT");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
    break;

  case 29:
#line 565 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("FLOAT","type_specifier",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
  (yyval.symbol)->setDataTypeOrReturnType("float");
  writeLogFile("type_specifier","FLOAT");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
    break;

  case 30:
#line 572 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("VOID","type_specifier",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
  (yyval.symbol)->setDataTypeOrReturnType("void");
  writeLogFile("type_specifier","VOID");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
    break;

  case 31:
#line 581 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("declaration_list COMMA ID", "declaration_list",(yyvsp[(1) - (3)].symbol)->getStartLine(),(yyvsp[(3) - (3)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (3)].symbol));
  (yyvsp[(1) - (3)].symbol)->necessaryList.push_back((yyvsp[(3) - (3)].symbol));
  (yyval.symbol)->necessaryList=(yyvsp[(1) - (3)].symbol)->necessaryList;
  writeLogFile("declaration_list","declaration_list COMMA ID");

}
    break;

  case 32:
#line 591 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("declaration_list COMMA ID LSQUARE CONST_INT RSQUARE", "declaration_list",(yyvsp[(1) - (6)].symbol)->getStartLine(),(yyvsp[(6) - (6)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (6)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (6)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (6)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(4) - (6)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(5) - (6)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(6) - (6)].symbol));

  (yyvsp[(3) - (6)].symbol)->sizeOfArray=(yyvsp[(5) - (6)].symbol)->getName();
  (yyvsp[(1) - (6)].symbol)->necessaryList.push_back((yyvsp[(3) - (6)].symbol));
  (yyval.symbol)->necessaryList=(yyvsp[(1) - (6)].symbol)->necessaryList;
  writeLogFile("declaration_list","declaration_list COMMA ID LSQUARE CONST_INT RSQUARE");
}
    break;

  case 33:
#line 605 "Parser.y"
    {
  (yyval.symbol)= new symbolInfo("ID","declaration_list",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
  writeLogFile("declaration_list","ID");
  (yyval.symbol)->necessaryList.push_back((yyvsp[(1) - (1)].symbol));
}
    break;

  case 34:
#line 611 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("ID LSQUARE CONST_INT RSQUARE","declaration_list",(yyvsp[(1) - (4)].symbol)->getStartLine(),(yyvsp[(4) - (4)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (4)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (4)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (4)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(4) - (4)].symbol));
  writeLogFile("declaration_list","ID LSQUARE CONST_INT RSQUARE");
  (yyval.symbol)->necessaryList.push_back((yyvsp[(1) - (4)].symbol));
  (yyvsp[(1) - (4)].symbol)->sizeOfArray=(yyvsp[(3) - (4)].symbol)->getName();
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
    break;

  case 35:
#line 624 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("statement","statements",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));

  (yyval.symbol)->necessaryList=(yyvsp[(1) - (1)].symbol)->necessaryList;
  writeLogFile("statements","statement");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
    break;

  case 36:
#line 632 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("statements statement","statements",(yyvsp[(1) - (2)].symbol)->getStartLine(),(yyvsp[(2) - (2)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (2)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (2)].symbol));

  (yyval.symbol)->necessaryList=(yyvsp[(1) - (2)].symbol)->necessaryList;
  writeLogFile("statements","statements statement");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
    break;

  case 37:
#line 643 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("var_declaration","statement",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));

  (yyval.symbol)->necessaryList=(yyvsp[(1) - (1)].symbol)->necessaryList;
  writeLogFile("statement","var_declaration");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
    break;

  case 38:
#line 651 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("expression_statement","statement",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
  (yyval.symbol)->necessaryList=(yyvsp[(1) - (1)].symbol)->necessaryList;
  writeLogFile("statement","expression_statement");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
    break;

  case 39:
#line 658 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("compound_statement","statement",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
  (yyval.symbol)->necessaryList=(yyvsp[(1) - (1)].symbol)->necessaryList;
  writeLogFile("statement","compound_statement");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
    break;

  case 40:
#line 665 "Parser.y"
    {
  (yyval.symbol)= new symbolInfo("FOR LPAREN expression_statement expression_statement expression RPAREN statement","statement",(yyvsp[(1) - (7)].symbol)->getStartLine(),(yyvsp[(7) - (7)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (7)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (7)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (7)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(4) - (7)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(5) - (7)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(6) - (7)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(7) - (7)].symbol));
  (yyval.symbol)->necessaryList=(yyvsp[(1) - (7)].symbol)->necessaryList;
  writeLogFile("statement","FOR LPAREN expression_statement expression_statement expression RPAREN statement");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
    break;

  case 41:
#line 678 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("IF LPAREN expression RPAREN statement","statement",(yyvsp[(1) - (5)].symbol)->getStartLine(),(yyvsp[(5) - (5)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (5)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (5)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (5)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(4) - (5)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(5) - (5)].symbol));

  (yyval.symbol)->necessaryList=(yyvsp[(1) - (5)].symbol)->necessaryList;
  writeLogFile("statement","IF LPAREN expression RPAREN statement");
  //$$->childList.push_back($6);
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
    break;

  case 42:
#line 691 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("IF LPAREN expression RPAREN statement ELSE statement","statement",(yyvsp[(1) - (7)].symbol)->getStartLine(),(yyvsp[(7) - (7)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (7)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (7)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (7)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(4) - (7)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(5) - (7)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(6) - (7)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(7) - (7)].symbol));

  (yyval.symbol)->necessaryList=(yyvsp[(1) - (7)].symbol)->necessaryList;
  writeLogFile("statement","IF LPAREN expression RPAREN statement ELSE statement");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
    break;

  case 43:
#line 705 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("WHILE LPAREN expression RPAREN statement","statement",(yyvsp[(1) - (5)].symbol)->getStartLine(),(yyvsp[(5) - (5)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (5)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (5)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (5)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(4) - (5)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(5) - (5)].symbol));

  (yyval.symbol)->necessaryList=(yyvsp[(1) - (5)].symbol)->necessaryList;
  writeLogFile("statement","WHILE LPAREN expression RPAREN statement");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
    break;

  case 44:
#line 718 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("RETURN expression SEMICOLON","statement",(yyvsp[(1) - (3)].symbol)->getStartLine(),(yyvsp[(3) - (3)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (3)].symbol));

  (yyval.symbol)->necessaryList=(yyvsp[(1) - (3)].symbol)->necessaryList;
  writeLogFile("statement","RETURN expression SEMICOLON");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
    break;

  case 45:
#line 730 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("SEMICOLON","expression_statement",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));

  (yyval.symbol)->necessaryList.push_back(new symbolInfo((yyvsp[(1) - (1)].symbol)->getName(),(yyvsp[(1) - (1)].symbol)->getType()));
  writeLogFile("expression_statement","SEMICOLON");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
    break;

  case 46:
#line 739 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("expression SEMICOLON","expression_statement",(yyvsp[(1) - (2)].symbol)->getStartLine(),(yyvsp[(2) - (2)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (2)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (2)].symbol));

  (yyval.symbol)->necessaryList=(yyvsp[(1) - (2)].symbol)->necessaryList;
  writeLogFile("expression_statement","expression SEMICOLON");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
    break;

  case 47:
#line 749 "Parser.y"
    {if(!isErrorHasOccured){
  extraInt=yylineno;
  isErrorHasOccured=true;
}}
    break;

  case 48:
#line 752 "Parser.y"
    {
  writeLogFile("expression_statement","expression SEMICOLON");
  writeErrorFile("Syntax error at expression of expression statement",extraInt);

  (yyval.symbol)=new symbolInfo("expression SEMICOLON","expression_statement",(yyvsp[(3) - (3)].symbol)->getStartLine(),(yyvsp[(3) - (3)].symbol)->getEndLine());

  (yyval.symbol)->childList.push_back( new symbolInfo("error","expression",extraInt,extraInt));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (3)].symbol));

  extraInt=0;
  isErrorHasOccured=false;
}
    break;

  case 49:
#line 766 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("ID","variable",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));

  symbolInfo *si = st.LookUp((yyvsp[(1) - (1)].symbol)->getName());

  if(si != NULL){
    if(si->isItArray()){
      //writeErrorFile("Type mismatch, "+si->getName()+" is an array");
    }
    (yyval.symbol)->necessaryList.push_back((yyvsp[(1) - (1)].symbol));
    (yyval.symbol)->necessaryList[0]->setDataTypeOrReturnType(si->getDataTypeOrReturnType());
  }else{
    writeErrorFile((string)"Undeclared variable '"+(string)(yyvsp[(1) - (1)].symbol)->getName()+(string)"'");
    (yyval.symbol)->necessaryList.push_back((yyvsp[(1) - (1)].symbol));
    (yyval.symbol)->necessaryList[0]->setDataTypeOrReturnType("");
  }

  
  writeLogFile("variable","ID");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
    break;

  case 50:
#line 789 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("ID LSQUARE expression RSQUARE","variable",(yyvsp[(1) - (4)].symbol)->getStartLine(),(yyvsp[(4) - (4)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (4)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (4)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (4)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(4) - (4)].symbol));

  symbolInfo *si = st.LookUp((yyvsp[(1) - (4)].symbol)->getName());
  if(si != NULL){
    (yyvsp[(1) - (4)].symbol)->setDataTypeOrReturnType(si->getDataTypeOrReturnType());

    if(!si->isItArray()){
      writeErrorFile((string)"'"+(string)(yyvsp[(1) - (4)].symbol)->getName()+(string)"' is not an array");
    }
    if((yyvsp[(3) - (4)].symbol)->necessaryList[0]->getDataTypeOrReturnType()!="int"){
      writeErrorFile("Array subscript is not an integer");
    }
  }
  else{
    writeErrorFile((string)"Undeclared variable '"+(string)(yyvsp[(1) - (4)].symbol)->getName()+(string)"'");
  }

  //string name=$1->getName()+"["+$3->getName()+"]";
  //$1->setName("");
  (yyval.symbol)->necessaryList.push_back((yyvsp[(1) - (4)].symbol));
  writeLogFile("variable","ID LSQUARE expression RSQUARE");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
    break;

  case 51:
#line 820 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("logic_expression","expression",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
  (yyval.symbol)->necessaryList=(yyvsp[(1) - (1)].symbol)->necessaryList;
  writeLogFile("expression","logic_expression");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
    break;

  case 52:
#line 828 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("variable ASSIGNOP logic_expression","expression",(yyvsp[(1) - (3)].symbol)->getStartLine(),(yyvsp[(3) - (3)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (3)].symbol));

  (yyval.symbol)->necessaryList=(yyvsp[(1) - (3)].symbol)->necessaryList;
  /*if(!checkVoidFunction($1->necessaryList[0],$3->necessaryList[0])){
    $$->necessaryList[0]->setDataTypeOrReturnType(typeCasting($1->necessaryList[0],$3->necessaryList[0]));
  }else{
    if($1->necessaryList[0]->getDataTypeOrReturnType()!="void"){
      $$->necessaryList[0]->setDataTypeOrReturnType($3->necessaryList[0]->getDataTypeOrReturnType());
    }
    else{
      $$->necessaryList[0]->setDataTypeOrReturnType($1->necessaryList[0]->getDataTypeOrReturnType());
    }
  }*/
  checkVoidFunction((yyvsp[(1) - (3)].symbol)->necessaryList[0],(yyvsp[(3) - (3)].symbol)->necessaryList[0]);

  if((yyvsp[(1) - (3)].symbol)->necessaryList[0]->getDataTypeOrReturnType()=="int" && (yyvsp[(3) - (3)].symbol)->necessaryList[0]->getDataTypeOrReturnType()=="float"){
    writeErrorFile("Warning: possible loss of data in assignment of FLOAT to INT");
  }
  (yyval.symbol)->necessaryList[0]->setDataTypeOrReturnType(typeCasting((yyvsp[(1) - (3)].symbol)->necessaryList[0],(yyvsp[(3) - (3)].symbol)->necessaryList[0]));
  writeLogFile("expression","variable ASSIGNOP logic_expression");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
    break;

  case 53:
#line 857 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("rel_expression","logic_expression",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
  (yyval.symbol)->necessaryList=(yyvsp[(1) - (1)].symbol)->necessaryList;
  writeLogFile("logic_expression","rel_expression");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
    break;

  case 54:
#line 865 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("rel_expression LOGICOP rel_expression","logic_expression",(yyvsp[(1) - (3)].symbol)->getStartLine(),(yyvsp[(3) - (3)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (3)].symbol));

  
  
  (yyval.symbol)->necessaryList=(yyvsp[(1) - (3)].symbol)->necessaryList;
  (yyval.symbol)->necessaryList[0]->setDataTypeOrReturnType("int");
  writeLogFile("logic_expression","rel_expression LOGICOP rel_expression");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
    break;

  case 55:
#line 881 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("simple_expression","rel_expression",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
  (yyval.symbol)->necessaryList=(yyvsp[(1) - (1)].symbol)->necessaryList;
  writeLogFile("rel_expression","simple_expression");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
    break;

  case 56:
#line 889 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("simple_expression RELOP simple_expression","rel_expression",(yyvsp[(1) - (3)].symbol)->getStartLine(),(yyvsp[(3) - (3)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (3)].symbol));
  (yyval.symbol)->necessaryList=(yyvsp[(1) - (3)].symbol)->necessaryList;
  (yyval.symbol)->necessaryList[0]->setDataTypeOrReturnType("int");
  writeLogFile("rel_expression","simple_expression RELOP simple_expression");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
    break;

  case 57:
#line 902 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("term","simple_expression",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));

  (yyval.symbol)->necessaryList=(yyvsp[(1) - (1)].symbol)->necessaryList;
  writeLogFile("simple_expression","term");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
    break;

  case 58:
#line 911 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("simple_expression ADDOP term","simple_expression",(yyvsp[(1) - (3)].symbol)->getStartLine(),(yyvsp[(3) - (3)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (3)].symbol));

  //checkVoidFunction($1,$3);
  (yyval.symbol)->necessaryList=(yyvsp[(1) - (3)].symbol)->necessaryList;
  /*if(!checkVoidFunction($1->necessaryList[0],$3->necessaryList[0])){
    $$->necessaryList[0]->setDataTypeOrReturnType(typeCasting($1->necessaryList[0],$3->necessaryList[0]));
  }else{
    if($1->necessaryList[0]->getDataTypeOrReturnType()!="void"){
      $$->necessaryList[0]->setDataTypeOrReturnType($3->necessaryList[0]->getDataTypeOrReturnType());
    }
    else{
      $$->necessaryList[0]->setDataTypeOrReturnType($1->necessaryList[0]->getDataTypeOrReturnType());
    }
  }*/

  checkVoidFunction((yyvsp[(1) - (3)].symbol)->necessaryList[0],(yyvsp[(3) - (3)].symbol)->necessaryList[0]);
  (yyval.symbol)->necessaryList[0]->setDataTypeOrReturnType(typeCasting((yyvsp[(1) - (3)].symbol)->necessaryList[0],(yyvsp[(3) - (3)].symbol)->necessaryList[0]));
  //$$->necessaryList[0]->setDataTypeOrReturnType(typeCasting($1,$3));
  writeLogFile("simple_expression","simple_expression ADDOP term");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
    break;

  case 59:
#line 939 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("unary_expression","term",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
  (yyval.symbol)->necessaryList = (yyvsp[(1) - (1)].symbol)->necessaryList;
  writeLogFile("term","unary_expression");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
    break;

  case 60:
#line 947 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("term MULOP unary_expression","term",(yyvsp[(1) - (3)].symbol)->getStartLine(),(yyvsp[(3) - (3)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (3)].symbol));

 

  if((yyvsp[(2) - (3)].symbol)->getName()=="%"){
    if((yyvsp[(3) - (3)].symbol)->necessaryList[0]->getName()=="0"){
      writeErrorFile("Warning: division by zero i=0f=1Const=0");
    }
    else if((yyvsp[(1) - (3)].symbol)->necessaryList[0]->getDataTypeOrReturnType()!="int" || (yyvsp[(3) - (3)].symbol)->necessaryList[0]->getDataTypeOrReturnType()!="int"){
      writeErrorFile("Operands of modulus must be integers ");
    }else{

    }
    (yyvsp[(1) - (3)].symbol)->necessaryList[0]->setDataTypeOrReturnType("int");
    (yyvsp[(3) - (3)].symbol)->necessaryList[0]->setDataTypeOrReturnType("int");
  }

  (yyval.symbol)->necessaryList=(yyvsp[(1) - (3)].symbol)->necessaryList;

  /*if(!checkVoidFunction($1->necessaryList[0],$3->necessaryList[0])){
    $$->necessaryList[0]->setDataTypeOrReturnType(typeCasting($1->necessaryList[0],$3->necessaryList[0]));
  }else{
    if($1->necessaryList[0]->getDataTypeOrReturnType()!="void"){
      $$->necessaryList[0]->setDataTypeOrReturnType($3->necessaryList[0]->getDataTypeOrReturnType());
    }
    else{
      $$->necessaryList[0]->setDataTypeOrReturnType($1->necessaryList[0]->getDataTypeOrReturnType());
    }
  }*/
  checkVoidFunction((yyvsp[(1) - (3)].symbol)->necessaryList[0],(yyvsp[(3) - (3)].symbol)->necessaryList[0]);
  (yyval.symbol)->necessaryList[0]->setDataTypeOrReturnType(typeCasting((yyvsp[(1) - (3)].symbol)->necessaryList[0],(yyvsp[(3) - (3)].symbol)->necessaryList[0]));
  //$$->necessaryList[0]->setDataTypeOrReturnType(typeCasting($1,$3));
  
  writeLogFile("term","term MULOP unary_expression");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
    break;

  case 61:
#line 990 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("ADDOP unary_expression","unary_expression",(yyvsp[(1) - (2)].symbol)->getStartLine(),(yyvsp[(2) - (2)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (2)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (2)].symbol));
  (yyval.symbol)->necessaryList=(yyvsp[(2) - (2)].symbol)->necessaryList;
  //checkVoidFunction($2->necessaryList[0],$2->necessaryList[0]);
  writeLogFile("unary_expression","ADDOP unary_expression");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
    break;

  case 62:
#line 1000 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("NOT unary_expression","unary_expression",(yyvsp[(1) - (2)].symbol)->getStartLine(),(yyvsp[(2) - (2)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (2)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (2)].symbol));
  (yyval.symbol)->necessaryList=(yyvsp[(2) - (2)].symbol)->necessaryList;
  //checkVoidFunction($2->necessaryList[0],$2->necessaryList[0]);
  writeLogFile("unary_expression","NOT unary_expression");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
    break;

  case 63:
#line 1010 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("factor","unary_expression",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
  (yyval.symbol)->necessaryList=(yyvsp[(1) - (1)].symbol)->necessaryList;
  
  
  writeLogFile("unary_expression","factor");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
    break;

  case 64:
#line 1022 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("variable","factor",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
  writeLogFile("factor","variable");
  (yyval.symbol)->necessaryList=(yyvsp[(1) - (1)].symbol)->necessaryList;
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
    break;

  case 65:
#line 1030 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("ID LPAREN argument_list RPAREN","factor",(yyvsp[(1) - (4)].symbol)->getStartLine(),(yyvsp[(4) - (4)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (4)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (4)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (4)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(4) - (4)].symbol));

  callFunction((yyvsp[(1) - (4)].symbol),&((yyvsp[(3) - (4)].symbol)->necessaryList));

  string str;
  symbolInfo* temp=st.LookUp((yyvsp[(1) - (4)].symbol)->getName());
  if(temp==NULL){
    
    str="";
  }else{
     str=temp->getDataTypeOrReturnType();
  }

  (yyval.symbol)->necessaryList.push_back(new symbolInfo("","function",str));

  writeLogFile("factor","ID LPAREN argument_list RPAREN");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
    break;

  case 66:
#line 1054 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("LPAREN expression RPAREN","factor",(yyvsp[(1) - (3)].symbol)->getStartLine(),(yyvsp[(3) - (3)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (3)].symbol));
  (yyval.symbol)->necessaryList= (yyvsp[(2) - (3)].symbol)->necessaryList;
  writeLogFile("factor","LPAREN expression RPAREN");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
    break;

  case 67:
#line 1064 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("CONST_INT","factor",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
  (yyval.symbol)->necessaryList.push_back(new symbolInfo((yyvsp[(1) - (1)].symbol)->getName(),(yyvsp[(1) - (1)].symbol)->getType(),"int"));
  writeLogFile("factor","CONST_INT");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
    break;

  case 68:
#line 1072 "Parser.y"
    {
 (yyval.symbol)=new symbolInfo("CONST_FLOAT","factor",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol)); 
  (yyval.symbol)->necessaryList.push_back(new symbolInfo((yyvsp[(1) - (1)].symbol)->getName(),(yyvsp[(1) - (1)].symbol)->getType(),"float"));
  writeLogFile("factor","CONST_FLOAT");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
    break;

  case 69:
#line 1080 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("variable INCOP","factor",(yyvsp[(1) - (2)].symbol)->getStartLine(),(yyvsp[(2) - (2)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (2)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (2)].symbol));
  (yyval.symbol)->necessaryList=(yyvsp[(1) - (2)].symbol)->necessaryList;
  writeLogFile("factor","variable INCOP");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
    break;

  case 70:
#line 1089 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("variable DECOP","factor",(yyvsp[(1) - (2)].symbol)->getStartLine(),(yyvsp[(2) - (2)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (2)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (2)].symbol));
  (yyval.symbol)->necessaryList=(yyvsp[(1) - (2)].symbol)->necessaryList;
  writeLogFile("factor","variable DECOP");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
    break;

  case 71:
#line 1100 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("arguments","argument_list",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));

  (yyval.symbol)->necessaryList=(yyvsp[(1) - (1)].symbol)->necessaryList;
  writeLogFile("argument_list","arguments");
  //parseTree<<"it has opened "<<$$->getName()<<endl;

}
    break;

  case 72:
#line 1109 "Parser.y"
    {
  /*$$=new symbolInfo("","arguments",$1->getStartLine(),$1->getEndLine());
  $$->childList.push_back($1);*/
}
    break;

  case 73:
#line 1115 "Parser.y"
    {
  (yyval.symbol) = new symbolInfo("arguments COMMA logic_expression","arguments",(yyvsp[(1) - (3)].symbol)->getStartLine(),(yyvsp[(3) - (3)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(2) - (3)].symbol));
  (yyval.symbol)->childList.push_back((yyvsp[(3) - (3)].symbol));

  for(symbolInfo* si : (yyvsp[(3) - (3)].symbol)->necessaryList){
    (yyvsp[(1) - (3)].symbol)->necessaryList.push_back(si);
  }
  
  (yyval.symbol)->necessaryList=(yyvsp[(1) - (3)].symbol)->necessaryList;
  writeLogFile("arguments","arguments COMMA logic_expression");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
    break;

  case 74:
#line 1129 "Parser.y"
    {
  (yyval.symbol)=new symbolInfo("logic_expression","arguments",(yyvsp[(1) - (1)].symbol)->getStartLine(),(yyvsp[(1) - (1)].symbol)->getEndLine());
  (yyval.symbol)->childList.push_back((yyvsp[(1) - (1)].symbol));
  
  for(symbolInfo* si : (yyvsp[(1) - (1)].symbol)->necessaryList){
    (yyval.symbol)->necessaryList.push_back(si);
  }
  
  //$$->necessaryList.push_back($1);
  writeLogFile("arguments","logic_expression");
  //parseTree<<"it has opened "<<$$->getName()<<endl;
}
    break;


/* Line 1267 of yacc.c.  */
#line 2882 "y.tab.c"
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


#line 1142 "Parser.y"


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
	
    parseTree.open("parseTree.txt");
    errorFile.open("errorFile.txt");
    freopen("log.txt", "w", stdout);
    //st.insert("printf","FUNCTION");
    
    // if we don't init the yyin, it will use stdin(console)
    yyin = fin;

    yylineno = 1; // line number starts from 1

    // start scanning the file here
	yyparse();

    fclose(yyin);
    return 0;
}
