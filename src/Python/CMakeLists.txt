set(TARGET_NAME PyCppLib)

find_package(pybind11 REQUIRED)

file(GLOB_RECURSE sources src/*.cpp src/*.h src/*.hpp)
file(GLOB_RECURSE pyfiles py/*.py)

add_library(${TARGET_NAME} MODULE ${sources})

target_link_libraries(${TARGET_NAME} PRIVATE pybind11::module CppLib)

set_target_properties(${TARGET_NAME} PROPERTIES
        PREFIX "${PYTHON_MODULE_PREFIX}"
        SUFFIX "${PYTHON_MODULE_EXTENSION}"
        BUILD_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}/libs"
        BUILD_WITH_INSTALL_RPATH TRUE)
set(TARGET_PYMODULE_NAME "${PYTHON_MODULE_PREFIX}${TARGET_NAME}${PYTHON_MODULE_EXTENSION}")

CONFIGURE_FILE(py/__init__.py.in
        ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}/__init__.py @ONLY
        )
CONFIGURE_FILE(setup.py.in
        ${CMAKE_CURRENT_BINARY_DIR}/setup.py @ONLY
        )
CONFIGURE_FILE(getwheelname.py.in
        ${CMAKE_CURRENT_BINARY_DIR}/getwheelname.py @ONLY
        )

foreach (filename ${pyfiles})
    get_filename_component(target "${filename}" NAME)
    message(STATUS "Copying ${filename} to ${TARGET_NAME}/${target}")
    configure_file("${filename}" "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}/${target}" COPYONLY)
endforeach (filename)

execute_process(COMMAND "${PYTHON_EXECUTABLE}" getwheelname.py OUTPUT_VARIABLE PY_WHEELFILE
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "Detected Python wheel filename ${PY_WHEELFILE}")

add_custom_target(PyPackageBuild
        COMMAND "${PYTHON_EXECUTABLE}" -m pip wheel .
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        COMMENT "Building python wheel package"
        )
add_dependencies(PyPackageBuild ${TARGET_NAME})

set_target_properties(PyPackageBuild PROPERTIES Package_Name ${PY_WHEELFILE})
add_custom_target(PyPackageInstall
        COMMAND "${PYTHON_EXECUTABLE}" -m pip install --upgrade --force-reinstall --no-deps "${PY_WHEELFILE}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        COMMENT "Installing wheel file"
        )
add_dependencies(PyPackageInstall PyPackageBuild)
