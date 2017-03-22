AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

pkgconfigdir = $(datadir)/pkgconfig
pkgconfig_DATA = @PACKAGE_NAME@-@PACKAGE_VERSION@.pc

SUBDIRS = src

if RUN_UNITTEST
SUBDIRS += test
endif

dist_noinst_SCRIPTS = autogen.sh

if HAVE_DOXYGEN
doxyfile.stamp: doxygen
	echo Timestamp > doxyfile.stamp
CLEANFILES = doxyfile.stamp
#all-local: doxyfile.stamp
endif

distclean-local:
	rm -rf sublime_project-includes.generated
	rm -rf sublime_project-paths.generated
