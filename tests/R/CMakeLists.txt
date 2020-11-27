set(R_TEST_LIBS_DIR "${CMAKE_CURRENT_BINARY_DIR}/Rlibs")
if (NOT EXISTS "${R_TEST_LIBS_DIR}")
    file(MAKE_DIRECTORY "${R_TEST_LIBS_DIR}")
endif ()

get_target_property(RPACKAGE_NAME RPackageBuild Package_Name)

# as we install the package in the ${R_TEST_LIBS_DIR} by setting R_LIBS_USER environment, we have to make sure
# to add the original R_LIBS_USER to the end of .libPaths() if testthat package is installed in the current user
# library directory
execute_process(COMMAND "${R_COMMAND}" --silent --slave -e "cat(Sys.getenv('R_LIBS_USER'))" OUTPUT_VARIABLE R_LIBS_USER
        OUTPUT_STRIP_TRAILING_WHITESPACE)
if (WIN32)
    STRING(REGEX REPLACE "\\\\" "/" R_LIBS_USER ${R_LIBS_USER} )
endif()

add_custom_target(RTests ALL
        DEPENDS RPackageBuild
        COMMAND ${CMAKE_COMMAND} -E env "R_LIBS_USER=${R_TEST_LIBS_DIR}"
        "${R_COMMAND}" CMD INSTALL ${RPACKAGE_NAME}
        COMMENT "Installing Rpackage"
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/src/RPackage"
        )
add_test(NAME run_rtests
        COMMAND "${R_COMMAND}" --silent --slave -e ".libPaths(c(.libPaths(), '${R_LIBS_USER}'));.libPaths();library(testthat); testthat::test_dir('.', stop_on_failure=TRUE);"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        )

set_tests_properties(
        run_rtests
        PROPERTIES
        ENVIRONMENT "R_LIBS_USER=${R_TEST_LIBS_DIR}"
)
