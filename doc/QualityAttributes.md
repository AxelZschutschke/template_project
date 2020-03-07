# Quality Attributes {#QualityAttributes}

# Overview 

Functional and non-functional (NFR) requirements are formulated for the development 
of the system, describing what (functional requirements) and how (non functional
requirements) a system is perfoming its work.

\dot
graph {
  edge [ style=invis ]
  node [ shape=box style="rounded,filled" color=white width=2 fixedsize=true ]
  graph [ nodesep="0.1" ranksep="0.1" pad="0.1" ]
  subgraph clusterFunctional 
  {
    style="filled,rounded"
    color=skyblue1
    URL="\ref FunctionalRequirements"
	
    Functional [ shape=plaintext style="" label=<<B>functional</B>> ]
    Feature [ label=<<B>feature</B>> ]
    Safety [ label=<<B>safety</B>> ]
    
    Functional -- Feature -- Safety 
  }

  subgraph clusterSecurity 
  {
    style="filled,rounded"
    color=sienna1
    URL="\ref SecurityRequirements"
	
    Security [ shape=plaintext style="" label=<<B>security</B>> ]
    Confidentiality [ label=<<B>confidentiality</B>> ]
    Integrity [ label=<<B>integrity</B>> ]
    Available [ label=<<B>available</B>> ]
    
    Security -- Confidentiality -- Integrity -- Available
  }


  subgraph clusterMaintainable 
  {
    style="filled,rounded"
    color=slategray1
    URL="\ref MaintainableRequirements"
	
    Maintainable [ shape=plaintext style="" label=<<B>maintainable</B>> ]
    Testable [ label=<<B>testable</B>> ]
    Traceable [ label=<<B>traceable</B>> ]
    Stable [ label=<<B>stable</B>> ]
    Modifiable [ label=<<B>modifiable</B>> ]
    
    Maintainable -- Testable -- Traceable -- Stable -- Modifiable
  }

  subgraph clusterEfficiency 
  {
    style="filled,rounded"
    color=maroon1
    URL="\ref EfficiencyRequirements"
	
    Efficiency [ shape=plaintext style="" label=<<B>efficiency</B>> ]
    Timing [ label=<<B>timing</B>> ]
    ResourceUtilization [ label=<<B>resource utilization</B>> ]
    
    Efficiency -- Timing -- ResourceUtilization
  }

  subgraph clusterReliable 
  {
    style="filled,rounded"
    color=springgreen1
    URL="\ref ReliableRequirements"
	
    Reliable [ shape=plaintext style="" label=<<B>reliable</B>> ]
    FaultTolerance [ label=<<B>fault tolerance</B>> ]
    Recoverable [ label=<<B>recoverable</B>> ]
    Available2 [ label=<<B>available</B>> ]
    
    Reliable -- FaultTolerance -- Recoverable -- Available2
  }

  subgraph clusterUseable 
  {
    style="filled,rounded"
    color=khaki1
    URL="\ref UseableRequirements"
	
    Useable [ shape=plaintext style="" label=<<B>useable</B>> ]
    Accesible [ label=<<B>accesible</B>> ]
    FaultTolerance2 [ label=<<B>fault tolerance</B>> ]
    Consistency [ label=<<B>consistency</B>> ]
    Attractiveness [ label=<<B>attractiveness</B>> ]
    Learnable [ label=<<B>learnable</B>> ]
    Adequacy [ label=<<B>adequacy</B>> ]
    
    Useable -- Accesible -- FaultTolerance2 -- Consistency -- Attractiveness -- Learnable -- Adequacy
  }

  subgraph clusterPortable 
  {
    style="filled,rounded"
    color=peachpuff1
    URL="\ref PortableRequirements"
	
    Portable [ shape=plaintext style="" label=<<B>portable</B>> ]
    Installable [ label=<<B>installable</B>> ]
    Replaceable [ label=<<B>replaceable</B>> ]
    Coexistence [ label=<<B>coexistence</B>> ]
    Adaptable [ label=<<B>adaptable</B>> ]
    
    Portable --Installable -- Replaceable -- Coexistence -- Adaptable
  }

  Safety -- Portable
  ResourceUtilization -- Reliable
  Modifiable -- Security
}
\enddot

## Functional Requirements {#FunctionalRequirements}

The aggregation of all aspects of the software describing what it does. Legal
and safety aspects are referred to as functional requirements as well.

**features** able of the system to perform a certain task, usually requested
by stakeholder

**safety** the system shall be safe to use and operate, it shall not harm
persons or equipment

**legal** the system shall not contradict applicable law with respect to
license and other obligations

## Security Requirements {#SecurityRequirements}

Extend to which the system is protected against deliberate and intrusive
faults from internal or external sources

**confidential** extend to which the system protects its users data
and intelectual property

**integrity** extend to which the system is protected against unwanted
modification of its internal state from internal or external sources

**available** timely extend to which the system is available for
the users interaction and provides its functionality

## Maintainable Requirements {#MaintainableRequirements}

Extend to which the system is open for change and further development and
changes are traceable and easy to apply.

**testable** extend to which tests can be formulated, implemented, set up and
executed against the system

**traceable** extend to which the system can be observed regarding its working
state and diagnosed in case of failures

**stable** extend to which the system is operable and recoverable due to
diagnosis and maintenance

**modifiable** extend to which the system can be adapted by a) replacing components
while leaving the rest of the system intact b) extending its functionality c) deploying
it to new environment d) scaling it to new load conditions

## Reliabiltiy Requirements {#ReliableRequirements}

Able of the system to maintain its performance level for fixed and
predefined conditions over a given amount of time.

**fault tolerant** extend to which the system maintains its functionality and
performance in case of internal errors or misuse of interfaces

**recoverable** extend to which the system is able to resume normal operation
after failures

**available** the amount of system failures over time 

## Useable Requirements {#UseableRequirements}

Extend to which the system software helps the user to easily set up, configure
and use the system.

**accessible** extend to which the system is useable by users without
dedicated training and without technical background

**fault tolerance** in terms of useable: ease for the user to perceive 
failure states and correct them

**consistence** identical functionality shall be presented and interacted with in
an identical way; also avoid unexpected conditions

**attractiveness** excitement of the user when using the system

**learnable / understandable** effort for the user to learn using the system,
including well structured documentation.

**adequacy** the system shall provide the adequate functionality easily, meaning
with low user interaction required and shall present expected behavior.

## Efficiency Requirements {#EfficiencyRequirements}

Extend to which the system is interacting with the hardware and time resources.

**timing** latency and throughput of the system

**resource utilization** during operation at different load levels and during
standby and idle mode, incl. cpu, memory, disk, network, ...

## Portable Requirements {#PortableRequirements}

Effort to bring the system to a different environment.

**installable** ease of deployment of the system

**replaceable** effort to replace the system or individual components by new
versions or alternatives

**coexistence** option to run functional identical software components in parallel

**adaptable** extend to which the system is independend of other components 
(software and hardware)
