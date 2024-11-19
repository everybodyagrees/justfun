#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

// Recursive function to perform insertion sort
void recursiveInsertionSort(int arr[], int n) {
    // Base case: Array of size 1 is sorted
    if (n <= 1)
        return;

    // Sort first n-1 elements
    recursiveInsertionSort(arr, n - 1);

    /* Insert nth element at its correct position
       in sorted array arr[0..n-1] */
    int last = arr[n - 1];
    int j = n - 2;

    // Move elements of arr[0..i-1], that are greater than key,
    // to one position ahead of their current position
    while (j >= 0 && arr[j] > last) {
        arr[j + 1] = arr[j];
        j--;
    }
    arr[j + 1] = last;
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    double best_time = 0.0, worst_time = 0.0, avg_time = 0.0;
    const int num_iterations = 10;

    int best_case[n], worst_case[n], avg_case[n];

    for (int i = 0; i < n; i++) {
        best_case[i] = i;
        worst_case[i] = n - i - 1;
    }

    // Calculate best case time
    clock_t start_time = clock();
    recursiveInsertionSort(best_case, n);
    clock_t end_time = clock();
    best_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Calculate worst case time
    start_time = clock();
    recursiveInsertionSort(worst_case, n);
    end_time = clock();
    worst_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Calculate average case time
    for (int i = 0; i < num_iterations; i++) {
        for (int j = 0; j < n; j++) {
            avg_case[j] = rand() % 100;
        }
        start_time = clock();
        recursiveInsertionSort(avg_case, n);
        end_time = clock();
        avg_time += (double)(end_time - start_time) / CLOCKS_PER_SEC;
    }
    avg_time /= num_iterations;

    // Print the table
    cout << fixed << setprecision(6);
    cout << "\n-----------------------------------------\n";
    cout << "| Case      | Time Taken (seconds) |\n";
    cout << "-----------------------------------------\n";
    cout << "| Best      | " << best_time << " |\n";
    cout << "| Worst     | " << worst_time << " |\n";
    cout << "| Average   | " << avg_time << " |\n";
    cout << "-----------------------------------------\n";

    return 0;
}
