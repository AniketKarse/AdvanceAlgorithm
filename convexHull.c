#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long x, y;
} Point;

typedef struct {
    Point* p;
    int size;
} Hull;

long long cross_product(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x);
}

int compare_points(const void* a, const void* b) {
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;
    if (p1->x != p2->x) return (p1->x > p2->x) ? 1 : -1;
    return (p1->y > p2->y) ? 1 : -1;
}

Hull get_base_hull(Point* pts, int n) {
    Hull h = { (Point*)malloc(n * sizeof(Point)), n };
    
    if (n <= 2 || cross_product(pts[0], pts[1], pts[2]) > 0) {
        for (int i = 0; i < n; i++) h.p[i] = pts[i];
    } else {
        h.p[0] = pts[0]; h.p[1] = pts[2]; h.p[2] = pts[1];
    }
    return h;
}

Hull merge_hulls(Hull left, Hull right) {
    int inner_l = 0, inner_r = 0;
    for (int i = 1; i < left.size; i++)  if (left.p[i].x > left.p[inner_l].x) inner_l = i;
    for (int i = 1; i < right.size; i++) if (right.p[i].x < right.p[inner_r].x) inner_r = i;

    int up_l = inner_l, up_r = inner_r;
    int down_l = inner_l, down_r = inner_r;
    int changed;

    do {
        changed = 0;
        while (cross_product(right.p[up_r], left.p[up_l], left.p[(up_l + 1) % left.size]) > 0) {
            up_l = (up_l + 1) % left.size; changed = 1;
        }
        while (cross_product(left.p[up_l], right.p[up_r], right.p[(up_r - 1 + right.size) % right.size]) < 0) {
            up_r = (up_r - 1 + right.size) % right.size; changed = 1;
        }
    } while (changed);

    do {
        changed = 0;
        while (cross_product(right.p[down_r], left.p[down_l], left.p[(down_l - 1 + left.size) % left.size]) < 0) {
            down_l = (down_l - 1 + left.size) % left.size; changed = 1;
        }
        while (cross_product(left.p[down_l], right.p[down_r], right.p[(down_r + 1) % right.size]) > 0) {
            down_r = (down_r + 1) % right.size; changed = 1;
        }
    } while (changed);

    Hull merged = { (Point*)malloc((left.size + right.size) * sizeof(Point)), 0 };
    
    int curr = up_l;
    do { 
        merged.p[merged.size++] = left.p[curr]; 
        curr = (curr + 1) % left.size; 
    } while (curr != (down_l + 1) % left.size);
    
    curr = down_r;
    do { 
        merged.p[merged.size++] = right.p[curr]; 
        curr = (curr + 1) % right.size; 
    } while (curr != (up_r + 1) % right.size);

    return merged;
}

Hull divide_and_conquer(Point* pts, int n) {
    if (n <= 3) return get_base_hull(pts, n);
    
    int mid = n / 2;
    Hull left = divide_and_conquer(pts, mid);
    Hull right = divide_and_conquer(pts + mid, n - mid);
    
    Hull merged = merge_hulls(left, right);
    
    free(left.p); 
    free(right.p);
    
    return merged;
}

int main() {
    Point pts[] = {{0, 0}, {3,3}, {1, 1}, {2, 2}, {0, 3},{1,2},{2,1}};
    int n = sizeof(pts) / sizeof(pts[0]);
    
    qsort(pts, n, sizeof(Point), compare_points);
    Hull final_hull = divide_and_conquer(pts, n);
    
    for (int i = 0; i < final_hull.size; i++) {
        printf("(%lld, %lld)\n", final_hull.p[i].x, final_hull.p[i].y);
    }
    
    free(final_hull.p);
    return 0;
}
