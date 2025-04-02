#include <iostream>
#include <cstdlib> //randomly pick up number
#include <utility> //swap
using namespace std;

void quicksort(int arr[], int low, int high);
int partition(int arr[], int low, int high);

int main() {

    int arr[] = {13, 16, 3, 6, 8, 11, 2, 20};

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
  
  return 0;
}

void quicksort(int arr[], int low, int high){
    
    if(low < high)
    {
        int pivot_index = partition(arr,low, high); // find the middle number within the array
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
