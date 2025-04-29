#include "helper.h"
#include <iostream>

using namespace std;

class LinkedList_Sort
{
public:
    /* Merge Sort Implementation - Linked List
    - Time Complexity: O(n log n)
    - Space Complexity: O(n)
    */
    template <typename NodeType>
    void mergeSort(NodeType*& head)
    {
        // Base case - empty list or list with only one node
        if (head == nullptr || head->next == nullptr)
        {
            return;
        }

        // Split the list into two halves
        NodeType* secondHalf = split(head);

        // Recursively sort both halves
        mergeSort(head);
        mergeSort(secondHalf);

        // Merge the sorted halves
        head = merge(head, secondHalf);
    }

private:
    // Split the linked list into two halves
    template <typename NodeType>
    NodeType* split(NodeType* head)
    {
        if (head == nullptr || head->next == nullptr)
        {
            return nullptr;
        }
        
        // Using slow and fast pointers to find the middle
        NodeType* slow = head;
        NodeType* fast = head->next;

        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        NodeType* middle = slow->next;
        slow->next = nullptr;
        return middle;
    }

    // Merge two sorted Linked Lists
    template <typename NodeType>
    NodeType* merge(NodeType* first, NodeType* second)
    {
        if (first == nullptr)
        {
            return second;
        }
        if (second == nullptr)
        {
            return first;
        }

        NodeType* result = nullptr;
        bool condition = false;  // Comparison variable

        if constexpr (std::is_same<NodeType, Both>::value)
        {
            condition = Helper::compareDate(first->date, second->date);  // Compare by date
        }
        else if constexpr (std::is_same<NodeType, Frequency>::value)
        {
            condition = first->count < second->count;  // Compare by count
        }

        if (condition)
        {
            // second value is later, or bigger
            result = second;
            result->next = merge(first, second->next);
        }
        else
        {
            // first value is later, or bigger
            result = first;
            result->next = merge(first->next, second);
        }
        return result;
    }

    void insertionSort()
    {
            
    }
    void bubbleSort()
    {

    }
    void selectionSort()
    {

    }
};

class Array_Sort
{
public:    
    /* Merge Sort Implementation - Array
    - Time Complexity: O(n log n)
    - Space Complexity: O(n)
    */
   template <typename ArrayType>
   void mergeSort(Bucket<ArrayType>& bucket)
   {
       mergeSort(bucket.data, 0, bucket.size - 1);
   }

private:
   template <typename ArrayType>
   void mergeSort(ArrayType* arr, int left, int right)
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

   template <typename ArrayType>
   void merge(ArrayType* arr, int left, int mid, int right)
   {
       // Create temporary arrays
       int sizeLeft = mid - left + 1;
       int sizeRight = right - mid;
       
       ArrayType* leftArr = new ArrayType[sizeLeft];
       ArrayType* rightArr = new ArrayType[sizeRight];
       
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
            bool condition = false; // Comparison variable

            if constexpr (std::is_same<ArrayType, Both>::value)
            {
                condition = Helper::compareDate(leftArr[i].date, rightArr[j].date);  // Compare by date
            }
            else if constexpr (std::is_same<ArrayType, Frequency>::value)
            {
                condition = leftArr[i].count < rightArr[j].count;  // Compare by count
            }
            
            if (condition)
            {
                arr[k] = rightArr[j];  // rightArr date 
                j++;
            }
            else
            {
                arr[k] = leftArr[i];   // leftArr date is later, or bigger
                i++;
            }
            k++;
       }
       
       // Copy remaining elements
       while (i < sizeLeft)
       {
           arr[k] = leftArr[i];
           i++;
           k++;
       }
       while (j < sizeRight)
       {
           arr[k] = rightArr[j];
           j++;
           k++;
       }
       
       // Free temporary arrays
       delete[] leftArr;
       delete[] rightArr;
   }

    void insertionSort()
    {

    }
    void heapSort()
    {

    }
    void quickSort()
    {

    }
};


class LinkedList_Search
{
public:
    /* Sequential Search Implementation - Linked List
    - Time Complexity: O(1) [Best Case], O(n) [Average & Worst Case]
    - Space Complexity: O(1)
    */
    template <typename NodeType>
    int sequentialSearch(NodeType* head, const string& field1, const string& text1, const string& field2 = "", const string& text2 = "")
    {
        int size = 0;
        NodeType* current = head;
        NodeType* prev = nullptr;  // To keep track of the previous node for filtered linked list
        
        while (current != nullptr)
        {
            bool match = false;
            bool condition1 = false; // Comparison variable
            bool condition2 = false;

            if constexpr (std::is_same<NodeType, Transaction>::value)
            {
                condition1 = (field1 == "category" && current->category == text1);
                condition2 = (field2 == "paymentMethod" && current->paymentMethod == text2);
            }
            else if constexpr (std::is_same<NodeType, Review>::value)
            {
                condition1 = (field1 == "rating" && to_string(current->rating) == text1);
            }
            
            if (condition1)
            {
                match = true;
            }          
            // If first condition matches & second condition exists, check second condition
            if (match && !field2.empty())
            {
                match = false;  
                if (condition2)
                {
                    match = true;
                }
            }
            
            if (match)
            {
                size++;  // Increment size for matching node
    
                // If current node is at the head, move head forward
                if (prev == nullptr) 
                {
                    head = current;
                }
    
                // Move to the next node
                prev = current;
                current = current->next;
            }
            else
            {
                // If no match, remove the current node from the Linked List
                if (prev != nullptr)
                {
                    prev->next = current->next;
                }
                NodeType* temp = current;
                current = current->next;
                delete temp;
            }
        }       
        return size;
    }

    void linearSearch()
    {

    }
    void recursiveSearch()
    {

    }
    void sentinelSearch()
    {

    }
};

class Array_Search
{
public:
    /* Sequential Search Implementation - Array
    - Time Complexity: O(1) [Best Case], O(n) [Average & Worst Case]
    - Space Complexity: O(1)
    */
    template <typename DataType>
    int sequentialSearch(Bucket<DataType>& bucket, const string& field1, const string& text1, const string& field2 = "", const string& text2 = "")
    {
        int size = 0;
        int readInd = 0;  // Index for reading elements
        int writeInd = 0; // Index for writing matching elements
        
        // Iterate through all elements
        while (readInd < bucket.size)
        {
            bool match = false;
            bool condition1 = false; // Comparison variable
            bool condition2 = false;

            if constexpr (std::is_same<DataType, Transaction>::value)
            {
                condition1 = (field1 == "category" && bucket.data[readInd].category == text1);
                condition2 = (field2 == "paymentMethod" && bucket.data[readInd].paymentMethod == text2);
            }
            else if constexpr (std::is_same<DataType, Review>::value)
            {
                condition1 = (field1 == "rating" && to_string(bucket.data[readInd].rating) == text1);
            }
            
            if (condition1)
            {
                match = true;
            }  
            // If first condition matches & second condition exists, check second condition
            if (match && !field2.empty())
            {
                match = false;
                if (condition2)
                {
                    match = true;
                }
            }
            
            if (match)
            {
                // Write matching elements
                if (writeInd != readInd)
                {
                    bucket.data[writeInd] = bucket.data[readInd];
                }
                size++;     // Increment size for matching element
                writeInd++; // Move write index forward
            }            
            readInd++; // Move read index forward
        }  
        bucket.size = size;   
        return size;
    }

    void linearSearch()
    {

    }
    void binarySearch()
    {

    }
    void jumpSearch()
    {

    }
};
