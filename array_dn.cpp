#include <iostream>
using namespace std;
// binary search, heap sort

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

int main() {
    int ar[] = {23, 20, 15, 25, 13, 8, 18};
    int num = 20;
    int arsize = sizeof(ar) / sizeof(ar[0]);
    int found = binarysearch(ar, num, 0, arsize - 1);
    if (found == -1){
        cout << num << " is not found is array.";
    }
    else {
        cout << num << " is located at index " << found;
    }
}