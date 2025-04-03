#include <iostream>
#include <cstdlib> //randomly pick up number
#include <utility> //swap
#include <cmath>
using namespace std;

/////////////// QUICKSORT /////////////////

void quicksort(int arr[], int low, int high);
int partition(int arr[], int low, int high);

/////////////// JUMPSEARCH /////////////////
int jumpSearch(int arr[], int n, int target);

int main() {

    int arr[] = {13, 16, 3, 6, 8, 11, 2, 20};
    int target = 11;

    // Calculate the size of the array
    int size_of_array = sizeof(arr) / sizeof(arr[0]); 


    // Printing Original Array
    cout << "Original array :" ; 
    for (int a =0; a<size_of_array ; a++)
    {
        cout <<  arr[a] << " ";
    }

    quicksort(arr, 0, size_of_array - 1);

  // Loop through and output the array elements to check the array is sorted
  cout << "\nSorted array: ";
  for (int b = 0; b < size_of_array ; b++)
  {
    cout << arr[b] << " ";
  }


  /////////////// JUMPSEARCH /////////////////
  int result = jumpSearch(arr, size_of_array, target);
    if (result != -1) {
        cout << "\nElement " << target << " found at index " << result << endl;
    } else {
        cout << "\nElement " << target << " not found in the array" << endl;
    }

  
  return 0;
}

void quicksort(int arr[], int low, int high){
    
    if(low < high)
    {
        int pivot_index = partition(arr,low, high); // // Partition the array and get the pivot's final index
        quicksort(arr,low, pivot_index-1); // sort the left side of the middle number
        quicksort(arr,pivot_index+1,high); // sort the right side of the middle number
    }
}

int partition(int arr[], int low, int high) {
    // Use the last element as the pivot
    int pivot = arr[high];
    int i = low - 1; // Pointer for the smaller element

    for (int j = low; j < high; j++) {
        // If the current element is smaller than or equal to the pivot
        if (arr[j] <= pivot) {
            i++; // Increment the index of the smaller element
            swap(arr[i], arr[j]); // Swap elements
        }
    }
    swap(arr[i + 1], arr[high]); // Place the pivot in the correct position
    return i + 1; // Return the index of the pivot
}

///////////// JUMP SEARCH ///////////////
int jumpSearch(int arr[], int n, int target) {
    int jump = sqrt(n);  // Calculate the optimal jump size
    int prev = 0;

    // Finding the block where the element is present
    while (arr[min(jump, n) - 1] < target) {
        prev = jump;
        jump = jump + sqrt(n);
        if (prev >= n) {
            return -1;  // If we have reached the end of the array
        }
    }

    // Linear search within the block
    for (int i = prev; i < min(jump, n); i++) {
        if (arr[i] == target) {
            return i;  // Return the index of the target element
        }
    }

    return -1;  // Target not found
}