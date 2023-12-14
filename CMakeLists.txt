cmake_minimum_required(VERSION 3.24)

project(cucumber-cpp-runner LANGUAGES C CXX VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

set_directory_properties(PROPERTY USE_FOLDERS ON)

include(FetchContent)
include(GNUInstallDirs)
include(CTest)
include(GoogleTest)


include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG        v1.14.0
)

set(gtest_force_shared_crt On CACHE BOOL "" FORCE) # For Windows: Prevent overriding the parent project's compiler/linker settings
set(INSTALL_GTEST Off CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

set_target_properties(gtest gtest_main gmock gmock_main PROPERTIES FOLDER External/GoogleTest)
mark_as_advanced(BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS gmock_build_tests gtest_build_samples test_build_tests gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols)

add_executable(tic-tac-toe.test)
add_test(NAME tic-tac-toe.test COMMAND tic-tac-toe.test)

target_link_libraries(tic-tac-toe.test PRIVATE
    gtest
    gmock
    gmock_main
)

target_sources(tic-tac-toe.test PRIVATE
    test.cpp
)
