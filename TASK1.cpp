#include <iostream>
#include <vector>

using namespace std;

void inputIDs(vector<int>& arr, int& n) {
	cout << "--- Task 1: Linear Search ---" << endl;
	cout << "Enter number of student IDs: ";
	cin >> n;
	arr.resize(n);
	cout << "Enter " << n << " student IDs (unsorted): " << endl;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
}

int linearSearch(const vector<int>& arr, int n, int target) {
	for (int i = 0; i < n; i++) {
		if (arr[i] == target) {
			return i; // Return the first occurrence index
		}
	}
	return -1; // Not found
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
	inputIDs(arr, n);

	int target;
	cout << "Enter target ID to search: ";
	cin >> target;

	int index = linearSearch(arr, n, target);
	displayResult(index);

	return 0;
}