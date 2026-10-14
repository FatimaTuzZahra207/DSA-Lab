#include <iostream>
#include <vector>

using namespace std;

bool isSorted(const vector<int>& arr, int n) {
	for (int i = 1; i < n; i++) {
		if (arr[i] < arr[i - 1]) {
			return false;
		}
	}
	return true;
}

void inputSortedIDs(vector<int>& arr, int& n) {
	cout << "--- Task 2: Binary Search ---" << endl;
	cout << "Enter number of registration numbers: ";
	cin >> n;
	arr.resize(n);
	cout << "Enter " << n << " registration numbers in ascending order: " << endl;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
}

int binarySearch(const vector<int>& arr, int low, int high, int target) {
	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (arr[mid] == target) {
			return mid;
		}
		if (arr[mid] < target) {
			low = mid + 1;
		}
		else {
			high = mid - 1;
		}
	}
	return -1;
}

void displayResult(int index) {
	if (index != -1) {
		cout << "Result: Found at Index " << index << endl;
	}
	else {
		cout << "Result: Not found / ID is not registered." << endl;
	}
}

int main() {
	vector<int> arr;
	int n;
	inputSortedIDs(arr, n);

	if (!isSorted(arr, n)) {
		cout << "Error: Array is not sorted! Binary search requires sorted input." << endl;
		return 0;
	}

	int target;
	cout << "Enter registration number to search: ";
	cin >> target;

	int index = binarySearch(arr, 0, n - 1, target);
	displayResult(index);

	return 0;
}