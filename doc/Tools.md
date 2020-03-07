# Used Tools {#Tools}

[TOC]

# Overview

Tools help with building, documenting and testing the code, as tools are somewhat individual with respect to setup and
operation, a short how to for each tool is given here.

# CDash {#CDash}

CDash is a dashboard tool developed by KitWare and released as BSD-3 open source tool. Albeit having a little dated
looks, it is still a valuable addition to CMake based build chains.

How to set up a dockerized cdash / ctest environment:

## Get CDash

Clone the [git repository](https://github.com/Kitware/CDash.git) to your local machine and edit the *docker-compose.yml*
file to your needs. Especially change the User and Admin accounts and passwords accordingly.

Example (probably not fit for production):

~~~~~.yml
version: '3.3'
services:
  cdash:
    image: "kitware/cdash"
    build: .
    depends_on:
      - mysql
    links:
      - mysql
    ports:
     - "8080:80"
    environment:
      CDASH_ROOT_ADMIN_PASS: mysecret


      CDASH_CONFIG: |
        $$CDASH_DB_HOST = 'mysql';
        $$CDASH_DB_NAME = 'cdash';
        $$CDASH_DB_TYPE = 'mysql';
        $$CDASH_DB_LOGIN = 'root';
        $$CDASH_DB_PORT = '';
        $$CDASH_DB_PASS = '';
        $$CDASH_DB_CONNECTION_TYPE = 'host';

      CDASH_STATIC_USERS: |
        ADMIN root@domain.de mysecret

        ADMIN axel@domain.de mysecret

        USER group@clt.de clt

  mysql:
    image: "mysql/mysql-server:5.5"
    environment:
      MYSQL_ALLOW_EMPTY_PASSWORD: 'yes'
      MYSQL_ROOT_PASSWORD: ''
      MYSQL_DATABASE: 'cdash'
      MYSQL_ROOT_HOST: '%'
~~~~~

And build / start the cdash environment via `docker-compose up`

This will build the docker environment and starts up an mysql docker and a cdash docker, which is not yet fit for login.
During this initial setup, no users have been created. Fix this using `docker-compose run --rm cdash install configure`.

This will update the mysql *cdash* database accordingly and add all required tables in the correct version. It will also
enter the user accounts as specified in the compose file.


## Set up CMake Project

Taken from [cmake.org](https://cmake.org/cmake/help/v3.3/module/CTest.html)

To main *CMakeLists.txt*, add the CTest module:

~~~~~.cmake
project(MyProject)
...
include(CTest)
~~~~~

The module automatically creates a *BUILD_TESTING* option that selects whether to enable testing support (ON by
default). After including the module, use code like:

~~~~~.cmake
if(BUILD_TESTING)
  # ... CMake code to create tests ...
endif()
~~~~~

To creating tests when testing is enabled.

To enable submissions to a CDash server, create a *CTestConfig.cmake* file at the top of the project with content such
as:

~~~~~.cmake
set(CTEST_PROJECT_NAME "MyProject")
set(CTEST_NIGHTLY_START_TIME "01:00:00 UTC")
set(CTEST_DROP_METHOD "http")
set(CTEST_DROP_SITE "my.cdash.org")
set(CTEST_DROP_LOCATION "/submit.php?project=MyProject")
set(CTEST_DROP_SITE_CDASH TRUE)
~~~~~

## Ship Results

Use cmake (or ccmake) for configuration of your project. This also enables the ctest environment. For further building
testing and submitting, use ctest targets directly, e.g. `ctest -D Experimental`, this will build, test and submit all
results automatically. The steps can be carried out manually as well, refer to the ctest manual.


# CMake {#CMake}

CMake is a cross-platform build system configuration tool developed by KitWare and released under a BSD-3 type open
source license. 

Building project sources into executable code usually is done using a build chain, which configures, builds, tests and
packages the project. These steps can be orchestrated using CMake. This only is the most basic step of a modern CI
chain, the build on a single host / platform. Usually, several individual of such builds with different configurations
need to be carried out, which is *NOT* the scope of CMake - refer to configuration management and continuous integration
tools for this.

## Get CMake

Get it from your OS's package store, most Linux distributions have CMake available, e.g. via `apt install cmake`.

One may get CMake as source distribution as well as [git repository](https://github.com/Kitware/CMake), follow the
projects build instructions. Hint: it may be easier to build a current CMake version using your OS's dated version, see
[building CMake with CMake](https://github.com/Kitware/CMake#building-cmake-with-cmake) on the projects own readme.

**ccmake** For debian-based projects use the *cmake-curses-gui* package, or build cmake manually with more current
version, enable the curses gui via configure.

## Enable CMake

CMake projects contain one (or more) *CMakeLists.txt* files, describing build targets and dependencies. Refer to
this projects *CMakeLists.txt* as a reference. It allows for non-code target, e.g. the Doxygen target used for
generating documentation and is able to automatically build and use external projects as dependencies. This becomes
trivial for git-hosted cmake-configured dependencies, which CMake is able to build and use out-of-the-box, e.g.
see the *googletest* target of this project.

## Use CMake

The easiest way to use CMake in a CMake configured project is by installing a CMake GUI, which is available as
curses based terminal version and as QT based app (the latter is a pro-tip for Windows builds). CMake automatically
performs a configuration run, make sure your compiler can be found. You may help CMake by specifying certain environment
variables, e.g. `CC=/usr/bin/clang` if you intend to use a different-than-standard compiler.

Changes to the current project configuration can be performed by specifying parameters on the command line, e.g. `cmake
<src-dir> -DDOXYGEN=ON`, which would enable an option switch in the config. This can be done graphically using either
the curses or QT GUI as well. Installation paths may be specified like that as well.

CMake encourages out-of-source builds, which also makes live easier with version control systems, as the source folder
stays clean during build an no build artifacts are created therein. For this create a build folder outside of the
project (or ignore a certain folder via *.gitignore* for example). From this folder perform `cmake <src-folder>
<options>` and watch CMake configuring the project. It will inform about problems. If everything works, then `cmake
--build . [--target X]` will build the project. 

# Doxygen {#Doxygen}

Doxygen helps render code and project documentation into different output formats. Usually, the target format is a set
of "static" HTML sites, which are linked and referenced to each other. Doxygen is aware of language features of C-Style
languages, esp. C++.

Doxygen is developed by Dimitry van Heesch and released under the GNU general public license v2.0. However, the works
generated by Doxygen, e.g. the documents created, are not affected by this license.

## Get Doxygen

Get it from your OS's package store, most Linux distributions have doxygen available, e.g. via `apt install doxygen`.
It is recommended to install the graphviz (dot) packages as well, for doxygen to generate inline graphs of class
inheritance and/or manually created architecture overviews.

One may get doxygen as source distribution as well as [git repository](https://github.com/doxygen/doxygen.git), follow
the guides for compilation.

## Doxygen Configuration

Doxygen is controlled by a *Doxyfile*, containing all the project relevant configurations - from project name, input
directories up to color hue and intesity of the resulting documents.

The *Doxyfile* can be created as dummy using the command `doxygen -g`. The resulting file contains all relevant options
as blank fields, each well documented. Just open the file in your favorite editor and perform all relevant changes.
You may refer to the *Doxyfile* of this project to get an idea, see 'doc/Doxyfile.in' for details.

As most of the options are contained in the CMake environment already, it is easy to re-use the values (instead of 
maintaining two sets of the same variables): use CMake variables e.g. `${CMAKE_SOURCE_DIR}` in the *Doxyfile* and
let CMake handle the actual configuration, see next section as well!

## Enable Doxygen as Build Target

To enable Doxygen as a CMake/make target, add the following options to CMake. Note, that the line `configure_file(...)`
will replace all CMake variables in the template *Doxyfile.in* and create the actual *Doxyfile* to be used for the
build. Build the documentation by using `cmake -DDOXYGEN=ON <src_dir> && cmake --build . --target doc`

~~~~~.cmake
option( DOXYGEN            "Build documentation"       ON)
...
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
~~~~~

## Doxygen and GitHub

For GitHub hosted repositories, the documentation (html folder) may be pushed to a dedicated project branch (only
containing the documentation). The branch should be named *gh-pages* and will be published automatically as 
github pages related to the project.

# GoogleTest {#GoogleTest}

GTest and GMock are a c/c++ testing and mocking framework respectively, actively developed and maintained by Google
and released under a BSD-3 clause open source license.

Formerly both project have been developed separately, but have been merged to *googletest* now. GTest can be used
in a header-only manner, while GMock needs some runtime libraries to be linked against the test executables.

## Get GoogleTest

Get it from your OS's package store, most Linux distributions have GoogleTest available, e.g. via `apt install
googletest`. 

One may get GoogleTest as source distribution as well as [git repository](https://github.com/google/googletest),
follow the build instructions of the libraries. Here, GoogleTest is downloaded, build and used during project
generation automatically, using the CMake ExternalProject module. See the main *CMakeLists.txt* file:

~~~~~.cmake
option( COMPILE_TESTS      "Enable tests"              ON)

include(ExternalProject)

...
if (COMPILE_TESTS)
    ... 
    ExternalProject_Add( googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
      INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}
      CMAKE_ARGS 
        -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/gtest 
        -DBUILD_SHARED_LIBS=ON
      )
~~~~~


## Set up CMake Project

For using GoogleTest from a CMake project, test cases / test runner executables need to be defined and backed with
source code. Each of the tests is build into and executable and linked against gtest, gmock and other relevant
libraries (also the projects target libraries if applicable).

When adding the test to ctest via `add_test()`, the tests will be executed and evaluated automatically with a ctest run.
Add a command line option for specifying an test report format, e.g. `--gtest_output="xml:file.xml"`.

~~~~~.cmake
option( COMPILE_TESTS      "Enable tests"              ON)

...
if (COMPILE_TESTS)
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
~~~~~

## Creating Tests with GTest

## Creating Fakes with GMock
