#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <iomanip>

using namespace std;
using namespace chrono;

void bubbleSortRecursive(int arr[], int n) {
    if (n == 1)
        return;

    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1])
            swap(arr[i], arr[i + 1]);
    }

    bubbleSortRecursive(arr, n - 1);
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Function to generate random arrays
void generateRandomArray(int arr[], int n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 1000);

    for (int i = 0; i < n; ++i) {
        arr[i] = dist(gen);
    }
}

// Function to measure time
double measureTime(void (*sortFunction)(int[], int), int arr[], int n) {
    auto start = high_resolution_clock::now();
    sortFunction(arr, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    return duration.count() / 1000.0; // Convert to milliseconds
}

int main() {
    int n; // Array size
    int arr[n];
    cout << "Enter the number of elements:";
    cin>>n;
    // Best case (already sorted)
    for (int i = 0; i < n; ++i) {
        arr[i] = i;
    }
    double bestTime = measureTime(bubbleSortRecursive, arr, n);

    // Worst case (reverse sorted)
    for (int i = 0; i < n; ++i) {
        arr[i] = n - i;
    }
    double worstTime = measureTime(bubbleSortRecursive, arr, n);

    // Average case (randomly generated)
    generateRandomArray(arr, n);
    double averageTime = measureTime(bubbleSortRecursive, arr, n);


    cout << fixed << setprecision(6);
    cout << "\n-----------------------------------------\n";
    cout << "| Case      | Time Taken  |\n";
    cout << "-----------------------------------------\n";
    cout << "| Best      | " << bestTime << " |\n";
    cout << "| Worst     | " << worstTime << " |\n";
    cout << "| Average   | " << averageTime << " |\n";
    cout << "-----------------------------------------\n";


    return 0;
}
