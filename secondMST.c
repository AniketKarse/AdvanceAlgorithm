#include <stdio.h>
#include <stdlib.h>

struct Edge {
    int u, v, w;
};

int p[1005], r[1005]; 

int find(int x) {
    return p[x] == x ? x : (p[x] = find(p[x]));
}

int unite(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return 0;
    if (r[a] < r[b]) p[a] = b;
    else if (r[a] > r[b]) p[b] = a;
    else { p[b] = a; r[a]++; }
    return 1;
}

int cmp(const void *a, const void *b) {
    return ((struct Edge*)a)->w - ((struct Edge*)b)->w;
}

int kruskal(int n, int m, struct Edge *edges, int skip_idx, int *mst_edges) {
    for (int i = 0; i < n; i++) {
        p[i] = i; 
        r[i] = 0;
    }
    
    int cost = 0, taken = 0;
    for (int i = 0; i < m; i++) {
        if (i == skip_idx) continue;
        
        if (unite(edges[i].u, edges[i].v)) {
            cost += edges[i].w;
            if (mst_edges) mst_edges[taken] = i;
            taken++;
        }
    }
    
    
    return (taken == n - 1) ? cost : 1e9;
}

int main() {
    int n = 5;
    struct Edge edges[] = {
        {0, 1, 4}, {0, 2, 3}, {1, 2, 1}, 
        {1, 3, 5}, {2, 3, 7}, {2, 4, 10}, {3, 4, 2}
    };
    int m = sizeof(edges) / sizeof(edges[0]);
    
    qsort(edges, m, sizeof(struct Edge), cmp);

    int mst_edges[1005];
    int mst_cost = kruskal(n, m, edges, -1, mst_edges);

    if (mst_cost == 1e9) {
        printf("Graph is disconnected so no MST exists \n");
        return 0;
    }

    int second_best = 1e9;

    for (int i = 0; i < n - 1; i++) {
        int current_cost = kruskal(n, m, edges, mst_edges[i], NULL);
        
        if (current_cost >= mst_cost && current_cost < second_best) {
            second_best = current_cost;
        }
    }

    if (second_best == 1e9) {
        printf("No second MST exists as graph becomes disconnected \n");
    } else {
        printf("Cost of 2nd MST: %d\n", second_best);
    }

    return 0;
}
