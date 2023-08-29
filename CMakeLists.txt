cmake_minimum_required(VERSION 3.14 FATAL_ERROR) #FetchContent_MakeAvailable
project(LTF)

# Globbing source files
file(GLOB_RECURSE SOURCES "includes/**/*.cpp")

add_library(LTF ${SOURCES})
target_include_directories(LTF PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
    $<INSTALL_INTERFACE:include>  # <prefix>/include
)


#. . . . . . . . . . . . . . . . . . . .
include(GNUInstallDirs)
if(MSVC)
    add_compile_options(/W4)
    add_link_options(/W4)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()


# place binaries and libraries according to GNU standards
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})



if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()
#. . . . . . . . . . . . . . . . . . . .


## Change ON <-> OFF for testing
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    ## ------------------------------------
    find_package(GTest QUIET)
    if (NOT ${GTest_FOUND}) # GTest not found, FetchContent!
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.13.0)
    FetchContent_MakeAvailable(googletest)
    endif()
        
    # ------------------------------------



    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    #   Grab all cpp files from includes folder
    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    set(INCLUDES_FOLDER includes)
    FILE(GLOB_RECURSE SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} CONFIGURE_DEPENDS "${INCLUDES_FOLDER}/*.cpp")
    #- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

    

    ADD_EXECUTABLE(main
        main.cpp
        ${SOURCE_FILES}
    )

    ADD_EXECUTABLE(test_ltf
        _tests/_test_files/test_ltf.cpp
        ${SOURCE_FILES}
    )


    TARGET_LINK_LIBRARIES(main GTest::gtest_main)
    TARGET_LINK_LIBRARIES(test_ltf GTest::gtest_main)
endif()



# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Install library target
install(TARGETS LTF
    EXPORT LTFTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# This makes project importable from the install directory
# Put config file into the CMake user package registry
install(EXPORT LTFTargets
    FILE LTFTargets.cmake
    NAMESPACE LTF::
    DESTINATION lib/cmake/LTF
)

# This makes project importable from the build directory
export(TARGETS LTF
    NAMESPACE LTF::
    FILE ${CMAKE_CURRENT_BINARY_DIR}/LTF.cmake
)