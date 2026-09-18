#include <stdio.h>
#include <limits.h>

int matrixChainRecursive(int p[], int i, int j) {
    if (i == j) {
        return 0;
    }

    int min = INT_MAX;
    int count;

    for (int k = i; k < j; k++) {
        count = matrixChainRecursive(p, i, k) + matrixChainRecursive(p, k + 1, j) + p[i - 1] * p[k] * p[j];

        if (count < min) {
            min = count;
        }
    }
    return min;
}

int matrixChainDP(int p[], int n) {
    int m[n][n];

    for (int i = 1; i < n; i++) {
        m[i][i] = 0;
    }

    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;

            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                }
            }
        }
    }

    return m[1][n - 1];
}

int main() {
    int num_matrix;

    scanf("%d", &num_matrix);

    int n = num_matrix + 1;
    int p[n]; 

    
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    int min_recursive = matrixChainRecursive(p, 1, n - 1);
    printf("Divide and Conquer : %d\n", min_recursive);

    int min_dp = matrixChainDP(p, n);
    printf("DP : %d\n", min_dp);

    return 0;
}