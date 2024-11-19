#include <bits/stdc++.h>

using namespace std;

// Function to perform Selection Sort
     // Function to perform Selection Sort recursively
void selectionSortRecursive(int arr[], int n, int index = 0) {
    // Base case: When index reaches the end of the array
    if (index == n - 1)
        return;

    // Find the minimum element in the unsorted part of the array
    int mini = index;
    for (int j = index + 1; j < n; j++) {
        if (arr[j] < arr[mini]) {
            mini = j;
        }
    }

    // Swap the found minimum element with the first element of the unsorted part
    int temp = arr[mini];
    arr[mini] = arr[index];
    arr[index] = temp;

    // Recursively call the function for the rest of the array
    selectionSortRecursive(arr, n, index + 1);
}



void bestcase(int n, int arr[]);
void worstcase(int n, int arr[]);
void avgcase(int n, int arr[]);
// void printArray(const int arr[], int length);

int main() {
    int length;
int mini;
    srand(static_cast<unsigned>(time(0)));
    cout << "Enter the number of elements in the array: ";
    cin >> length;

    int* a = new int[length];

    // Best Case
    bestcase(length, a);
  //  cout << "\nBest Case array: ";
//    printArray(a, length);
    clock_t startbest = clock();
   selectionSortRecursive(a, length);
    clock_t endbest = clock();
    double durationbest = double(endbest - startbest) / CLOCKS_PER_SEC * 1000;

    // Worst Case
    worstcase(length, a);
   // cout << "\nWorst Case array: ";
   // printArray(a, length);
    clock_t startworst = clock();
    selectionSortRecursive(a, length);
    clock_t endworst = clock();
    double durationworst = double(endworst - startworst) / CLOCKS_PER_SEC * 1000;

    // Average Case
    avgcase(length, a);
   // cout << "\nAverage Case array: ";
   // printArray(a, length);
   clock_t startavg = clock();
    selectionSortRecursive(a, length);
    clock_t endavg = clock();
    double durationavg = double(endavg - startavg) / CLOCKS_PER_SEC * 1000;


     cout << fixed << setprecision(6);
    cout << "\n-----------------------------------------\n";
    cout << "| Case      | Time Taken (ms) |\n";
    cout << "-----------------------------------------\n";
    cout << "| Best      | " << durationbest << " |\n";
    cout << "| Worst     | " <<  durationworst << " |\n";
    cout << "| Average   | " << durationavg << " |\n";
    cout << "-----------------------------------------\n";

    delete[] a;

    return 0;
}

void bestcase(int n, int arr[]) {
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
}

void worstcase(int n, int arr[]) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

void avgcase(int n, int arr[]) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % n;
    }
}

//void printArray(const int arr[], int length) {
  //  for (int i = 0; i < length; i++) {
    //    cout << arr[i] << " ";
   // }
   // cout << endl;
//}
