cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
project(template-project VERSION 1.0.0 LANGUAGES CXX)

option( COMPILE_TESTS      "Enable tests"              ON)
option( COMPILE_EXAMPLES   "Enable examples"           ON)
option( CODE_COVERAGE      "Enable coverage reporting" OFF)
option( DOXYGEN            "Build documentation"       ON)
option( CPPCHECK           "Enable cppcheck"           OFF)
option( CCCC               "Enable cccc"               OFF)

include(CTest)
include(GNUInstallDirs)
include(ExternalProject)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

if (COMPILE_TESTS)
    enable_testing()
    if (CODE_COVERAGE)
      target_compile_options(coverage_config INTERFACE -O0 -g --coverage)
      target_link_libraries(coverage_config INTERFACE --coverage)
    endif ()
    
    ExternalProject_Add( googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
      INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
      CMAKE_ARGS 
        -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/gtest 
        -DBUILD_SHARED_LIBS=ON
      )

    file( GLOB GTEST_FILES test/unit/*)
    foreach( FILENAME ${GTEST_FILES} )
      get_filename_component( TESTNAME ${FILENAME} NAME_WE )
      link_directories( ${CMAKE_CURRENT_BINARY_DIR}/gtest/lib )
      add_executable(  ${TESTNAME} ${FILENAME} )
      add_dependencies( ${TESTNAME} googletest )
      target_include_directories( ${TESTNAME} 
        PRIVATE 
          ${CMAKE_CURRENT_BINARY_DIR}/gtest/include 
        )
      target_link_libraries( ${TESTNAME} 
        gtest 
        gmock )
      add_test( NAME ${TESTNAME} 
        COMMAND ${TESTNAME} --gtest_output="xml:${TESTPATH}_gtest.xml")
    endforeach()
endif ()

if (COMPILE_EXAMPLES)
    find_package(Threads)
    add_executable(template-example )
    target_link_libraries(template-example Threads::Threads)
    target_include_directories(template-example PRIVATE vendor examples)
endif ()

if( CPPCHECK )
  find_program( CPPCHECK_EXECUTABLE NAMES cppcheck )

  if( CPPCHECK_EXECUTABLE )
    file(GLOB CPPCHECK_IN 
      ${CMAKE_CURRENT_SOURCE_DIR}/include/* 
      ${CMAKE_CURRENT_SOURCE_DIR}/src/* 
      ${CMAKE_CURRENT_SOURCE_DIR}/test/unit/* 
      ${CMAKE_CURRENT_SOURCE_DIR}/test/api/* 
    )
    set(CPPCHECK_INCLUDE_DIRS 
      -I${CMAKE_CURRENT_SOURCE_DIR}
      -I${CMAKE_CURRENT_SOURCE_DIR}/include 
      -I${CMAKE_CURRENT_SOURCE_DIR}/vendor 
      -I${CMAKE_CURRENT_SOURCE_DIR}/test/api/*
    )

    set(CPPCHECK_OPTIONS 
      --xml 
      --language=c++ 
      --std=c++14 
      --enable=all 
      --inconclusive )
    set(CPPCHECK_OUT 
      --output-file=${CMAKE_CURRENT_BINARY_DIR}/cppcheck.xml )

    add_custom_target( cppcheck ALL
      COMMAND ${CPPCHECK_EXECUTABLE} 
        ${CPPCHECK_OUT} 
        ${CPPCHECK_OPTIONS} 
        ${CPPCHECK_INCLUDE_DIRS} 
        ${CPPCHECK_IN}
      COMMENT "Running cppcheck"
      VERBATIM )
  else()
    message( "cppcheck need to be installed to generate the cppcheck report" )
  endif()
endif()

if( CCCC )
  find_program( CCCC_EXECUTABLE NAMES cccc )
  if( CCCC_EXECUTABLE )
    file(GLOB CCCC_IN 
      ${CMAKE_CURRENT_SOURCE_DIR} )
    set(CCCC_INCLUDE_DIRS 
      -I${CMAKE_CURRENT_SOURCE_DIR} 
      -I${CMAKE_CURRENT_SOURCE_DIR}/test/api
      -I${CMAKE_CURRENT_SOURCE_DIR}/include 
      -I${CMAKE_CURRENT_SOURCE_DIR}/vendor 
      -I${CMAKE_CURRENT_SOURCE_DIR}/examples )
    set(CCCC_OPTIONS  
      --lang=c++ )
    set(CCCC_OUT 
      --outdir=${CMAKE_CURRENT_BINARY_DIR}/cccc 
      --html_outfile=${CMAKE_CURRENT_BINARY_DIR}/cccc/cccc.html )
    add_custom_target( cccc ALL
      COMMAND ${CCCC_EXECUTABLE} ${CCCC_OUT} ${CCCC_OPTIONS} ${CCCC_INCLUDE_DIRS} ${CCCC_IN}
      COMMENT "Running cccc"
      VERBATIM )
  else()
    message( "cccc need to be installed to generate the cccc report" )
  endif()
endif()

if ( DOXYGEN )
  # check if Doxygen is installed
  find_package(Doxygen)
  if (DOXYGEN_FOUND)
    # set input and output files
    set( DOXYGEN_IN 
      ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
    set( DOXYGEN_OUT 
      ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT})

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc ALL
      COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Generating API documentation with Doxygen"
      VERBATIM )
  else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
  endif (DOXYGEN_FOUND)
endif( DOXYGEN )
