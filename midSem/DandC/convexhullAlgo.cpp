// Structure to define a 2D coordinate
struct Point {
    int x;
    int y;
};

// Sub-routine to merge two convex hulls (Step 4)
Point[] MergeHulls(Point C1[], int n1, Point C2[], int n2) {
    
    // 4a. Find rightmost point of left hull (C1)
    int rightmost_left = 0;
    for (int i = 1; i < n1; i++) {
        if (C1[i].x > C1[rightmost_left].x) {
            rightmost_left = i;
        }
    }

    // 4b. Find leftmost point of right hull (C2)
    int leftmost_right = 0;
    for (int i = 1; i < n2; i++) {
        if (C2[i].x < C2[leftmost_right].x) {
            leftmost_right = i;
        }
    }

    // 4c. Find the Upper Tangent
    int up_left = rightmost_left;
    int up_right = leftmost_right;
    
    while (upper tangent is not valid) {
        // Shift left point counter-clockwise
        up_left = (up_left - 1 + n1) % n1; 
        
        // Shift right point clockwise
        up_right = (up_right + 1) % n2;    
    }

    // 4d. Find the Lower Tangent
    int low_left = rightmost_left;
    int low_right = leftmost_right;
    
    while (lower tangent is not valid) {
        // Shift left point clockwise
        low_left = (low_left + 1) % n1;        
        
        // Shift right point counter-clockwise
        low_right = (low_right - 1 + n2) % n2; 
    }

    // 4e. Assemble final merged hull
    Point mergedHull[];
    // Append C1 points moving counter-clockwise from up_left to low_left
    Append(mergedHull, C1[up_left ... low_left]);
    
    // Append C2 points moving counter-clockwise from low_right to up_right
    Append(mergedHull, C2[low_right ... up_right]);

    return mergedHull;
}


// Main Divide and Conquer Function
Point[] DivideAndConquerHull(Point P[], int n) {
    
    // Base Case: 3 or fewer points naturally form a convex hull
    if (n <= 3) {
        return P; 
    }

    // Step 2: Divide points into two halves
    int mid = n / 2;
    Point S1[] = P[0 ... mid-1];     // Points to the left of median
    Point S2[] = P[mid ... n-1];     // Points to the right of median

    // Step 3: Conquer (Recursive calls for individual convex hulls)
    Point C1[] = DivideAndConquerHull(S1, mid);
    Point C2[] = DivideAndConquerHull(S2, n - mid);

    // Step 4: Combine the two sub-hulls
    return MergeHulls(C1, length(C1), C2, length(C2));
}


// Driver Program
int main() {
    Point P[] = {{0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};
    int n = length(P);

    // Step 1: Sort points initially based on x-coordinates
    Sort(P, n); 

    Point ResultHull[] = DivideAndConquerHull(P, n);
    
    return 0;
}
