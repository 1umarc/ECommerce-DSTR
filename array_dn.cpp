#include <iostream>
using namespace std;

// HEAP SORT
void heapify(int ar[], int size, int i) {
    // find largest number between root, left child, and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && ar[left] > ar[largest]) {
        largest = left;
    }
    if (right < size && ar[right] > ar[largest]) {
        largest = right;
    }
    // swap and continue heapify if root is not largest
    if (largest != i) {
        swap(ar[i], ar[largest]);
        heapify(ar, size, largest);
    }
}

void heapsort(int ar[], int size){
    // build max heap
    for(int i = size / 2 - 1; i >= 0; i--){
        heapify(ar, size, i);
    }

    // heap sort
    for(int i = size - 1; i >= 0; i--){
        swap(ar[0], ar[i]);

        // heapify root element to obtain highest element at root again
        heapify(ar, i, 0);
    }
}

// BINARY SEARCH
int binarysearch(int ar[], int num, int first, int last) {
    // repeat until pointers first and last meet each other
    while (first <= last) {
        int mid = first + (last - first) / 2;
        if (num == ar[mid]) {
            return mid; // num is at the middle of array
        }
        else if (num > ar[mid]) {
            first = mid + 1; // num is at the right side of mid
        }
        else {
            last = mid - 1; // num is at the left side of mid
        }
    }
    return -1; // num is not found in array
}

// MAIN CODE
int main() {
    int ar[] = {23, 20, 15, 25, 13, 8, 18};
    int num = 20;
    int arsize = sizeof(ar) / sizeof(ar[0]);
    
    // sort the array
    heapsort(ar, arsize);

    // display the sorted array
    cout << "Result of sorted array: ";
    for (int i = 0; i < arsize; ++i){
        cout << ar[i] << " ";
    }
    cout << "\n";

    // search for num
    int found = binarysearch(ar, num, 0, arsize - 1);
    if (found == -1){
        cout << num << " is not found is array.";
    }
    else {
        cout << num << " is located at index " << found;
    }
}