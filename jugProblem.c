#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1005

typedef struct {
    int j1;
    int j2;
    int steps;
} State;

typedef struct {
    State data[MAX * MAX];
    int front, rear;
} Queue;

void initQueue(Queue* q){
    q->front = 0;
    q->rear = 0;
}

bool isEmpty(Queue* q){
    return q->front == q->rear;
}

void enqueue(Queue* q, State s){
    q->data[q->rear++] = s;
}

State dequeue(Queue* q){
    return q->data[q->front++];
}

int minOps(int m,int n,int d){
    if(d > m && d > n)return -1;
    
    static bool visited[MAX][MAX];
    for(int i=0;i<=m;i++){
        for(int j=0;j<=n;j++){
            visited[i][j] = false;
        }
    }
    
    Queue q;
    initQueue(&q);
    
    State start = {0,0,0};
    enqueue(&q, start);
    visited[0][0] = true;
    
    while(!isEmpty(&q)){
        State curr = dequeue(&q);
        
        if(curr.j1 == d || curr.j2 == d){
            return curr.steps;
        }
        
        State nextStates[6];
        int count = 0;
        
        nextStates[count++] = (State){m, curr.j2,curr.steps + 1};
        nextStates[count++] = (State){curr.j1, n, curr.steps + 1};
        nextStates[count++] = (State){0, curr.j2, curr.steps + 1};
        nextStates[count++] = (State){curr.j1, 0, curr.steps + 1};
        
        int pour1to2 = (curr.j1 < n - curr.j2) ? curr.j1 : (n - curr.j2);
        nextStates[count++] = (State){curr.j1 - pour1to2, curr.j2 + pour1to2, curr.steps + 1};
        
        int pour2to1 = (curr.j2 < m - curr.j1) ? curr.j2 : (m - curr.j1);
        nextStates[count++] = (State){curr.j1 + pour2to1, curr.j2 - pour2to1, curr.steps + 1};
        
        for(int i = 0; i < count; i++){
            State next = nextStates[i];
            if(next.j1 >= 0 && next.j1 <= m && next.j2 >= 0 && next.j2 <= n){
                if(!visited[next.j1][next.j2]){
                    visited[next.j1][next.j2] = true;
                    enqueue(&q, next);
                }
            }
        }
    } 
    return -1;
}

int main() {
	// your code goes here
	int m, n, d;

    scanf("%d", &m);
    scanf("%d", &n);
    scanf("%d", &d);

    int result = minOps(m, n, d);

    if (result != -1) {
        printf("Min operations- %d", result);
    } else {
        printf("No solution");
    }

    return 0;
	

}

