# Declaration et nommage du projet
project(parser)

# Minimum version of CMake to build this project
cmake_minimum_required(VERSION 2.6)

# Includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Packages
find_package(BISON)
find_package(FLEX)

# Variables
set(CXX "clang++-13")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -W -Werror -pedantic -g")
set(CMAKE_CXX_FLAGS "-O3 -Wall -W -pedantic")

# LLVM
find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER clang-13)
set(CMAKE_CXX_COMPILER clang++-13)
link_libraries()
execute_process(COMMAND llvm-config-13 --libs OUTPUT_VARIABLE LIBS)
execute_process(COMMAND llvm-config-13 --system-libs OUTPUT_VARIABLE SYS_LIBS)
execute_process(COMMAND llvm-config-13 --ldflags OUTPUT_VARIABLE LDF)
#message(STATUS "Found LLVM" ${LIBS})
string(STRIP ${LIBS} LIBS)
string(STRIP ${SYS_LIBS} SYS_LIBS)
string(STRIP ${LDF} LDF)

link_libraries(${LIBS} ${SYS_LIBS} ${LDF})

execute_process(COMMAND llvm-config-13 --cxxflags OUTPUT_VARIABLE CMAKE_CXX_FLAGS)
string(STRIP ${CMAKE_CXX_FLAGS} CMAKE_CXX_FLAGS)

llvm_map_components_to_libnames(llvm_libs support core irreader)

# Files
file(GLOB HH_FILES *.hh)
file(GLOB SRC_FILES *.cc)

# BISON and FLEX
bison_target(Parser parser.yy ${CMAKE_CURRENT_BINARY_DIR}/parser.cc)
flex_target(Scanner scanner.ll ${CMAKE_CURRENT_BINARY_DIR}/scanner.cc)
add_flex_bison_dependency(Scanner Parser)

# Output directoru
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Add the binary and sources
add_executable(
  sc
  ${HH_FILES}
  ${SRC_FILES}
  ${FLEX_Scanner_OUTPUTS}
  ${BISON_Parser_OUTPUTS}
)
