cmake_minimum_required(VERSION 3.20)

project(my_language
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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

file(GLOB_RECURSE SOURCES
    CONFIGURE_DEPENDS
    src/*.cpp
)

# --------------------------------------------------
# Executable
# --------------------------------------------------

add_executable(my_language
    ${SOURCES}
)

# --------------------------------------------------
# Includes
# --------------------------------------------------

target_include_directories(my_language PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${LLVM_INCLUDE_DIRS}
)

# --------------------------------------------------
# LLVM definitions
# --------------------------------------------------

target_compile_definitions(my_language PRIVATE
    ${LLVM_DEFINITIONS}
)

# --------------------------------------------------
# LLVM libraries
# --------------------------------------------------

llvm_map_components_to_libnames(LLVM_LIBS
    core
    support
    irreader
)

target_link_libraries(my_language PRIVATE
    ${LLVM_LIBS}
)
