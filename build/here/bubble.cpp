#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

void bubbleSort(int arr[], int n) {
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    // Arrays to store times for best, worst, and average cases
    double best_time = 0.0, worst_time = 0.0, avg_time = 0.0;

    // Number of iterations for average case calculation
    const int num_iterations = 10;

    // Best case (already sorted array)
    int best_case[n];
    for (int i = 0; i < n; i++) {
        best_case[i] = i;
    }

    // Worst case (reverse sorted array)
    int worst_case[n];
    for (int i = 0; i < n; i++) {
        worst_case[i] = n - i - 1;
    }

    // Average case (random array)
    int avg_case[n];

    // Calculate best case time
    clock_t start_time = clock();
    bubbleSort(best_case, n);
    clock_t end_time = clock();
    best_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Calculate worst case time
    start_time = clock();
    bubbleSort(worst_case, n);
    end_time = clock();
    worst_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Calculate average case time
    for (int i = 0; i < num_iterations; i++) {
        for (int j = 0; j < n; j++) {
            avg_case[j] = rand() % 100;
        }
        start_time = clock();
        bubbleSort(avg_case, n);
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
