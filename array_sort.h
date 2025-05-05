#include "helper.h"
#include <iostream>

using namespace std;

class Array_Sort
{
public:
    // ----------- Function Prototypes ----------
    void mergeSort(BothBucket&);
    void mergeSort(FrequencyBucket&);
private:
    void mergeSort(Both*, int, int);
    void mergeSort(Frequency*, int, int);
    void merge(Both*, int, int, int);
    void merge(Frequency*, int, int, int);
public:
    void insertionSort(BothBucket&);
    void insertionSort(FrequencyBucket&);
    void heapSort(BothBucket&);
    void heapSort(FrequencyBucket&);
private:
    void heapify(BothBucket&, int, int);
    void heapify(FrequencyBucket&, int, int);
public:
    void quickSort(BothBucket&);
    void quickSort(FrequencyBucket&);
private:
    void quickSort(Both*, int, int);
    void quickSort(Frequency*, int, int);
    int partition(Both*, int, int);
    int partition(Frequency*, int, int);
    // ------------------------------------------  
};  

/* Merge Sort Implementation - Array
- Time Complexity: O(n log n)
- Space Complexity: O(n)
*/
void Array_Sort::mergeSort(BothBucket& bucket)
{
    mergeSort(bucket.data, 0, bucket.size - 1);
}
void Array_Sort::mergeSort(FrequencyBucket& bucket)
{
    mergeSort(bucket.data, 0, bucket.size - 1);
}

void Array_Sort::mergeSort(Both* arr, int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int mid = left + (right - left) / 2;
    
    // Recursively sort both halves
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    
    // Merge the sorted halves
    merge(arr, left, mid, right);
}
void Array_Sort::mergeSort(Frequency* arr, int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int mid = left + (right - left) / 2;
    
    // Recursively sort both halves
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    
    // Merge the sorted halves
    merge(arr, left, mid, right);
}

// Merge two sorted arrays
void Array_Sort::merge(Both* arr, int left, int mid, int right)
{
    // Create temporary arrays
    int sizeLeft = mid - left + 1;
    int sizeRight = right - mid;
    
    Both* leftArr = new Both[sizeLeft];
    Both* rightArr = new Both[sizeRight];
    
    // Copy data to temporary arrays
    for (int i = 0; i < sizeLeft; i++)
    {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < sizeRight; i++)
    {
        rightArr[i] = arr[mid + 1 + i];
    }
    
    int i = 0, j = 0, k = left; // Merge the temporary arrays back
    
    while (i < sizeLeft && j < sizeRight)
    {
        if (Helper::compareDate(leftArr[i].date, rightArr[j].date))  // Compare by date
        {
            arr[k++] = rightArr[j++];  // rightArr date is later
        }
        else
        {
            arr[k++] = leftArr[i++];   // leftArr date is later
        }
    }
    
    // Copy remaining elements
    while (i < sizeLeft)
    {
        arr[k++] = leftArr[i++];
    }
    while (j < sizeRight)
    {
        arr[k++] = rightArr[j++];
    }
    
    // Free temporary arrays
    delete[] leftArr;
    delete[] rightArr;
}
void Array_Sort::merge(Frequency* arr, int left, int mid, int right)
{
    // Create temporary arrays
    int sizeLeft = mid - left + 1;
    int sizeRight = right - mid;
    
    Frequency* leftArr = new Frequency[sizeLeft];
    Frequency* rightArr = new Frequency[sizeRight];
    
    // Copy data to temporary arrays
    for (int i = 0; i < sizeLeft; i++)
    {
        leftArr[i] = arr[left + i];
    }
    for (int i = 0; i < sizeRight; i++)
    {
        rightArr[i] = arr[mid + 1 + i];
    }
    
    int i = 0, j = 0, k = left; // Merge the temporary arrays back
    
    while (i < sizeLeft && j < sizeRight)
    {           
        if (leftArr[i].count < rightArr[j].count)  // Compare by count
        {
            arr[k++] = rightArr[j++];  // rightArr is bigger
        }
        else
        {
            arr[k++] = leftArr[i++];   // leftArr is bigger
        }
    }
    
    // Copy remaining elements
    while (i < sizeLeft)
    {
        arr[k++] = leftArr[i++];
    }
    while (j < sizeRight)
    {
        arr[k++] = rightArr[j++];
    }
    
    // Free temporary arrays
    delete[] leftArr;
    delete[] rightArr;
}

/* Insertion Sort Implementation - Array
- Time Complexity: O(n) [Best Case], O(n²) [Worst Case]
- Space Complexity: O(1)
*/
void Array_Sort::insertionSort(BothBucket& bucket) 
{
    int n = bucket.size;
    if (n <= 1)
    {
        return;  // Array is already sorted or empty
    }
    
    // Temporary array to store comparison results
    bool* isNewer = new bool[n];
    
    for (int i = 1; i < n; i++) 
    {
        Both key = bucket.data[i];
        int j = i - 1;
        
        // Cache comparison results for adjacent elements
        while (j >= 0) 
        {
            if (!isNewer[j]) 
            {  // If not cached
                isNewer[j] = Helper::compareDate(bucket.data[j].date, key.date);
            }
            if (isNewer[j]) break;
            
            bucket.data[j + 1] = bucket.data[j];
            j--;
        }
        
        bucket.data[j + 1] = key;
    }
    
    delete[] isNewer;
}
void Array_Sort::insertionSort(FrequencyBucket& bucket)
{
    int n = bucket.size;
    
    for (int i = 1; i < n; i++)
    {
        Frequency key = bucket.data[i];
        int j = i - 1;
        
        // Compare based on type, for Frequency elements, compare by count (higher count comes first)
        while (j >= 0 && (key.count > bucket.data[j].count))
        {
            bucket.data[j + 1] = bucket.data[j];
            j--;
        }
        
        bucket.data[j + 1] = key;
    }
}

/* Heap Sort Implementation - Array
- Time Complexity: O(n log(n))
- Space Complexity: O(1)
*/
void Array_Sort::heapSort(BothBucket& bucket) 
{
    // Build max heap for newest dates first
    for (int i = bucket.size / 2 - 1; i >= 0; i--) {
        heapify(bucket, bucket.size, i);
    }

    // Heap sort
    for (int i = bucket.size - 1; i > 0; i--) {
        // Swap root (newest date) with the last element
        swap(bucket.data[0], bucket.data[i]);
        // Call heapify on the reduced heap
        heapify(bucket, i, 0);
    }
}
void Array_Sort::heapSort(FrequencyBucket& bucket) 
{
    // Build max heap based on frequency counts
    for (int i = bucket.size / 2 - 1; i >= 0; i--) 
    {
        heapify(bucket, bucket.size, i);
    }

    // Heap sort
    for (int i = bucket.size - 1; i > 0; i--) {
        // Swap root (highest frequency) with the last element
        swap(bucket.data[0], bucket.data[i]);
        // Call heapify on the reduced heap
        heapify(bucket, i, 0);
    }
}

void Array_Sort::heapify(BothBucket& bucket, int size, int i) 
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Compare based on date (descending order)
    // Note the reversed comparison: we want newer dates to be "larger"
    // So if left.date is newer than largest.date, largest should become left
    if (left < size && Helper::compareDate(bucket.data[left].date, bucket.data[largest].date)) 
    {
        largest = left;
    }
    if (right < size && Helper::compareDate(bucket.data[right].date, bucket.data[largest].date)) 
    {
        largest = right;
    }
    
    if (largest != i) 
    {
        swap(bucket.data[i], bucket.data[largest]);
        heapify(bucket, size, largest);
    }
}
void Array_Sort::heapify(FrequencyBucket& bucket, int size, int i) 
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Compare based on count (max heap for descending order)
    if (left < size && bucket.data[left].count < bucket.data[largest].count) 
    {
        largest = left;
    }
    if (right < size && bucket.data[right].count < bucket.data[largest].count) 
    {
        largest = right;
    }
    
    if (largest != i) 
    {
        swap(bucket.data[i], bucket.data[largest]);
        heapify(bucket, size, largest);
    }
}

/* Quick Sort Implementation - Array
- Time Complexity: O(n*log(n)) [Best Case], O(n²) [Worst Case]
- Space Complexity: O(log(n)) [Best Case], O(n) [Worst Case]
*/    
void Array_Sort::quickSort(BothBucket& bucket)
{
    quickSort(bucket.data, 0, bucket.size - 1);
}
void Array_Sort::quickSort(FrequencyBucket& bucket)
{
    quickSort(bucket.data, 0, bucket.size - 1);
}

void Array_Sort::quickSort(Both* arr, int low, int high)
{
    if (low < high)
    {
        // Partition the array and get pivot index
        int pivotIndex = partition(arr, low, high);
        
        // Recursively sort elements before and after partition
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}
void Array_Sort::quickSort(Frequency* arr, int low, int high)
{
    if (low < high)
    {
        // Partition the array and get pivot index
        int pivotIndex = partition(arr, low, high);
        
        // Recursively sort elements before and after partition
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

int Array_Sort::partition(Both* arr, int low, int high)
{
    // Choose rightmost element as pivot
    Both pivot = arr[high];
    int i = low - 1;  // Index of smaller element
    
    for (int j = low; j < high; j++)
    {           
        // If current element is bigger than pivot
        if (Helper::compareDate(pivot.date, arr[j].date))  // Compare by date
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    // Place pivot in its correct position
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
int Array_Sort::partition(Frequency* arr, int low, int high)
{
    // Choose rightmost element as pivot
    Frequency pivot = arr[high];
    int i = low - 1;  // Index of smaller element
    
    for (int j = low; j < high; j++)
    {           
        // If current element is bigger than pivot
        if (arr[j].count > pivot.count) // Compare by count (descending)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    // Place pivot in its correct position
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
