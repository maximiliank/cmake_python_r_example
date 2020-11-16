set(TARGET_NAME CppLib)

file(GLOB_RECURSE headers include/CppLib/*.h include/CppLib/*.hpp)
file(GLOB_RECURSE sources src/*.cpp src/*.h src/*.hpp)

add_library(${TARGET_NAME} ${sources} ${headers})

target_include_directories(${TARGET_NAME} PRIVATE include/)
target_include_directories(${TARGET_NAME} SYSTEM INTERFACE include/)
