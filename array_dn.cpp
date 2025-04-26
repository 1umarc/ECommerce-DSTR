#include <iostream>
#include <string>
using namespace std;

// HEAP SORT
void heapify(string ar[], int size, int i) {
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

void heapsort(string ar[], int size){
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
int binarysearch(string ar[], const string& str, int first, int last) {
    // repeat until pointers first and last meet each other
    while (first <= last) {
        int mid = first + (last - first) / 2;
        if (str == ar[mid]) {
            return mid; // num is at the middle of array
        }
        else if (str > ar[mid]) {
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
    string ar[] = {"banana", "apple", "grape", "orange", "kiwi", "mango", "cherry"};
    string strToFind = "apple";
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
    int found = binarysearch(ar, strToFind, 0, arsize - 1);
    if (found == -1){
        cout << strToFind << " is not found is array.";
    }
    else {
        cout << strToFind << " is located at index " << found;
    }
}