if (NOT ${Python_Interpreter_FOUND})
    message(FATAL_ERROR "No Python interpreter found")
endif ()

set(PYTHON_VIRTUAL_ENV "${CMAKE_CURRENT_BINARY_DIR}/pytest_venv")
if (NOT EXISTS "${PYTHON_VIRTUAL_ENV}")
    message(STATUS "Creating virtual python environment for testing [${PYTHON_VIRTUAL_ENV}]")
    execute_process(COMMAND "${PYTHON_EXECUTABLE}" -m venv "${PYTHON_VIRTUAL_ENV}")
else ()
    message(STATUS "Using virtual python environment for testing [${PYTHON_VIRTUAL_ENV}]")
endif ()

# update the environment with VIRTUAL_ENV variable (mimic the activate script) and search again
set(ENV{VIRTUAL_ENV} "${PYTHON_VIRTUAL_ENV}")
set(Python3_FIND_VIRTUALENV FIRST)
unset(Python3_EXECUTABLE)
find_package(Python3 COMPONENTS Interpreter)

get_target_property(PYPACKAGE_NAME PyPackageBuild Package_Name)

add_custom_target(PyTests ALL
        DEPENDS PyPackageBuild
        COMMAND "${Python3_EXECUTABLE}" -m pip install "${CMAKE_BINARY_DIR}/src/Python/${PYPACKAGE_NAME}"
        COMMENT "Installing python package in virtual test environment"
        )

add_test(NAME run_pytests
        COMMAND "${Python3_EXECUTABLE}" ${CMAKE_CURRENT_SOURCE_DIR}/test_sample.py
        )
