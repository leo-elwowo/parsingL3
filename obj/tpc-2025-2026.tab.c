/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/tpc-2025-2026.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

int yylex();
void yyerror(const char *s);
extern int lineno;
int nberror = 0;

Node *root = NULL;

#line 85 "obj/tpc-2025-2026.tab.c"

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

#include "tpc-2025-2026.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUM = 3,                        /* NUM  */
  YYSYMBOL_IDENT = 4,                      /* IDENT  */
  YYSYMBOL_TYPE = 5,                       /* TYPE  */
  YYSYMBOL_CHARACTER = 6,                  /* CHARACTER  */
  YYSYMBOL_ADDSUB = 7,                     /* ADDSUB  */
  YYSYMBOL_DIVSTAR = 8,                    /* DIVSTAR  */
  YYSYMBOL_EQ = 9,                         /* EQ  */
  YYSYMBOL_ORDER = 10,                     /* ORDER  */
  YYSYMBOL_IF = 11,                        /* IF  */
  YYSYMBOL_ELSE = 12,                      /* ELSE  */
  YYSYMBOL_WHILE = 13,                     /* WHILE  */
  YYSYMBOL_RETURN = 14,                    /* RETURN  */
  YYSYMBOL_STRUCT = 15,                    /* STRUCT  */
  YYSYMBOL_VOID = 16,                      /* VOID  */
  YYSYMBOL_AND = 17,                       /* AND  */
  YYSYMBOL_OR = 18,                        /* OR  */
  YYSYMBOL_19_ = 19,                       /* ';'  */
  YYSYMBOL_20_ = 20,                       /* '{'  */
  YYSYMBOL_21_ = 21,                       /* '}'  */
  YYSYMBOL_22_ = 22,                       /* ','  */
  YYSYMBOL_23_ = 23,                       /* '('  */
  YYSYMBOL_24_ = 24,                       /* ')'  */
  YYSYMBOL_25_ = 25,                       /* '='  */
  YYSYMBOL_26_ = 26,                       /* '.'  */
  YYSYMBOL_27_ = 27,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 28,                  /* $accept  */
  YYSYMBOL_Prog = 29,                      /* Prog  */
  YYSYMBOL_Globals = 30,                   /* Globals  */
  YYSYMBOL_DeclVars = 31,                  /* DeclVars  */
  YYSYMBOL_ListDeclVars = 32,              /* ListDeclVars  */
  YYSYMBOL_DeclStruct = 33,                /* DeclStruct  */
  YYSYMBOL_Declarateurs = 34,              /* Declarateurs  */
  YYSYMBOL_TypeName = 35,                  /* TypeName  */
  YYSYMBOL_DeclFoncts = 36,                /* DeclFoncts  */
  YYSYMBOL_DeclFonct = 37,                 /* DeclFonct  */
  YYSYMBOL_EnTeteFonct = 38,               /* EnTeteFonct  */
  YYSYMBOL_Parametres = 39,                /* Parametres  */
  YYSYMBOL_ListTypVar = 40,                /* ListTypVar  */
  YYSYMBOL_Corps = 41,                     /* Corps  */
  YYSYMBOL_SuiteInstr = 42,                /* SuiteInstr  */
  YYSYMBOL_Instr = 43,                     /* Instr  */
  YYSYMBOL_LValue = 44,                    /* LValue  */
  YYSYMBOL_Exp = 45,                       /* Exp  */
  YYSYMBOL_TB = 46,                        /* TB  */
  YYSYMBOL_FB = 47,                        /* FB  */
  YYSYMBOL_M = 48,                         /* M  */
  YYSYMBOL_E = 49,                         /* E  */
  YYSYMBOL_T = 50,                         /* T  */
  YYSYMBOL_F = 51,                         /* F  */
  YYSYMBOL_Arguments = 52,                 /* Arguments  */
  YYSYMBOL_ListExp = 53                    /* ListExp  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   130

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  28
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  60
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  118

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   273


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
       2,     2,     2,    27,     2,     2,     2,     2,     2,     2,
      23,    24,     2,     2,    22,     2,    26,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    19,
       2,    25,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    20,     2,    21,     2,     2,     2,     2,
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
      15,    16,    17,    18
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    37,    37,    46,    52,    58,    62,    73,    79,    83,
      92,    98,   108,   113,   122,   129,   137,   146,   155,   167,
     168,   169,   173,   182,   193,   202,   208,   212,   218,   224,
     232,   238,   245,   250,   252,   253,   257,   262,   271,   274,
     277,   280,   283,   289,   292,   298,   301,   307,   310,   316,
     319,   325,   330,   332,   337,   342,   344,   354,   356,   360,
     367
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUM", "IDENT", "TYPE",
  "CHARACTER", "ADDSUB", "DIVSTAR", "EQ", "ORDER", "IF", "ELSE", "WHILE",
  "RETURN", "STRUCT", "VOID", "AND", "OR", "';'", "'{'", "'}'", "','",
  "'('", "')'", "'='", "'.'", "'!'", "$accept", "Prog", "Globals",
  "DeclVars", "ListDeclVars", "DeclStruct", "Declarateurs", "TypeName",
  "DeclFoncts", "DeclFonct", "EnTeteFonct", "Parametres", "ListTypVar",
  "Corps", "SuiteInstr", "Instr", "LValue", "Exp", "TB", "FB", "M", "E",
  "T", "F", "Arguments", "ListExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-88)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -88,    37,    25,   -88,   -88,    11,    16,   -88,   -88,    21,
      66,   -88,    24,    44,    12,    57,    72,    80,    84,   -88,
     -88,   -88,   -88,    70,    70,   -88,    86,   -88,    57,     1,
      53,   -88,    88,    45,    54,    73,   -88,   -88,    94,    35,
      81,   -88,   -88,     1,   -88,   -88,    76,    78,    79,    15,
     -88,   -88,   -88,   -88,   -18,   -88,    99,    20,    20,    20,
     -88,    82,   -88,    20,   -88,    20,    20,    83,    34,    87,
      97,    98,   100,   102,   -88,    46,    20,   107,   -88,    95,
      90,    93,   -15,    65,    20,   -88,    69,   -88,    20,   -88,
      20,    20,    20,    20,    20,   -88,    77,   -88,   101,    20,
      59,    59,    92,   -88,    87,    97,    98,   100,   102,   -88,
     -88,   -88,    95,   105,   -88,   -88,    59,   -88
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,     0,     0,     1,    12,     0,     0,     4,     3,     0,
       2,    15,     0,    13,     0,    11,     0,     0,     0,    14,
       8,    16,     8,    21,    21,     6,     0,    13,     0,    26,
       0,    19,     0,     0,    20,     0,    10,     7,     0,     0,
       0,    23,    18,     0,    17,    11,    36,     0,     0,     0,
      35,    26,    24,    25,     0,     9,     0,    58,     0,     0,
      53,    36,    54,     0,    33,     0,     0,    55,     0,    39,
      41,    43,    45,    47,    49,     0,     0,     0,    22,    60,
       0,    57,     0,     0,    58,    50,     0,    51,     0,    32,
       0,     0,     0,     0,     0,    34,     0,    37,     0,     0,
       0,     0,     0,    52,    38,    40,    42,    44,    46,    48,
      27,    31,    59,    28,    30,    56,     0,    29
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -88,   -88,   -88,   110,    96,   -88,   -88,     2,   -88,   109,
     -88,   103,   -88,   -88,    71,   -87,   -39,   -48,    33,    36,
      32,    38,    31,   -61,    41,   -88
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    37,    29,     8,    16,    32,    10,    11,
      12,    33,    34,    21,    39,    53,    67,    79,    69,    70,
      71,    72,    73,    74,    80,    81
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      54,    68,    85,    88,     9,    87,     4,    76,    77,   100,
      82,    83,    18,   113,   114,    13,    17,    86,    60,    61,
      14,    62,    63,    60,    61,    15,    62,    63,    96,   117,
       4,    38,    38,   109,    64,    23,    54,     3,    65,    46,
       5,     6,    66,    65,    20,    56,    47,    66,    48,    49,
      46,   112,    88,    89,    50,    51,    52,    47,     4,    48,
      49,    54,    54,    46,    22,    50,    51,    95,    17,    42,
      47,     4,    48,    49,    40,     4,    43,    54,    50,    51,
      24,    17,     6,    88,    27,    17,    31,    88,    28,   101,
      36,    25,    41,   103,    26,    88,   110,    44,    45,    57,
      55,    58,    59,    78,    90,    84,    91,    93,    92,    77,
      94,    97,     7,    88,    98,    99,   115,   116,    30,    19,
     111,   104,    75,   106,   108,   102,   105,    35,     0,     0,
     107
};

static const yytype_int8 yycheck[] =
{
      39,    49,    63,    18,     2,    66,     5,    25,    26,    24,
      58,    59,    10,   100,   101,     4,    15,    65,     3,     4,
       4,     6,     7,     3,     4,     4,     6,     7,    76,   116,
       5,    29,    30,    94,    19,    23,    75,     0,    23,     4,
      15,    16,    27,    23,    20,    43,    11,    27,    13,    14,
       4,    99,    18,    19,    19,    20,    21,    11,     5,    13,
      14,   100,   101,     4,    20,    19,    20,    21,    15,    24,
      11,     5,    13,    14,    21,     5,    22,   116,    19,    20,
      23,    15,    16,    18,     4,    15,    16,    18,     4,    24,
       4,    19,     4,    24,    22,    18,    19,    24,     4,    23,
      19,    23,    23,     4,    17,    23,     9,     7,    10,    26,
       8,     4,     2,    18,    24,    22,    24,    12,    22,    10,
      19,    88,    51,    91,    93,    84,    90,    24,    -1,    -1,
      92
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    29,    30,     0,     5,    15,    16,    31,    33,    35,
      36,    37,    38,     4,     4,     4,    34,    15,    35,    37,
      20,    41,    20,    23,    23,    19,    22,     4,     4,    32,
      32,    16,    35,    39,    40,    39,     4,    31,    35,    42,
      21,     4,    24,    22,    24,     4,     4,    11,    13,    14,
      19,    20,    21,    43,    44,    19,    35,    23,    23,    23,
       3,     4,     6,     7,    19,    23,    27,    44,    45,    46,
      47,    48,    49,    50,    51,    42,    25,    26,     4,    45,
      52,    53,    45,    45,    23,    51,    45,    51,    18,    19,
      17,     9,    10,     7,     8,    21,    45,     4,    24,    22,
      24,    24,    52,    24,    46,    47,    48,    49,    50,    51,
      19,    19,    45,    43,    43,    24,    12,    43
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    28,    29,    30,    30,    30,    31,    32,    32,    33,
      34,    34,    35,    35,    36,    36,    37,    38,    38,    39,
      39,    39,    40,    40,    41,    42,    42,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    44,    44,    45,    45,
      46,    46,    47,    47,    48,    48,    49,    49,    50,    50,
      51,    51,    51,    51,    51,    51,    51,    52,    52,    53,
      53
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     2,     0,     3,     2,     0,     6,
       3,     1,     1,     2,     2,     1,     2,     5,     5,     1,
       1,     0,     4,     2,     4,     2,     0,     4,     5,     7,
       5,     5,     3,     2,     3,     1,     1,     3,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       2,     2,     3,     1,     1,     1,     4,     1,     0,     3,
       1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


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

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Prog: Globals DeclFoncts  */
#line 38 "src/tpc-2025-2026.y"
    {
        root = makeNode(T_PROG);
        addChild(root, (yyvsp[-1].node));
        addChild(root, (yyvsp[0].node));
    }
#line 1204 "obj/tpc-2025-2026.tab.c"
    break;

  case 3: /* Globals: Globals DeclStruct  */
#line 47 "src/tpc-2025-2026.y"
       { 
           (yyval.node) = (yyvsp[-1].node);
           if ((yyval.node) == NULL) (yyval.node) = makeNode(T_LIST);
           addChild((yyval.node), (yyvsp[0].node)); 
       }
#line 1214 "obj/tpc-2025-2026.tab.c"
    break;

  case 4: /* Globals: Globals DeclVars  */
#line 53 "src/tpc-2025-2026.y"
       {
           (yyval.node) = (yyvsp[-1].node);
           if ((yyval.node) == NULL) (yyval.node) = makeNode(T_LIST);
           addChild((yyval.node), (yyvsp[0].node));
       }
#line 1224 "obj/tpc-2025-2026.tab.c"
    break;

  case 5: /* Globals: %empty  */
#line 58 "src/tpc-2025-2026.y"
        {(yyval.node) = NULL;}
#line 1230 "obj/tpc-2025-2026.tab.c"
    break;

  case 6: /* DeclVars: TypeName Declarateurs ';'  */
#line 63 "src/tpc-2025-2026.y"
       {
           (yyval.node) = makeNode(T_DECL_VARS);
           Node *groupe = makeNode(T_LIST);
           addChild(groupe, (yyvsp[-2].node));
           addChild(groupe, (yyvsp[-1].node));
           addChild((yyval.node), groupe);
       }
#line 1242 "obj/tpc-2025-2026.tab.c"
    break;

  case 7: /* ListDeclVars: ListDeclVars DeclVars  */
#line 74 "src/tpc-2025-2026.y"
       {
           (yyval.node) = (yyvsp[-1].node);
           if ((yyval.node) == NULL) (yyval.node) = makeNode(T_LIST);
           addChild((yyval.node), (yyvsp[0].node));
       }
#line 1252 "obj/tpc-2025-2026.tab.c"
    break;

  case 8: /* ListDeclVars: %empty  */
#line 79 "src/tpc-2025-2026.y"
     { (yyval.node) = NULL; }
#line 1258 "obj/tpc-2025-2026.tab.c"
    break;

  case 9: /* DeclStruct: STRUCT IDENT '{' ListDeclVars '}' ';'  */
#line 84 "src/tpc-2025-2026.y"
       {
           (yyval.node) = makeNode(T_STRUCT_DECL);
           Node *nId = makeNode(T_IDENT); strcpy(nId->ident, (yyvsp[-4].ident));
           addChild((yyval.node), nId); 
           addChild((yyval.node), (yyvsp[-2].node));  
       }
#line 1269 "obj/tpc-2025-2026.tab.c"
    break;

  case 10: /* Declarateurs: Declarateurs ',' IDENT  */
#line 93 "src/tpc-2025-2026.y"
       {
           (yyval.node) = (yyvsp[-2].node);
           Node *id = makeNode(T_IDENT); strcpy(id->ident, (yyvsp[0].ident));
           addChild((yyval.node), id);
       }
#line 1279 "obj/tpc-2025-2026.tab.c"
    break;

  case 11: /* Declarateurs: IDENT  */
#line 99 "src/tpc-2025-2026.y"
       {
           (yyval.node) = makeNode(T_LIST); 
           Node *id = makeNode(T_IDENT);
           strcpy(id->ident, (yyvsp[0].ident));
           addChild((yyval.node), id);
       }
#line 1290 "obj/tpc-2025-2026.tab.c"
    break;

  case 12: /* TypeName: TYPE  */
#line 109 "src/tpc-2025-2026.y"
       { 
           (yyval.node) = makeNode(T_TYPE);
           strcpy((yyval.node)->ident, (yyvsp[0].ident));
       }
#line 1299 "obj/tpc-2025-2026.tab.c"
    break;

  case 13: /* TypeName: STRUCT IDENT  */
#line 114 "src/tpc-2025-2026.y"
       {
           (yyval.node) = makeNode(T_TYPE_STRUCT);
           Node *id = makeNode(T_IDENT); strcpy(id->ident, (yyvsp[0].ident));
           addChild((yyval.node), id);
       }
#line 1309 "obj/tpc-2025-2026.tab.c"
    break;

  case 14: /* DeclFoncts: DeclFoncts DeclFonct  */
#line 123 "src/tpc-2025-2026.y"
       {
           (yyval.node) = (yyvsp[-1].node);
           if ((yyval.node) == NULL) (yyval.node) = makeNode(T_DECL_FONCTS);
           addChild((yyval.node), (yyvsp[0].node));
       }
#line 1319 "obj/tpc-2025-2026.tab.c"
    break;

  case 15: /* DeclFoncts: DeclFonct  */
#line 130 "src/tpc-2025-2026.y"
       {
           (yyval.node) = makeNode(T_DECL_FONCTS);
           addChild((yyval.node), (yyvsp[0].node));
       }
#line 1328 "obj/tpc-2025-2026.tab.c"
    break;

  case 16: /* DeclFonct: EnTeteFonct Corps  */
#line 138 "src/tpc-2025-2026.y"
       {
           (yyval.node) = makeNode(T_FUNC);
           addChild((yyval.node), (yyvsp[-1].node));
           addChild((yyval.node), (yyvsp[0].node));
       }
#line 1338 "obj/tpc-2025-2026.tab.c"
    break;

  case 17: /* EnTeteFonct: TypeName IDENT '(' Parametres ')'  */
#line 147 "src/tpc-2025-2026.y"
       {
           (yyval.node) = makeNode(T_HEADER);
           addChild((yyval.node), (yyvsp[-4].node)); 
           Node *id = makeNode(T_IDENT); strcpy(id->ident, (yyvsp[-3].ident));
           addChild((yyval.node), id);
           addChild((yyval.node), (yyvsp[-1].node)); 
       }
#line 1350 "obj/tpc-2025-2026.tab.c"
    break;

  case 18: /* EnTeteFonct: VOID IDENT '(' Parametres ')'  */
#line 156 "src/tpc-2025-2026.y"
       {
           (yyval.node) = makeNode(T_HEADER);
           Node *v = makeNode(T_TYPE); strcpy(v->ident, "void");
           addChild((yyval.node), v);
           Node *id = makeNode(T_IDENT); strcpy(id->ident, (yyvsp[-3].ident));
           addChild((yyval.node), id);
           addChild((yyval.node), (yyvsp[-1].node));
       }
#line 1363 "obj/tpc-2025-2026.tab.c"
    break;

  case 19: /* Parametres: VOID  */
#line 167 "src/tpc-2025-2026.y"
            { (yyval.node) = NULL; }
#line 1369 "obj/tpc-2025-2026.tab.c"
    break;

  case 20: /* Parametres: ListTypVar  */
#line 168 "src/tpc-2025-2026.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1375 "obj/tpc-2025-2026.tab.c"
    break;

  case 21: /* Parametres: %empty  */
#line 169 "src/tpc-2025-2026.y"
       { (yyval.node) = NULL; }
#line 1381 "obj/tpc-2025-2026.tab.c"
    break;

  case 22: /* ListTypVar: ListTypVar ',' TypeName IDENT  */
#line 174 "src/tpc-2025-2026.y"
       {
           (yyval.node) = (yyvsp[-3].node);
           Node *p = makeNode(T_PARAM);
           addChild(p, (yyvsp[-1].node));
           Node *id = makeNode(T_IDENT); strcpy(id->ident, (yyvsp[0].ident));
           addChild(p, id);
           addChild((yyval.node), p);
       }
#line 1394 "obj/tpc-2025-2026.tab.c"
    break;

  case 23: /* ListTypVar: TypeName IDENT  */
#line 183 "src/tpc-2025-2026.y"
       {
           (yyval.node) = makeNode(T_LIST);
           Node *p = makeNode(T_PARAM);
           addChild(p, (yyvsp[-1].node));
           Node *id = makeNode(T_IDENT); strcpy(id->ident, (yyvsp[0].ident));
           addChild(p, id);
           addChild((yyval.node), p);
       }
#line 1407 "obj/tpc-2025-2026.tab.c"
    break;

  case 24: /* Corps: '{' ListDeclVars SuiteInstr '}'  */
#line 194 "src/tpc-2025-2026.y"
    {
        (yyval.node) = makeNode(T_BODY);
        addChild((yyval.node), (yyvsp[-2].node)); /* Var locales */
        addChild((yyval.node), (yyvsp[-1].node)); /* Instructions */
    }
#line 1417 "obj/tpc-2025-2026.tab.c"
    break;

  case 25: /* SuiteInstr: SuiteInstr Instr  */
#line 203 "src/tpc-2025-2026.y"
       {
           (yyval.node) = (yyvsp[-1].node);
           if ((yyval.node) == NULL) (yyval.node) = makeNode(T_INSTR_LIST);
           addChild((yyval.node), (yyvsp[0].node));
       }
#line 1427 "obj/tpc-2025-2026.tab.c"
    break;

  case 26: /* SuiteInstr: %empty  */
#line 208 "src/tpc-2025-2026.y"
       { (yyval.node) = NULL; }
#line 1433 "obj/tpc-2025-2026.tab.c"
    break;

  case 27: /* Instr: LValue '=' Exp ';'  */
#line 213 "src/tpc-2025-2026.y"
       {
           (yyval.node) = makeNode(T_ASSIGN);
           addChild((yyval.node), (yyvsp[-3].node));
           addChild((yyval.node), (yyvsp[-1].node));
       }
#line 1443 "obj/tpc-2025-2026.tab.c"
    break;

  case 28: /* Instr: IF '(' Exp ')' Instr  */
#line 219 "src/tpc-2025-2026.y"
       {
           (yyval.node) = makeNode(T_IF);
           addChild((yyval.node), (yyvsp[-2].node));
           addChild((yyval.node), (yyvsp[0].node));
       }
#line 1453 "obj/tpc-2025-2026.tab.c"
    break;

  case 29: /* Instr: IF '(' Exp ')' Instr ELSE Instr  */
#line 225 "src/tpc-2025-2026.y"
       {
           (yyval.node) = makeNode(T_IF);
           addChild((yyval.node), (yyvsp[-4].node));
           addChild((yyval.node), (yyvsp[-2].node));
           addChild((yyval.node), (yyvsp[0].node));
       }
#line 1464 "obj/tpc-2025-2026.tab.c"
    break;

  case 30: /* Instr: WHILE '(' Exp ')' Instr  */
#line 233 "src/tpc-2025-2026.y"
       {
           (yyval.node) = makeNode(T_WHILE);
           addChild((yyval.node), (yyvsp[-2].node));
           addChild((yyval.node), (yyvsp[0].node));
       }
#line 1474 "obj/tpc-2025-2026.tab.c"
    break;

  case 31: /* Instr: IDENT '(' Arguments ')' ';'  */
#line 239 "src/tpc-2025-2026.y"
       {
           (yyval.node) = makeNode(T_FCALL);
           Node *id = makeNode(T_IDENT); strcpy(id->ident, (yyvsp[-4].ident));
           addChild((yyval.node), id);
           addChild((yyval.node), (yyvsp[-2].node));
       }
#line 1485 "obj/tpc-2025-2026.tab.c"
    break;

  case 32: /* Instr: RETURN Exp ';'  */
#line 246 "src/tpc-2025-2026.y"
       {
           (yyval.node) = makeNode(T_RETURN);
           addChild((yyval.node), (yyvsp[-1].node));
       }
#line 1494 "obj/tpc-2025-2026.tab.c"
    break;

  case 33: /* Instr: RETURN ';'  */
#line 250 "src/tpc-2025-2026.y"
                  { (yyval.node) = makeNode(T_RETURN); }
#line 1500 "obj/tpc-2025-2026.tab.c"
    break;

  case 34: /* Instr: '{' SuiteInstr '}'  */
#line 252 "src/tpc-2025-2026.y"
                          { (yyval.node) = (yyvsp[-1].node); }
#line 1506 "obj/tpc-2025-2026.tab.c"
    break;

  case 35: /* Instr: ';'  */
#line 253 "src/tpc-2025-2026.y"
           { (yyval.node) = NULL; }
#line 1512 "obj/tpc-2025-2026.tab.c"
    break;

  case 36: /* LValue: IDENT  */
#line 258 "src/tpc-2025-2026.y"
       { 
           (yyval.node) = makeNode(T_IDENT);
           strcpy((yyval.node)->ident, (yyvsp[0].ident)); 
       }
#line 1521 "obj/tpc-2025-2026.tab.c"
    break;

  case 37: /* LValue: LValue '.' IDENT  */
#line 263 "src/tpc-2025-2026.y"
       {
           (yyval.node) = makeNode(T_MEMBER_ACCESS);
           addChild((yyval.node), (yyvsp[-2].node)); 
           Node *id = makeNode(T_IDENT); strcpy(id->ident, (yyvsp[0].ident));
           addChild((yyval.node), id);
       }
#line 1532 "obj/tpc-2025-2026.tab.c"
    break;

  case 38: /* Exp: Exp OR TB  */
#line 272 "src/tpc-2025-2026.y"
       { (yyval.node) = makeNode(T_OR); addChild((yyval.node), (yyvsp[-2].node));
         addChild((yyval.node), (yyvsp[0].node)); }
#line 1539 "obj/tpc-2025-2026.tab.c"
    break;

  case 39: /* Exp: TB  */
#line 274 "src/tpc-2025-2026.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 1545 "obj/tpc-2025-2026.tab.c"
    break;

  case 40: /* TB: TB AND FB  */
#line 278 "src/tpc-2025-2026.y"
       { (yyval.node) = makeNode(T_AND); addChild((yyval.node), (yyvsp[-2].node));
         addChild((yyval.node), (yyvsp[0].node)); }
#line 1552 "obj/tpc-2025-2026.tab.c"
    break;

  case 41: /* TB: FB  */
#line 280 "src/tpc-2025-2026.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 1558 "obj/tpc-2025-2026.tab.c"
    break;

  case 42: /* FB: FB EQ M  */
#line 284 "src/tpc-2025-2026.y"
       { 
           (yyval.node) = makeNode(T_EQ);
           strcpy((yyval.node)->comp, (yyvsp[-1].comp)); 
           addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); 
       }
#line 1568 "obj/tpc-2025-2026.tab.c"
    break;

  case 43: /* FB: M  */
#line 289 "src/tpc-2025-2026.y"
         { (yyval.node) = (yyvsp[0].node); }
#line 1574 "obj/tpc-2025-2026.tab.c"
    break;

  case 44: /* M: M ORDER E  */
#line 293 "src/tpc-2025-2026.y"
       { 
           (yyval.node) = makeNode(T_ORDER);
           strcpy((yyval.node)->comp, (yyvsp[-1].comp)); 
           addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); 
       }
#line 1584 "obj/tpc-2025-2026.tab.c"
    break;

  case 45: /* M: E  */
#line 298 "src/tpc-2025-2026.y"
         { (yyval.node) = (yyvsp[0].node); }
#line 1590 "obj/tpc-2025-2026.tab.c"
    break;

  case 46: /* E: E ADDSUB T  */
#line 302 "src/tpc-2025-2026.y"
       { 
           (yyval.node) = makeNode(T_ADDSUB);
           (yyval.node)->byte = (yyvsp[-1].byte);
           addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); 
       }
#line 1600 "obj/tpc-2025-2026.tab.c"
    break;

  case 47: /* E: T  */
#line 307 "src/tpc-2025-2026.y"
         { (yyval.node) = (yyvsp[0].node); }
#line 1606 "obj/tpc-2025-2026.tab.c"
    break;

  case 48: /* T: T DIVSTAR F  */
#line 311 "src/tpc-2025-2026.y"
       { 
           (yyval.node) = makeNode(T_DIVSTAR);
           (yyval.node)->byte = (yyvsp[-1].byte); 
           addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); 
       }
#line 1616 "obj/tpc-2025-2026.tab.c"
    break;

  case 49: /* T: F  */
#line 316 "src/tpc-2025-2026.y"
         { (yyval.node) = (yyvsp[0].node); }
#line 1622 "obj/tpc-2025-2026.tab.c"
    break;

  case 50: /* F: ADDSUB F  */
#line 320 "src/tpc-2025-2026.y"
       {
           (yyval.node) = makeNode(T_ADDSUB);
           (yyval.node)->byte = (yyvsp[-1].byte); 
           addChild((yyval.node), (yyvsp[0].node));
       }
#line 1632 "obj/tpc-2025-2026.tab.c"
    break;

  case 51: /* F: '!' F  */
#line 326 "src/tpc-2025-2026.y"
       {
           (yyval.node) = makeNode(T_NOT);
           addChild((yyval.node), (yyvsp[0].node));
       }
#line 1641 "obj/tpc-2025-2026.tab.c"
    break;

  case 52: /* F: '(' Exp ')'  */
#line 330 "src/tpc-2025-2026.y"
                   { (yyval.node) = (yyvsp[-1].node); }
#line 1647 "obj/tpc-2025-2026.tab.c"
    break;

  case 53: /* F: NUM  */
#line 333 "src/tpc-2025-2026.y"
       { 
           (yyval.node) = makeNode(T_NUM);
           (yyval.node)->num = (yyvsp[0].num); 
       }
#line 1656 "obj/tpc-2025-2026.tab.c"
    break;

  case 54: /* F: CHARACTER  */
#line 338 "src/tpc-2025-2026.y"
       {
           (yyval.node) = makeNode(T_CHARACTER);
           (yyval.node)->character = (yyvsp[0].character);
       }
#line 1665 "obj/tpc-2025-2026.tab.c"
    break;

  case 55: /* F: LValue  */
#line 343 "src/tpc-2025-2026.y"
       { (yyval.node) = (yyvsp[0].node); }
#line 1671 "obj/tpc-2025-2026.tab.c"
    break;

  case 56: /* F: IDENT '(' Arguments ')'  */
#line 345 "src/tpc-2025-2026.y"
       {
           (yyval.node) = makeNode(T_FCALL);
           Node *id = makeNode(T_IDENT); strcpy(id->ident, (yyvsp[-3].ident));
           addChild((yyval.node), id);
           addChild((yyval.node), (yyvsp[-1].node));
       }
#line 1682 "obj/tpc-2025-2026.tab.c"
    break;

  case 57: /* Arguments: ListExp  */
#line 354 "src/tpc-2025-2026.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 1688 "obj/tpc-2025-2026.tab.c"
    break;

  case 58: /* Arguments: %empty  */
#line 356 "src/tpc-2025-2026.y"
       { (yyval.node) = NULL; }
#line 1694 "obj/tpc-2025-2026.tab.c"
    break;

  case 59: /* ListExp: ListExp ',' Exp  */
#line 361 "src/tpc-2025-2026.y"
       {
           (yyval.node) = (yyvsp[-2].node);
           if ((yyval.node) == NULL) (yyval.node) = makeNode(T_LIST);
           addChild((yyval.node), (yyvsp[0].node));
       }
#line 1704 "obj/tpc-2025-2026.tab.c"
    break;

  case 60: /* ListExp: Exp  */
#line 368 "src/tpc-2025-2026.y"
       {
           (yyval.node) = makeNode(T_LIST);
           addChild((yyval.node), (yyvsp[0].node));
       }
#line 1713 "obj/tpc-2025-2026.tab.c"
    break;


#line 1717 "obj/tpc-2025-2026.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 374 "src/tpc-2025-2026.y"


void yyerror(const char *s) {
    fprintf(stderr, "Erreur ligne %d : %s\n", lineno, s);
}

int main(int argc, char **argv) {
    int print = 0;
    if (argc > 1 && (strcmp(argv[1], "-t") == 0 || strcmp(argv[1], "--tree") == 0)) print = 1;
    if (argc > 1 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)){
        printf("Utiliser l'analyseur syntaxique : \n\t ./tpcas [options] < fichier.tpc\n\n\tLes options sont : \n\t\t-h / --help : afficher cette aide\n\t\t-t / --tree : afficher l'arbre abstrait généré par Bison\n\n");
        return 0;
    }
    if (yyparse() == 0) {
        /*si ya pas de problèmes !!!!*/
        if (print && root != NULL) {
            printTree(root);
        }
        return 0;
    }
    return 1 + nberror;
}
