###############################################################################
# COMMONCLI CONFIGURATION
###############################################################################
AC_INIT([commoncli],
    m4_esyscmd_s([./version.sh]),
    [fabian@cpqd.com.br , gcuriel@cpqd.com.br],
    [commoncli],
    [https://gerrit.cpqd.com.br/#/admin/projects/vppd/shared/libcommoncli])

AC_CONFIG_HEADERS([config.h])
AC_PREREQ([2.59])
AM_INIT_AUTOMAKE([1.10 -Wall no-define foreign])

###############################################################################
# PACKAGE METADATA
###############################################################################

dnl Following parameters are used to register this component for future re-use
dnl JIRA if no component for this package has been created just provide the ID
dnl otherwise ID/component/XXXXXX for direct linkage.

PACKAGE_GROUP_ID="br.com.cpqd.shared"
PACKAGE_KEYWORDS="cli library"
PACKAGE_TYPE="library"
PACKAGE_LANGUAGES="C++"
PACKAGE_SUPPORTED_PLATFORMS="x86_64, m68k-linux-gnu, i586-padtec-linux-spvl91"
PACKAGE_PROJ_INIT="XCP"
PACKAGE_PROJ_USING="XCP"
PACKAGE_NEXUS_REPOSITORY="vppd"
PACKAGE_JIRA_ID="28975"
PACKAGE_DESCRIPTION="CLI Based on Quagga/Zebra"
PACKAGE_DESCRIPTION_LONG="CLI Based on Quagga/Zebra - Quagga is free software that manages various IPv4 and IPv6 routing protocols."

AC_SUBST([PACKAGE_GROUP_ID],[$PACKAGE_GROUP_ID])
AC_SUBST([PACKAGE_KEYWORDS],[$PACKAGE_KEYWORDS])
AC_SUBST([PACKAGE_TYPE],[$PACKAGE_TYPE])
AC_SUBST([PACKAGE_LANGUAGES],[$PACKAGE_LANGUAGES])
AC_SUBST([PACKAGE_SUPPORTED_PLATFORMS],[$PACKAGE_SUPPORTED_PLATFORMS])
AC_SUBST([PACKAGE_PROJ_INIT],[$PACKAGE_PROJ_INIT])
AC_SUBST([PACKAGE_PROJ_USING],[$PACKAGE_PROJ_USING])
AC_SUBST([PACKAGE_NEXUS_REPOSITORY],[$PACKAGE_NEXUS_REPOSITORY])
AC_SUBST([PACKAGE_JIRA_ID],[$PACKAGE_JIRA_ID])
AC_SUBST([PACKAGE_DESCRIPTION], [${PACKAGE_DESCRIPTION}])
AC_SUBST([PACKAGE_DESCRIPTION_LONG], [${PACKAGE_DESCRIPTION_LONG}])

###############################################################################
# CHECK AND APPEND FLAGS FROM REQUIRED PACKAGES
###############################################################################
PACKAGE_REQUIRES=`./req.sh`
AC_SUBST([PACKAGE_REQUIRES],[$PACKAGE_REQUIRES])

#Check if $PACKAGE_REQUIRES is not empty
if test -z "$PACKAGE_REQUIRES";
then
    AC_MSG_WARN([Can't read package REQUIRES])
else
    PKG_CHECK_MODULES([PKGREQ], [${PACKAGE_REQUIRES}])
fi

#Append flags
CFLAGS+=" $PKGREQ_CXXFLAGS $PKGREQ_CFLAGS "
CXXFLAGS+=" $CFLAGS "
LIBS+=" $PKGREQ_LIBS "

#******************************************************************************
#                               MODEL PACKAGES MUST ENABLE THIS PART
#******************************************************************************

###############################################################################
# CHECK FOR PYANG (Model packages)
###############################################################################
# AC_CHECK_PROGS([PYANG], [pyang])

###############################################################################
# CHECK FOR XSLTPROC (Model Packages)
###############################################################################
# AC_CHECK_PROGS([XSLTPROC], [xsltproc])

###############################################################################
# CHECK FOR DAOGENERATOR
###############################################################################
# DAOGEN_PCK=`./req.sh generator`
# BIN_DIR="$(pkg-config --variable=prefix $DAOGEN_PCK)/bin"

# AC_SUBST([BIN_DIR],[$BIN_DIR])
# AC_SUBST([GEN_DIR],[$BIN_DIR])

###############################################################################
# CHECK AND CONFIGURE DOXYGEN
###############################################################################
AC_CHECK_PROGS([DOXYGEN], [doxygen])
if test -z "$DOXYGEN";
then
    AC_MSG_WARN([doxygen not found - sudo apt-get install doxygen - might resolve this])
fi
AM_CONDITIONAL([HAVE_DOXYGEN], [test -n "$DOXYGEN"])

###############################################################################
# CHECK FOR M68K COMPILATION
###############################################################################
AC_CHECK_DECL([__m68k__],
    [AC_DEFINE([M68K_OPT], 1, [Define to 1 to activate m68k optimizations])
        echo Engaging m68k optimizations
         AM_CONDITIONAL([M68K], [true])
         CFLAGS+=" -mcfv4e -gdwarf-2 "
         CXXFLAGS+=" -mcfv4e -gdwarf-2 "],
    [AM_CONDITIONAL([M68K], [false])] )


#******************************************************************************
#                                           DEFAULT OPTIONAL FLAGS
#******************************************************************************

###############################################################################
# CHECK UNITTESTS SETTINGS
###############################################################################
AC_ARG_WITH([unittest], AS_HELP_STRING([--with-unittest], [Build with unittesting]))
if test "x$with_unittest" = "xyes";
then
    TESTINFRA=`./req.sh pkgt`
    PKG_CHECK_MODULES([GTEST], [${TESTINFRA}])
    unittest="true"
fi
AM_CONDITIONAL([RUN_UNITTEST], [ test "x$unittest" = "xtrue" ])

###############################################################################
# DEBUG - compilation with debugging symbols and without optimization
###############################################################################
AC_ARG_WITH([debug], AS_HELP_STRING([--with-debug], [Build with debugging symbols and without optimization]))
if test "x$with_debug" = "xyes";
then
    CFLAGS+=" -g3 -O0 "
    CXXFLAGS+=" -g3 -O0 "
fi
AM_CONDITIONAL([BUILD_WITH_DEBUG], [ test "x$with_debug" = "xyes" ])

###############################################################################
# DEBUG - compilation with debugging symbols
###############################################################################
AC_ARG_WITH([debug-symbols], AS_HELP_STRING([--with-debug-symbols], [Build with debugging symbols]))
if test "x$with_debug_symbols" = "xyes";
then
    CFLAGS+=" -g3 "
    CXXFLAGS+=" -g3 "
fi
AM_CONDITIONAL([BUILD_WITH_DEBUG_SYMBOLS], [ test "x$with_debug_symbols" = "xyes" ])

###############################################################################
# EFENCE - compilation with efence
###############################################################################
AC_ARG_WITH([efence], AS_HELP_STRING([--with-efence], [Build with efence support]))
if test "x$with_efence" = "xyes";
then
    CFLAGS+=" -Wall -lefence "
    CXXFLAGS+=" -Wall -lefence "
fi
AM_CONDITIONAL([BUILD_WITH_EFENCE], [ test "x$with_efence" = "xyes" ])

###############################################################################
# EMBEDDED SYSTEM - compilation with "-Os"
###############################################################################
AC_ARG_WITH([embedded], AS_HELP_STRING([--with-embedded],
    [Build for embedded-systems]))
if test "x$with_embedded" = "xyes";
then
    CFLAGS+=" -Os "
    CXXFLAGS+=" -Os "
fi
AM_CONDITIONAL([BUILD_WITH_EMBEDDED], [ test "x$with_embedded" = "xyes" ])

###############################################################################
# EXTRA WARNING's MESSAGES - compilation with "-W*" flags (except Werror)
###############################################################################
AC_ARG_WITH([wall], AS_HELP_STRING([--with-wall], [Build showing all warnings]))
if test "x$with_wall" = "xyes";
then
    WALLFLAGS=" -W -Wall -Wextra -Wmissing-include-dirs -Wreturn-type "
    WALLFLAGS+=" -Wsuggest-attribute=pure -Wsuggest-attribute=const "
    WALLFLAGS+=" -Wsuggest-attribute=noreturn -Wfloat-equal -Wshadow "
    WALLFLAGS+=" -Wwrite-strings -Wuseless-cast "

    CFLAGS+=" $WALLFLAGS "
    CXXFLAGS+=" $WALLFLAGS "
fi
AM_CONDITIONAL([BUILD_WITH_WALL], [ test "x$with_wall" = "xyes" ])

###############################################################################
# WARNING AS ERRORS - compilation with "-Werror" flag
###############################################################################
AC_ARG_WITH([werror], AS_HELP_STRING([--with-werror],
    [Build showing all warnings as error]))
if test "x$with_werror" = "xyes";
then
    CFLAGS+="  -Werror "
    CXXFLAGS+="  -Werror "
fi
AM_CONDITIONAL([BUILD_WITH_WERROR], [ test "x$with_werror" = "xyes" ])

###############################################################################
# SETUP COVERAGE - compilation with coverage
###############################################################################
AC_ARG_WITH([coverage], AS_HELP_STRING([--with-coverage],
    [Build with code-coverage support]))
if test "x$with_coverage" = "xyes";
then
    CXXFLAGS+=" -fprofile-arcs -ftest-coverage -lgcov "
fi
AM_CONDITIONAL([BUILD_WITH_COVERAGE], [ test "x$with_coverage" = "xyes" ])

###############################################################################
# PROFILING - compilation with profiling
###############################################################################
AC_ARG_WITH([profiling], AS_HELP_STRING([--with-profiling],
    [Build with profiling support]))
if test "x$with_profiling" = "xyes";
then
    CXXFLAGS+=" -pg "
    CFLAGS+=" -pg "
fi
AM_CONDITIONAL([BUILD_WITH_PROFILING], [ test "x$with_profiling" = "xyes" ])

###############################################################################
# STACK PROTECTION - stack protection
###############################################################################
AC_ARG_WITH([stack-protection], AS_HELP_STRING([--with-stack-protection],
      [Build with stack protection]))
if test "x$with_stack_protection" = "xyes";
then
    CXXFLAGS+=" -fstack-protector-all "
    CFLAGS+=" -fstack-protector-all "
fi
AM_CONDITIONAL([BUILD_WITH_STACK_PROTECTION], [ test "x$with_stack_protection" = "xyes" ])

###############################################################################
# LOGS - enable logs macros
###############################################################################
AC_ARG_WITH([logs], AS_HELP_STRING([--with-logs], [Build with logs macros defined]))
if test "x$with_logs" = "xyes";
then
    CFLAGS+=" -DLOW_LEVEL_LOG "
    CXXFLAGS+=" -DLOW_LEVEL_LOG "
fi
AM_CONDITIONAL([BUILD_WITH_DEBUG], [ test "x$with_logs" = "xyes" ])

###############################################################################
# SANITY CHECK
###############################################################################

# If flag --with-embedded is enable, --with-debug and --with-stack-protection must be off
# Colision with "-OX" flag
if test "x$with_embedded" = "xyes";
then
    if test "x$with_debug" = "xyes";
    then
        AC_MSG_ERROR([Can't use flag '--with-embedded' along with '--with-debug',
        both alter the same flag ('-OX') !. Try to use '--with-debug-symbols'
        and '--with-embedded' instead.])
    fi
fi

#******************************************************************************
#                                                PACKAGE CUSTOMIZATION
#******************************************************************************

dnl ------------------QUAGGA ------------------------------
dnl IPv6 header checks
dnl -------------------------------------------------------

AC_CHECK_HEADERS([netinet6/in6.h netinet/in6_var.h netinet/icmp6.h \
  netinet6/in6_var.h netinet6/nd6.h], [], [],
  QUAGGA_INCLUDES)

  m4_define([QUAGGA_INCLUDES],
    QUAGGA_INCLUDES
    [#if HAVE_NETINET6_IN6_H
    #include <netinet6/in6.h>
    #endif
    #if HAVE_NETINET_IN6_VAR_H
    #include <netinet/in6_var.h>
    #endif
    #if HAVE_NETINET_ICMP6_H
    # include <netinet/icmp6.h>
    #endif
    #if HAVE_NETINET6_IN6_VAR_H
    # include <netinet6/in6_var.h>
    #endif
    #if HAVE_NETINET6_ND6_H
    # include <netinet6/nd6.h>
    #endif
    ])

    dnl ------------------QUAGGA ----------------------------

AC_CONFIG_FILES([src/version.h:version.h.in])
AC_CONFIG_FILES([Makefile ${PACKAGE_NAME}-${PACKAGE_VERSION}.pc:pkg.pc.in])
AC_CONFIG_FILES([src/Makefile])
AC_CONFIG_FILES([test/Makefile])

#******************************************************************************
#                                                THE LAST PART
#******************************************************************************

# Compilers
AC_PROG_CC
AC_PROG_CXX

# Enable static libraries
LT_INIT([static])

# Generate config.status and launch it. Call this macro once, at the end of configure.ac
AC_OUTPUT
