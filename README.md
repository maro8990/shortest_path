# Network Routing & Resilience Engine

A C++ implementation of fundamental graph traversal and shortest-path algorithms, built as an interactive network simulation tool.

The project models a weighted network in which vertices represent nodes and weighted edges represent connections between them. It provides implementations of **Breadth-First Search (BFS)**, **Depth-First Search (DFS)**, and **Dijkstra's shortest-path algorithm**, while also allowing users to simulate network link failures and restore connections dynamically.

---

## Features

- Display the current network topology
- Traverse the network using **Breadth-First Search (BFS)**
- Traverse the network using **Depth-First Search (DFS)**
- Detect whether the network is connected or disconnected
- Identify individual connected components
- Calculate shortest distances using **Dijkstra's algorithm**
- Reconstruct the shortest path between two vertices
- Simulate network link failures
- Restore failed links with configurable weights
- Validate user input through an interactive command-line interface

---

## Algorithms Implemented

### Breadth-First Search (BFS)

BFS explores the graph level by level starting from a vertex selected by the user.

The implementation uses:

- `std::queue` to manage vertices waiting to be processed
- A visited map to prevent vertices from being processed more than once

BFS is useful for systematic graph traversal and for exploring nodes based on their distance, in number of edges, from a starting vertex.

**Time Complexity:** `O(V + E)`

Where:

- `V` = number of vertices
- `E` = number of edges

---

### Depth-First Search (DFS)

DFS explores the graph by following a path as deeply as possible before continuing with unexplored vertices.

The implementation uses:

- `std::stack` for iterative traversal
- A visited map for tracking discovered vertices
- Component identifiers for determining network connectivity

After traversing the component containing the selected starting vertex, the program checks for any remaining unvisited vertices.

If additional unvisited vertices exist, further DFS traversals are performed to identify separate connected components.

The program therefore reports whether the network is:

- **Connected**
- **Disconnected**

It also displays the vertices belonging to each connected component.

**Time Complexity:** `O(V + E)`

---

### Dijkstra's Shortest-Path Algorithm

Dijkstra's algorithm calculates the shortest distance from a user-selected source vertex to every reachable vertex in the weighted graph.

The implementation maintains:

- The shortest-known distance for each vertex
- The visited state of each vertex
- Predecessor information for path reconstruction

After calculating the shortest distances, the user can select a destination vertex and the program reconstructs the shortest path.

Example:

```text
Shortest path : A --> D --> X --> Y
```

The implementation assumes **non-negative edge weights**, as required by Dijkstra's algorithm.

The current version selects the next minimum-distance unvisited vertex by scanning through the graph.

**Time Complexity:** approximately `O(V² + E)`

For larger graphs, this could be optimized using a priority queue such as `std::priority_queue`.

---

## Network Representation

The network is represented using nested C++ maps:

```cpp
map<char, map<char, int>> network;
```

Conceptually:

```text
Vertex
  |
  +-- Neighbor -> Weight
  +-- Neighbor -> Weight
```

For example:

```text
A
├── B (5)
├── C (6)
└── D (2)
```

Each connection is stored in both directions, creating an **undirected weighted graph**.

The default graph contains the following vertices:

```text
A, B, C, D, X, Y
```

The configured connections are:

```text
A <----> B    weight: 5
A <----> C    weight: 6
A <----> D    weight: 2
B <----> C    weight: 1
C <----> D    weight: 3
D <----> X    weight: 2
X <----> Y    weight: 7
```

---

## Network Resilience Simulation

The project also allows the graph topology to be modified while the program is running.

### Simulate Link Failure

The user can select two connected vertices and remove the edge between them.

Example:

```text
Enter first vertex: D
Enter second vertex: X

Link D <----> X has been removed.
```

After removing a connection, BFS, DFS, or Dijkstra's algorithm can be executed again to observe how the network has changed.

This makes it possible to demonstrate how link failures affect:

- Reachability
- Connectivity
- Connected components
- Shortest paths

---

### Restore Link

A removed connection can be restored by selecting two vertices and assigning a non-negative weight.

Example:

```text
Enter first vertex: D
Enter second vertex: X
Enter link weight: 2

Link D <----> X has been restored with weight 2
```

---

## Interactive Menu

When the application starts, the following menu is displayed:

```text
=====NETWORK ROUTING & RESILIENCE ENGINE=====

1. Show network
2. Run BFS
3. Run DFS
4. Find shortest path (Run Dijkstra)
5. Simulate link failure
6. Restore link
7. Exit
```

The user can continuously interact with the network until selecting the **Exit** option.

---

## Building the Project

### Requirements

- C++ compiler with C++11 support or later
- GCC, Clang, or another standards-compliant C++ compiler

No external libraries are required.

### Compile with GCC

```bash
g++ -std=c++11 -Wall -Wextra main.cpp -o network_simulator
```

### Run on Linux/macOS

```bash
./network_simulator
```

### Run on Windows

```text
network_simulator.exe
```

---

## Example Workflow

A typical session could involve:

1. Displaying the original network
2. Running BFS from vertex `A`
3. Running DFS to examine network connectivity
4. Calculating the shortest path from `A` to `Y`
5. Removing the connection between `D` and `X`
6. Running DFS again to determine whether the network became disconnected
7. Running Dijkstra again to examine the effect of the failure
8. Restoring the `D-X` connection
9. Verifying that network connectivity has been restored

This demonstrates how changes to graph topology can affect traversal, connectivity, and routing.

---

## Data Structures Used

| Data Structure | Purpose |
|---|---|
| `std::map` | Graph representation, visited states, distances, predecessors, and component identifiers |
| `std::queue` | BFS traversal |
| `std::stack` | DFS traversal and shortest-path reconstruction |

These Standard Library containers allow the implementation to focus on the graph algorithms while using reliable C++ data structures for storage and traversal.

---

## Project Structure

```text
.
├── main.cpp
└── README.md
```

`main.cpp` contains:

- Graph representation
- BFS implementation
- DFS implementation
- Dijkstra's algorithm
- Connected-component detection
- Link failure simulation
- Link restoration
- Input validation
- Interactive command-line interface

---

## Learning Objectives

This project demonstrates concepts including:

- Graph representation
- Graph traversal
- Breadth-First Search
- Depth-First Search
- Dijkstra's shortest-path algorithm
- Weighted graphs
- Connected components
- Stacks and queues
- Associative containers
- Path reconstruction
- Network resilience
- Algorithmic complexity
- Input validation
- Interactive C++ application design

---

## Potential Improvements

Possible future extensions include:

- Using a priority queue to optimize Dijkstra's algorithm
- Supporting dynamic creation and removal of vertices
- Allowing new links to be added during runtime
- Loading network topology from a file
- Saving modified graph configurations
- Separating graph functionality into dedicated classes
- Adding automated unit tests
- Supporting graph visualization
- Supporting arbitrary vertex names instead of single characters
- Implementing additional graph algorithms such as:
  - A*
  - Bellman-Ford
  - Prim's algorithm
  - Kruskal's algorithm

---

## About

This project demonstrates the implementation of fundamental graph algorithms in C++ through a practical network-routing and resilience scenario.

Rather than executing the algorithms independently, the application combines graph traversal, shortest-path calculation, connectivity analysis, and dynamic topology changes in a single interactive program.