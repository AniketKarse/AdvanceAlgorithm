#include <bits/stdc++.h>

using namespace std;

int partition(vector<int>& arr, int low, int high){
	int pivot = arr[high];
	int i = low - 1;
	for(int j = low;j<high;j++){
		if(arr[j] <= pivot){
			i++;
			swap(arr[i],arr[j]);
		}
	}
	swap(arr[high],arr[i+1]);
	return i+1;
}

void quicksort(vector<int>& arr, int low, int high){
	if(low < high){
		int part = partition(arr, low, high);

		quicksort(arr, low , part - 1);
		quicksort(arr, part + 1, high);
	}
}

void printVector(const vector<int>& arr) {
    for (int num : arr)
        cout << " " << num;
}

int main() {
	vector<int> arr = { 64, 34, 25, 12, 22, 11, 90 };
	int n = arr.size();
	quicksort(arr,0,n-1);
	cout << "Sorted array: \n";
	printVector(arr);
	return 0;
}
