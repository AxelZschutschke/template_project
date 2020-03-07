# CDash {#CDash}

[TOC]

# Overview 

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

