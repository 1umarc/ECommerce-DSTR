#include "helper.h"
#include <iostream>

using namespace std;

class LinkedList_Sort
{
    // ----------- Function Prototypes ----------
public:
    void mergeSort(Both*& head);
    void mergeSort(Frequency*& head);
private:
    Both* split(Both* head);
    Frequency* split(Frequency* head);
    Both* merge(Both* left, Both* right);
    Frequency* merge(Frequency* left, Frequency* right);
public:
    void insertionSort(Both*& head);
    void insertionSort(Frequency*& head);
    void bubbleSort(Both*& head);
    void bubbleSort(Frequency*& head);
    void selectionSort(Both*& head);
    void selectionSort(Frequency*& head);
    // ------------------------------------------
};

/* Merge Sort Implementation - Linked List
- Time Complexity: O(n log n)
- Space Complexity: O(log n)
*/
void LinkedList_Sort::mergeSort(Both*& head)
{
    // Base case - empty list or list with only one node
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }

    // Split the list into two halves
    Both* secondHalf = split(head);

    // Recursively sort both halves
    mergeSort(head);
    mergeSort(secondHalf);

    // Merge the sorted halves
    head = merge(head, secondHalf);
}
void LinkedList_Sort::mergeSort(Frequency*& head)
{
    // Base case - empty list or list with only one node
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }

    // Split the list into two halves
    Frequency* secondHalf = split(head);

    // Recursively sort both halves
    mergeSort(head);
    mergeSort(secondHalf);

    // Merge the sorted halves
    head = merge(head, secondHalf);
}

// Split the linked list into two halves
Both* LinkedList_Sort::split(Both* head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return nullptr;
    }
    
    // Using slow and fast pointers to find the middle
    Both* slow = head;
    Both* fast = head->next;

    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    Both* middle = slow->next;
    slow->next = nullptr;
    return middle;
}
Frequency* LinkedList_Sort::split(Frequency* head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return nullptr;
    }
    
    // Using slow and fast pointers to find the middle
    Frequency* slow = head;
    Frequency* fast = head->next;

    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    Frequency* middle = slow->next;
    slow->next = nullptr;
    return middle;
}

// Merge two sorted Linked Lists
Both* LinkedList_Sort::merge(Both* first, Both* second)
{
    if (first == nullptr)
    {
        return second;
    }
    if (second == nullptr)
    {
        return first;
    }

    Both* result = nullptr;
    if (Helper::compareDate(first->date, second->date))
    {
        // second value is later
        result = second;
        result->next = merge(first, second->next);
    }
    else
    {
        // first value is later
        result = first;
        result->next = merge(first->next, second);
    }
    return result;
}
Frequency* LinkedList_Sort::merge(Frequency* first, Frequency* second)
{
    if (first == nullptr)
    {
        return second;
    }
    if (second == nullptr)
    {
        return first;
    }

    Frequency* result = nullptr;
    if (first->count < second->count)
    {
        // second value is bigger
        result = second;
        result->next = merge(first, second->next);
    }
    else
    {
        // first value is bigger
        result = first;
        result->next = merge(first->next, second);
    }
    return result;
}

/* Insertion Sort Implementation - Linked List
- Time Complexity: O(n) [Best Case], O(n²) [Worst Case]
- Space Complexity: O(1)
*/
void LinkedList_Sort::insertionSort(Both*& head)
{
    // Base case - empty list or list with only one node
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }

    Both* sorted = nullptr;  // Initialize sorted linked list
    Both* current = head;    // Current node to be inserted

    // Traverse the original list
    while (current != nullptr)
    {
        // Store next for next iteration
        Both* next = current->next;

        // Insert current in sorted linked list
        if (sorted == nullptr || Helper::compareDate(sorted->date, current->date))
        {
            // Insert at beginning
            current->next = sorted;
            sorted = current;
        }
        else
        {
            // Locate node before point of insertion
            Both* temp = sorted;
            // For Both nodes, compare by date
            while (temp->next != nullptr && !Helper::compareDate(temp->next->date , current->date))
            {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;  // Move to next node
    }
    head = sorted;  // Update head to point to sorted list
}
void LinkedList_Sort::insertionSort(Frequency*& head)
{
    // Base case - empty list or list with only one node
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }

    Frequency* sorted = nullptr;  // Initialize sorted linked list
    Frequency* current = head;    // Current node to be inserted

    // Traverse the original list
    while (current != nullptr)
    {
        // Store next for next iteration
        Frequency* next = current->next;

        // Insert current in sorted linked list
        if (sorted == nullptr || (sorted->count < current->count))
        {
            // Insert at beginning
            current->next = sorted;
            sorted = current;
        }
        else
        {
            // Locate node before point of insertion
            Frequency* temp = sorted;
            // For Frequency nodes, compare by count (higher count comes first)
            while (temp->next != nullptr && !(temp->next->count < current->count))
            {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;  // Move to next node
    }
    head = sorted;  // Update head to point to sorted list
}

/* Bubble Sort Implementation - Linked List
- Time Complexity: O(n²)
- Space Complexity: O(1)
*/  
void LinkedList_Sort::bubbleSort(Both*& head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return; // Empty or single-node list
    }

    bool swapped;
    do 
    {
        swapped = false;
        Both* current = head;
        Both* nextNode = head->next;

        while (nextNode) 
        {
            // Compare dates: if current is older than next, swap
            if (Helper::compareDate(current->date, nextNode->date)) 
            {
                // Swap Both node data
                swap(current->customerID, nextNode->customerID);
                swap(current->productID, nextNode->productID);
                swap(current->category, nextNode->category);
                swap(current->price, nextNode->price);
                swap(current->date, nextNode->date);
                swap(current->paymentMethod, nextNode->paymentMethod);
                swap(current->productID, nextNode->productID);
                swap(current->rating, nextNode->rating);
                swap(current->reviewText, nextNode->reviewText);
                swapped = true;
            }
            current = nextNode;
            nextNode = nextNode->next;
        }
    } while (swapped);
}
void LinkedList_Sort::bubbleSort(Frequency*& head)
{
    if (head == nullptr || head->next == nullptr) return; // Empty or single-node list

    bool swapped;
    do {
        swapped = false;
        Frequency* current = head;
        Frequency* nextNode = head->next;

        while (nextNode) 
        {
            // For frequency nodes, sort by count in ascending order
            if (current->count < nextNode->count) 
            {
                swap(current->text, nextNode->text);
                swap(current->count, nextNode->count);
                swapped = true;
            }
            current = nextNode;
            nextNode = nextNode->next;
        }
    } while (swapped);
}

/* Selection Sort Implementation - Linked List
- Time Complexity: O(n²)
- Space Complexity: O(1)
*/
void LinkedList_Sort::selectionSort(Both*& head)
{
    // Base case - empty list or list with only one node
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }

    Both* current = head;
    
    // Traverse the list
    while (current != nullptr)
    {
        Both* minNode = current;
        Both* temp = current->next;
        
        // Find the minimum node in the unsorted part
        while (temp != nullptr)
        {
            if (Helper::compareDate(minNode->date, temp->date)) // Compare by date
            {
                // If temp node value is smaller or later date
                minNode = temp;
            }
            temp = temp->next;
        }
        
        // Swap data if minNode is not the current node
        if (minNode != current)
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
        current = current->next;
    }
}
void LinkedList_Sort::selectionSort(Frequency*& head)
{
    // Base case - empty list or list with only one node
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }

    Frequency* current = head;
    
    // Traverse the list
    while (current != nullptr)
    {
        Frequency* minNode = current;
        Frequency* temp = current->next;
        
        // Find the minimum node in the unsorted part
        while (temp != nullptr)
        {
            if (minNode->count < temp->count) // Compare by count (descending)
            {
                // If temp node value is smaller or later date
                minNode = temp;
            }
            temp = temp->next;
        }
        
        // Swap data if minNode is not the current node
        if (minNode != current)
        {
            swap(current->text, minNode->text);
            swap(current->count, minNode->count);
        } 
        current = current->next;
    }
}
