#include <iostream>
#include <vector>

const int INSERTION_THRESHOLD = 2; // Threshold for switching to insertion sort

// Merge two sorted subarrays into one sorted array
void merge(std::vector<int>& arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<int> leftSubarray(n1);
    std::vector<int> rightSubarray(n2);

    for (int i = 0; i < n1; ++i)
        leftSubarray[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        rightSubarray[j] = arr[middle + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftSubarray[i] <= rightSubarray[j]) {
            arr[k] = leftSubarray[i];
            ++i;
        } else {
            arr[k] = rightSubarray[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = leftSubarray[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = rightSubarray[j];
        ++j;
        ++k;
    }
	for (int i  = 0; i < right; i++)
		std::cout << arr[i] << std::endl;
	std::cout << "\n=====\n";
}

// Insertion sort for small subarrays
void insertionSort(std::vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int key = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }

        arr[j + 1] = key;
    }
}

// Merge-insertion sort function
void mergeInsertionSort(std::vector<int>& arr, int left, int right) {
    if (left >= right)
        return;

    int middle = left + (right - left) / 2;

    if (right - left + 1 <= INSERTION_THRESHOLD) {
        insertionSort(arr, left, right);
    } else {
        mergeInsertionSort(arr, left, middle);
        mergeInsertionSort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

int main() {
    int arr[7] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    std::vector<int> vec(arr, arr + n);

    std::cout << "Original array: ";
    for (int i = 0; i < n; ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    mergeInsertionSort(vec, 0, n - 1);

    std::cout << "Sorted array: ";
    for (int i = 0; i < n; ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}

