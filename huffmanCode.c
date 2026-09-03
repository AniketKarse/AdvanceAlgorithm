#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char character;
    int frequency;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(char character, int frequency) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->character = character;
    newNode->frequency = frequency;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

typedef struct {
    int size;
    int capacity;
    Node** array;
} PriorityQueue;

PriorityQueue* CreateEmptyPriorityQueue(int capacity) {
    PriorityQueue* Q = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    Q->size = 0;
    Q->capacity = capacity;
    Q->array = (Node**)malloc(Q->capacity * sizeof(Node*));
    return Q;
}

void swapNode(Node** a, Node** b) {
    Node* temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(PriorityQueue* Q, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < Q->size && Q->array[left]->frequency < Q->array[smallest]->frequency)
        smallest = left;

    if (right < Q->size && Q->array[right]->frequency < Q->array[smallest]->frequency)
        smallest = right;

    if (smallest != idx) {
        swapNode(&Q->array[smallest], &Q->array[idx]);
        minHeapify(Q, smallest);
    }
}

Node* ExtractMin(PriorityQueue* Q) {
    Node* temp = Q->array[0];
    Q->array[0] = Q->array[Q->size - 1];
    Q->size--;
    minHeapify(Q, 0);
    return temp;
}

void Insert(PriorityQueue* Q, Node* node) {
    Q->size++;
    int i = Q->size - 1;
    
    while (i && node->frequency < Q->array[(i - 1) / 2]->frequency) {
        Q->array[i] = Q->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    Q->array[i] = node;
}

Node* BuildHuffmanTree(char Characters[], int Frequencies[], int n) {
    PriorityQueue* Q = CreateEmptyPriorityQueue(n);
    
    for (int i = 0; i < n; i++) {
        Node* leafNode = createNode(Characters[i], Frequencies[i]);
        Insert(Q, leafNode);
    }
    
    while (Q->size > 1) {
        Node* leftNode = ExtractMin(Q);
        Node* rightNode = ExtractMin(Q);
        
        Node* parentNode = createNode('$', leftNode->frequency + rightNode->frequency);
        parentNode->left = leftNode;
        parentNode->right = rightNode;
        
        Insert(Q, parentNode);
    }
    
    Node* root = ExtractMin(Q);
    
    free(Q->array);
    free(Q);
    
    return root;
}

void GenerateCodes(Node* node, char CurrentCode[], int depth) {
    if (node->left == NULL && node->right == NULL) {
        CurrentCode[depth] = '\0';
        printf("%c: %s\n", node->character, CurrentCode);
        return;
    }
    
    if (node->left != NULL) {
        CurrentCode[depth] = '0';
        GenerateCodes(node->left, CurrentCode, depth + 1);
    }
    
    if (node->right != NULL) {
        CurrentCode[depth] = '1';
        GenerateCodes(node->right, CurrentCode, depth + 1);
    }
}


int main() {
    // char C[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    // int F[] = {5, 9, 12, 13, 16, 45};

    int n;

    printf("Enter number of elements: ");
    
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive number.\n");
        return 1; 
    }

    char* C = (char*)malloc(n * sizeof(char));
    int* F = (int*)malloc(n * sizeof(int));

    if (C == NULL || F == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter character and frequency for element %d: ", i + 1);
        scanf(" %c %d", &C[i], &F[i]);
    }

    printf("\nEntered Chars: ");
    for (int i = 0; i < n; i++) {
        printf("%c ", C[i]);
    }

    printf("\nEntered Frequencies: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", F[i]);
    }
    
    Node* TreeRoot = BuildHuffmanTree(C, F, n);
    
    char CurrentCode[100];
    GenerateCodes(TreeRoot, CurrentCode, 0);
    
    return 0;
}
