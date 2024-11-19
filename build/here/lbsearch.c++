#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib> // For rand and srand
#include <ctime> // For time
using namespace std;
using namespace std::chrono;
// Linear Search Function
int linearSearch(const vector<int>& arr, int target) {
for (int i = 0; i < arr.size(); i++) {
 if (arr[i] == target) {
 return i;
 }
}
return -1;
}
// Binary Search Function
int binarySearch(const vector<int>& arr, int target) {
int low = 0, high = arr.size() - 1;
while (low <= high) {
 int mid = low + (high - low) / 2;
 if (arr[mid] == target) {
 return mid;
 } else if (arr[mid] < target) {
 low = mid + 1;
 } else {
 high = mid - 1;
 }
}
return -1;
}

int main() {
// Seed the random number generator
srand(static_cast<unsigned>(time(0)));
// Take user input for dataset size and target value
int datasetSize;
cout << "Enter the size of the dataset: ";
cin >> datasetSize;
if (datasetSize <= 0) {
 cerr << "Dataset size must be positive." << endl;
 return 1;
}
int target;
cout << "Enter the target value to search for: ";
cin >> target;
// Generate a large dataset
vector<int> largeDataset;
for (int i = 0; i < datasetSize; i++) {
 largeDataset.push_back(rand() % 10000000 + 1);
}
// Sort the dataset for binary search
vector<int> sortedDataset = largeDataset;
sort(sortedDataset.begin(), sortedDataset.end());
// Measure time for Linear Search
auto start = high_resolution_clock::now();
int linearResult = linearSearch(largeDataset, target);
auto stop = high_resolution_clock::now();
auto linearSearchTime = duration_cast<nanoseconds>(stop - start);
// Measure time for Binary Search
start = high_resolution_clock::now();
int binaryResult = binarySearch(sortedDataset, target);
stop = high_resolution_clock::now();
auto binarySearchTime = duration_cast<nanoseconds>(stop - start);
// Output the results
cout << "Linear Search Time: " << linearSearchTime.count() << " microseconds" <<
endl;
cout << "Binary Search Time: " << binarySearchTime.count() << " microseconds" <<
endl;
return 0;
}
