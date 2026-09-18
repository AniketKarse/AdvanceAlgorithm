#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void minMax(const vector<int>& arr, int i, int j, int& fmax, int& fmin) {
    if (i == j) {
        fmax = arr[i];
        fmin = arr[i];
        return;
    }

    if (i == j - 1) {
        if (arr[i] > arr[j]) {
            fmax = arr[i];
            fmin = arr[j];
        } else {
            fmax = arr[j];
            fmin = arr[i];
        }
        return;
    }

    int mid = (i + j) / 2;
    int gmax, gmin, hmax, hmin;

    minMax(arr, i, mid, gmax, gmin);
    minMax(arr, mid + 1, j, hmax, hmin);

    fmax = max(gmax, hmax);
    fmin = min(gmin, hmin);
}

int main() {
    vector<int> arr = {12, 11, 45, 2, 9, 34, 78, 3};
    int fmax, fmin;
    int n = arr.size();
    minMax(arr, 0, n - 1, fmax, fmin);
    
    cout << "Minimum element is: " << fmin << endl;
    cout << "Maximum element is: " << fmax << endl;
    
    return 0;
}
