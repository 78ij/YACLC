/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "YACL.y"

#define YYDEBUG 1
#include "decl.h"
#include <iostream>
#include <stdio.h>
using std::cout;
using std::endl;
void yyerror(const char *s);
extern int yylex(void);
extern int yylineno;
ast_node_prog *root;
struct yt {
  vector<ast_node*> set;
  vector<parm_type> parms;
  parm_type para;
  int dims;
  types type;
  ast_node * ast;
  float floatcon;
  int intcon;
  char charcon;
  /* which operator to use (for relational and equality operators). */
  string id;
  //struct symbol_node * symbol;
};
#define YYSTYPE yt

/* Line 371 of yacc.c  */
#line 96 "YACL.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "YACL.tab.h".  */
#ifndef YY_YY_YACL_TAB_H_INCLUDED
# define YY_YY_YACL_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTCON = 258,
     CHARCON = 259,
     FLOATCON = 260,
     ID = 261,
     LT = 262,
     LE = 263,
     GE = 264,
     GT = 265,
     EQ = 266,
     NEQ = 267,
     PLUS = 268,
     MINUS = 269,
     MULTIPLY = 270,
     DIVIDE = 271,
     PLUSASSG = 272,
     MINUSASSG = 273,
     MULTIPLYASSG = 274,
     DIVIDEASSG = 275,
     NOT = 276,
     AND = 277,
     OR = 278,
     SELFMINUS = 279,
     SELFPLUS = 280,
     WHILE = 281,
     FOR = 282,
     BREAK = 283,
     CONTINUE = 284,
     RETURN = 285,
     IF = 286,
     INT = 287,
     FLOAT = 288,
     CHAR = 289,
     VOID = 290,
     LB = 291,
     RB = 292,
     LP = 293,
     RP = 294,
     LA = 295,
     RA = 296,
     COMMA = 297,
     SEMI = 298,
     ERROR = 299,
     NO_ELSE = 300,
     ELSE = 301,
     ASSG = 302,
     UMINUS = 303,
     UNOT = 304
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;
extern YYLTYPE yylloc;
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

#endif /* !YY_YY_YACL_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 223 "YACL.tab.c"

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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   430

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  82
/* YYNRULES -- Number of states.  */
#define YYNSTATES  184

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,    10,    11,    13,    15,    21,    27,
      32,    37,    38,    44,    45,    50,    51,    53,    55,    57,
      61,    62,    64,    69,    72,    76,    77,    86,    95,    99,
     100,   103,   106,   107,   115,   121,   127,   137,   146,   155,
     164,   172,   180,   188,   195,   199,   202,   206,   209,   211,
     214,   217,   222,   223,   227,   231,   235,   239,   243,   246,
     249,   252,   256,   260,   264,   268,   272,   276,   280,   284,
     288,   292,   296,   300,   302,   306,   312,   314,   318,   320,
     322,   324,   327
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      51,     0,    -1,    52,    43,    51,    -1,    62,    51,    -1,
      -1,    53,    -1,    54,    -1,    58,     6,    38,    60,    39,
      -1,    35,     6,    38,    60,    39,    -1,    58,     6,    57,
      55,    -1,    42,     6,    57,    55,    -1,    -1,    42,    58,
       6,    59,    56,    -1,    -1,    36,     3,    37,    57,    -1,
      -1,    34,    -1,    32,    -1,    33,    -1,    36,    37,    59,
      -1,    -1,    35,    -1,    58,     6,    59,    56,    -1,    65,
      61,    -1,    54,    43,    61,    -1,    -1,    58,     6,    38,
      60,    39,    40,    61,    41,    -1,    35,     6,    38,    60,
      39,    40,    61,    41,    -1,    42,    69,    63,    -1,    -1,
      65,    64,    -1,    54,    64,    -1,    -1,    31,    38,    69,
      39,    65,    46,    65,    -1,    31,    38,    69,    39,    65,
      -1,    26,    38,    69,    39,    65,    -1,    27,    38,    67,
      43,    69,    43,    67,    39,    65,    -1,    27,    38,    67,
      43,    69,    43,    39,    65,    -1,    27,    38,    67,    43,
      43,    67,    39,    65,    -1,    27,    38,    43,    69,    43,
      67,    39,    65,    -1,    27,    38,    43,    43,    67,    39,
      65,    -1,    27,    38,    43,    69,    43,    39,    65,    -1,
      27,    38,    67,    43,    43,    39,    65,    -1,    27,    38,
      43,    43,    39,    65,    -1,    30,    69,    43,    -1,    30,
      43,    -1,    40,    64,    41,    -1,    69,    43,    -1,    43,
      -1,    28,    43,    -1,    29,    43,    -1,    36,    69,    37,
      66,    -1,    -1,    68,    47,    69,    -1,    68,    17,    69,
      -1,    68,    18,    69,    -1,    68,    20,    69,    -1,    68,
      19,    69,    -1,     6,    66,    -1,    14,    69,    -1,    21,
      69,    -1,    69,    13,    69,    -1,    69,    14,    69,    -1,
      69,    15,    69,    -1,    69,    16,    69,    -1,    69,    11,
      69,    -1,    69,    12,    69,    -1,    69,     8,    69,    -1,
      69,     9,    69,    -1,    69,    10,    69,    -1,    69,     7,
      69,    -1,    69,    22,    69,    -1,    69,    23,    69,    -1,
      68,    -1,     6,    38,    39,    -1,     6,    38,    69,    63,
      39,    -1,    67,    -1,    38,    69,    39,    -1,     3,    -1,
       4,    -1,     5,    -1,    68,    25,    -1,    68,    24,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    65,    65,    66,    67,    68,    69,    70,    78,    87,
      96,   103,   104,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   129,   134,   139,   140,   149,   158,   159,
     160,   161,   162,   163,   171,   178,   185,   194,   202,   210,
     218,   225,   232,   239,   245,   251,   256,   262,   265,   266,
     272,   278,   279,   280,   288,   296,   304,   312,   320,   327,
     334,   341,   349,   357,   365,   373,   381,   389,   397,   405,
     413,   421,   429,   437,   441,   447,   455,   459,   463,   471,
     479,   487,   494
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTCON", "CHARCON", "FLOATCON", "ID",
  "LT", "LE", "GE", "GT", "EQ", "NEQ", "PLUS", "MINUS", "MULTIPLY",
  "DIVIDE", "PLUSASSG", "MINUSASSG", "MULTIPLYASSG", "DIVIDEASSG", "NOT",
  "AND", "OR", "SELFMINUS", "SELFPLUS", "WHILE", "FOR", "BREAK",
  "CONTINUE", "RETURN", "IF", "INT", "FLOAT", "CHAR", "VOID", "LB", "RB",
  "LP", "RP", "LA", "RA", "COMMA", "SEMI", "ERROR", "NO_ELSE", "ELSE",
  "ASSG", "UMINUS", "UNOT", "$accept", "prog", "dcl", "funcdcl", "vardcl",
  "decllist", "parmlist", "arraylist", "type", "multidim", "parm_types",
  "funcbody", "func", "exprlist", "stmtlist", "stmt", "multidim_ind",
  "assg", "expr_left", "expr", YY_NULL
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    51,    51,    51,    52,    52,    53,    53,    54,
      55,    55,    56,    56,    57,    57,    58,    58,    58,    59,
      59,    60,    60,    61,    61,    61,    62,    62,    63,    63,
      64,    64,    64,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    66,    66,    67,    67,    67,    67,    67,    68,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     0,     1,     1,     5,     5,     4,
       4,     0,     5,     0,     4,     0,     1,     1,     1,     3,
       0,     1,     4,     2,     3,     0,     8,     8,     3,     0,
       2,     2,     0,     7,     5,     5,     9,     8,     8,     8,
       7,     7,     7,     6,     3,     2,     3,     2,     1,     2,
       2,     4,     0,     3,     3,     3,     3,     3,     2,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     3,     5,     1,     3,     1,     1,
       1,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,    17,    18,    16,     0,     0,     0,     5,     6,     0,
       4,     0,     1,     4,    15,     3,     0,     2,     0,     0,
      11,    21,     0,     0,     0,     0,     0,     9,    20,     8,
      15,     7,    15,     0,    13,    25,    14,    25,    11,    20,
       0,    22,    78,    79,    80,    52,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    32,    48,     0,     0,     0,
      25,    76,    73,     0,     0,    10,    19,     0,     0,     0,
      58,    59,    60,     0,     0,    49,    50,    45,     0,     0,
       0,    32,     0,    32,    25,    15,    27,    23,     0,     0,
       0,     0,    82,    81,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    47,    26,    20,
       0,    74,    29,     0,    52,     0,     0,     0,    44,     0,
      77,    31,    46,    30,    24,    54,    55,    57,    56,    53,
      70,    67,    68,    69,    65,    66,    61,    62,    63,    64,
      71,    72,    13,    52,     0,     0,     0,     0,     0,     0,
       0,    12,    51,    29,    75,    35,     0,     0,     0,     0,
       0,    34,    28,    43,     0,     0,     0,     0,     0,     0,
       0,    40,    41,     0,    42,     0,     0,     0,    33,    39,
      38,    37,     0,    36
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,     7,    57,    27,    41,    20,    58,    34,
      23,    59,    10,   145,    82,    60,    70,    61,    62,    63
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -74
static const yytype_int16 yypact[] =
{
     109,   -74,   -74,   -74,     5,    18,   -16,   -74,   -74,    60,
     109,    34,   -74,   109,   -15,   -74,   192,   -74,    73,   192,
      31,   -74,    74,    40,    46,    54,    88,   -74,    61,    58,
      71,    66,    71,    89,    90,   119,   -74,   119,    31,    61,
      70,   -74,   -74,   -74,   -74,    75,   294,   294,    96,    99,
      95,   112,    27,   101,   294,   119,   -74,   113,   148,   120,
     119,   -74,   111,   207,   130,   -74,   -74,   154,   294,   282,
     -74,   -74,   -74,   294,     0,   -74,   -74,   -74,   229,   294,
     332,   119,   131,   119,   119,    71,   -74,   -74,   294,   294,
     294,   294,   -74,   -74,   294,   294,   294,   294,   294,   294,
     294,   294,   294,   294,   294,   294,   294,   -74,   -74,    61,
     387,   -74,   315,   351,   137,   164,   132,    -5,   -74,   369,
     -74,   -74,   -74,   -74,   -74,   404,   404,   404,   404,   404,
     414,   414,   414,   414,   233,   233,    22,    22,   -74,   -74,
     404,   404,    90,   137,   294,   138,   160,     1,   246,   190,
     160,   -74,   -74,   315,   -74,   -74,   160,   140,    28,    30,
     268,   134,   -74,   -74,   160,   160,   143,   160,   144,    43,
     160,   -74,   -74,   160,   -74,   160,   160,   145,   -74,   -74,
     -74,   -74,   160,   -74
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -74,     7,   -74,   -74,     9,   159,    50,    84,    68,   -34,
     157,   -21,   -74,    48,    36,   -55,    56,   -73,   -70,   -44
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      83,   116,    71,    72,   117,    66,   114,   114,    78,     8,
      80,    11,    88,    89,    90,    91,    64,    15,    12,     8,
      17,    18,     8,    19,   110,   112,    83,    13,    83,   113,
      42,    43,    44,    45,   114,   119,   114,   103,   104,    87,
     156,    46,    94,   115,   125,   126,   127,   128,    47,   114,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   124,    81,    54,    14,   165,     9,   167,
      77,   148,    16,    26,   157,   142,    24,   117,     9,    29,
      28,     9,   176,    30,    22,   166,   168,    22,   117,   117,
      81,   155,    81,    31,    32,   161,   177,    33,    35,   117,
     153,   163,     1,     2,     3,   160,    37,    18,    67,   171,
     172,    68,   174,    69,    36,   178,    38,   121,   179,   123,
     180,   181,    42,    43,    44,    45,    39,   183,    88,    89,
      90,    91,    40,    46,    73,    92,    93,    74,    75,    79,
      47,     1,     2,     3,     4,    48,    49,    50,    51,    52,
      53,     1,     2,     3,    85,    76,    84,    54,    94,    55,
     109,    86,    56,    42,    43,    44,    45,    42,    43,    44,
      45,   108,   122,    68,    46,   149,    25,   154,    46,   164,
     170,    47,   173,   175,   182,    47,    48,    49,    50,    51,
      52,    53,   151,    42,    43,    44,    45,    65,    54,   152,
      55,   162,    54,    56,    46,     0,     0,   147,     0,     0,
       0,    47,     0,     0,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,     1,     2,     3,    21,    54,   105,
     106,     0,     0,   159,     0,     0,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   101,   102,   103,   104,
     107,   105,   106,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,     0,     0,     0,     0,     0,   105,   106,
       0,     0,   118,     0,     0,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,    42,    43,    44,    45,   158,
     105,   106,     0,     0,     0,     0,    46,    42,    43,    44,
      45,     0,     0,    47,     0,     0,     0,     0,    46,     0,
       0,   169,     0,     0,     0,    47,     0,     0,     0,     0,
      54,   111,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,    54,     0,     0,     0,     0,   105,   106,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,     0,
       0,     0,     0,     0,   105,   106,     0,   144,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,     0,     0,
       0,   120,     0,   105,   106,     0,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,     0,     0,     0,     0,
     146,   105,   106,     0,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,     0,     0,     0,     0,   150,   105,
     106,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,     0,     0,     0,   143,    99,   100,   101,   102,   103,
     104
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-74)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      55,    74,    46,    47,    74,    39,     6,     6,    52,     0,
      54,     6,    17,    18,    19,    20,    37,    10,     0,    10,
      13,    36,    13,    38,    68,    69,    81,    43,    83,    73,
       3,     4,     5,     6,     6,    79,     6,    15,    16,    60,
      39,    14,    47,    43,    88,    89,    90,    91,    21,     6,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,    84,    55,    38,     6,    39,     0,    39,
      43,   115,    38,    42,   147,   109,     3,   147,    10,    39,
       6,    13,    39,    37,    16,   158,   159,    19,   158,   159,
      81,   146,    83,    39,     6,   150,   169,    36,    40,   169,
     144,   156,    32,    33,    34,   149,    40,    36,    40,   164,
     165,    36,   167,    38,    30,   170,    32,    81,   173,    83,
     175,   176,     3,     4,     5,     6,    37,   182,    17,    18,
      19,    20,    42,    14,    38,    24,    25,    38,    43,    38,
      21,    32,    33,    34,    35,    26,    27,    28,    29,    30,
      31,    32,    33,    34,     6,    43,    43,    38,    47,    40,
       6,    41,    43,     3,     4,     5,     6,     3,     4,     5,
       6,    41,    41,    36,    14,    43,    19,    39,    14,    39,
      46,    21,    39,    39,    39,    21,    26,    27,    28,    29,
      30,    31,   142,     3,     4,     5,     6,    38,    38,   143,
      40,   153,    38,    43,    14,    -1,    -1,    43,    -1,    -1,
      -1,    21,    -1,    -1,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    32,    33,    34,    35,    38,    22,
      23,    -1,    -1,    43,    -1,    -1,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    13,    14,    15,    16,
      43,    22,    23,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    -1,    -1,    22,    23,
      -1,    -1,    43,    -1,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,     3,     4,     5,     6,    43,
      22,    23,    -1,    -1,    -1,    -1,    14,     3,     4,     5,
       6,    -1,    -1,    21,    -1,    -1,    -1,    -1,    14,    -1,
      -1,    43,    -1,    -1,    -1,    21,    -1,    -1,    -1,    -1,
      38,    39,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    38,    -1,    -1,    -1,    -1,    22,    23,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    -1,    -1,    -1,    22,    23,    -1,    42,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    -1,    -1,
      -1,    39,    -1,    22,    23,    -1,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    -1,    -1,    -1,    -1,
      39,    22,    23,    -1,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    -1,    -1,    -1,    -1,    39,    22,
      23,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    37,    11,    12,    13,    14,    15,
      16
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    32,    33,    34,    35,    51,    52,    53,    54,    58,
      62,     6,     0,    43,     6,    51,    38,    51,    36,    38,
      57,    35,    58,    60,     3,    60,    42,    55,     6,    39,
      37,    39,     6,    36,    59,    40,    57,    40,    57,    37,
      42,    56,     3,     4,     5,     6,    14,    21,    26,    27,
      28,    29,    30,    31,    38,    40,    43,    54,    58,    61,
      65,    67,    68,    69,    61,    55,    59,    58,    36,    38,
      66,    69,    69,    38,    38,    43,    43,    43,    69,    38,
      69,    54,    64,    65,    43,     6,    41,    61,    17,    18,
      19,    20,    24,    25,    47,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    22,    23,    43,    41,     6,
      69,    39,    69,    69,     6,    43,    67,    68,    43,    69,
      39,    64,    41,    64,    61,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    59,    37,    42,    63,    39,    43,    69,    43,
      39,    56,    66,    69,    39,    65,    39,    67,    43,    43,
      69,    65,    63,    65,    39,    39,    67,    39,    67,    43,
      46,    65,    65,    39,    65,    39,    39,    67,    65,    65,
      65,    65,    39,    65
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (YYID (N))                                                     \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (YYID (0))
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

__attribute__((__unused__))
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
#else
static unsigned
yy_location_print_ (yyo, yylocp)
    FILE *yyo;
    YYLTYPE const * const yylocp;
#endif
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += fprintf (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += fprintf (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += fprintf (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += fprintf (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += fprintf (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

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
		  Type, Value, Location); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;


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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 65 "YACL.y"
    {root->lst.insert((root->lst).begin(),(yyvsp[(1) - (3)].ast));}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 66 "YACL.y"
    {root->lst.insert((root->lst).begin(),(yyvsp[(1) - (2)].ast));}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 67 "YACL.y"
    {root = new ast_node_prog();}
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 68 "YACL.y"
    {(yyval.ast) = (yyvsp[(1) - (1)].ast);}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 69 "YACL.y"
    {(yyval.ast) = (yyvsp[(1) - (1)].ast);}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 71 "YACL.y"
    {
                ast_node_funcdec *tmp = new ast_node_funcdec();
                tmp->type = (yyvsp[(1) - (5)].type);
                tmp->id = (yyvsp[(2) - (5)].id);
                tmp->parms = (yyvsp[(4) - (5)].parms);
                (yyval.ast)=tmp;
              }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 79 "YACL.y"
    {
                ast_node_funcdec *tmp = new ast_node_funcdec();
                tmp->type = T_VOID;
                tmp->id = (yyvsp[(2) - (5)].id);
                tmp->parms = (yyvsp[(4) - (5)].parms);
                (yyval.ast)=tmp;
              }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 87 "YACL.y"
    {
                ast_node_vardec *tmp = new ast_node_vardec();
                (yyvsp[(3) - (4)].para).ident = (yyvsp[(2) - (4)].id); 
                (yyvsp[(3) - (4)].para).isarray = (yyvsp[(3) - (4)].para).arraydim == 0? false : true;
                (yyvsp[(4) - (4)].parms).insert((yyvsp[(4) - (4)].parms).begin(),(yyvsp[(3) - (4)].para));
                tmp->type = (yyvsp[(1) - (4)].type);
                tmp->vars = (yyvsp[(4) - (4)].parms);
                (yyval.ast) = tmp;
            }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 97 "YACL.y"
    {
                (yyvsp[(3) - (4)].para).ident = (yyvsp[(2) - (4)].id); 
                (yyvsp[(3) - (4)].para).isarray = (yyvsp[(3) - (4)].para).arraydim == 0? false : true;
                (yyvsp[(4) - (4)].parms).insert((yyvsp[(4) - (4)].parms).begin(),(yyvsp[(3) - (4)].para));
                (yyval.parms) = (yyvsp[(4) - (4)].parms);
              }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 103 "YACL.y"
    {(yyval.parms) = vector<parm_type>();}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 105 "YACL.y"
    {
              (yyvsp[(4) - (5)].para).isarray = (yyvsp[(4) - (5)].para).arraydim == 0? false : true;
              (yyvsp[(4) - (5)].para).ident = (yyvsp[(3) - (5)].id);
              (yyvsp[(4) - (5)].para).type = (yyvsp[(2) - (5)].type);
              (yyvsp[(5) - (5)].parms).insert((yyvsp[(5) - (5)].parms).begin(),(yyvsp[(4) - (5)].para));
              (yyval.parms) = (yyvsp[(5) - (5)].parms);
            }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 112 "YACL.y"
    {(yyval.parms) = vector<parm_type>();}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 113 "YACL.y"
    {(yyval.para) = (yyvsp[(4) - (4)].para); (yyval.para).arraysize[(yyval.para).arraydim] = (yyvsp[(2) - (4)].intcon); ((yyval.para).arraydim)++;}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 114 "YACL.y"
    {(yyval.para) = parm_type(); (yyval.para).arraydim = 0;}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 115 "YACL.y"
    {(yyval.type) = T_CHAR;}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 116 "YACL.y"
    {(yyval.type) = T_INT;}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 117 "YACL.y"
    {(yyval.type)=T_FLOAT;}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 118 "YACL.y"
    {(yyval.para) = (yyvsp[(3) - (3)].para); ((yyval.para).arraydim)++;}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 119 "YACL.y"
    {(yyval.para) = parm_type();(yyval.para).arraydim=0;}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 120 "YACL.y"
    {(yyval.parms) = vector<parm_type>();}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 122 "YACL.y"
    {
              (yyvsp[(3) - (4)].para).ident = (yyvsp[(2) - (4)].id);
              (yyvsp[(3) - (4)].para).isarray = (yyvsp[(3) - (4)].para).arraydim == 0? false : true;
              (yyvsp[(3) - (4)].para).type = (yyvsp[(1) - (4)].type);
              (yyvsp[(4) - (4)].parms).insert((yyvsp[(4) - (4)].parms).begin(),(yyvsp[(3) - (4)].para));
              (yyval.parms) = (yyvsp[(4) - (4)].parms);
            }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 130 "YACL.y"
    {
              (yyvsp[(2) - (2)].set).insert((yyvsp[(2) - (2)].set).begin(),(yyvsp[(1) - (2)].ast));
            (yyval.set) = (yyvsp[(2) - (2)].set);
            }
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 135 "YACL.y"
    {
              (yyvsp[(3) - (3)].set).insert((yyvsp[(3) - (3)].set).begin(),(yyvsp[(1) - (3)].ast));
              (yyval.set) = (yyvsp[(3) - (3)].set);
            }
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 139 "YACL.y"
    {(yyval.set) = vector<ast_node*>();}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 141 "YACL.y"
    {
                ast_node_funcdef *tmp = new ast_node_funcdef();
               tmp->ret = (yyvsp[(1) - (8)].type);
               tmp->id = (yyvsp[(2) - (8)].id);
               tmp->body = (yyvsp[(7) - (8)].set);
               tmp->parms = (yyvsp[(4) - (8)].parms);
               (yyval.ast) = tmp;
            }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 150 "YACL.y"
    {
               ast_node_funcdef *tmp = new ast_node_funcdef();
               tmp->ret = T_VOID;
               tmp->id = (yyvsp[(2) - (8)].id);
               tmp->body = (yyvsp[(7) - (8)].set);
               tmp->parms = (yyvsp[(4) - (8)].parms);
               (yyval.ast) = tmp;
             }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 158 "YACL.y"
    {(yyvsp[(3) - (3)].set).insert((yyvsp[(3) - (3)].set).begin(),(yyvsp[(2) - (3)].ast)); (yyval.set) = (yyvsp[(3) - (3)].set);}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 159 "YACL.y"
    {(yyval.set) = vector<ast_node*>();}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 160 "YACL.y"
    {(yyvsp[(2) - (2)].set).insert((yyvsp[(2) - (2)].set).begin(),(yyvsp[(1) - (2)].ast)); (yyval.set) = (yyvsp[(2) - (2)].set);}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 161 "YACL.y"
    {(yyvsp[(2) - (2)].set).insert((yyvsp[(2) - (2)].set).begin(),(yyvsp[(1) - (2)].ast));(yyval.set) = (yyvsp[(2) - (2)].set);}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 162 "YACL.y"
    {(yyval.set) = vector<ast_node*>();}
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 164 "YACL.y"
    {
              ast_node_if *tmp = new ast_node_if();
              tmp->cond = (yyvsp[(3) - (7)].ast);
              tmp->body = (yyvsp[(5) - (7)].ast);
              tmp->el = (yyvsp[(7) - (7)].ast);
              (yyval.ast) = tmp;
            }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 172 "YACL.y"
    {
              ast_node_if *tmp = new ast_node_if();
              tmp->cond = (yyvsp[(3) - (5)].ast);
              tmp->body = (yyvsp[(5) - (5)].ast);
              (yyval.ast) = tmp;
            }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 179 "YACL.y"
    {
              ast_node_while *tmp = new ast_node_while();
              tmp->cond = (yyvsp[(3) - (5)].ast);
              tmp->body = (yyvsp[(5) - (5)].ast);
              (yyval.ast) = tmp;
            }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 186 "YACL.y"
    {
              ast_node_for *tmp = new ast_node_for();
              tmp->init = (yyvsp[(3) - (9)].ast);
              tmp->cond = (yyvsp[(5) - (9)].ast);
              tmp->iter = (yyvsp[(7) - (9)].ast);
              tmp->body = (yyvsp[(9) - (9)].ast);
              (yyval.ast) = tmp;
            }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 195 "YACL.y"
    {
              ast_node_for *tmp = new ast_node_for();
              tmp->init = (yyvsp[(3) - (8)].ast);
              tmp->cond = (yyvsp[(5) - (8)].ast);
              tmp->body = (yyvsp[(8) - (8)].ast);
              (yyval.ast) = tmp;
            }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 203 "YACL.y"
    {
              ast_node_for *tmp = new ast_node_for();
              tmp->init = (yyvsp[(3) - (8)].ast);
              tmp->iter = (yyvsp[(6) - (8)].ast);
              tmp->body = (yyvsp[(8) - (8)].ast);
              (yyval.ast) = tmp;
            }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 211 "YACL.y"
    {
              ast_node_for *tmp = new ast_node_for();
              tmp->cond = (yyvsp[(4) - (8)].ast);
              tmp->iter = (yyvsp[(6) - (8)].ast);
              tmp->body = (yyvsp[(8) - (8)].ast);
              (yyval.ast) = tmp;
            }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 219 "YACL.y"
    {
              ast_node_for *tmp = new ast_node_for();
              tmp->iter = (yyvsp[(5) - (7)].ast);
              tmp->body = (yyvsp[(7) - (7)].ast);
              (yyval.ast) = tmp;
            }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 226 "YACL.y"
    {
              ast_node_for *tmp = new ast_node_for();
              tmp->cond = (yyvsp[(4) - (7)].ast);
              tmp->body = (yyvsp[(7) - (7)].ast);
              (yyval.ast) = tmp;
            }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 233 "YACL.y"
    {
              ast_node_for *tmp = new ast_node_for();
              tmp->init = (yyvsp[(3) - (7)].ast);
              tmp->body = (yyvsp[(7) - (7)].ast);
              (yyval.ast) = tmp;
            }
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 240 "YACL.y"
    {
              ast_node_for *tmp = new ast_node_for();
              tmp->body = (yyvsp[(6) - (6)].ast);
              (yyval.ast) = tmp;
            }
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 246 "YACL.y"
    {
              ast_node_ret *tmp = new ast_node_ret();
              tmp->stmt = (yyvsp[(2) - (3)].ast);
              (yyval.ast) =tmp;
            }
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 252 "YACL.y"
    {
              ast_node_ret *tmp = new ast_node_ret();
              (yyval.ast) =tmp;
            }
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 257 "YACL.y"
    {
              ast_node_bigbrac *tmp = new ast_node_bigbrac();
              tmp->body = (yyvsp[(2) - (3)].set);
              (yyval.ast) = tmp;
            }
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 262 "YACL.y"
    {
              (yyval.ast) = (yyvsp[(1) - (2)].ast);
            }
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 265 "YACL.y"
    {}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 267 "YACL.y"
    {
              ast_node_control *tmp = new ast_node_control();
              tmp->ctrltype = C_BREAK;
              (yyval.ast) = tmp;
            }
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 273 "YACL.y"
    {
              ast_node_control *tmp = new ast_node_control();
              tmp->ctrltype = C_CONTINUE;
              (yyval.ast) = tmp;
            }
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 278 "YACL.y"
    {(yyvsp[(4) - (4)].set).push_back((yyvsp[(2) - (4)].ast)); (yyval.set) = (yyvsp[(4) - (4)].set);}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 279 "YACL.y"
    {(yyval.set) = vector<ast_node *>();}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 281 "YACL.y"
    {
              ast_node_assg *tmp = new ast_node_assg();
              tmp->left = (yyvsp[(1) - (3)].ast);
              tmp->right = (yyvsp[(3) - (3)].ast);
              tmp->op = O_EQ;
              (yyval.ast) = tmp;
            }
    break;

  case 54:
/* Line 1792 of yacc.c  */
#line 289 "YACL.y"
    {
              ast_node_assg *tmp = new ast_node_assg();
              tmp->left = (yyvsp[(1) - (3)].ast);
              tmp->right = (yyvsp[(3) - (3)].ast);
              tmp->op = O_PLUS;
              (yyval.ast) = tmp;
            }
    break;

  case 55:
/* Line 1792 of yacc.c  */
#line 297 "YACL.y"
    {
              ast_node_assg *tmp = new ast_node_assg();
              tmp->left = (yyvsp[(1) - (3)].ast);
              tmp->right = (yyvsp[(3) - (3)].ast);
              tmp->op = O_MINUS;
              (yyval.ast) = tmp;
            }
    break;

  case 56:
/* Line 1792 of yacc.c  */
#line 305 "YACL.y"
    {
              ast_node_assg *tmp = new ast_node_assg();
              tmp->left = (yyvsp[(1) - (3)].ast);
              tmp->right = (yyvsp[(3) - (3)].ast);
              tmp->op = O_DIVIDE;
              (yyval.ast) = tmp;
            }
    break;

  case 57:
/* Line 1792 of yacc.c  */
#line 313 "YACL.y"
    {
              ast_node_assg *tmp = new ast_node_assg();
              tmp->left = (yyvsp[(1) - (3)].ast);
              tmp->right = (yyvsp[(3) - (3)].ast);
              tmp->op = O_MULTIPLY;
              (yyval.ast) = tmp;
            }
    break;

  case 58:
/* Line 1792 of yacc.c  */
#line 321 "YACL.y"
    {
                ast_node_lvalue *tmp = new ast_node_lvalue();
                tmp->id = (yyvsp[(1) - (2)].id);
                tmp->arrayind = (yyvsp[(2) - (2)].set);
                (yyval.ast) = tmp; 
            }
    break;

  case 59:
/* Line 1792 of yacc.c  */
#line 328 "YACL.y"
    {
              ast_node_unary *tmp = new ast_node_unary();
              tmp->body = (yyvsp[(2) - (2)].ast);
              tmp->op = O_UMINUS;
              (yyval.ast) = tmp;
            }
    break;

  case 60:
/* Line 1792 of yacc.c  */
#line 335 "YACL.y"
    {
              ast_node_unary *tmp = new ast_node_unary();
              tmp->body = (yyvsp[(2) - (2)].ast);
              tmp->op = O_UNOT;
              (yyval.ast) = tmp;
            }
    break;

  case 61:
/* Line 1792 of yacc.c  */
#line 342 "YACL.y"
    {
              ast_node_bin *tmp = new ast_node_bin();
              tmp->left = (yyvsp[(1) - (3)].ast);
              tmp->right = (yyvsp[(3) - (3)].ast);
              tmp->op =  O_PLUS;
              (yyval.ast) = tmp;
            }
    break;

  case 62:
/* Line 1792 of yacc.c  */
#line 350 "YACL.y"
    {
              ast_node_bin *tmp = new ast_node_bin();
              tmp->left = (yyvsp[(1) - (3)].ast);
              tmp->right = (yyvsp[(3) - (3)].ast);
              tmp->op =  O_MINUS;
              (yyval.ast) = tmp;
            }
    break;

  case 63:
/* Line 1792 of yacc.c  */
#line 358 "YACL.y"
    {
              ast_node_bin *tmp = new ast_node_bin();
              tmp->left = (yyvsp[(1) - (3)].ast);
              tmp->right = (yyvsp[(3) - (3)].ast);
              tmp->op =  O_MULTIPLY;
              (yyval.ast) = tmp;
            }
    break;

  case 64:
/* Line 1792 of yacc.c  */
#line 366 "YACL.y"
    {
              ast_node_bin *tmp = new ast_node_bin();
              tmp->left = (yyvsp[(1) - (3)].ast);
              tmp->right = (yyvsp[(3) - (3)].ast);
              tmp->op =  O_DIVIDE;
              (yyval.ast) = tmp;
            }
    break;

  case 65:
/* Line 1792 of yacc.c  */
#line 374 "YACL.y"
    {
              ast_node_bin *tmp = new ast_node_bin();
              tmp->left = (yyvsp[(1) - (3)].ast);
              tmp->right = (yyvsp[(3) - (3)].ast);
              tmp->op =  O_EQ;
              (yyval.ast) = tmp;
            }
    break;

  case 66:
/* Line 1792 of yacc.c  */
#line 382 "YACL.y"
    {
              ast_node_bin *tmp = new ast_node_bin();
              tmp->left = (yyvsp[(1) - (3)].ast);
              tmp->right = (yyvsp[(3) - (3)].ast);
              tmp->op =  O_NEQ;
              (yyval.ast) = tmp;
            }
    break;

  case 67:
/* Line 1792 of yacc.c  */
#line 390 "YACL.y"
    {
              ast_node_bin *tmp = new ast_node_bin();
              tmp->left = (yyvsp[(1) - (3)].ast);
              tmp->right = (yyvsp[(3) - (3)].ast);
              tmp->op =  O_LE;
              (yyval.ast) = tmp;
            }
    break;

  case 68:
/* Line 1792 of yacc.c  */
#line 398 "YACL.y"
    {
              ast_node_bin *tmp = new ast_node_bin();
              tmp->left = (yyvsp[(1) - (3)].ast);
              tmp->right = (yyvsp[(3) - (3)].ast);
              tmp->op =  O_GE;
              (yyval.ast) = tmp;
            }
    break;

  case 69:
/* Line 1792 of yacc.c  */
#line 406 "YACL.y"
    {
              ast_node_bin *tmp = new ast_node_bin();
              tmp->left = (yyvsp[(1) - (3)].ast);
              tmp->right = (yyvsp[(3) - (3)].ast);
              tmp->op =  O_GT;
              (yyval.ast) = tmp;
            }
    break;

  case 70:
/* Line 1792 of yacc.c  */
#line 414 "YACL.y"
    {
              ast_node_bin *tmp = new ast_node_bin();
              tmp->left = (yyvsp[(1) - (3)].ast);
              tmp->right = (yyvsp[(3) - (3)].ast);
              tmp->op =  O_LT;
              (yyval.ast) = tmp;
            }
    break;

  case 71:
/* Line 1792 of yacc.c  */
#line 422 "YACL.y"
    {
              ast_node_bin *tmp = new ast_node_bin();
              tmp->left = (yyvsp[(1) - (3)].ast);
              tmp->right = (yyvsp[(3) - (3)].ast);
              tmp->op =  O_AND;
              (yyval.ast) = tmp;
            }
    break;

  case 72:
/* Line 1792 of yacc.c  */
#line 430 "YACL.y"
    {
              ast_node_bin *tmp = new ast_node_bin();
              tmp->left = (yyvsp[(1) - (3)].ast);
              tmp->right = (yyvsp[(3) - (3)].ast);
              tmp->op =  O_OR;
              (yyval.ast) = tmp;
            }
    break;

  case 73:
/* Line 1792 of yacc.c  */
#line 438 "YACL.y"
    {
              (yyval.ast) = (yyvsp[(1) - (1)].ast);
            }
    break;

  case 74:
/* Line 1792 of yacc.c  */
#line 442 "YACL.y"
    {
              ast_node_callfunc *tmp = new ast_node_callfunc();
              tmp->id = (yyvsp[(1) - (3)].id);
              (yyval.ast) = tmp;
            }
    break;

  case 75:
/* Line 1792 of yacc.c  */
#line 448 "YACL.y"
    {
              ast_node_callfunc *tmp = new ast_node_callfunc();
              tmp->id = (yyvsp[(1) - (5)].id);
              (yyvsp[(4) - (5)].set).insert((yyvsp[(4) - (5)].set).begin(),(yyvsp[(3) - (5)].ast));
              tmp->params = (yyvsp[(4) - (5)].set);
              (yyval.ast) = tmp;
            }
    break;

  case 76:
/* Line 1792 of yacc.c  */
#line 456 "YACL.y"
    {
              (yyval.ast) = (yyvsp[(1) - (1)].ast);
            }
    break;

  case 77:
/* Line 1792 of yacc.c  */
#line 460 "YACL.y"
    {
              (yyval.ast)= (yyvsp[(2) - (3)].ast);
            }
    break;

  case 78:
/* Line 1792 of yacc.c  */
#line 464 "YACL.y"
    {
              ast_node_const *tmp = new ast_node_const();
              (tmp->data).i = (yyvsp[(1) - (1)].intcon);
              tmp->type = T_INT;
              
              (yyval.ast) = tmp;
            }
    break;

  case 79:
/* Line 1792 of yacc.c  */
#line 472 "YACL.y"
    {
              ast_node_const *tmp = new ast_node_const();
              (tmp->data).c = (yyvsp[(1) - (1)].charcon);
              tmp->type = T_CHAR;
              
              (yyval.ast) = tmp;
            }
    break;

  case 80:
/* Line 1792 of yacc.c  */
#line 480 "YACL.y"
    {
              ast_node_const *tmp = new ast_node_const();
              (tmp->data).f = (yyvsp[(1) - (1)].floatcon);
              tmp->type = T_FLOAT;
              
              (yyval.ast) = tmp;
            }
    break;

  case 81:
/* Line 1792 of yacc.c  */
#line 488 "YACL.y"
    {
              ast_node_unary *tmp = new ast_node_unary();
              tmp->body = (yyvsp[(1) - (2)].ast);
              tmp->op = O_SELFPLUS;
              (yyval.ast) = tmp;
            }
    break;

  case 82:
/* Line 1792 of yacc.c  */
#line 495 "YACL.y"
    {
              ast_node_unary *tmp = new ast_node_unary();
              tmp->body = (yyvsp[(1) - (2)].ast);
              tmp->op = O_SELFMINUS;
              (yyval.ast) = tmp;
            }
    break;


/* Line 1792 of yacc.c  */
#line 2523 "YACL.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
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

  yyerror_range[1] = yylsp[1-yylen];
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
      if (!yypact_value_is_default (yyn))
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
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


/* Line 2055 of yacc.c  */
#line 501 "YACL.y"

 
void yyerror(const char *s)	//当yacc遇到语法错误时，会回调yyerror函数，并且把错误信息放在参数s中
{
	cout <<s << " at line " <<yylineno << " ,lookahead token is "<< yychar<< endl;//直接输出错误信息
}

void printtokenpair(int tokentype){
  cout << "(" << yytname[tokentype-255] << ", ";
  switch(tokentype){
    case INTCON:
      cout << yylval.intcon;
      break;
    case FLOATCON:
      cout << yylval.floatcon;
      break;
    case CHARCON:
      cout << yylval.charcon;
      break;
    case ID:
      cout << yylval.id;
      break;
  }
  cout << ") ";
}
