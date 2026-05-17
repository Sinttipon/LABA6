cmake_minimum_required(VERSION 3.16)
project(Lab3 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Wconversion)

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-fsanitize=address -fsanitize=undefined -g)
        add_link_options(-fsanitize=address -fsanitize=undefined)
    endif()
elseif(MSVC)
    add_compile_options(/W4 /permissive-)
endif()


set(TEST_SOURCES
    Tests/VectorTest.cpp
    Tests/BitSeqTest.cpp
    Tests/DynamicArrayTest.cpp
    Tests/LinkedListTest.cpp
    Tests/ListSeqTest.cpp
    
)

set(MAIN_SOURCES
    main.cpp
)

set(HEADERS
    Base/Sequence.h
    Base/exceptions.hpp
    Base/concepts.hpp
    Collections/DynamicArray.hpp
    Collections/ArraySequence.h
    Collections/ListSequence.h
    Collections/BitSequence.h
    ADT/Vector.h
    Tests/tests.h
    Tests/BitSeqTest.h
    Tests/DynamicArrayTest.h
    Tests/LinkedListTest.h
    Tests/ListSeqTest.h
)


add_executable(Tests
    ${MAIN_SOURCES} 
    ${TEST_SOURCES} 
    ${HEADERS}
)

target_include_directories(Tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()