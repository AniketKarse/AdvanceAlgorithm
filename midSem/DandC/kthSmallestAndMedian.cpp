#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int partition(vector<int>& arr, int low, int high){
    int pivot = arr[high];
    int i = low - 1;

    for(int j = low;j <= high - 1;j++){
        if(arr[j] < pivot){
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[high], arr[i+1]);
    return i+1;
}

int quickselect(vector<int>& arr, int low, int high, int k){
    if(k > 0 && k <= high - low + 1){
        int pi = partition(arr ,low ,high);

        if(pi - low == k - 1)return arr[pi];

        if(pi - low > k -1){
            return quickselect(arr, low, pi - 1, k);
        }

        return quickselect(arr, pi + 1, high, k - pi + low - 1);
    }
    return -1;
}

int median(vector<int>& arr){
    int n = arr.size();

    if(n%2 != 0){
        return quickselect(arr,0, n -1, n/2 + 1);
    }else{
        int leftMid = quickselect(arr,0,n-1,n/2);
        int rightMid = quickselect(arr, 0, n-1,n/2+1);
        return(leftMid+rightMid)/2;
    }

}

int main() {
    vector<int> arr = {12, 11, 45, 2, 9, 34, 78, 3};
    int n = arr.size();
    
    cout << "kth smallest element is: " << quickselect(arr,0,n-1,4) << endl;
    cout << "Median element is: " << median(arr) << endl;
    
    return 0;
}
