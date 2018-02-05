cmake_minimum_required(VERSION 2.8.11)
set(PROJECT_NAME "clang-tidy")
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

project(${PROJECT_NAME})
list(APPEND CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_program(
  CLANG_TIDY_EXE
  NAMES "clang-tidy"
  DOC "Path to clang-tidy executable"
  )

if(NOT CLANG_TIDY_EXE)
  message(STATUS "clang-tidy not found.")
else()
  message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
  set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-checks=*,-clang-analyzer-alpha.*")
endif()

include(ClangTidy)

set(APPLICATION_NAME jetson-tx2)

set(APPLICATION_SOURCES
  main.cpp)


add_executable(${APPLICATION_NAME} ${APPLICATION_SOURCES})
SetupClangTidy(${APPLICATION_NAME})
