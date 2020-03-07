# Template Project {#C2_TemplateProject}

# Overview

The Template Project itself consists of different workers (performing tasks on the operating system, which really is all
the template project does - for a real project you *should* enter some meaningful documentation here.

\dot
digraph {
  node [ shape=box fillcolor=grey93 style=filled ];

  subgraph cluster_Template {
    label = "Template Project";
    fillcolor = azure2;

    ConfigReader [ fillcolor=limegreen label="Config Reader" URL="\ref C3_ConfigReader" ];
    Worker1 [ fillcolor=limegreen label="Worker 1" URL="\ref C3_Worker" ];
    Worker2 [ fillcolor=limegreen label="Worker 2" URL="\ref C3_Worker" ];
  }
  User [ shape=star label="User" ];
  OperatingSystem [ label="Linux" ];

  Config [ label="config.json" fillcolor=chocolate ];

  User -> Worker1 -> OperatingSystem;
  Worker2 -> OperatingSystem;

  ConfigReader -> Worker1 [ dir=back color=chocolate ];
  ConfigReader -> Worker2 [ dir=back color=chocolate ];
  ConfigReader -> Config [ dir=back color=chocolate ];
}
\enddot
