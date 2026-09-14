cmake_minimum_required(VERSION 3.16)
project(pok_lab01_strings LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(mystring mystring.cpp mystring_c.cpp)
target_include_directories(mystring PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

foreach(target mystring)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -pedantic -Werror=vla)
    endif()
endforeach()

add_executable(string_tests tests.cpp)
target_link_libraries(string_tests PRIVATE mystring)
add_executable(c_api_demo c_api_demo.c)
target_link_libraries(c_api_demo PRIVATE mystring)

enable_testing()
add_test(NAME string_tests COMMAND string_tests)
add_test(NAME c_api_demo COMMAND c_api_demo)
