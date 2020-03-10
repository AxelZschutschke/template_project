# Template Project {#Main}

# Overview

C++ template project containing some basic test / documentation

* \subpage C1_Overview
* \subpage TestDocumentation
* \subpage StyleGuide
* \subpage Definitions
* \subpage Tools

# Status

The tamplate project contains document templates, giving an outline for the actual project's documentation. They should
be reviewed and modified to your needs at project start, they are merely serving as some guidance for not forgetting
about parts of the documentation.

The template project itself is under development, it does not contain everything I think should be in here. There are
time constraints for not having it in better shape. Things missing:

* example code - I would like to add some examples with intentional errors for several reasons:
  - get some documentation output
  - get some testreport output
  - show how the open source tools work for the specific issues

* more documentation
  - writing down the definitions and test documentation helps a lot to sort out things for myself
  - takes a lot of time to get it right
  - would take even more time to get it nice with some pictures etc.

* requirement engineering
  - I did not find an open source tool for that which could be integrated here

* test reporting
  - I am currently working on an offline python-based "dashboarding" tool creating md files as docygen input
  - might be a personal thing: I am not all in for online dashboards, helpful as they may be -> I miss the "complete
  overview" in there and the long term documentation
  - my preffered way: having it all in the code doc (doxygen), create your architecture, requirement and test
  documentation in there and just store the one folder with doxygen results along with your artifacts and maybe a copy
  of your sources. That way you can easily take up work from there even if your preffered online dashboard cannot show
  you your year-old info anymore.

# License

The template project is available under MIT license, leaving it up to you making use of it. For me, it serves as a
private reference and landing zone for ideas. I would be happy if it serves anybody else - feedback and attribution are
welcome!
