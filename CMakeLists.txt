cmake_minimum_required(VERSION 3.15)
project(cmake_python_r_example)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -Wold-style-cast -pedantic -Werror)
endif()

option(BUILD_RPACKAGE "Build RPackage bindings" ON)
option(BUILD_PYPACKAGE "Build Python package bindings" ON)

# version handling
set(CppLIB_VERSION "0.0.1")
add_subdirectory(src/CppLib)

define_property(TARGET PROPERTY Package_Name
        BRIEF_DOCS "The name of R/Python package to be installed"
        FULL_DOCS "The name of R/Python package to be installed"
        )

enable_testing()
if (BUILD_RPACKAGE)
    if(WIN32 AND NOT MINGW)
        message(WARNING "R packages on Windows are only supported using MINGW as a compiler. "
                "Disabling building R package.")
    else()
        add_subdirectory(src/RPackage)
        add_subdirectory(tests/R)
    endif()
endif ()

if (BUILD_PYPACKAGE)
    add_subdirectory(src/Python)
    add_subdirectory(tests/Python)
endif ()
