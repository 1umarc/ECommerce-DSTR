// #include "helper.h"
// #include <iostream>
// #include <cmath>

// using namespace std;

// class LinkedList_Sort
// {
// public:
//     void mergeSort(Both*& head);
//     void mergeSort(Frequency*& head);
// private:
//     Both* split(Both* head);
//     Frequency* split(Frequency* head);
//     Both* merge(Both* left, Both* right);
//     Frequency* merge(Frequency* left, Frequency* right);
// public:
//     void insertionSort(Both*& head);
//     void insertionSort(Frequency*& head);
//     void bubbleSort(Both*& head);
//     void bubbleSort(Frequency*& head);
//     void selectionSort(Both*& head);
//     void selectionSort(Frequency*& head);
// };

// /* Merge Sort Implementation - Linked List
// - Time Complexity: O(n log n)
// - Space Complexity: O(n)
// */
// void LinkedList_Sort::mergeSort(Both*& head)
// {
//     // Base case - empty list or list with only one node
//     if (head == nullptr || head->next == nullptr)
//     {
//         return;
//     }

//     // Split the list into two halves
//     Both* secondHalf = split(head);

//     // Recursively sort both halves
//     mergeSort(head);
//     mergeSort(secondHalf);

//     // Merge the sorted halves
//     head = merge(head, secondHalf);
// }
// void LinkedList_Sort::mergeSort(Frequency*& head)
// {
//     // Base case - empty list or list with only one node
//     if (head == nullptr || head->next == nullptr)
//     {
//         return;
//     }

//     // Split the list into two halves
//     Frequency* secondHalf = split(head);

//     // Recursively sort both halves
//     mergeSort(head);
//     mergeSort(secondHalf);

//     // Merge the sorted halves
//     head = merge(head, secondHalf);
// }

// // Split the linked list into two halves
// Both* LinkedList_Sort::split(Both* head)
// {
//     if (head == nullptr || head->next == nullptr)
//     {
//         return nullptr;
//     }
    
//     // Using slow and fast pointers to find the middle
//     Both* slow = head;
//     Both* fast = head->next;

//     while (fast != nullptr && fast->next != nullptr)
//     {
//         slow = slow->next;
//         fast = fast->next->next;
//     }

//     Both* middle = slow->next;
//     slow->next = nullptr;
//     return middle;
// }
// Frequency* LinkedList_Sort::split(Frequency* head)
// {
//     if (head == nullptr || head->next == nullptr)
//     {
//         return nullptr;
//     }
    
//     // Using slow and fast pointers to find the middle
//     Frequency* slow = head;
//     Frequency* fast = head->next;

//     while (fast != nullptr && fast->next != nullptr)
//     {
//         slow = slow->next;
//         fast = fast->next->next;
//     }

//     Frequency* middle = slow->next;
//     slow->next = nullptr;
//     return middle;
// }

// // Merge two sorted Linked Lists
// Both* LinkedList_Sort::merge(Both* first, Both* second)
// {
//     if (first == nullptr)
//     {
//         return second;
//     }
//     if (second == nullptr)
//     {
//         return first;
//     }

//     Both* result = nullptr;
//     if (Helper::compareDate(first->date, second->date))
//     {
//         // second value is later
//         result = second;
//         result->next = merge(first, second->next);
//     }
//     else
//     {
//         // first value is later
//         result = first;
//         result->next = merge(first->next, second);
//     }
//     return result;
// }
// Frequency* LinkedList_Sort::merge(Frequency* first, Frequency* second)
// {
//     if (first == nullptr)
//     {
//         return second;
//     }
//     if (second == nullptr)
//     {
//         return first;
//     }

//     Frequency* result = nullptr;
//     if (first->count < second->count)
//     {
//         // second value is bigger
//         result = second;
//         result->next = merge(first, second->next);
//     }
//     else
//     {
//         // first value is bigger
//         result = first;
//         result->next = merge(first->next, second);
//     }
//     return result;
// }

// /* Insertion Sort Implementation - Linked List
// - Time Complexity: O(n) [Best Case], O(n²) [Average & Worst Case]
// - Space Complexity: O(1)
// */
// void LinkedList_Sort::insertionSort(Both*& head)
// {
//     // Base case - empty list or list with only one node
//     if (head == nullptr || head->next == nullptr)
//     {
//         return;
//     }

//     Both* sorted = nullptr;  // Initialize sorted linked list
//     Both* current = head;    // Current node to be inserted

//     // Traverse the original list
//     while (current != nullptr)
//     {
//         // Store next for next iteration
//         Both* next = current->next;

//         // Insert current in sorted linked list
//         if (sorted == nullptr || Helper::compareDate(sorted->date, current->date))
//         {
//             // Insert at beginning
//             current->next = sorted;
//             sorted = current;
//         }
//         else
//         {
//             // Locate node before point of insertion
//             Both* temp = sorted;
//             // For Both nodes, compare by date
//             while (temp->next != nullptr && !Helper::compareDate(temp->next->date , current->date))
//             {
//                 temp = temp->next;
//             }
//             current->next = temp->next;
//             temp->next = current;
//         }
//         current = next;  // Move to next node
//     }
//     head = sorted;  // Update head to point to sorted list
// }
// void LinkedList_Sort::insertionSort(Frequency*& head)
// {
//     // Base case - empty list or list with only one node
//     if (head == nullptr || head->next == nullptr)
//     {
//         return;
//     }

//     Frequency* sorted = nullptr;  // Initialize sorted linked list
//     Frequency* current = head;    // Current node to be inserted

//     // Traverse the original list
//     while (current != nullptr)
//     {
//         // Store next for next iteration
//         Frequency* next = current->next;

//         // Insert current in sorted linked list
//         if (sorted == nullptr || (sorted->count < current->count))
//         {
//             // Insert at beginning
//             current->next = sorted;
//             sorted = current;
//         }
//         else
//         {
//             // Locate node before point of insertion
//             Frequency* temp = sorted;
//             // For Frequency nodes, compare by count (higher count comes first)
//             while (temp->next != nullptr && !(temp->next->count < current->count))
//             {
//                 temp = temp->next;
//             }
//             current->next = temp->next;
//             temp->next = current;
//         }
//         current = next;  // Move to next node
//     }
//     head = sorted;  // Update head to point to sorted list
// }

// /* Bubble Sort Implementation - Linked List
// - Time Complexity: O(n) [Best Case], O(n²) [Average & Worst Case]
// - Space Complexity: O(1)
// */  
// void LinkedList_Sort::bubbleSort(Both*& head)
// {
//     if (head == nullptr || head->next == nullptr)
//     {
//         return; // Empty or single-node list
//     }

//     bool swapped;
//     do 
//     {
//         swapped = false;
//         Both* current = head;
//         Both* nextNode = head->next;

//         while (nextNode) 
//         {
//             // Compare dates: if current is older than next, swap
//             if (Helper::compareDate(current->date, nextNode->date)) 
//             {
//                 // Swap Both node data
//                 swap(current->customerID, nextNode->customerID);
//                 swap(current->productID, nextNode->productID);
//                 swap(current->category, nextNode->category);
//                 swap(current->price, nextNode->price);
//                 swap(current->date, nextNode->date);
//                 swap(current->paymentMethod, nextNode->paymentMethod);
//                 swap(current->productID, nextNode->productID);
//                 swap(current->rating, nextNode->rating);
//                 swap(current->reviewText, nextNode->reviewText);
//                 swapped = true;
//             }
//             current = nextNode;
//             nextNode = nextNode->next;
//         }
//     } while (swapped);
// }
// void LinkedList_Sort::bubbleSort(Frequency*& head)
// {
//     if (head == nullptr || head->next == nullptr) return; // Empty or single-node list

//     bool swapped;
//     do {
//         swapped = false;
//         Frequency* current = head;
//         Frequency* nextNode = head->next;

//         while (nextNode) 
//         {
//             // For frequency nodes, sort by count in ascending order
//             if (current->count < nextNode->count) 
//             {
//                 swap(current->text, nextNode->text);
//                 swap(current->count, nextNode->count);
//                 swapped = true;
//             }
//             current = nextNode;
//             nextNode = nextNode->next;
//         }
//     } while (swapped);
// }

// /* Selection Sort Implementation - Linked List
// - Time Complexity: O(n) [Best Case], O(n²) [Average & Worst Case]
// - Space Complexity: O(1)
// */
// void LinkedList_Sort::selectionSort(Both*& head)
// {
//     // Base case - empty list or list with only one node
//     if (head == nullptr || head->next == nullptr)
//     {
//         return;
//     }

//     Both* current = head;
    
//     // Traverse the list
//     while (current != nullptr)
//     {
//         Both* minNode = current;
//         Both* temp = current->next;
        
//         // Find the minimum node in the unsorted part
//         while (temp != nullptr)
//         {
//             if (Helper::compareDate(minNode->date, temp->date)) // Compare by date
//             {
//                 // If temp node value is smaller or later date
//                 minNode = temp;
//             }
//             temp = temp->next;
//         }
        
//         // Swap data if minNode is not the current node
//         if (minNode != current)
//         {
//             // Swap all fields
//             swap(current->customerID, minNode->customerID);
//             swap(current->product, minNode->product);
//             swap(current->category, minNode->category);
//             swap(current->price, minNode->price);
//             swap(current->date, minNode->date);
//             swap(current->paymentMethod, minNode->paymentMethod);
//             swap(current->productID, minNode->productID);
//             swap(current->rating, minNode->rating);
//             swap(current->reviewText, minNode->reviewText);
//         } 
//         current = current->next;
//     }
// }
// void LinkedList_Sort::selectionSort(Frequency*& head)
// {
//     // Base case - empty list or list with only one node
//     if (head == nullptr || head->next == nullptr)
//     {
//         return;
//     }

//     Frequency* current = head;
    
//     // Traverse the list
//     while (current != nullptr)
//     {
//         Frequency* minNode = current;
//         Frequency* temp = current->next;
        
//         // Find the minimum node in the unsorted part
//         while (temp != nullptr)
//         {
//             if (minNode->count < temp->count) // Compare by count (descending)
//             {
//                 // If temp node value is smaller or later date
//                 minNode = temp;
//             }
//             temp = temp->next;
//         }
        
//         // Swap data if minNode is not the current node
//         if (minNode != current)
//         {
//             swap(current->text, minNode->text);
//             swap(current->count, minNode->count);
//         } 
//         current = current->next;
//     }
// }


// class Array_Sort
// {
// public:
//     // ----------- Function Prototypes ----------
//     void mergeSort(BothBucket&);
//     void mergeSort(FrequencyBucket&);
// private:
//     void mergeSort(Both*, int, int);
//     void mergeSort(Frequency*, int, int);
//     void merge(Both*, int, int, int);
//     void merge(Frequency*, int, int, int);
// public:
//     void insertionSort(BothBucket&);
//     void insertionSort(FrequencyBucket&);
//     void heapSort(BothBucket&);
//     void heapSort(FrequencyBucket&);
// private:
//     void heapify(BothBucket&, int, int);
//     void heapify(FrequencyBucket&, int, int);
// public:
//     void quickSort(BothBucket&);
//     void quickSort(FrequencyBucket&);
// private:
//     void quickSort(Both*, int, int);
//     void quickSort(Frequency*, int, int);
//     int partition(Both*, int, int);
//     int partition(Frequency*, int, int);
//     // ------------------------------------------  
// };  

// /* Merge Sort Implementation - Array
// - Time Complexity: O(n log n)
// - Space Complexity: O(n)
// */
// void Array_Sort::mergeSort(BothBucket& bucket)
// {
//     mergeSort(bucket.data, 0, bucket.size - 1);
// }
// void Array_Sort::mergeSort(FrequencyBucket& bucket)
// {
//     mergeSort(bucket.data, 0, bucket.size - 1);
// }

// void Array_Sort::mergeSort(Both* arr, int left, int right)
// {
//     if (left >= right)
//     {
//         return;
//     }

//     int mid = left + (right - left) / 2;
    
//     // Recursively sort both halves
//     mergeSort(arr, left, mid);
//     mergeSort(arr, mid + 1, right);
    
//     // Merge the sorted halves
//     merge(arr, left, mid, right);
// }
// void Array_Sort::mergeSort(Frequency* arr, int left, int right)
// {
//     if (left >= right)
//     {
//         return;
//     }

//     int mid = left + (right - left) / 2;
    
//     // Recursively sort both halves
//     mergeSort(arr, left, mid);
//     mergeSort(arr, mid + 1, right);
    
//     // Merge the sorted halves
//     merge(arr, left, mid, right);
// }

// // Merge two sorted arrays
// void Array_Sort::merge(Both* arr, int left, int mid, int right)
// {
//     // Create temporary arrays
//     int sizeLeft = mid - left + 1;
//     int sizeRight = right - mid;
    
//     Both* leftArr = new Both[sizeLeft];
//     Both* rightArr = new Both[sizeRight];
    
//     // Copy data to temporary arrays
//     for (int i = 0; i < sizeLeft; i++)
//     {
//         leftArr[i] = arr[left + i];
//     }
//     for (int i = 0; i < sizeRight; i++)
//     {
//         rightArr[i] = arr[mid + 1 + i];
//     }
    
//     int i = 0, j = 0, k = left; // Merge the temporary arrays back
    
//     while (i < sizeLeft && j < sizeRight)
//     {
//         if (Helper::compareDate(leftArr[i].date, rightArr[j].date))  // Compare by date
//         {
//             arr[k++] = rightArr[j++];  // rightArr date is later
//         }
//         else
//         {
//             arr[k++] = leftArr[i++];   // leftArr date is later
//         }
//     }
    
//     // Copy remaining elements
//     while (i < sizeLeft)
//     {
//         arr[k++] = leftArr[i++];
//     }
//     while (j < sizeRight)
//     {
//         arr[k++] = rightArr[j++];
//     }
    
//     // Free temporary arrays
//     delete[] leftArr;
//     delete[] rightArr;
// }
// void merge(Frequency* arr, int left, int mid, int right)
// {
//     // Create temporary arrays
//     int sizeLeft = mid - left + 1;
//     int sizeRight = right - mid;
    
//     Frequency* leftArr = new Frequency[sizeLeft];
//     Frequency* rightArr = new Frequency[sizeRight];
    
//     // Copy data to temporary arrays
//     for (int i = 0; i < sizeLeft; i++)
//     {
//         leftArr[i] = arr[left + i];
//     }
//     for (int i = 0; i < sizeRight; i++)
//     {
//         rightArr[i] = arr[mid + 1 + i];
//     }
    
//     int i = 0, j = 0, k = left; // Merge the temporary arrays back
    
//     while (i < sizeLeft && j < sizeRight)
//     {           
//         if (leftArr[i].count < rightArr[j].count)  // Compare by count
//         {
//             arr[k++] = rightArr[j++];  // rightArr is bigger
//         }
//         else
//         {
//             arr[k++] = leftArr[i++];   // leftArr is bigger
//         }
//     }
    
//     // Copy remaining elements
//     while (i < sizeLeft)
//     {
//         arr[k++] = leftArr[i++];
//     }
//     while (j < sizeRight)
//     {
//         arr[k++] = rightArr[j++];
//     }
    
//     // Free temporary arrays
//     delete[] leftArr;
//     delete[] rightArr;
// }

// /* Insertion Sort Implementation - Array
// - Time Complexity: O(n) [Best Case], O(n²) [Average & Worst Case]
// - Space Complexity: O(1)
// */
// void Array_Sort::insertionSort(BothBucket& bucket)
// {
//     int n = bucket.size;
    
//     for (int i = 1; i < n; i++)
//     {
//         Both key = bucket.data[i];
//         int j = i - 1;
        
//         // Compare based on type, for Both elements, compare by date
//         while (j >= 0 && !Helper::compareDate(key.date, bucket.data[j].date))
//         {
//             bucket.data[j + 1] = bucket.data[j];
//             j--;
//         }
        
//         bucket.data[j + 1] = key;
//     }
// }
// void insertionSort(FrequencyBucket& bucket)
// {
//     int n = bucket.size;
    
//     for (int i = 1; i < n; i++)
//     {
//         Frequency key = bucket.data[i];
//         int j = i - 1;
        
//         // Compare based on type, for Frequency elements, compare by count (higher count comes first)
//         while (j >= 0 && (key.count > bucket.data[j].count))
//         {
//             bucket.data[j + 1] = bucket.data[j];
//             j--;
//         }
        
//         bucket.data[j + 1] = key;
//     }
// }

// /* Heap Sort Implementation - Array
// - Time Complexity: O(n) [Best Case], O(n*log(n)) [Average & Worst Case]
// - Space Complexity: O(1)
// */
// void Array_Sort::heapSort(BothBucket& bucket) 
// {
//     // Build max heap for newest dates first
//     for (int i = bucket.size / 2 - 1; i >= 0; i--) {
//         heapify(bucket, bucket.size, i);
//     }

//     // Heap sort
//     for (int i = bucket.size - 1; i > 0; i--) {
//         // Swap root (newest date) with the last element
//         swap(bucket.data[0], bucket.data[i]);
//         // Call heapify on the reduced heap
//         heapify(bucket, i, 0);
//     }
// }
// void Array_Sort::heapSort(FrequencyBucket& bucket) 
// {
//     // Build max heap based on frequency counts
//     for (int i = bucket.size / 2 - 1; i >= 0; i--) 
//     {
//         heapify(bucket, bucket.size, i);
//     }

//     // Heap sort
//     for (int i = bucket.size - 1; i > 0; i--) {
//         // Swap root (highest frequency) with the last element
//         swap(bucket.data[0], bucket.data[i]);
//         // Call heapify on the reduced heap
//         heapify(bucket, i, 0);
//     }
// }

// void Array_Sort::heapify(BothBucket& bucket, int size, int i) 
// {
//     int largest = i;
//     int left = 2 * i + 1;
//     int right = 2 * i + 2;

//     // Compare based on date (descending order)
//     // Note the reversed comparison: we want newer dates to be "larger"
//     // So if left.date is newer than largest.date, largest should become left
//     if (left < size && Helper::compareDate(bucket.data[left].date, bucket.data[largest].date)) 
//     {
//         largest = left;
//     }
//     if (right < size && Helper::compareDate(bucket.data[right].date, bucket.data[largest].date)) 
//     {
//         largest = right;
//     }
    
//     if (largest != i) 
//     {
//         swap(bucket.data[i], bucket.data[largest]);
//         heapify(bucket, size, largest);
//     }
// }
// void Array_Sort::heapify(FrequencyBucket& bucket, int size, int i) 
// {
//     int largest = i;
//     int left = 2 * i + 1;
//     int right = 2 * i + 2;

//     // Compare based on count (max heap for descending order)
//     if (left < size && bucket.data[left].count < bucket.data[largest].count) 
//     {
//         largest = left;
//     }
//     if (right < size && bucket.data[right].count < bucket.data[largest].count) 
//     {
//         largest = right;
//     }
    
//     if (largest != i) 
//     {
//         swap(bucket.data[i], bucket.data[largest]);
//         heapify(bucket, size, largest);
//     }
// }

// /* Quick Sort Implementation - Array
// - Time Complexity: O(n*log(n)) [Best Case], O(n*log(n)) [Average & Worst Case]
// - Space Complexity: O(log(n))
// */    
// void Array_Sort::quickSort(BothBucket& bucket)
// {
//     quickSort(bucket.data, 0, bucket.size - 1);
// }
// void Array_Sort::quickSort(FrequencyBucket& bucket)
// {
//     quickSort(bucket.data, 0, bucket.size - 1);
// }

// void Array_Sort::quickSort(Both* arr, int low, int high)
// {
//     if (low < high)
//     {
//         // Partition the array and get pivot index
//         int pivotIndex = partition(arr, low, high);
        
//         // Recursively sort elements before and after partition
//         quickSort(arr, low, pivotIndex - 1);
//         quickSort(arr, pivotIndex + 1, high);
//     }
// }
// void Array_Sort::quickSort(Frequency* arr, int low, int high)
// {
//     if (low < high)
//     {
//         // Partition the array and get pivot index
//         int pivotIndex = partition(arr, low, high);
        
//         // Recursively sort elements before and after partition
//         quickSort(arr, low, pivotIndex - 1);
//         quickSort(arr, pivotIndex + 1, high);
//     }
// }

// int Array_Sort::partition(Both* arr, int low, int high)
// {
//     // Choose rightmost element as pivot
//     Both pivot = arr[high];
//     int i = low - 1;  // Index of smaller element
    
//     for (int j = low; j < high; j++)
//     {           
//         // If current element is bigger than pivot
//         if (Helper::compareDate(pivot.date, arr[j].date))  // Compare by date
//         {
//             i++;
//             swap(arr[i], arr[j]);
//         }
//     }

//     // Place pivot in its correct position
//     swap(arr[i + 1], arr[high]);
//     return i + 1;
// }
// int Array_Sort::partition(Frequency* arr, int low, int high)
// {
//     // Choose rightmost element as pivot
//     Frequency pivot = arr[high];
//     int i = low - 1;  // Index of smaller element
    
//     for (int j = low; j < high; j++)
//     {           
//         // If current element is bigger than pivot
//         if (arr[j].count > pivot.count) // Compare by count (descending)
//         {
//             i++;
//             swap(arr[i], arr[j]);
//         }
//     }
//     // Place pivot in its correct position
//     swap(arr[i + 1], arr[high]);
//     return i + 1;
// }


// class LinkedList_Search
// {
// public:
//     // ----------- Function Prototypes ----------
//     Transaction* sequentialSearch(int*, Transaction*, const string&, const string&, const string&, const string&);
//     Review* sequentialSearch(int*, Review*, const string&, const string&);

//     Transaction* linearSearch(int*, Transaction*, const string&, const string&, const string&, const string&);
//     Review* linearSearch(int*, Review*, const string&, const string&);

//     Transaction* recursiveSearch(int*, Transaction*, const string&, const string&, const string&, const string&);
//     Review* recursiveSearch(int*, Review*, const string&, const string&);

//     Transaction* sentinelSearch(int*, Transaction*, const string&, const string&, const string&, const string&);
//     Review* sentinelSearch(int*, Review*, const string&, const string&);
//     // ------------------------------------------
// };

// /* Sequential Search Implementation - Linked List
// - Time Complexity: O(1) [Best Case], O(n) [Average & Worst Case]
// - Space Complexity: O(1)
// */
// Transaction* LinkedList_Search::sequentialSearch(int* sizePtr, Transaction* head, const string& field1, const string& text1, const string& field2, const string& text2)
// {
//     int size = 0;
//     Transaction* current = head;
//     Transaction* prev = nullptr;  // Keep track of previous node
    
//     while (current != nullptr)
//     {
//         // Check first & second condition together
//         if ((field1 == "category" && current->category == text1) && (field2 == "paymentMethod" && current->paymentMethod == text2))
//         {
//             size++;
//             prev = current;
//             current = current->next;
//         }
//         else
//         {
//             Transaction* temp = current;
//             current = current->next;
//             if (prev != nullptr)
//             {
//                 prev->next = current;
//             }
//             else
//             {
//                 head = current;
//             }
//             delete temp;
//         }
//     }          
//     *sizePtr = size;
//     return head;
// }
// Review* LinkedList_Search::sequentialSearch(int* sizePtr, Review* head, const string& field1, const string& text1)
// {
//     int size = 0;
//     Review* current = head;
//     Review* prev = nullptr;  // Keep track of previous node
    
//     while (current != nullptr)
//     {
//         if (field1 == "rating" && to_string(current->rating) == text1)
//         {
//             size++;
//             prev = current;
//             current = current->next;
//         }          
//         else
//         {
//             Review* temp = current;
//             current = current->next;
//             if (prev != nullptr)
//             {
//                 prev->next = current;
//             }
//             else
//             {
//                 head = current;
//             }
//             delete temp;
//         }
//     }
//     *sizePtr = size;
//     return head;
// }

// /* Linear Search Implementation - Linked List
// - Time Complexity: O(1) [Best Case], O(n) [Average & Worst Case]
// - Space Complexity: O(1)
// */
// Transaction* LinkedList_Search::linearSearch(int* sizePtr, Transaction* head, const string& field1, const string& text1, const string& field2, const string& text2)
// {
//     int count = 0;
//     Transaction* current = head;
//     Transaction* filtered = nullptr;  // Head of filtered list
//     Transaction* filteredTail = nullptr;  // Tail of filtered list for easy appending
    
//     while (current != nullptr)
//     {
//         Transaction* next = current->next;  // Save next pointer before potentially modifying current
//         bool condition1 = false;
//         bool condition2 = true;  // Default to true if field2 is empty
        
//         if (field1 == "category")
//         {
//             condition1 = (current->category == text1);
//         }

//         if (!field2.empty())
//         {
//             if (field2 == "paymentMethod")
//             {
//                 condition2 = (current->paymentMethod == text2);
//             }
//         }
        
//         if (condition1 && condition2)
//         {
//             count++;
            
//             // Move this node to filtered list (no need to create new node)
//             current->next = nullptr;
            
//             // Add to filtered list
//             if (filtered == nullptr)
//             {
//                 filtered = current;
//                 filteredTail = current;
//             }
//             else
//             {
//                 filteredTail->next = current;
//                 filteredTail = current;
//             }
//         }
//         else
//         {
//             // Free the node that doesn't match
//             delete current;
//         }
//         current = next;
//     }
//     // Update head to filtered list
//     *sizePtr = count;
//     return filtered;
// }
// Review* LinkedList_Search::linearSearch(int* sizePtr, Review* head, const string& field1, const string& text1)
// {
//     int count = 0;
//     Review* current = head;
//     Review* filtered = nullptr;  // Head of filtered list
//     Review* filteredTail = nullptr;  // Tail of filtered list for easy appending
    
//     while (current != nullptr)
//     {
//         Review* next = current->next;  // Save next pointer before potentially modifying current
//         bool condition1 = false;

//         if (field1 == "rating")
//         {
//             condition1 = (to_string(current->rating) == text1);
//         }
        
//         if (condition1)
//         {
//             count++;
            
//             // Move this node to filtered list (no need to create new node)
//             current->next = nullptr;
            
//             // Add to filtered list
//             if (filtered == nullptr)
//             {
//                 filtered = current;
//                 filteredTail = current;
//             }
//             else
//             {
//                 filteredTail->next = current;
//                 filteredTail = current;
//             }
//         }
//         else
//         {
//             // Free the node that doesn't match
//             delete current;
//         }
        
//         current = next;
//     }
//     // Update head to filtered list
//     *sizePtr = count;
//     return filtered;
// }

// /* Recursive Search Implementation - Linked List
// - Time Complexity: O(1) [Best Case], O(n) [Average & Worst Case]
// - Space Complexity: O(1)
// */
// Transaction* LinkedList_Search::recursiveSearch(int* sizePtr, Transaction* head, const string& field1, const string& text1, const string& field2, const string& text2)
// {
//     // Base case: end of list
//     if (head == nullptr)
//     {
//         *sizePtr = 0;
//         return nullptr;
//     }
//     Transaction* nextNode = head->next;
    
//     // Check match condition
//     bool match1 = (field1 == "category" && head->category == text1) ||
//                     (field1 == "paymentMethod" && head->paymentMethod == text1);

//     bool match2 = true;
//     if (!field2.empty()) 
//     {
//         match2 = (field2 == "category" && head->category == text2) ||
//                 (field2 == "paymentMethod" && head->paymentMethod == text2);
//     }
    
//     // Recursive call for the rest of the list
//     Transaction* filteredNext = recursiveSearch(sizePtr, nextNode, field1, text1, field2, text2);

//     if (match1 && match2)
//     {
//         // Keep this node and add it to the count
//         head->next = filteredNext;
//         (*sizePtr)++;
//         return head;    
//     }
//     else
//     {
//         // Remove this node from the list
//         delete head;
//         return filteredNext;
//     }
// }
// Review* LinkedList_Search::recursiveSearch(int* sizePtr, Review* head, const string& field1, const string& text1)
// { 
//     // Base case: end of list
//     if (head == nullptr)
//     {
//         *sizePtr = 0;
//         return nullptr;
//     }
//     Review* nextNode = head->next;

//     // Check match condition
//     bool match = false;
//     if (field1 == "rating")
//     {
//         match = (to_string(head->rating) == text1);
//     }

//     // Recursive call for the rest of the list
//     Review* filteredNext = recursiveSearch(sizePtr, nextNode, field1, text1);

//     if (match)
//     {
//         // Keep this node and add it to the count
//         head->next = filteredNext;
//         (*sizePtr)++;
//         return head;
//     }
//     else
//     {
//         // Remove this node from the list
//         delete head;
//         return filteredNext;
//     }
// }      

// /* Sentinel Search Implementation - Linked List
// - Time Complexity: O(n) [Best Case], O(n) [Average & Worst Case]
// - Space Complexity: O(1)
// */
// Transaction* LinkedList_Search::sentinelSearch(int* sizePtr, Transaction* head, const string& field1, const string& value1, const string& field2, const string& value2) 
// {
//     int count = 0;
//     Transaction* current = head;
//     Transaction* prev = nullptr; 

//     while (current != nullptr)
//     {
//         bool match1 = false;
//         bool match2 = true;

//         // Handle field1
//         if (field1 == "category")
//         {
//             match1 = (current->category == value1);
//         }
//         else if (field1 == "paymentMethod")
//         {
//             match1 = (current->paymentMethod == value2);
//         }

//         // Handle field2
//         if (match1 && !field2.empty())
//         {
//             match2 = false;
//             if (field2 == "category")
//             {
//                 match2 = (current->category == value1);
//             }
//             else if (field2 == "paymentMethod")
//             {
//                 match2 = (current->paymentMethod == value2);
//             }
//         }

//         if (match1 && match2)
//         {
//             count++;
//             prev = current;
//             current = current->next;
//         }
//         else
//         {
//             // If no match, remove the current node from the Linked List
//             Transaction* temp = current;
//             current = current->next;
//             if (prev != nullptr)
//             {
//                 prev->next = current;
//             }
//             else
//             {
//                 head = current;
//             }
//             delete temp;
//         }
//     }          
//     *sizePtr = count;
//     return head;
// }
// Review* LinkedList_Search::sentinelSearch(int* sizePtr, Review* head, const string& field1, const string& value1) 
// {
//     int count = 0;
//     Review* current = head;
//     Review* prev = nullptr; 

//     while (current != nullptr)
//     {
//         bool match1 = false;

//         if (field1 == "rating")
//         {
//             match1 = (to_string(current->rating) == value1);
//         }
    
//         if (match1) 
//         {
//             count++;
//             prev = current;
//             current = current->next;
//         }
//         else
//         {
//             // If no match, remove the current node from the Linked List
//             Review* temp = current;
//             current = current->next;
//             if (prev != nullptr)
//             {
//                 prev->next = current;
//             }
//             else
//             {
//                 head = current;
//             }
//             delete temp;
//         }
//     }
//     *sizePtr = count;
//     return head;
// }


// class Array_Search
// {
// public:
//     // ----------- Function Prototypes ----------
//     int sequentialSearch(TransactionBucket&, const string&, const string&, const string&, const string&);
//     int sequentialSearch(ReviewBucket&, const string&, const string&);

//     int linearSearch(TransactionBucket&, const string&, const string&, const string&, const string&);
//     int linearSearch(ReviewBucket&, const string&, const string&);

//     int binarySearch(TransactionBucket&, const string&, const string&, const string&, const string&);
//     int binarySearch(ReviewBucket&, const string&, const string&);
    
//     int jumpSearch(TransactionBucket&, const string&, const string&, const string&, const string&);
//     int jumpSearch(ReviewBucket&, const string&, const string&);
//     // ------------------------------------------
// };

// /* Sequential Search Implementation - Array
// - Time Complexity: O(1) [Best Case], O(n) [Average & Worst Case]
// - Space Complexity: O(1)
// */
// int Array_Search::sequentialSearch(TransactionBucket& bucket, const string& field1, const string& text1, const string& field2, const string& text2)
// {
//     int size = 0;
//     int readInd = 0;  // Index for reading elements
//     int writeInd = 0; // Index for writing matching elements
    
//     // Iterate through all elements
//     while (readInd < bucket.size)
//     {         
//         if (field1 == "category" && bucket.data[readInd].category == text1)
//         {
//             // If first condition matches, check second condition
//             if(field2 == "paymentMethod" && bucket.data[readInd].paymentMethod == text2)
//             {
//                 // Write matching elements
//                 if (writeInd != readInd)
//                 {
//                     bucket.data[writeInd] = bucket.data[readInd];
//                 }
//                 size++;     // Increment size for matching element
//                 writeInd++; // Move write index forward
//             }
//         }            
//         readInd++; // Move read index forward 
//     }  
//     bucket.size = size;   
//     return size;
// }
// int Array_Search::sequentialSearch(ReviewBucket& bucket, const string& field1, const string& text1)
// {
//     int size = 0;
//     int readInd = 0;  // Index for reading elements
//     int writeInd = 0; // Index for writing matching elements
    
//     // Iterate through all elements
//     while (readInd < bucket.size)
//     {
//         if (field1 == "rating" && to_string(bucket.data[readInd].rating) == text1)
//         {
//             // Write matching elements
//             if (writeInd != readInd)
//             {
//                 bucket.data[writeInd] = bucket.data[readInd];
//             }
//             size++;     // Increment size for matching element
//             writeInd++; // Move write index forward
//         }   
//         readInd++; // Move read index forward
//     }  
//     bucket.size = size;   
//     return size;
// }

// /* Linear Search Implementation - Array
// - Time Complexity: O(1) [Best Case], O(n) [Average & Worst Case]
// - Space Complexity: O(n) due to creating filtered array
// */
// int Array_Search::linearSearch(TransactionBucket& bucket, const string& field1, const string& text1, const string& field2, const string& text2)
// {
//     int count = 0;
//     TransactionBucket filteredBucket;
    
//     for (int i = 0; i < bucket.size; i++)
//     {
//         bool condition1 = false;
//         bool condition2 = true;  // Default to true if field2 is empty 

//         if (field1 == "category")
//         {
//             condition1 = (bucket.data[i].category == text1);
//         }
//         if (!field2.empty())
//         {
//             if (field2 == "paymentMethod")
//             {
//                 condition2 = (bucket.data[i].paymentMethod == text2);
//             }
//         }
//         bool match = condition1 && condition2;
        
//         if (match)
//         {
//             count++;
//             filteredBucket.add(bucket.data[i]);
//         }
//     }
    
//     // Replace the original bucket with the filtered bucket if any matches were found
//     if (count > 0)
//     {
//         // Clean up original bucket
//         delete[] bucket.data;
        
//         // Copy filtered data to original bucket
//         bucket.size = filteredBucket.size;
//         bucket.capacity = filteredBucket.capacity;
//         bucket.data = new Transaction[bucket.capacity];

//         for (int i = 0; i < bucket.size; i++)
//         {
//             bucket.data[i] = filteredBucket.data[i];
//         }
        
//         // Set filtered bucket's data to nullptr to prevent deletion when it goes out of scope
//         filteredBucket.data = nullptr;
//     }
//     else
//     {
//         // If no matches, empty the bucket
//         delete[] bucket.data;
//         bucket.data = new Transaction[bucket.capacity];
//         bucket.size = 0;
//     }
//     return count;
// }
// int Array_Search::linearSearch(ReviewBucket& bucket, const string& field1, const string& text1)
// {
//     int count = 0;
//     ReviewBucket filteredBucket;
    
//     for (int i = 0; i < bucket.size; i++)
//     {
//         bool condition1 = false;

//         if (field1 == "rating" && to_string(bucket.data[i].rating) == text1)
//         {
//             filteredBucket.add(bucket.data[i]);
//             count++;
//         }
//     }
    
//     // Replace the original bucket with the filtered bucket if any matches were found
//     if (count > 0)
//     {
//         // Clean up original bucket
//         delete[] bucket.data;
        
//         // Copy filtered data to original bucket
//         bucket.size = filteredBucket.size;
//         bucket.capacity = filteredBucket.capacity;
//         bucket.data = new Review[bucket.capacity];

//         for (int i = 0; i < bucket.size; i++)
//         {
//             bucket.data[i] = filteredBucket.data[i];
//         }
        
//         // Set filtered bucket's data to nullptr to prevent deletion when it goes out of scope
//         filteredBucket.data = nullptr;
//     }
//     else
//     {
//         // If no matches, empty the bucket
//         delete[] bucket.data;
//         bucket.data = new Review[bucket.capacity];
//         bucket.size = 0;
//     }
//     return count;
// }

// /* Binary Search Implementation - Array
// - Time Complexity: O(log n) [Best Case], O(n) [Average & Worst Case]
// - Space Complexity: O(1)
// */
// int Array_Search::binarySearch(TransactionBucket& bucket, const string& field1, const string& value1, const string& field2, const string& value2) 
// {
//     int count = 0;
    
//     for (int i = 0; i < bucket.size; i++) 
//     {
//         bool match1 = false;
//         bool match2 = true;

//         if (field1 == "category")
//         {
//             match1 = (bucket.data[i].category == value1);
//         }
//         else if (field1 == "paymentMethod")
//         {
//             match1 = (bucket.data[i].paymentMethod == value1);
//         }

//         if (match1 && !field2.empty())
//         {
//             match2 = false;
//             if (field2 == "category")
//             {
//                 match2 = (bucket.data[i].category == value2);
//             }
//             else if (field2 == "paymentMethod")
//             {
//                 match2 = (bucket.data[i].paymentMethod == value2);
//             }
//         }

//         if (match1 && match2)
//         {
//             count++;
//         }
//     }
//     return count;
// }
// int Array_Search::binarySearch(ReviewBucket& bucket, const string& field1, const string& value1) 
// {
//     int count = 0;
    
//     for (int i = 0; i < bucket.size; i++) 
//     {
//         bool match1 = false;

//         if (field1 == "rating")
//         {
//             match1 = (to_string(bucket.data[i].rating) == value1);
//         }
    
//         if (match1) 
//         {
//             count++;
//         }
//     }
//     return count;
// }

// /* Jump Search Implementation - Array
// - Time Complexity: O(sqrt(n)) [Best Case], O(n) [Average & Worst Case]
// - Space Complexity: O(1)
// */
// int Array_Search::jumpSearch(TransactionBucket& bucket, const string& field1, const string& text1, const string& field2, const string& text2)
// {
//     int size = 0;
//     int readInd = 0;  // Index for reading elements
//     int writeInd = 0; // Index for writing matching elements
    
//     // Jump search block size
//     int blockSize = sqrt(bucket.size);
//     if (blockSize < 1)
//     {
//         blockSize = 1;
//     }
    
//     // Process the data in blocks
//     while (readInd < bucket.size)
//     {
//         // Determine the end of the current block
//         int blockEnd = min(readInd + blockSize, bucket.size);
        
//         // Process all elements in this block
//         for (int i = readInd; i < blockEnd; i++)
//         {
//             bool match = false;
//             bool condition1 = (field1 == "category" && bucket.data[i].category == text1);
//             bool condition2 = (field2 == "paymentMethod" && bucket.data[i].paymentMethod == text2);
                
//             // If first condition matches & second condition exists, check second condition
//             if (condition1 && !field2.empty())
//             {
//                 match = false;
//                 if (condition2)
//                 {
//                     match = true;
//                 }
//             }
            
//             if (match)
//             {
//                 // Write matching elements
//                 if (writeInd != i)
//                 {
//                     bucket.data[writeInd] = bucket.data[i];
//                 }
//                 size++;     // Increment size for matching element
//                 writeInd++; // Move write index forward
//             }
//         }   
//         // Jump to the next block
//         readInd = blockEnd;
//     }   
//     bucket.size = size;
//     return size;
// }
// int Array_Search::jumpSearch(ReviewBucket& bucket, const string& field1, const string& text1)
// {
//     int size = 0;
//     int readInd = 0;  // Index for reading elements
//     int writeInd = 0; // Index for writing matching elements
    
//     // Jump search block size
//     int blockSize = sqrt(bucket.size);
//     if (blockSize < 1)
//     {
//         blockSize = 1;
//     }
    
//     // Process the data in blocks
//     while (readInd < bucket.size)
//     {
//         // Determine the end of the current block
//         int blockEnd = min(readInd + blockSize, bucket.size);
        
//         // Process all elements in this block
//         for (int i = readInd; i < blockEnd; i++)
//         {
//             bool match = false;
//             bool condition1 = (field1 == "rating" && to_string(bucket.data[i].rating) == text1);
                
//             // Check if statement matches
//             if (condition1)
//             {
//                 match = true;
//             }
//             if (match)
//             {
//                 // Write matching elements
//                 if (writeInd != i)
//                 {
//                     bucket.data[writeInd] = bucket.data[i];
//                 }
//                 size++;     // Increment size for matching element
//                 writeInd++; // Move write index forward
//             }
//         }   
//         // Jump to the next block
//         readInd = blockEnd;
//     }   
//     bucket.size = size;
//     return size;
// }