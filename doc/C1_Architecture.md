# Architecture Documentation {#C1_Overview}

[TOC] 

# Overview

The architecture documentation is based on the [C4 model](https://c4model.com/) and is summarized in figures of
different detail level. Interfaces are documented separately.

\dot
digraph {
  node [ fillcolor=grey93 shape=box style=filled ]
  TemplateProject [ fillcolor=limegreen label="Template Project" URL="\ref C2_TemplateProject" ];
  User [ shape=star label="User" ];
  OperatingSystem [ label="Linux" ];

  Config [ shape=box label="config.json" fillcolor=chocolate ];

  User -> TemplateProject -> OperatingSystem;
  TemplateProject -> Config [ dir=back color=chocolate ];
}
\enddot
* zoom in: \subpage C2_TemplateProject ""

# Requirements

The requirement engineering is done with [TOOL]. For non-functional requirements (NFRs), different quality attributes
are used for classification, see \subpage QualityAttributes.
