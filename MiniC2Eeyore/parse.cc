/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parse.y" /* yacc.c:339  */

#include "util.h"
#include "node.h"
#include "type.h"
#include "env.h"

using namespace std;
#define YYERROR_VERBOSE 1

#line 76 "parse.cc" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TYPE = 258,
    INTEGER = 259,
    PLUS = 260,
    MINUS = 261,
    TIME = 262,
    DIVIDE = 263,
    MOD = 264,
    NOT = 265,
    AND = 266,
    OR = 267,
    LESS = 268,
    GREATER = 269,
    EQUAL = 270,
    NOTEQUAL = 271,
    ASSIGN = 272,
    IF = 273,
    ELSE = 274,
    WHILE = 275,
    RETURN = 276,
    MAIN = 277,
    DOUBLEPLUS = 278,
    DOUBLEMINUS = 279,
    ID = 280,
    UMINUS = 281
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 16 "parse.y" /* yacc.c:355  */

    int ival;
    char* sval;
    Node* nval;

#line 146 "parse.cc" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);



/* Copy the second part of user declarations.  */

#line 177 "parse.cc" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   236

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  116

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      25,    26,     2,     2,    32,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    31,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    27,     2,    28,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,     2,    30,     2,     2,     2,     2,
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
      33,    34
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    42,    42,    52,    60,    68,    77,    81,    91,   102,
     112,   120,   126,   132,   138,   144,   152,   159,   169,   175,
     180,   188,   196,   195,   230,   237,   237,   243,   256,   275,
     292,   301,   308,   313,   318,   328,   337,   345,   352,   360,
     366,   374,   383,   396,   409,   421,   434,   451,   468,   481,
     494,   506,   519,   532,   546,   560,   608,   627,   641,   670,
     682,   698,   710
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TYPE", "INTEGER", "PLUS", "MINUS",
  "TIME", "DIVIDE", "MOD", "NOT", "AND", "OR", "LESS", "GREATER", "EQUAL",
  "NOTEQUAL", "ASSIGN", "IF", "ELSE", "WHILE", "RETURN", "MAIN",
  "DOUBLEPLUS", "DOUBLEMINUS", "'('", "')'", "'['", "']'", "'{'", "'}'",
  "';'", "','", "ID", "UMINUS", "$accept", "Program", "GlobalList",
  "VarDefn", "ParaDecl", "ParaDecls", "ParaList", "FuncDecl", "FuncDefn",
  "$@1", "Block", "$@2", "Blocks", "Statement", "ExprList", "Expressions",
  "Expression", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,    40,    41,    91,    93,   123,
     125,    59,    44,   280,   281
};
# endif

#define YYPACT_NINF -56

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-56)))

#define YYTABLE_NINF -32

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      83,   -28,   -10,    50,   -56,    83,    83,    83,   -56,   108,
     -56,   -56,   -56,   -56,    52,    53,   -56,   -22,    28,   -56,
      37,    38,    40,    42,    52,    -9,    46,   -56,    -2,   -56,
     -56,   -56,   -56,    63,   -56,    41,   -56,    49,    61,   -56,
      75,    75,    81,    82,    75,    67,    93,   -56,    29,   -56,
      41,    84,   -56,   116,   -56,    -6,   -56,   -56,    75,    75,
     137,   -56,   -56,    41,    75,   -56,   -56,    75,    75,   -56,
     -56,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,   -56,   149,   165,   -56,   107,   181,   112,   -56,
     104,     1,    80,    80,   -56,   -56,   -56,   205,   193,   227,
     227,   217,   217,    72,    72,   -56,   -56,    75,   117,   121,
     -56,   -56,    75,    72,   181,   -56
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     7,     0,     0,     2,     0,     0,     0,    10,     0,
       1,     3,     5,     4,    19,     0,     8,    14,    16,    18,
       0,     0,     0,    11,     0,     0,     0,    15,     0,    17,
      22,    20,     9,     0,    13,     0,    12,     0,     0,    40,
       0,     0,     0,     0,     0,     0,     0,    25,    41,    33,
       0,     0,    24,     0,    10,     0,    44,    50,     0,     0,
       0,    59,    61,     0,     0,    60,    62,    37,     0,    30,
      23,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    32,     0,     0,    34,     0,    57,     0,    36,
      39,     0,    42,    43,    45,    46,    47,    48,    49,    51,
      52,    53,    54,     0,     0,    26,    55,     0,    56,    27,
      29,    38,     0,     0,    58,    28
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -56,   -56,   177,    97,   -56,   135,   -56,   -56,   -56,   -56,
     -55,   -56,   -20,   -56,   -56,    34,   -40
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,    49,    18,    19,    20,     6,     7,    35,
      50,    63,    51,    52,    88,    89,    53
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      56,    57,    33,     8,    60,    22,    71,    72,    73,    74,
      75,    23,    76,    77,    78,    79,    80,    81,    83,    84,
      30,    15,    31,     9,    87,    16,    34,    90,    91,   108,
      69,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,    37,    86,    38,    39,    64,    40,   109,   110,
      10,    41,    65,    66,    67,    17,    68,    21,   115,    42,
      24,    43,    44,    25,    45,    46,    26,    90,    27,    28,
      47,   -31,   114,    37,    48,    38,    39,    32,    40,    39,
      54,    40,    41,    -6,     1,    41,     2,    73,    74,    75,
      42,    36,    43,    44,    55,    45,    46,     5,    45,    46,
      61,    47,     5,     5,     5,    48,    58,    59,    48,    71,
      72,    73,    74,    75,    70,    76,    77,    78,    79,    80,
      81,    71,    72,    73,    74,    75,    62,    76,    77,    78,
      79,    80,    81,    14,   112,    15,   107,   105,   106,    16,
     113,   111,    71,    72,    73,    74,    75,    82,    76,    77,
      78,    79,    80,    81,    71,    72,    73,    74,    75,    29,
      76,    77,    78,    79,    80,    81,     0,     0,    85,     0,
      71,    72,    73,    74,    75,   103,    76,    77,    78,    79,
      80,    81,    11,    12,    13,     0,    71,    72,    73,    74,
      75,   104,    76,    77,    78,    79,    80,    81,    71,    72,
      73,    74,    75,     0,    76,     0,    78,    79,    80,    81,
      71,    72,    73,    74,    75,     0,     0,     0,    78,    79,
      80,    81,    71,    72,    73,    74,    75,     0,     0,     0,
      78,    79,    71,    72,    73,    74,    75
};

static const yytype_int8 yycheck[] =
{
      40,    41,     4,    31,    44,    27,     5,     6,     7,     8,
       9,    33,    11,    12,    13,    14,    15,    16,    58,    59,
      29,    27,    31,    33,    64,    31,    28,    67,    68,    28,
      50,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,     1,    63,     3,     4,    17,     6,   103,   104,
       0,    10,    23,    24,    25,     3,    27,     4,   113,    18,
      32,    20,    21,    26,    23,    24,    28,   107,    28,    27,
      29,    30,   112,     1,    33,     3,     4,    31,     6,     4,
      31,     6,    10,     0,     1,    10,     3,     7,     8,     9,
      18,    28,    20,    21,    33,    23,    24,     0,    23,    24,
      33,    29,     5,     6,     7,    33,    25,    25,    33,     5,
       6,     7,     8,     9,    30,    11,    12,    13,    14,    15,
      16,     5,     6,     7,     8,     9,    33,    11,    12,    13,
      14,    15,    16,    25,    17,    27,    32,    30,    26,    31,
      19,   107,     5,     6,     7,     8,     9,    31,    11,    12,
      13,    14,    15,    16,     5,     6,     7,     8,     9,    24,
      11,    12,    13,    14,    15,    16,    -1,    -1,    31,    -1,
       5,     6,     7,     8,     9,    26,    11,    12,    13,    14,
      15,    16,     5,     6,     7,    -1,     5,     6,     7,     8,
       9,    26,    11,    12,    13,    14,    15,    16,     5,     6,
       7,     8,     9,    -1,    11,    -1,    13,    14,    15,    16,
       5,     6,     7,     8,     9,    -1,    -1,    -1,    13,    14,
      15,    16,     5,     6,     7,     8,     9,    -1,    -1,    -1,
      13,    14,     5,     6,     7,     8,     9
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     3,    36,    37,    38,    42,    43,    31,    33,
       0,    37,    37,    37,    25,    27,    31,     3,    39,    40,
      41,     4,    27,    33,    32,    26,    28,    28,    27,    40,
      29,    31,    31,     4,    28,    44,    28,     1,     3,     4,
       6,    10,    18,    20,    21,    23,    24,    29,    33,    38,
      45,    47,    48,    51,    31,    33,    51,    51,    25,    25,
      51,    33,    33,    46,    17,    23,    24,    25,    27,    47,
      30,     5,     6,     7,     8,     9,    11,    12,    13,    14,
      15,    16,    31,    51,    51,    31,    47,    51,    49,    50,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    26,    26,    30,    26,    32,    28,    45,
      45,    50,    17,    19,    51,    45
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    35,    36,    37,    37,    37,    37,    37,    38,    38,
      38,    39,    39,    39,    39,    39,    40,    40,    41,    41,
      42,    42,    44,    43,    45,    46,    45,    45,    45,    45,
      47,    47,    48,    48,    48,    48,    49,    49,    50,    50,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     0,     1,     3,     6,
       2,     2,     5,     4,     1,     3,     1,     3,     1,     0,
       6,     2,     0,     9,     1,     0,     4,     5,     7,     5,
       2,     0,     2,     1,     3,     2,     1,     0,     3,     1,
       1,     1,     3,     3,     2,     3,     3,     3,     3,     3,
       2,     3,     3,     3,     3,     4,     4,     3,     6,     2,
       2,     2,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
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
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
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

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

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
      yychar = yylex ();
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
     '$$ = $1'.

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
#line 43 "parse.y" /* yacc.c:1646  */
    {
            debugging("finish parsing\n");
            RootNode* ret = new RootNode();
            ret->addChild((yyvsp[0].nval));
            ret->finishParsing();
            (yyval.nval) = (Node*)ret;
    }
#line 1454 "parse.cc" /* yacc.c:1646  */
    break;

  case 3:
#line 53 "parse.y" /* yacc.c:1646  */
    {
        Node* ret = new OtherNode();
        ret->addChild((yyvsp[-1].nval));
        ret->addChild((yyvsp[0].nval));
        (yyval.nval) = ret;
    }
#line 1465 "parse.cc" /* yacc.c:1646  */
    break;

  case 4:
#line 61 "parse.y" /* yacc.c:1646  */
    {
        Node* ret = new OtherNode();
        ret->addChild((yyvsp[-1].nval));
        ret->addChild((yyvsp[0].nval));
        (yyval.nval) = ret;
    }
#line 1476 "parse.cc" /* yacc.c:1646  */
    break;

  case 5:
#line 69 "parse.y" /* yacc.c:1646  */
    {
        Node* ret = new OtherNode();
        ret->addChild((yyvsp[-1].nval));
        ret->addChild((yyvsp[0].nval));
        (yyval.nval) = ret;
    }
#line 1487 "parse.cc" /* yacc.c:1646  */
    break;

  case 6:
#line 77 "parse.y" /* yacc.c:1646  */
    {
        (yyval.nval) = new EmptyNode();
    }
#line 1495 "parse.cc" /* yacc.c:1646  */
    break;

  case 7:
#line 82 "parse.y" /* yacc.c:1646  */
    {
        string errMsg = 
        "your code is such a mess that compiler" \
        " can't decide which part is wrong";
        printErrorInfo(errMsg, (yylsp[0])); // ?
        (yyval.nval) = new EmptyNode();
    }
#line 1507 "parse.cc" /* yacc.c:1646  */
    break;

  case 8:
#line 92 "parse.y" /* yacc.c:1646  */
    {
        // this part could be added to createIdEntry
        createIdEntry((yyvsp[-1].sval), IntType, (yylsp[-1]));
        string name = getIdName((yyvsp[-1].sval),(yylsp[-1]));
        string code = "var " + name + "\n";
        Node* ret = new StatementNode();
        ret->appendCode(code);
        (yyval.nval) = ret;
    }
#line 1521 "parse.cc" /* yacc.c:1646  */
    break;

  case 9:
#line 103 "parse.y" /* yacc.c:1646  */
    {
        createIdEntry((yyvsp[-4].sval), ArrayType, (yylsp[-4]));
        string name = getIdName((yyvsp[-4].sval),(yylsp[-4]));
        string code = "var " + to_string(4*(yyvsp[-2].ival)) + " " + name + "\n";
        Node* ret = new StatementNode();
        ret->appendCode(code);
        (yyval.nval) = ret;
    }
#line 1534 "parse.cc" /* yacc.c:1646  */
    break;

  case 10:
#line 113 "parse.y" /* yacc.c:1646  */
    {
        printErrorInfo("wrong variable definition method", (yylsp[0]));
        (yyval.nval) = new StatementNode();
    }
#line 1543 "parse.cc" /* yacc.c:1646  */
    break;

  case 11:
#line 121 "parse.y" /* yacc.c:1646  */
    {
        Node* ret = new ParaNode((yyvsp[0].sval),IntType);
        (yyval.nval) = ret;
    }
#line 1552 "parse.cc" /* yacc.c:1646  */
    break;

  case 12:
#line 127 "parse.y" /* yacc.c:1646  */
    {
        Node* ret = new ParaNode((yyvsp[-3].sval),ArrayType);
        (yyval.nval) = ret;
    }
#line 1561 "parse.cc" /* yacc.c:1646  */
    break;

  case 13:
#line 133 "parse.y" /* yacc.c:1646  */
    {
        Node* ret = new ParaNode((yyvsp[-2].sval),ArrayType);
        (yyval.nval) = ret;
    }
#line 1570 "parse.cc" /* yacc.c:1646  */
    break;

  case 14:
#line 139 "parse.y" /* yacc.c:1646  */
    {
        Node* ret = new ParaNode(IntType);
        (yyval.nval) = ret;
    }
#line 1579 "parse.cc" /* yacc.c:1646  */
    break;

  case 15:
#line 145 "parse.y" /* yacc.c:1646  */
    {
        Node* ret = new ParaNode(ArrayType);
        (yyval.nval) = ret;
    }
#line 1588 "parse.cc" /* yacc.c:1646  */
    break;

  case 16:
#line 153 "parse.y" /* yacc.c:1646  */
    {
        Node* ret = new ParaListNode();
        ret->addChild((yyvsp[0].nval));
        (yyval.nval) = (yyvsp[0].nval);
    }
#line 1598 "parse.cc" /* yacc.c:1646  */
    break;

  case 17:
#line 160 "parse.y" /* yacc.c:1646  */
    {
        Node* ret = new ParaListNode();
        ret->addChild((yyvsp[-2].nval));
        ret->addChild((yyvsp[0].nval));
        (yyval.nval) = ret;
    }
#line 1609 "parse.cc" /* yacc.c:1646  */
    break;

  case 18:
#line 170 "parse.y" /* yacc.c:1646  */
    {
        (yyval.nval) = (yyvsp[0].nval);
    }
#line 1617 "parse.cc" /* yacc.c:1646  */
    break;

  case 19:
#line 175 "parse.y" /* yacc.c:1646  */
    {
        (yyval.nval) = new ParaListNode();
    }
#line 1625 "parse.cc" /* yacc.c:1646  */
    break;

  case 20:
#line 181 "parse.y" /* yacc.c:1646  */
    {
        Node* ret = new FuncNode();
        string name = string((yyvsp[-4].sval));
        createFuncEntry(name, DeclType, (ParaListNode*)(yyvsp[-2].nval), (yylsp[-4]));
        (yyval.nval) = ret;
    }
#line 1636 "parse.cc" /* yacc.c:1646  */
    break;

  case 21:
#line 189 "parse.y" /* yacc.c:1646  */
    {
        printErrorInfo("wrong function declare method", (yylsp[0]));
        (yyval.nval) = new FuncNode();
    }
#line 1645 "parse.cc" /* yacc.c:1646  */
    break;

  case 22:
#line 196 "parse.y" /* yacc.c:1646  */
    {
    /*
    * check func's compatability with previous ones
    * if ok, insert funcEntry to funcTable for future check
    * if also FuncDefn insert paraList to idTable and newScope()
    */
        string name = string((yyvsp[-4].sval));
        createFuncEntry(name, DefnType,(ParaListNode*)(yyvsp[-2].nval), (yylsp[-4]));
    }
#line 1659 "parse.cc" /* yacc.c:1646  */
    break;

  case 23:
#line 206 "parse.y" /* yacc.c:1646  */
    {
        debugging("finish parsing block\n");
        Node* ret = new FuncNode();
        ret->addChild((yyvsp[-1].nval));
        int paraNum = getParaNum((ParaListNode*)(yyvsp[-5].nval));
        string codeBefore = "f_" + string((yyvsp[-7].sval)) + " [" +to_string(paraNum)
         + "]\n";
        string codeAfter;

        // add return automatically
        if(!hasReturn)
            codeAfter = "return 0\nend f_" + string((yyvsp[-7].sval)) + "\n";
        else
            codeAfter = "end f_" + string((yyvsp[-7].sval)) +"\n";
        ret->appendCodeBefore(codeBefore);
        ret->appendCodeAfter(codeAfter);
        (yyval.nval) = ret;

        // exit func, endScope(), reset funcName
        exitFunc();
    }
#line 1685 "parse.cc" /* yacc.c:1646  */
    break;

  case 24:
#line 231 "parse.y" /* yacc.c:1646  */
    {
        Node* ret = new OtherNode();
        ret->addChild((yyvsp[0].nval));
        (yyval.nval) = ret;
    }
#line 1695 "parse.cc" /* yacc.c:1646  */
    break;

  case 25:
#line 237 "parse.y" /* yacc.c:1646  */
    {newScope();}
#line 1701 "parse.cc" /* yacc.c:1646  */
    break;

  case 26:
#line 238 "parse.y" /* yacc.c:1646  */
    {
        endScope();
        (yyval.nval) = (yyvsp[-1].nval);
    }
#line 1710 "parse.cc" /* yacc.c:1646  */
    break;

  case 27:
#line 244 "parse.y" /* yacc.c:1646  */
    {
        Node* ret = new OtherNode();
        ret->addChild((yyvsp[-2].nval));
        ret->addChild((yyvsp[0].nval));
        string l = newLabel();
        string jmpCode = 
        "if " + ((ExprNode*)(yyvsp[-2].nval))->valueID + " == 0 goto " + l + "\n";
        ret->appendCodeMiddle(jmpCode);
        ret->appendCodeAfter(l + ":\n");
        (yyval.nval) = ret;
    }
#line 1726 "parse.cc" /* yacc.c:1646  */
    break;

  case 28:
#line 257 "parse.y" /* yacc.c:1646  */
    {
        Node* midNode = new OtherNode();
        midNode->addChild((yyvsp[-2].nval));
        midNode->addChild((yyvsp[0].nval));
        Node* ret = new OtherNode();
        ret->addChild((yyvsp[-4].nval));
        ret->addChild(midNode);
        (yyval.nval) = ret;
        string l1 = newLabel();
        string l2 = newLabel();
        string jmp1 = 
        "if " + ((ExprNode*)(yyvsp[-4].nval))->valueID + " == 0 goto " + l1 + "\n";
        string jmp2 = "goto " + l2 + "\n";
        midNode->appendCodeBefore(jmp1);
        midNode->appendCodeMiddle(jmp2 + l1 + ":\n");
        midNode->appendCodeAfter(l2+":\n");
    }
#line 1748 "parse.cc" /* yacc.c:1646  */
    break;

  case 29:
#line 276 "parse.y" /* yacc.c:1646  */
    {
        Node* ret = new OtherNode();
        ret->addChild((yyvsp[-2].nval));
        ret->addChild((yyvsp[0].nval));
        string l1 = newLabel();
        string l2 = newLabel();
        string jmp1 = 
        "if " + ((ExprNode*)(yyvsp[-2].nval))->valueID + " == 0 goto " + l2 + "\n";
        string jmp2 = "goto " + l1 + "\n";
        ret->appendCodeMiddle(l1 + ":\n" + jmp1);
        ret->appendCodeAfter(jmp2 + l2 + ":\n");
        (yyval.nval) = ret;
    }
#line 1766 "parse.cc" /* yacc.c:1646  */
    break;

  case 30:
#line 293 "parse.y" /* yacc.c:1646  */
    {
        Node* ret = new OtherNode();
        ret->addChild((yyvsp[-1].nval));
        ret->addChild((yyvsp[0].nval));
        (yyval.nval) = ret;
    }
#line 1777 "parse.cc" /* yacc.c:1646  */
    break;

  case 31:
#line 301 "parse.y" /* yacc.c:1646  */
    {
        Node* ret = new EmptyNode();
        (yyval.nval) = ret;
    }
#line 1786 "parse.cc" /* yacc.c:1646  */
    break;

  case 32:
#line 309 "parse.y" /* yacc.c:1646  */
    {
        (yyval.nval) = (yyvsp[-1].nval);
    }
#line 1794 "parse.cc" /* yacc.c:1646  */
    break;

  case 33:
#line 314 "parse.y" /* yacc.c:1646  */
    {
        (yyval.nval) = (yyvsp[0].nval);
    }
#line 1802 "parse.cc" /* yacc.c:1646  */
    break;

  case 34:
#line 319 "parse.y" /* yacc.c:1646  */
    {
        Node* ret = new OtherNode();
        ret->addChild((yyvsp[-1].nval));
        (yyval.nval) = ret;
        string s = "return " + ((ExprNode*)(yyvsp[-1].nval))->valueID + "\n";
        ret->appendCodeAfter(s);
        hasReturn = true;
    }
#line 1815 "parse.cc" /* yacc.c:1646  */
    break;

  case 35:
#line 329 "parse.y" /* yacc.c:1646  */
    {
        (yyval.nval) = new OtherNode();
        string errMsg = "broken statement";
        printErrorInfo(errMsg, (yylsp[0]));
    }
#line 1825 "parse.cc" /* yacc.c:1646  */
    break;

  case 36:
#line 338 "parse.y" /* yacc.c:1646  */
    {
        Node* ret = new ExprListNode();
        ret->addChild((yyvsp[0].nval));
        (yyval.nval) = ret;
    }
#line 1835 "parse.cc" /* yacc.c:1646  */
    break;

  case 37:
#line 345 "parse.y" /* yacc.c:1646  */
    {
        Node* ret = new ExprListNode();
        (yyval.nval) = ret;
    }
#line 1844 "parse.cc" /* yacc.c:1646  */
    break;

  case 38:
#line 353 "parse.y" /* yacc.c:1646  */
    {
        Node* ret = new OtherNode();
        ret->addChild((yyvsp[-2].nval));
        ret->addChild((yyvsp[0].nval));
        (yyval.nval) = ret;
    }
#line 1855 "parse.cc" /* yacc.c:1646  */
    break;

  case 39:
#line 361 "parse.y" /* yacc.c:1646  */
    {
        (yyval.nval) = (yyvsp[0].nval);
    }
#line 1863 "parse.cc" /* yacc.c:1646  */
    break;

  case 40:
#line 367 "parse.y" /* yacc.c:1646  */
    {
        ExprNode* ret = new ExprNode();
        ret->isInteger = true;
        ret->valueID = to_string((yyvsp[0].ival));
        (yyval.nval) = (Node*)ret;
    }
#line 1874 "parse.cc" /* yacc.c:1646  */
    break;

  case 41:
#line 375 "parse.y" /* yacc.c:1646  */
    {
        ExprNode* ret = new ExprNode();
        string name = string((yyvsp[0].sval));
        ret->isID = true;
        ret->valueID = getIdName(name, (yylsp[0]));
        (yyval.nval) = (Node*)ret;
    }
#line 1886 "parse.cc" /* yacc.c:1646  */
    break;

  case 42:
#line 384 "parse.y" /* yacc.c:1646  */
    {
        ExprNode* ret = new ExprNode();
        ret->addChild((yyvsp[-2].nval));
        ret->addChild((yyvsp[0].nval));
        string tmp = newTemp();
        string code = "var " + tmp + "\n" + tmp + " = " + 
         ((ExprNode*)(yyvsp[-2].nval))->valueID + " + " + ((ExprNode*)(yyvsp[0].nval))->valueID + "\n";
        ret->appendCodeAfter(code);
        ret->valueID = tmp;
        (yyval.nval) = (Node*)ret;           
    }
#line 1902 "parse.cc" /* yacc.c:1646  */
    break;

  case 43:
#line 397 "parse.y" /* yacc.c:1646  */
    {
        ExprNode* ret = new ExprNode();
        ret->addChild((yyvsp[-2].nval));
        ret->addChild((yyvsp[0].nval));
        string tmp = newTemp();
        string code = "var " + tmp + "\n" + tmp + " = " + 
         ((ExprNode*)(yyvsp[-2].nval))->valueID + " - " + ((ExprNode*)(yyvsp[0].nval))->valueID + "\n";
        ret->appendCodeAfter(code);
        ret->valueID = tmp;
        (yyval.nval) = (Node*)ret;           
    }
#line 1918 "parse.cc" /* yacc.c:1646  */
    break;

  case 44:
#line 410 "parse.y" /* yacc.c:1646  */
    {
        ExprNode* ret = new ExprNode();
        ret->addChild((yyvsp[0].nval));
        string tmp = newTemp();
        string code = "var " + tmp + "\n" + tmp + " = -" +
         ((ExprNode*)(yyvsp[0].nval))->valueID + "\n";
        ret->appendCodeAfter(code);
        ret->valueID = tmp;
        (yyval.nval) = (Node*)ret;      
    }
#line 1933 "parse.cc" /* yacc.c:1646  */
    break;

  case 45:
#line 422 "parse.y" /* yacc.c:1646  */
    {
        ExprNode* ret = new ExprNode();
        ret->addChild((yyvsp[-2].nval));
        ret->addChild((yyvsp[0].nval));
        string tmp = newTemp();
        string code = "var " + tmp + "\n" + tmp + " = " +
         ((ExprNode*)(yyvsp[-2].nval))->valueID + " * " + ((ExprNode*)(yyvsp[0].nval))->valueID + "\n";
        ret->appendCodeAfter(code);
        ret->valueID = tmp;
        (yyval.nval) = (Node*)ret;           
    }
#line 1949 "parse.cc" /* yacc.c:1646  */
    break;

  case 46:
#line 435 "parse.y" /* yacc.c:1646  */
    {
        ExprNode* ret = new ExprNode();
        ret->addChild((yyvsp[-2].nval));
        ret->addChild((yyvsp[0].nval));
        string tmp = newTemp();
        string code = "var " + tmp + "\n" + tmp + " = " +
         ((ExprNode*)(yyvsp[-2].nval))->valueID + " / " + ((ExprNode*)(yyvsp[0].nval))->valueID + "\n";
        ret->appendCodeAfter(code);
        ret->valueID = tmp;
        (yyval.nval) = (Node*)ret;      

        if(((ExprNode*)(yyvsp[0].nval))->valueID=="0"){
            printWarningInfo("division by zero", (yylsp[-1]));
        }
    }
#line 1969 "parse.cc" /* yacc.c:1646  */
    break;

  case 47:
#line 452 "parse.y" /* yacc.c:1646  */
    {
        ExprNode* ret = new ExprNode();
        ret->addChild((yyvsp[-2].nval));
        ret->addChild((yyvsp[0].nval));
        string tmp = newTemp();
        string code = "var " + tmp + "\n" + tmp + " = " +
         ((ExprNode*)(yyvsp[-2].nval))->valueID + " % " + ((ExprNode*)(yyvsp[0].nval))->valueID + "\n";
        ret->appendCodeAfter(code);
        ret->valueID = tmp;
        (yyval.nval) = (Node*)ret;      

        if(((ExprNode*)(yyvsp[0].nval))->valueID=="0"){
            printWarningInfo("division by zero", (yylsp[-1]));
        }
    }
#line 1989 "parse.cc" /* yacc.c:1646  */
    break;

  case 48:
#line 469 "parse.y" /* yacc.c:1646  */
    {
        ExprNode* ret = new ExprNode();
        ret->addChild((yyvsp[-2].nval));
        ret->addChild((yyvsp[0].nval));
        string tmp = newTemp();
        string code = "var " + tmp + "\n" + tmp + " = "
         + ((ExprNode*)(yyvsp[-2].nval))->valueID + " && " + ((ExprNode*)(yyvsp[0].nval))->valueID + "\n";
        ret->appendCodeAfter(code);
        ret->valueID = tmp;
        (yyval.nval) = (Node*)ret;      
    }
#line 2005 "parse.cc" /* yacc.c:1646  */
    break;

  case 49:
#line 482 "parse.y" /* yacc.c:1646  */
    {
        ExprNode* ret = new ExprNode();
        ret->addChild((yyvsp[-2].nval));
        ret->addChild((yyvsp[0].nval));
        string tmp = newTemp();
        string code = "var " + tmp + "\n" + tmp + " = " +
         ((ExprNode*)(yyvsp[-2].nval))->valueID + " || " + ((ExprNode*)(yyvsp[0].nval))->valueID + "\n";
        ret->appendCodeAfter(code);
        ret->valueID = tmp;
        (yyval.nval) = (Node*)ret;   
    }
#line 2021 "parse.cc" /* yacc.c:1646  */
    break;

  case 50:
#line 495 "parse.y" /* yacc.c:1646  */
    {
        ExprNode* ret = new ExprNode();
        ret->addChild((yyvsp[0].nval));
        string tmp = newTemp();
        string code = "var " + tmp + "\n" + tmp + " = !" +
         ((ExprNode*)(yyvsp[0].nval))->valueID + "\n";
        ret->appendCodeAfter(code);
        ret->valueID = tmp;
        (yyval.nval) = (Node*)ret;
    }
#line 2036 "parse.cc" /* yacc.c:1646  */
    break;

  case 51:
#line 507 "parse.y" /* yacc.c:1646  */
    {
        ExprNode* ret = new ExprNode();
        ret->addChild((yyvsp[-2].nval));
        ret->addChild((yyvsp[0].nval));
        string tmp = newTemp();
        string code = "var " + tmp + "\n" + tmp + " = " +
         ((ExprNode*)(yyvsp[-2].nval))->valueID + " < " + ((ExprNode*)(yyvsp[0].nval))->valueID + "\n";
        ret->appendCodeAfter(code);
        ret->valueID = tmp;
        (yyval.nval) = (Node*)ret;      
    }
#line 2052 "parse.cc" /* yacc.c:1646  */
    break;

  case 52:
#line 520 "parse.y" /* yacc.c:1646  */
    {
        ExprNode* ret = new ExprNode();
        ret->addChild((yyvsp[-2].nval));
        ret->addChild((yyvsp[0].nval));
        string tmp = newTemp();
        string code = "var " + tmp + "\n" + tmp + " = " +
         ((ExprNode*)(yyvsp[-2].nval))->valueID + " > " + ((ExprNode*)(yyvsp[0].nval))->valueID + "\n";
        ret->appendCodeAfter(code);
        ret->valueID = tmp;
        (yyval.nval) = (Node*)ret;  
    }
#line 2068 "parse.cc" /* yacc.c:1646  */
    break;

  case 53:
#line 533 "parse.y" /* yacc.c:1646  */
    {
        ExprNode* ret = new ExprNode();
        ret->addChild((yyvsp[-2].nval));
        ret->addChild((yyvsp[0].nval));
        (yyval.nval) = (Node*)ret;     

        string tmp = newTemp();
        string code = "var " + tmp + "\n" + tmp + " = " +
         ((ExprNode*)(yyvsp[-2].nval))->valueID + " == " + ((ExprNode*)(yyvsp[0].nval))->valueID + "\n";
        ret->appendCodeAfter(code);
        ret->valueID = tmp;
    }
#line 2085 "parse.cc" /* yacc.c:1646  */
    break;

  case 54:
#line 547 "parse.y" /* yacc.c:1646  */
    {
        ExprNode* ret = new ExprNode();
        ret->addChild((yyvsp[-2].nval));
        ret->addChild((yyvsp[0].nval));
        (yyval.nval) = (Node*)ret;             

        string tmp = newTemp();
        string code = "var " + tmp + "\n" + tmp + " = " +
         ((ExprNode*)(yyvsp[-2].nval))->valueID + " != " + ((ExprNode*)(yyvsp[0].nval))->valueID + "\n";
        ret->appendCodeAfter(code);
        ret->valueID = tmp;
    }
#line 2102 "parse.cc" /* yacc.c:1646  */
    break;

  case 55:
#line 561 "parse.y" /* yacc.c:1646  */
    {
        ExprNode* ret = new ExprNode();
        ret->addChild((yyvsp[-1].nval));
        (yyval.nval) = (Node*)ret;
        string name = string((yyvsp[-3].sval));
        ExprListNode* exprList = (ExprListNode*)(yyvsp[-1].nval);
        FuncEntry call = FuncEntry(name, exprList);
        FuncEntry* called = findFuncEntry(name, (yylsp[-3]));
        if(called!=NULL){
            int cmpParaNum = cmpFuncParaNum(call, *called);
            if(cmpParaNum > 0){
                string errMsg = "too many arguments to function '" + name + "'";
                printErrorInfo(errMsg,(yylsp[-3]));
            }
            else if(cmpParaNum < 0){
                string errMsg = "too few arguments to function '" + name + "'";
                printErrorInfo(errMsg,(yylsp[-3]));
            }
            else{
                // main branch
                stringstream code = stringstream();
                string tmp = newTemp();
                ret->valueID = tmp;
                code << "var " << tmp << endl;
                for(auto& para:call.paraList){
                    code << "param " << para.EName << endl;
                }
                code << tmp << " = call f_" << name << endl;
                ret->appendCodeAfter(code.str());
                ret->valueID = tmp;
            }
        }
        else{
            // warning but still do same thing as main branch
            stringstream code = stringstream();
            string tmp = newTemp();
            ret->valueID = tmp;
            code << "var " << tmp << endl;
            for(auto& para:call.paraList){
                code << "param " << para.EName << endl;
            }
            code << tmp << " = call f_" << name << endl;
            ret->appendCodeAfter(code.str());
            ret->valueID = tmp;
        }
    }
#line 2153 "parse.cc" /* yacc.c:1646  */
    break;

  case 56:
#line 609 "parse.y" /* yacc.c:1646  */
    {
        ExprNode* ret = new ExprNode();
        ret->addChild((yyvsp[-1].nval));
        (yyval.nval) = (Node*)ret;

        string CName = string((yyvsp[-3].sval));
        string EName = getIdName(CName, (yylsp[-3]));
        string temp1 = newTemp();
        string temp2 = newTemp();
        string valueID = ((ExprNode*)(yyvsp[-1].nval))->valueID;
        string code;
        code = "var " + temp1 + "\n" + temp1 + " = 4 * " + valueID + "\n" +
         "var " + temp2 + "\n" + temp2 + " = " + EName + "[" + temp1 + "]" +
          "\n";
        ret->appendCodeAfter(code);
        ret->valueID = temp2;
    }
#line 2175 "parse.cc" /* yacc.c:1646  */
    break;

  case 57:
#line 628 "parse.y" /* yacc.c:1646  */
    {
        ExprNode* ret = new ExprNode();
        ret->addChild((yyvsp[0].nval));
        (yyval.nval) = (ExprNode*)ret;

        string CName = string((yyvsp[-2].sval));
        string EName = getIdName(CName,(yylsp[-2]));
        string code;
        code = EName + " = " + ((ExprNode*)(yyvsp[0].nval))->valueID + "\n";
        ret->appendCodeAfter(code);
        ret->valueID = EName;
    }
#line 2192 "parse.cc" /* yacc.c:1646  */
    break;

  case 58:
#line 642 "parse.y" /* yacc.c:1646  */
    {
        ExprNode* ret = new ExprNode();
        ret->addChild((yyvsp[-3].nval));
        ret->addChild((yyvsp[0].nval));
        (yyval.nval) = ret;

        string CName = string((yyvsp[-5].sval));
        string EName = getIdName(CName,(yylsp[-5]));
        // string temp2 = newTemp();
        stringstream code = stringstream();
        ExprNode* expr = (ExprNode*)(yyvsp[-3].nval);
        if(expr->isInteger){
            int bias = 4 * stoi(expr->valueID);
            code << EName << "[" << to_string(bias) << "] = " << ((ExprNode*)(yyvsp[0].nval))->valueID << endl;
        }
        else{
            string temp1 = newTemp();
            code << "var " << temp1 << endl;
            code << temp1 << " = 4 * " << ((ExprNode*)(yyvsp[-3].nval))->valueID <<endl;
            // code << "var " << temp2 << endl;
            code << EName << "[" << temp1 << "] = " << ((ExprNode*)(yyvsp[0].nval))->valueID << endl;
        }

        ret->appendCodeAfter(code.str());
        // ret->valueID = temp2;
        // ?
    }
#line 2224 "parse.cc" /* yacc.c:1646  */
    break;

  case 59:
#line 671 "parse.y" /* yacc.c:1646  */
    {
        ExprNode* ret = new ExprNode();
        (yyval.nval) = ret;

        string CName =string((yyvsp[0].sval));
        string EName = getIdName(CName,(yylsp[0]));
        string code = EName + " = " + EName + " + 1\n";
        ret->appendCode(code);
        ret->valueID = EName; 
    }
#line 2239 "parse.cc" /* yacc.c:1646  */
    break;

  case 60:
#line 683 "parse.y" /* yacc.c:1646  */
    {
        ExprNode* ret = new ExprNode();
        (yyval.nval) = ret;

        string CName =string((yyvsp[-1].sval));
        string EName = getIdName(CName,(yylsp[-1]));
        string temp = newTemp();
        stringstream code = stringstream();
        code << "var " << temp << endl;
        code << temp << " = " << EName << endl;
        code << EName << " = " << EName << " + 1" << endl;
        ret->appendCode(code.str());
        ret->valueID = temp;
    }
#line 2258 "parse.cc" /* yacc.c:1646  */
    break;

  case 61:
#line 699 "parse.y" /* yacc.c:1646  */
    {
        ExprNode* ret = new ExprNode();
        (yyval.nval) = ret;

        string CName =string((yyvsp[0].sval));
        string EName = getIdName(CName,(yylsp[0]));
        string code = EName + " = " + EName + " - 1\n";
        ret->appendCode(code);
        ret->valueID = EName; 
    }
#line 2273 "parse.cc" /* yacc.c:1646  */
    break;

  case 62:
#line 711 "parse.y" /* yacc.c:1646  */
    {
        ExprNode* ret = new ExprNode();
        (yyval.nval) = ret;

        string CName =string((yyvsp[-1].sval));
        string EName = getIdName(CName,(yylsp[-1]));
        string temp = newTemp();
        stringstream code = stringstream();
        code << "var " << temp << endl;
        code << temp << " = " << EName << endl;
        code << EName << " = " << EName << " - 1" << endl;
        ret->appendCode(code.str());
        ret->valueID = temp;
    }
#line 2292 "parse.cc" /* yacc.c:1646  */
    break;


#line 2296 "parse.cc" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 727 "parse.y" /* yacc.c:1906  */

void yyerror(const char *s) {
    cerr << s;
}