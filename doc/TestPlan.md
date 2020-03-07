# Test Plan {#TestPlan}

\tableofcontents

# Overview 

Document authors: A. Zschutschke

This document is created as template for teaching purposes, please adapt to
your own project needs.

Please refer to the [definitions page](\ref Definitions) for details of
specific key words and phrases.

## Abbreviations

| symbol  | meaning |
| ------- | ------- |
| CI      | continuous integration |
| DEV     | developer (doubles as tester) |
| NFR     | non functional requirement |

## Introduction

The test plan is based on the [test strategy](\ref TestStrategy), which it
translates into concrete test scenarios and time lines. While the test strategy
usually is changing only slightly from release to release (representing the 
learning process of the team and changing requirements and environments during
developement), the test plan usually changes significantly per release, as 
new requirements are implemented or old requirements are signed off.

## Inspection Specifications / Procedure

There are two major reasons for carrying out the software test:
* test if newly introduced functionality is working as expected
* test for absence of regression: old functionality shall not be broken by new features

Automated fast tests and analysis tools generate reports per build, which are thus always
up to date. Tests may be executed on a slower interval as well, e.g. manual tests or 
weekly (long-running) system tests. The test results of these less-frequent tests are
valid only for the exact build they have been carried out with. Especially for manual 
run test cases, an exact documentation which versions and environment have been engaged
is necessary.

### Defect Handling

Minor defects found during software test should be corrected straight away, 
for major or complex-to-solve issues an bug tracking item shall be created. 
The reason for this is twofold:
* make the problem visible to everyone as fast as possible (even if fixing is taking some time)
* enable a discussion on how to solve (or document if fixture is not realistic) the issue

# Test Description
## Unit Test
Unit tests shall be implemented for each individual component. The tests themselves should be classified
as black box test. This implies, that a tester only needs information about the unit interfaces and does
not need to know about the inner structure of the system under test. 
The tester may be the same person as the developer, as unit tests shall proof that the method provides 
the desired functionality and does not show unexpected behavior. For implementing the unit test a set 
of style guides is formulated.

### Style Guide

1) naming of source files for test:
    <unit_name>Test.cpp e.g. JSONParser.cpp
2) creating stubs/mocks/fakes
    <unit_name>Fake.h e.g. JSONParserFake.h
3) test classes / suites are named by their class under test:
    <unit_name>Test<_specific_aspect> e.g. JSONParserTest_Strings
4) a test name is assembled like 
    <scenario>_<expectedBehavior> e.g. whenValidStringEntered_shallConstructJSONStringObject
5) camel cases for testnames start lowerCase
6) camel cases for any class names start UpperCase
7) tests do not contain logic (if, for, while, switch are bad)
8) tests only test agains public methods containing logic, esp. simple setters/getters are not tested!
9) tests shall be consistent (no random, time- or hardware dependend data shall be used for checking)
10) tests shall be independend of each other, e.g. shall not change the state of the test system
11) use the arrange-act-assert pattern and dont mix up asserts with method calls
12) for test code, refer to the code style guide
13) test code shall be commented with care
  
## System Test

(description of individual system tests)

## Explorative Testing

Explorative testing is a special kind of manual testing without a pre-described test proceduce. It has
been found highly advantageous. A tester sets up a test-environment as close to production as possible 
and documents all hardware and software components in the environment. Then the tester starts a timeboxed 
test, mostly 90 minutes, where the tester can perform any operations on the system and records the actions
and observations. If the observation is not equal to the expectation, the test is accounted for as failure.

It makes sense to set up the mood of the tester to either "intruder" or "developer" for the test, so the
tester either tries to prove that the system works as expected or tries to break the system intentionally.

## Code Coverage

The unit tests are run multiple times with different build options. One build is carried out with code
instrumentation for measuring code coverage during unit test. This measure describes how much code has
been executed in total during the unit test. A project should strive for 100 % code (line) coverage and
a high branch coverage (as high as 100 % for security or mission critical code, see 
[ASIL](https://en.wikipedia.org/wiki/Automotive_Safety_Integrity_Level)). Here the following coverage
levels are set as target:

* line coverage: 100 % ( > 95 % is green, > 80 % is yellow and less is red )
* branch coverage: 80 % ( > 75 % is green, > 60 % is yellow and less is red )

The reports are generated using gcc, gcov and lcov for compiling the coverage reports.

Combining unit tests and test coverage metrics blurrs the boundary of black box and white box testing.
This is not a problem in general, as the tester may be informed about whitespots in the test by this
method. Care should be taken, as untrained testers tend to "only increase the coverage" while not 
creating strict tests anymore.

## Static Code Analysis

Static code analysis is used as a first step of code review, not replacing the code review of other
developers and testers. It assists the developer and the reviewer for standard tasks (e.g. are all
class members initialized?) and simple declare / define / use checks.  Static code analysis is classified
as white-box test/

Here, cppcheck is utilized for this. The tool creates an xml report for the source base. Unfortunately,
the tool has some issues with header-only libraries. Thus the result must be handled with care. The code
coverage of the unit test also forces the cppcheck tool to really examine all code of the header only
parts of the library.

Supressions may be introduced with care and shall be reviewed for each release.

## Memory Check

The tool valgrind/memcheck is utilized for a special unit test configuration and execution. It creates
an jailed environment and replaces standard libraries with its own tracing tools. It is a powerfull tool 
for detecting unitialized variables and memory leaks as well as buffer overflows.

Supressions may be introduced with care and shall be reviewed for each release.

## Multi-Thread Check

The tool valgrind/helgrind is utilized for a special unit test configuration and execution. It creates
a jailed environment and replaces standard libraries with its own tracing tools. It is a powerfull tool 
for detecting potential race conditions, dead locks or unprotected thread interactions.

Supressions may be introduced with care and shall be reviewed for each release.

## Code Metrics

The tool CCCC is utilized to generate a report about overall code metrics, e.g. lines of code, cyclomatic
complexity, lines of comment / lines of code etc. These numbers, while beeing less expressive if viewed in 
isolation, might help during refactoring and review. For example could a refactoring reduce the complexity
of the code and increase the number of comments.
The numbers are useful for comparing source files and projects (of the same language and standard) 
against each other.

# System Test / Long-Term Testing

The system test of the project is partially carried out in a manual fashion. This has various reasons:
* high effort of automating the test in different environments
* instability of connections to the testing system (for long term tests, the executor cannot "hold-the-line")
* manual tests are more likely to find new defects (compared to automated/regression tests)

The system test shall cover the following scenarios:

## TSC_0001

(description of test scenarios)


## Test Tools

For system tests, special tester tools are developed and described in the following
(description of testers)

# Appendix

(copy-paste script snippets for testing and evaluation of test results here)
