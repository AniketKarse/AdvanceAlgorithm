# Advanced Algorithms Mid-Semester Examination Answer Keys

## Mid-Semester Examination (Odd Semester) 2025-26

### 1. Recurrence Relations (6 Marks)

**(i) Solve $a(n) = a(n-1) + n^2$, $a(0)=0$**
Using the substitution method
$$a(n) = a(n-1) + n^2$$
$$a(n-1) = a(n-2) + (n-1)^2$$
$$a(n-2) = a(n-3) + (n-2)^2$$
Continuing this down to the base case $a(1) = a(0) + 1^2$. 
Summing all the equations yields:
$$a(n) = a(0) + 1^2 + 2^2 + 3^2 + \dots + n^2$$
Substituting $a(0) = 0$ and applying the standard sum of squares formula:
$$a(n) = \frac{n(n+1)(2n+1)}{6}$$
The time complexity is $O(n^3)$.

**(ii) Solve $a(n) = 5a(n-1) + 6a(n-2)$, $a(0)=1$, $a(1)=2$**
This is a homogeneous recurrence relation. Rewrite it as:
$$a(n) - 5a(n-1) - 6a(n-2) = 0$$
Form the characteristic equation:
$$x^2 - 5x - 6 = 0$$
Factoring yields $(x-6)(x+1) = 0$, giving roots $r_1 = 6$ and $r_2 = -1$.
The general solution takes the form:
$$a(n) = C_1(6)^n + C_2(-1)^n$$
Apply the initial conditions to find the constants $C_1$ and $C_2$:
1.  $a(0) = 1 \implies C_1(6)^0 + C_2(-1)^0 = 1 \implies C_1 + C_2 = 1$
2.  $a(1) = 2 \implies C_1(6)^1 + C_2(-1)^1 = 2 \implies 6C_1 - C_2 = 2$

Adding equations 1 and 2:
$$7C_1 = 3 \implies C_1 = \frac{3}{7}$$
Substituting $C_1$ back into equation 1:
$$\frac{3}{7} + C_2 = 1 \implies C_2 = \frac{4}{7}$$
The final exact solution is:
$$a(n) = \frac{3}{7}(6)^n + \frac{4}{7}(-1)^n$$
The time complexity is $O(6^n)$.

### 2. Median Algorithm (6 Marks)
The most efficient method to find the median of $N$ numbers is the QuickSelect algorithm, applying a Divide and Conquer approach adapted from Quick Sort's `PARTITION` logic.

**Algorithm Steps:**
1.  **Partition:** Choose a pivot element (e.g., the last element). Iterate through the array, shifting all elements smaller than the pivot to its left and larger elements to its right. Return the final sorted index of this pivot.
2.  **Divide & Conquer:** 
    *   Calculate the target median index $K$. For an odd $N$, $K = N/2$. For an even $N$, the median is the average of elements at $(N/2 - 1)$ and $N/2$.
    *   Compare the pivot's returned index (`pi`) to $K$.
    *   If `pi == K`, the median element is found.
    *   If `pi > K`, recursively call the algorithm only on the left subarray.
    *   If `pi < K`, recursively call the algorithm only on the right subarray.

**Time Complexity:** 
Because this algorithm discards one half of the partition at every recursive step, the average time complexity is $O(N)$. In the worst case, it degrades to $O(N^2)$.

### 3. Non-Recursive Tree Traversals (6 Marks)

**Inorder Traversal (Left, Root, Right):**
1.  Initialize an empty stack `S`. Set `current` node to `root`.
2.  Loop while `current` is not NULL or `S` is not empty:
    *   Traverse down the left side: While `current` is not NULL, push `current` to `S` and set `current = current.left`.
    *   Pop the top node from `S` and print its value.
    *   Move to the right subtree: Set `current = popped_node.right`.

**Postorder Traversal (Left, Right, Root):**
1.  Initialize two stacks, `S1` and `S2`. Push `root` to `S1`.
2.  Loop while `S1` is not empty:
    *   Pop a node from `S1` and immediately push it to `S2`.
    *   Push the popped node's left child, then its right child, to `S1` (if they exist).
3.  Once `S1` is empty, loop through `S2`, popping and printing each node to output the postorder sequence.

### 4. Convex Hull Problem (6 Marks)
**Definition:** A convex hull is the smallest convex polygon that contains a given set of points. 

**Divide & Conquer Algorithm:**
1.  **Sort:** Sort all points in ascending order based on their x-coordinates.
2.  **Divide:** Divide the sorted points into two equal halves, $S_1$ (left of the median) and $S_2$ (right of the median).
3.  **Conquer:** Recursively compute the individual convex hulls for sets $S_1$ and $S_2$. Let these be $C_1$ and $C_2$.
4.  **Combine:** Merge $C_1$ and $C_2$ to form the overall convex hull $C$ by calculating the upper and lower tangent lines connecting the two sub-hulls, removing any internal points.

**Time Complexity Derivation:**
*   Sorting the points initially takes $O(n \log n)$.
*   Dividing the points requires $O(1)$ time.
*   The algorithm makes two recursive calls on halves of the points, yielding $2T(n/2)$.
*   Merging the two hulls takes $O(n)$ time to walk the perimeters and find tangents.
*   The recurrence relation is $T(n) = 2T(n/2) + O(n)$, which resolves to a time complexity of $O(n \log n)$ via the Master Theorem.

### 5. Max_Heapify and Build_MaxHeap (6 Marks)

**Max_Heapify (Fixing a Violation):**
The `Max_Heapify` procedure restores the max-heap property for a given node index $i$, assuming its left and right subtrees are already valid max-heaps.
1.  Identify the left child index ($2i$) and right child index ($2i+1$).
2.  Compare the value at node $i$ with its children to find the maximum value among the three.
3.  If the maximum is one of the children, swap the value at node $i$ with the maximum child's value.
4.  Recursively call `Max_Heapify` on the child node that received the swapped value until no violations remain.

**Build_MaxHeap (Constructing the Heap):**
This procedure transforms an unordered array of $N$ elements into a valid max-heap.
1.  Treat the input array as an almost complete binary tree.
2.  Start from the last non-leaf node, located at index $\lfloor N/2 \rfloor$, because leaf nodes inherently satisfy the heap property on their own.
3.  Perform a level-order traversal backward from index $\lfloor N/2 \rfloor$ down to 1 (the root).
4.  At each step, call `Max_Heapify` on the current node to iteratively build the heap structure upwards.

---

## Mid-Semester Examination (Odd Semester) 2024-25[cite: 9]

### 1. Recurrence Relation (4 Marks)
**Solve $T(n) = 2T(n-1) + n + 2^n$ for $n \ge 1$ and $T(0) = 0$**
This is an inhomogeneous recurrence relation. 
$$T(n) - 2T(n-1) = n + 2^n$$

**Step 1: Homogeneous Solution ($T_h$)**
The characteristic equation for the homogeneous part is $r - 2 = 0 \implies r = 2$.
$$T_h(n) = C_1(2^n)$$

**Step 2: Particular Solution ($T_p$)**
Since the non-homogeneous part has a polynomial ($n$) and an exponential ($2^n$), we find a particular solution for each.
*   For the polynomial term $n$, assume $P_1(n) = An + B$.
    Substitute into the recurrence: $(An + B) - 2(A(n-1) + B) = n$.
    $-An + 2A - B = n$. 
    Equating coefficients: $-A = 1 \implies A = -1$.
    $2A - B = 0 \implies 2(-1) - B = 0 \implies B = -2$.
    $P_1(n) = -n - 2$.
*   For the exponential term $2^n$, since 2 is already a root of the homogeneous equation, multiply by $n$. Assume $P_2(n) = C n 2^n$.
    Substitute: $C n 2^n - 2(C (n-1) 2^{n-1}) = 2^n$.
    $C n 2^n - C(n-1)2^n = 2^n$.
    Divide by $2^n$: $C n - Cn + C = 1 \implies C = 1$.
    $P_2(n) = n 2^n$.

**Step 3: General Solution**
$$T(n) = T_h(n) + P_1(n) + P_2(n)$$
$$T(n) = C_1(2^n) - n - 2 + n2^n$$
Apply the initial condition $T(0) = 0$:
$$0 = C_1(2^0) - 0 - 2 + 0 \implies C_1 = 2$$
The final solution is:
$$T(n) = 2(2^n) + n2^n - n - 2 = 2^{n+1} + n2^n - n - 2$$

### 2. Second Best Minimum Spanning Tree (4 Marks)

**Algorithm:**
1.  Compute the optimal Minimum Spanning Tree (MST) of the given weighted graph $G$ using Kruskal's algorithm. Store the edges belonging to this MST in set $T$.
2.  Initialize `min_second_best_cost` to infinity.
3.  For each edge $e$ currently in $T$:
    *   Temporarily remove $e$ from the graph $G$.
    *   Execute Kruskal's algorithm on the remaining edges of $G$ to find a new spanning tree $T'$.
    *   If $T'$ is a valid spanning tree and its total weight is less than `min_second_best_cost`, update the variable and save $T'$ as the current second best MST.
4.  Restore edge $e$ to graph $G$ and proceed to the next edge in $T$. 
5.  Return the saved $T'$.

**Time Complexity:**
Finding the initial MST takes $O(E \log E)$ time using Kruskal's algorithm. The algorithm then repeats Kruskal's for each of the $(V-1)$ edges in the MST. Therefore, the total time complexity is $O(V \cdot E \log E)$.

### 3. Spanning Trees (4 Marks)
**Definition:** A spanning tree is a connected, acyclic subgraph that contains all the vertices of the original graph. 

**Expression for a Complete Graph:**
According to Cayley's formula, the total number of spanning trees in a complete graph with $N$ vertices is $N^{N-2}$.
*   **Derivation:** Any labeled tree with $N$ vertices can be uniquely mapped to a sequence of $N-2$ integers using Prüfer sequences, where each integer is chosen from the vertex labels $1$ to $N$.
*   Since the sequence has a length of $N-2$, and each position can independently take any of the $N$ possible vertex labels, the total number of unique sequences is $N \times N \times \dots \times N$ ($N-2$ times). This yields exactly $N^{N-2}$ distinct sequences, mapping to $N^{N-2}$ distinct spanning trees.

### 4. Longest Increasing Subsequence (LIS) (4 Marks)
This problem is efficiently solved using a bottom-up Dynamic Programming approach.

**Algorithm:**
1.  Initialize an array `L` of size $N$, where `L[i]` stores the length of the LIS ending at index `i`. Set every element in `L` to 1 (each number is an increasing subsequence of length 1 by default).
2.  Initialize an array `Parent` to track the indices for printing the final sequence.
3.  Use two nested loops:
    *   For $i$ from 1 to $N-1$:
        *   For $j$ from 0 to $i-1$:
            *   If $Sequence[i] > Sequence[j]$ AND $L[i] < L[j] + 1$:
                *   Update $L[i] = L[j] + 1$.
                *   Update $Parent[i] = j$.
4.  Find the index holding the maximum value in `L`. Starting from this index, use the `Parent` array to backtrack and print the elements of the Longest Increasing Subsequence in reverse order. 

### 5. Branch and Bound for 15-Puzzle (4 Marks)
The Branch and Bound method solves the 15-puzzle optimization problem by generating a state space tree and eliminating unpromising sub-problems using a bounding function.

**Working Mechanism:**
1.  **Define Cost Function:** The algorithm utilizes a heuristic cost function $M(i) = \text{depth} + \text{number of non-blank tiles not in their final position}$.
2.  **Generate Moves:** From the initial root state (E-node), the algorithm generates all possible legal child configurations by moving the blank tile UP, DOWN, LEFT, and RIGHT.
3.  **Calculate Bounds:** It calculates the $M(i)$ bound value for each newly generated child node (live node).
4.  **LC Search Strategy:** Using Least Cost (LC) Search paired with a Priority Queue, the algorithm selects the live node with the absolute lowest $M(i)$ value to become the next E-node for expansion.
5.  **Pruning:** The algorithm continually explores the most promising branch. Sub-trees with high $M(i)$ values are naturally delayed or ignored entirely (pruned). The process halts once the target goal state is reached at the lowest possible depth.
