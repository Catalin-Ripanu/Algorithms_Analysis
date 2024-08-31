# HW_AA

## Problem 1 - Chess

### Problem Reformulation:
Find a sequence of N numbers (a₁, a₂, ..., aₙ), where 1 ≤ aᵢ ≤ N represents the row occupied by the queen on column i, such that if i ≠ j then aᵢ ≠ aⱼ, aᵢ + i ≠ aⱼ + j, and aᵢ - i ≠ aⱼ - j.

### Deterministic Algorithm:
- Used backtracking to solve this problem.
- Used a global variable 'cont' to prevent calling the 'Display' function twice (for N=8, there are 92 solutions).
- Solves the recurrence T(n) = n * T(n-1) + O(n²) using iterative method and recursion tree method.
- Time complexity: O(n!)

### Non-deterministic Algorithm:
- `verif_queen_row[i]`: number (0 or 1) of queens on row i.
- `verif_queen_diag1[i]`: number of queens (0 or 1) on the diagonal where row index plus column index equals j.
- `verif_queen_diag2[j]`: number of queens (0 or 1) on the diagonal where row index minus column index equals j.
- Time complexity: O(n) (Polynomial time complexity).
- This algorithm is presented in the file 1_N-Queens_ned.txt

## Problem 2 - Graphs

### Deterministic Algorithm:
- Used backtracking to obtain and evaluate combinations (subgraphs).
- 'Vector' is a vector of matrices storing adjacency matrices.
- 'Combinations' function calculates combinations of Vj node sets.
- Combinations are saved in a 'Data' matrix vector.
- 'Vertex' is a vector storing the size of each graph.
- Time complexity: O(K2² * (Combinations of 'element_Vertex' taken K2 at a time)² + K * (Combinations of 'element_Vertex' taken K2 at a time))

### Non-deterministic Algorithm:
- Vj: nodes of graph j, V = {V₁, V₂, ..., Vₖ}
- Ej: edges of graph j, E = {E₁, E₂, ..., Eₖ}
- V'j: nodes of a subgraph (using choice) from graph j
- marcatj: vector of marked elements, 'marcat' is a vector of vectors
- Generation is done in a 'for' loop from 1 to K
- Testing is done in another 'for' loop, x from 1 to K-1
- Time complexity: O(K * K2²) (Polynomial time complexity in K and K2)
- This algorithm is presented in the file 2_Isomorphic-Graph_ned.txt

## Problem 3 - Reduction

### Problem_1:
Given a city with N houses and M bidirectional roads connecting these houses. Roads need repair, and materials must be in at least one of the two houses connecting the road. For a given number K, can we choose K houses to place materials in so that we can repair all roads?

#### Reformulation:
Given a graph G = (V, E) and an integer K, is there a subset B of nodes such that |B| = K, and each edge has at least one end in B? (A vertex cover)

#### Non-deterministic Algorithm:
- Time complexity: O(N⁴) (Polynomial time complexity)
- This algorithm is presented in the file 3_Problem1_ned.txt

### Problem_2:
David has a collection of N unique old banknotes. He has M student friends. Each student has a subset of David's banknotes. David gives them a number K and tells them that to get a perfect score on the assignment, K students must be found who together have all types of banknotes David has.

#### Reformulation:
Given a set U, a collection S₁, S₂, ..., Sₘ of subsets of U, and an integer K, is there a collection of K such subsets whose union is U? (A set cover)

#### Non-deterministic Algorithm:
- Time complexity: O(M² * N) (Polynomial time complexity in N and M)
- This algorithm is presented in the file 3_Problem2_ned.txt

### Reduction:
We show that Problem_1 ≤p Problem_2 by constructing a specific instance for Problem_2 from any instance of Problem_1:

Polynomial-time transformation of input data:
Problem_1 → Problem_2
G=(V,E), K → K=K
              U=E
              Sᵥ = { e ∈ E | ∃ u ∈ V such that e=(u,v) }

The transformation (G=(V,E),K) → (U,S,K) has a time complexity of O(M*N) (Polynomial in N and M).

We prove that Problem_1(x) = 1 ⇔ Problem_2(F(x)) = 1 (F represents the table above), x from I1.

We call Problem_1 vertex cover and Problem_2 set cover.

Left to right: "⇒" (B is a vertex cover of size K ⇒ C={ Sᵥ | v ∈ B } is a set cover of size K)
Right to left: "⇐" (C={ Sᵥ | v ∈ B } is a set cover of size K ⇒ B={ v | Sᵥ ∈ C } is a vertex cover of size K)

An interesting assignment.
Ripanu Catalin-Alexandru.
