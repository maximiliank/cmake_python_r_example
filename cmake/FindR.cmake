# FindR.cmake
# - Try to find R
#
# The following variables are optionally searched for defaults
#  R_ROOT_DIR:  Base directory where all R components are found
#
# Once done this will define
#  R_FOUND - System has Rcpp
#  R_COMMAND - Path to R executable
#  R_INCLUDE_DIRS - The R include directories
#  R_LIBRARIES - The libraries needed to use R

# find the home path
if (WIN32 AND NOT LIBR_HOME)

	# read home from the registry
	get_filename_component(LIBR_HOME
			"[HKEY_LOCAL_MACHINE\\SOFTWARE\\R-core\\R;InstallPath]"
			ABSOLUTE CACHE)

	# print message if not found
	if (NOT LIBR_HOME)
		message(STATUS "Unable to locate R home (not written to registry)")
	else ()
		message(STATUS "Found LibR home ${LIBR_HOME}")
	endif ()

endif ()
find_program(R_COMMAND R DOC "R executable." HINTS "${LIBR_HOME}/bin/x64")

if (NOT R_COMMAND)
	message(FATAL_ERROR "Unable to locate R executable")
else ()
	message(STATUS "Found R: ${R_COMMAND}")
endif ()

execute_process(
		COMMAND ${R_COMMAND} "--slave" "--no-save" "-e" "cat(Sys.getenv('R_HOME'))"
		OUTPUT_VARIABLE R_HOME
)
message(STATUS "Found R_HOME ${R_HOME}")

IF (MINGW)
	SET(CMAKE_FIND_LIBRARY_PREFIXES "lib" "")
	SET(CMAKE_FIND_LIBRARY_SUFFIXES ".dll" ".dll.a" ".a" ".lib")
ENDIF (MINGW)

find_path(R_INCLUDE_DIR "R.h"
		PATHS ${R_ROOT_DIR} /usr/share/R /usr/include/R "${LIBR_HOME}" "${R_HOME}"
		PATH_SUFFIXES include
		NO_DEFAULT_PATH)

find_library(R_LIBRARY NAMES "R"
		PATHS ${R_ROOT_DIR} /usr/lib64/R /usr/lib/R "${LIBR_HOME}/bin" "${R_HOME}"
		PATH_SUFFIXES lib lib64 x64
		NO_DEFAULT_PATH)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(R REQUIRED_VARS R_INCLUDE_DIR R_LIBRARY)


if (R_FOUND)
	set(R_INCLUDE_DIRS ${R_INCLUDE_DIR})
	set(R_LIBRARIES ${R_LIBRARY})
	mark_as_advanced(R_INCLUDE_DIR R_LIBRARY)
endif ()
