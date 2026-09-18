#include <bits/stdc++.h>

using namespace std;

void merge(vector<int>& arr, int l, int r, int mid){
	int n1 = mid - l + 1;
	int n2 = r - mid;

	vector<int> L(n1),R(n2);
	for (int i = 0; i < n1; ++i)
	{
		L[i] = arr[l+i];
	}
	for (int i = 0; i < n2; ++i)
	{
		R[i] = arr[mid+i+1];
	}

	int i = 0, j =0;
	int k = l;

	while(i<n1 && j <n2){
		if(L[i] <= R[j]){
			arr[k] = L[i];
			i++;
		}
		else{
			arr[k] = R[j];;
			j++;
		}
		k++;
	}

	while(i < n1){
		arr[k] = L[i];
		i++;k++;
	}
	while(j < n2){
		arr[k] = R[j];
		j++;k++;
	}

}

void mergeSort(vector<int>& arr, int l, int r){
	if(l >= r) return;

	int mid = l+(r - l)/2;
	mergeSort(arr, l, mid);
	mergeSort(arr, mid+1,r);
	merge(arr, l, r, mid);
}

void printVector(const vector<int>& arr) {
    for (int num : arr)
        cout << " " << num;
}

int main() {
	vector<int> arr = { 64, 34, 25, 12, 22, 11, 90 };
	int n = arr.size();
	mergeSort(arr,0,n-1);
	cout << "Sorted array: \n";
	printVector(arr);
	return 0;
}
