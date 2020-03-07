# Code Style Guide {#StyleGuide}

[TOC]

# Overview

Describes the general rules for styling and outlining code in this project. Describes the naming conventions for
variables, classes, namespaces etc. 

See the \ref TestPlan as well for special rules applying to the tests.

## Tooling

To enforce a common appearance of the codebase, the tool clang-format is utilized, which describes indentation
and define patterns in classes. Unfortunately, it cannot protect from mis-styled variable names etc.

# Rules

## Files

Files are named according to their contents either `*.h` for header files, `*.cpp` for implementation etc. Filenames are
started with a capital letter and continued camel case. Interfaces get an capital `I` as prefix, e.g. `IParser.h` 

## Namespaces

Namespaces are used for each sub-module individually and may be nested. A special namespace is Test, encapsulating
all test related definitions and test cases.

Namespace names are started with lower case letter and continued in camel case like: `myLongNamespace`

Namespaces should be documented briefly, to do this only once, please create (if not existing) a header file with
the same name (e.g. Namespace.h), declaring and document the namespace in there.

~~~~~.cpp
namespace {
}
~~~~~

## Classes

Like namespaces, start with capital letter and continue camel case. 

If classes serve as *pure virtual* interface, they get prefixed by an capital `I`, e.g. `class IParser`, while the
implementation does not receive an prefix, e.g. `class Parser : public IParser`

Define only one class per file and use the class name as the filename, e.g. the `class Parser` would be defined in the
file `Parser.h`. Classes should be nested in namespaces. Test files and test classes affilitated to the original are
named accordingly with a \*Test or \*Fake or \*Stub attached, e.g. the file `ParserTest.cpp` could contain the `class
 ParserTest` and the respective test methods.

~~~~~.cpp
namespace {
  class ClassName {
  };
}
~~~~~

## Methods

Free functions and class member methods get an expressive name, which does not need to be short. A maximum of 3
parameters is used (while not strictly prohibiting more parameters in special cases) and output parameters are avoided.

Ideally, a method does not create "side effects" and does only modify the system by its return values (as teached by
functional programming). Methods shall only do one thing (contain a single logic), that does not imply that they are 
prohibited to combine other methods, as the logic may be exactly this combination (but then this is the only thing they
should be doing). The ideal length of a method is approx. 5 lines.

Method names start with a lower case letter and continue with camel case (if the language does not dictate otherwise,
e.g. for constructors) . Underscores and other special characters shall not be used (if not mandatory, e.g. destructors
or operators). An exception for this rule are test names, which contain an underscore character to seperate the scenario
and expectation part.

~~~~~.cpp
namespace {
  class ClassName {
    ClassName() 
    {}
    ~ClassName() 
    {}

    int method( int const & input ) const 
    {}
  };

  int freeFunction( std::string const & input ) 
  {}
}
~~~~~

## Statements

Only one statement in terms of programming logic shall be used per line, such that line coverage = statement coverage.
