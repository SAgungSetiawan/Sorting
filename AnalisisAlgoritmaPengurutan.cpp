#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>

using namespace std;
using namespace std::chrono;

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(arr[min_idx], arr[i]);
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void generateRandomArray(int arr[], int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000);
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
}

void generateSortedArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }
}

void generateReverseSortedArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = size - i;
    }
}

int main() {
    int n;
    cout << "Masukkan ukuran array: ";
    cin >> n;

    int choice;
    cout << "Pilih jenis data:\n";
    cout << "1. Acak\n";
    cout << "2. Terurut\n";
    cout << "3. Terurut Terbalik\n";
    cin >> choice;

    int* arr = new int[n];

    switch (choice) {
        case 1:
            generateRandomArray(arr, n);
            break;
        case 2:
            generateSortedArray(arr, n);
            break;
        case 3:
            generateReverseSortedArray(arr, n);
            break;
        default:
            cout << "Pilihan tidak valid.\n";
            return 1;
    }

    int* bubbleArr = new int[n];
    int* insertionArr = new int[n];
    int* selectionArr = new int[n];
    int* mergeArr = new int[n];
    int* quickArr = new int[n];

    // Copy arrays
    copy(arr, arr + n, bubbleArr);
    copy(arr, arr + n, insertionArr);
    copy(arr, arr + n, selectionArr);
    copy(arr, arr + n, mergeArr);
    copy(arr, arr + n, quickArr);

     // Bubble Sort
    auto start = high_resolution_clock::now();
    bubbleSort(bubbleArr, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Bubble Sort: ";
    printArray(bubbleArr, n);
    cout << "Time: " << duration.count() << " microseconds" << endl;
    cout << endl;

     // Insertion Sort
    start = high_resolution_clock::now();
    insertionSort(insertionArr, n);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Insertion Sort: ";
    printArray(insertionArr, n);
    cout << "Time: " << duration.count() << " microseconds" << endl;
    cout << endl;
    
    // Selection Sort
    start = high_resolution_clock::now();
    selectionSort(selectionArr, n);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Selection Sort: ";
    printArray(selectionArr, n);
    cout << "Time: " << duration.count() << " microseconds" << endl;
    cout << endl;
    
    // Merge Sort
    start = high_resolution_clock::now();
    mergeSort(mergeArr, 0, n - 1);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Merge Sort: ";
    printArray(mergeArr, n);
    cout << "Time: " << duration.count() << " microseconds" << endl;
    cout << endl;
    
    // Quick Sort
    start = high_resolution_clock::now();
    quickSort(quickArr, 0, n - 1);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Quick Sort: ";
    printArray(quickArr, n);
    cout << "Time: " << duration.count() << " microseconds" << endl;
    cout << endl;
    
    delete[] arr;
    delete[] bubbleArr;
    delete[] insertionArr;
    delete[] selectionArr;
    delete[] mergeArr;
    delete[] quickArr;

    return 0;
}

