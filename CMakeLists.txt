cmake_minimum_required(VERSION 3.20)

project(steel_compiler
    VERSION 0.1.0
    LANGUAGES CXX
)

# --------------------------------------------------
# C++ Standard
# --------------------------------------------------

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --------------------------------------------------
# LLVM
# --------------------------------------------------

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "LLVM include dirs: ${LLVM_INCLUDE_DIRS}")

# --------------------------------------------------
# Sources
# --------------------------------------------------

file(GLOB_RECURSE STEEL_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# --------------------------------------------------
# Executable
# --------------------------------------------------

add_executable(steel_compiler
    ${STEEL_SOURCES}
)

# --------------------------------------------------
# LLVM Includes
# --------------------------------------------------

target_include_directories(steel_compiler PRIVATE
    ${LLVM_INCLUDE_DIRS}
)

# --------------------------------------------------
# LLVM Definitions
# --------------------------------------------------

target_compile_definitions(steel_compiler PRIVATE
    ${LLVM_DEFINITIONS}
)

# --------------------------------------------------
# LLVM Libraries
# --------------------------------------------------

target_link_libraries(steel_compiler PRIVATE
    ${LLVM_LIBS}
)
