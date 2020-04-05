# Test Strategy {#TestStrategy}

[TOC]

# Overview 

Document authors: A. Zschutschke

This document is created as template for teaching purposes, please adapt to
your own project needs. Usually, your organisation should supply a Test Strategy 
document, which acts as basis for the project's \ref TestPlan as well and is based
on the organisation's \ref TestPolicy document.

Please refer to the [definitions page](\ref Definitions) for details of
specific key words and phrases and explanation for abbreviations.

## Introduction

The test documentation gives an overview of test targets, test scope and
defines and explains the internal notations. Also, an overview of the test
environment and the test approach is presented. 

During a release cycle all test related documents are updated according to
their natural dependency. The [test strategy](\ref TestStrategy) is the most
stable document (time-wise), as it describes general definitions and the long
term test approach (strategy) of the organisation. In terms of 
[ISO 29119-2](\ref TestStrategyRef), it reassembles the OT1 (test specification of the
organisation) on project level and may as well be an exact copy of the test strategy of
the organisation if applicable.

The [test plan](\ref TestPlan) will be adapted to new
features and found defects, for the next release while the 
[test report](\ref TestReport) is virtually subject to change with each new
build.

@dot
digraph Timeline
{
	splines=ortho

	TestStrategy [ URL="\ref TestStrategy" label="test strategy" shape=box style=filled color=skyblue1 fixedsize=true width=2 ]
	TestPlan [ URL="\ref TestPlan" label="test plan" shape=box  style=filled color=skyblue2 fixedsize=true width=2 ]
	TestReport [ URL="\ref TestReport" label="test report" shape=box  style=filled color=skyblue3 fixedsize=true width=2 ]
	DefectManagement [ URL="\ref Defects" label="defect management" shape=box style=filled color=tomato fixedsize=true width=2 ]

	TestStrategy -> TestPlan -> TestReport -> DefectManagement
}
@enddot

## Scope

The test strategy document shall define the goal of all activities related to
test and quality. It should align all developers, testers and other relevant
stakeholders with regards to a common understanding of quality goals and test
related notation. The document shall be reviewed and agreed on by developers,
testers and other relevant stakeholders.

Testing activities are conducted in a continuous manner, meaning that with
every product iteration, the quality gates for releasing the respective
increment to customers shall be assessed and be reached prior to shipment.  The
main goal of the testing activities is to detect errors early, while creating a
culture of quality awareness and an open error culture. Error reports are
appreciated at any point of the development cycle to enable transparent defect
management.

## Requirements

[Requirements](\ref Requirements) can be destinquished into two different
levels and two different types:

@dot
digraph Requirements
{
	splines=ortho

	Functional [ label="functional requirements" shape=box style=filled color=skyblue1 fixedsize=true width=3 ]
	NonFunctional [ label="non-functional requirements" shape=box style=filled color=skyblue1 fixedsize=true width=3 ]
	Technical [ label="technical level" shape=box style=filled color=slategray1 fixedsize=true width=2 ]
	Customer [ label="stakeholder level" shape=box style=filled color=slategray1 fixedsize=true width=2 ]
	Middle [ shape=point ]

	Functional -> Middle [dir=back]
	Technical -> Middle [dir=back]
	Middle -> Customer
	Middle -> NonFunctional

	{ rank=same; Technical; Middle; Customer }
}
@enddot

Requirements on **technical level** shall be reflected by the review process
and the acceptance criteria of development activities. They are created during
technical analysis of the problem and software design. There is little to no
cutomer gain and feedback for such requirements.

Requirements on the **stakeholder level** are based on stakeholder request and
describe the features the software product shall include. They are directly
evaluated by the stakeholder and should be explicitely tested.

**Functional** requirements are usually introduced as feature request,
describing the functionality of the software product.

**Non-functional** requirements are more delicate, as they are often expected
silently by stakeholders. They must be asked explitely from stakeholders and some
must be formulated by development.

## Test Approach

Facing the requirements of continuous integration, the test process must be
adapted.  Here, methods of continuous testing will be applied to ensure a high
level of quality of the product while keeping the pace of modern development. 

**Continuos testing** is a pipeline strategy, not bound to dedicated testing
phases and with different closed feedback loops. [Zimmerer 2019](\ref TestStrategyRef)

## Legal / Regulations

The test procedure also takes legal aspects into considerations, including the
(redistributable) license status of all components used, legal regulations for
the acceptance and permissions to release the system and the applicance of
standard specifications.

Special care must be taken for open source software components used in the
product, as they have different and potentially very restrictive license types.
Also, law is very specific with respect to using these components, as the full
test responsibility is remaining by the product using the open source software.

## Test Levels

There are four levels of testing considered in this project:
* unit test
* integration test
* sub-system test
* system test

The amount and intesity of testing together with the level of automation is
decreasing from unit to system test level.  The higher test levels, e.g.
sub-system and system test also include all external components to assure the
correct integration and interaction of the product with the environment. The
test levels are not bound to software test alone but also include documentation
and design as well as all other (testable) artifacts, prepared during product
development.

### Unit Test

Test of the smallest building blocks of the software. The test focusses on a
single method or class, calling a public interface and evaluating its result.
Three different types of results can be evaluated (while one test should only
evaluate one of the three): the returned value, a measurable change of the
state of the system or by the way an other part of the system is called. Side
effects and integration effects should be excluded from the unit test, to
ensure the consistency and repeadability of the test.

The unit test is a developer-oriented test and is usually designed and
implemented by the author of the code. An independend review should be carried
out to ensure sharpness of the test. Unit tests are completely automated,
consistent and fast, which makes them available for regression testing on a
daily basis.

### Integration Test

The integration test very similar to an unit test. The main difference is that
the integration test is not actively avoiding internal dependencies, while
still not openly relying on external dependencies. Target is to verify the
correct interaction and collaboration of the internal components via their
interfaces.

### Sub-System Test

The unit and integration test extract parts of the software and create a
"virtual" environment for the tests to run in. The sub-system test shall partly
overcome this limitation and test the individual packages of the final product
as shipped, while still simulating parts of the interaction of other packages
and/or hardware.

### System Test

The system test shall test the product under real world conditions, with all
external and internal components in place and on the target hardware. As this
would create an infinite number of test scenarios with different environments
and component versions, dedicated test scenarios need to be identified, which
shall represent all imaginable combinations.

## Roles and Responsibilities

Any team member of the developer team can take on one or more of the following
roles for his/her work. Sometimes, it may be beneficial to employ dedicated 
testers and developers, but often, they may double up on both roles. For high
level test, a different person should test the product than the one who implemented
it. Also, peer reviews shall protect from soft testing. 

For details on the role's responsibilities, please refer to the 
[definition page](\ref Definition).

A team consists of one **product owner** and a development team. 
The development team should staff the following roles: 
* one **team quality representative**
* one **team architect**
* several **developers**
* several **testers**

## Types of Testing

* white box
* black box
* static

## Explorative Testing

Next to the thoroughly planned test tasks during sub-system and system test
a less restricted approach is explorative testing. This approach is used to
find "new defects" by setting the developers, testers or other stakeholders
into an unconstrained test scenario. A general topic and state of mind is
set to begin with, then a time boxed test session without any rules or concrete
test steps is conducted and recorded. This approach allows for a more creative
setup and "random" findings, which are triggered by certain chain of events
unforseeable or overseen by the test plan. It is beneficial to have a test
document with a fixed checklist to query the whole test environment. The list 
is filled prior to testing, so that in case of an finding, a complete error
report can be created with ease and no questions about the actual situation
and versions arrise. 

## Security Testing

Security in terms of data security and ITSec is an crucial part of any modern
system. Special care must be taken to ensure the secure and uninterrupted
operation of the system, even in case of targeted attacks against the system.
Applying a set of secure coding guidelines, which can be enforced by analyis
tools and code reviews, can help to reduce attack vectors against the system.
The test activities with respect to security shall be conducted by specially
trained professionals. The budget and time for this analysis must be planned
early in the project.
 
# Environment
## Test Object

* description of the product, its application and use cases
* requirements of the product towards its execution environment

## Physical Environment (target)

* description of the (hardware) target platform for the (software) product
* required system resources
* discussion of specific aspects and risks (cross-compiling, reduced system resources...)
* availabilty (and discussion of quality) of the hardware and virtual environments

## Software Environment

* interaction with base / operating system
* description of external and interface components

## Test Tools

For different levels of testing, different tools and environments are utilized.
For unit- and integration tests, a unit test and isolation framework is used,
which provides means for faking parts of the runtime system and creates
executable binaries, which internally call the parts of the system under test,
which are focussed at by the active test case. They are compiling the test
report and execute the test cases in a configurable order (e.g. in random
order, to make sure the test cases are independend of each other). Here, the
google testing framework is used for these low level tests. 

For higher test levels, the actual artifacts of the product built are used
as test specimens. They are relying on the actual platform they are built for
and may lack to "set up" defined test conditions artificially. For this,
the artifacts are executed in a virtual (sub-system test) environment or on
the actual target (system test), which creates a set of obstacles, especially
for test automation.

## Reporting

The tools used for testing create a junit-style test result file in xml format.
The coverage is presented as raw coverage file, as generated by the coverage
tools.  The dashboard application and CI chain can read these files to create
trends of code coverage, test executed and failed next to the build results.

The visualization of test results is done within the documentation of the
project. The documentation shall include:
* code documentation
* architectural documentation (C4 model)
* test documentation
* active requirements
* list of open (known) defects
* changelog, incl. closed defects
* test report of the current build

Using this approach, a complete and archivable artifact is created without 
external dependencies.

## Defect Tracking

* tool used for defect tracking and brief description

# Definition of Done
## Reviews

Reviews shall be carried out for all design documentation and all implemented
code, be it production or test code. For test code, a walkthrough is sufficient
as review, for design documents and production code (inluding the code
generated by pair-programming), a dedicated peer review shall be carried out by
at least one peer.

## Coverage

As the test process has no natural completed critereon, the test coverage is
used as end-of test indicator for the low level test types (unit and
integration testing). Given reviewed test cases, the coverage becomes a valid
measure for the overall status of testing. Both test levels shall cover 100 %
of statements and at least 100 % of branches. Modified condition/decision
coverage is used as measure for code of highest integrety requirements, which
is not the case here, thus basic branch coverage is a sufficient measure.

The higher test levels are measured based on the requirements. Here, a
requirement coverage is defined, and set to 100 % as target coverage criterion.
That means that all requirements applicable for a given software release shall
be tested by at least one test scenario, specifically designed for this
requirement. Requirements may be tested on lower test levels, which would make
a re-test on system level optional.

## Automation

The project aims for a high degree of test automation. For unit and low-level
integration testing, full automation shall be reached (100% of tests). For
higher test levels, individual test cases might be hard or impossible to
automate.  For these, a detailed instruction and questionaire shall be created
to ensure repeatability and expressiveness of the test result. The test then
may be carried out manually, following the questionaire. Overall, 80 % of test
cases shall be automated.

## Reporting

The product documentation, release notes and test report are sent to the test
manager for review and approval **1 week** before the planned release.

## Documentation

The changelog for the current release is present and the user documentation is
updated. A review is carried out in peer review manner and no open points review
findings are remaining.  

## Defect management

The defect management includes all steps from adding newly found defects to the
defect tracking tool, the defect triage, fixing the source location, retesting
and accepting the fix. Defects are prioritized in the defect triage. Here, also
the scope of the fix (or the termination of the defect) are decided as well as
a time schedule. The defect will be rated regarding its severity. For defects
of medium and high severity, the release documentations need to be adapted, for
announcing the issue to users.

# Considerations
## Risks

* test hardware availability
* test team members
* ...?

## Staffing

| role | name | email |
| ---- | ---- | ----- |
| product manager (PM) | | |
| test manager (TM) | | |
| test architect (TA) | | |
| chief architect (CA) | | |
| product owner (PO) | | |
| team quality representative (TQR) | | |
| tester | | |
| ... | | |
 
## Training Needs

* test manager needs more training
* new employed testers shall take training XY

# References {#TestStrategyRef}
* **ISO/IEC 29119-2**: Software and System Engineering - Software Testing - Part 2: 
  Test Processes, **2013**
* **P. Zimmerer**: The Future of Testing is Continuous, OOP **2019**
