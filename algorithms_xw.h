#include "helper.h"
#include <iostream>
#include <cmath>

using namespace std;

class LinkedList_Sort
{
public:
    template <typename NodeType>
    void selectionSort(NodeType*& head)
    {
        // Base case - empty list or list with only one node
        if (head == nullptr || head->next == nullptr)
        {
            return;
        }

        NodeType* current = head;
        
        // Traverse the list
        while (current != nullptr)
        {
            NodeType* minNode = current;
            NodeType* temp = current->next;
            
            // Find the minimum node in the unsorted part
            while (temp != nullptr)
            {
                bool condition = false;

                if constexpr (std::is_same<NodeType, Both>::value)
                {
                    condition = Helper::compareDate(minNode->date, temp->date);  // Compare by date
                }
                else if constexpr (std::is_same<NodeType, Frequency>::value)
                {
                    condition = minNode->count > temp->count;  // Compare by count (descending)
                }

                // If temp node value is smaller or later date
                if (condition)
                {
                    minNode = temp;
                }
                
                temp = temp->next;
            }
            
            // Swap data if minNode is not the current node
            if (minNode != current)
            {
                // For Both node type
                if constexpr (std::is_same<NodeType, Both>::value)
                {
                    // Swap all fields
                    swap(current->customerID, minNode->customerID);
                    swap(current->product, minNode->product);
                    swap(current->category, minNode->category);
                    swap(current->price, minNode->price);
                    swap(current->date, minNode->date);
                    swap(current->paymentMethod, minNode->paymentMethod);
                    swap(current->productID, minNode->productID);
                    swap(current->rating, minNode->rating);
                    swap(current->reviewText, minNode->reviewText);
                }
                // For Frequency node type
                else if constexpr (std::is_same<NodeType, Frequency>::value)
                {
                    swap(current->text, minNode->text);
                    swap(current->count, minNode->count);
                }
            } 
            current = current->next;
        }
    }
};

class Array_Sort
{
public:
    template <typename ArrayType>
    void quickSort(Bucket<ArrayType>& bucket)
    {
        quickSort(bucket.data, 0, bucket.size - 1);
    }
private:
    template <typename ArrayType>
    void quickSort(ArrayType* arr, int low, int high)
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
    
    template <typename ArrayType>
    int partition(ArrayType* arr, int low, int high)
    {
        // Choose rightmost element as pivot
        ArrayType pivot = arr[high];
        int i = low - 1;  // Index of smaller element
        
        for (int j = low; j < high; j++)
        {
            bool condition = false;
            
            // Determine comparison based on type
            if constexpr (std::is_same<ArrayType, Both>::value)
            {
                condition = Helper::compareDate(arr[j].date, pivot.date);  // Compare by date
            }
            else if constexpr (std::is_same<ArrayType, Frequency>::value)
            {
                condition = arr[j].count > pivot.count;  // Compare by count (descending)
            }
            
            // If current element is greater than pivot
            if (condition)
            {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        // Place pivot in its correct position
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }
};

class LinkedList_Search
{
public:
    template <typename NodeType>
    int sentinelSearch(NodeType* head, const string& field1, const string& text1, const string& field2 = "", const string& text2 = "")
    {
        int size = 0;
        NodeType* current = head;
        NodeType* prev = nullptr;  // To keep track of the previous node for filtered linked list
        
        while (current != nullptr)
        {
            bool match = false;
            bool condition1 = false;
            bool condition2 = false;

            // First condition check
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
};

class Array_Search
{
public:
   template <typename DataType>
   int jumpSearch(Bucket<DataType>& bucket, const string& field1, const string& text1, const string& field2 = "", const string& text2 = "")
   {
       int size = 0;
       int readInd = 0;  // Index for reading elements
       int writeInd = 0; // Index for writing matching elements
       
       // Jump search block size
       int blockSize = sqrt(bucket.size);
       if (blockSize < 1) blockSize = 1;
       
       // Process the data in blocks
       while (readInd < bucket.size)
       {
           // Determine the end of the current block
           int blockEnd = min(readInd + blockSize, bucket.size);
           
           // Process all elements in this block
           for (int i = readInd; i < blockEnd; i++)
           {
               bool match = false;
               bool condition1 = false;
               bool condition2 = false;
   
               if constexpr (std::is_same<DataType, Transaction>::value)
               {
                   condition1 = (field1 == "category" && bucket.data[i].category == text1);
                   condition2 = (field2 == "paymentMethod" && bucket.data[i].paymentMethod == text2);
               }
               else if constexpr (std::is_same<DataType, Review>::value)
               {
                   condition1 = (field1 == "rating" && to_string(bucket.data[i].rating) == text1);
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
                   if (writeInd != i)
                   {
                       bucket.data[writeInd] = bucket.data[i];
                   }
                   size++;     // Increment size for matching element
                   writeInd++; // Move write index forward
               }
           }
           
           // Jump to the next block
           readInd = blockEnd;
       }   
       bucket.size = size;
       return size;
   }
};