#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 2005

struct Node {
    int dest;
    struct Node* next;
};

struct Node* adj[MAX];
struct Node* revAdj[MAX];

int visited[MAX];
int s_stack[MAX];
int top = -1;
int scc[MAX];
int scc_count = 0;

void addEdge(struct Node* graph[], int u, int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = v;
    newNode->next = graph[u];
    graph[u] = newNode;
}

void dfs1(int u) {
    visited[u] = 1;
    struct Node* temp = adj[u];
    while (temp != NULL) {
        if (!visited[temp->dest]) {
            dfs1(temp->dest);
        }
        temp = temp->next;
    }
    s_stack[++top] = u;
}

void dfs2(int u, int compID) {
    visited[u] = 1;
    scc[u] = compID;
    struct Node* temp = revAdj[u];
    while (temp != NULL) {
        if (!visited[temp->dest]) {
            dfs2(temp->dest, compID);
        }
        temp = temp->next;
    }
}

int getNeg(int node, int n) {
    return (node > n) ? (node - n) : (node + n);
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 1;

    // Clear graphs
    for (int i = 0; i <= 2 * n; i++) {
        adj[i] = NULL;
        revAdj[i] = NULL;
    }

    for (int i = 0; i < m; i++) {
        int uLit, vLit;
        scanf("%d %d", &uLit, &vLit);

        int uNode = (uLit > 0) ? uLit : (-uLit + n);
        int notU = getNeg(uNode, n);

        int vNode = (vLit > 0) ? vLit : (-vLit + n);
        int notV = getNeg(vNode, n);

        addEdge(adj, notU, vNode);
        addEdge(revAdj, vNode, notU);

        addEdge(adj, notV, uNode);
        addEdge(revAdj, uNode, notV);
    }

    for (int i = 1; i <= 2 * n; i++) {
        visited[i] = 0;
    }
    top = -1;
    for (int i = 1; i <= 2 * n; i++) {
        if (!visited[i]) {
            dfs1(i);
        }
    }
    
    for (int i = 1; i <= 2 * n; i++) {
        visited[i] = 0;
    }
    scc_count = 0;
    while (top >= 0) {
        int node = s_stack[top--];
        if (!visited[node]) {
            scc_count++;
            dfs2(node, scc_count);
        }
    }

    bool possible = true;
    for (int i = 1; i <= n; i++) {
        if (scc[i] == scc[getNeg(i, n)]) {
            possible = false;
            break;
        }
    }

    if (!possible) {
        printf("UNSATISFIABLE.\n");
    } else {
        printf("SATISFIABLE.\n");
        for (int i = 1; i <= n; i++) {
            if (scc[i] > scc[getNeg(i, n)]) {
                printf("x%d = true\n", i);
            } else {
                printf("x%d = false\n", i);
            }
        }
    }

    return 0;
}
