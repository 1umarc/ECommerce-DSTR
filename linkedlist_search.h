#include "helper.h"
#include <iostream>

using namespace std;

class LinkedList_Search
{
public:
    // ----------- Function Prototypes ----------
    Transaction* sequentialSearch(int*, Transaction*, const string&, const string&, const string&, const string&);
    Review* sequentialSearch(int*, Review*, const string&, const string&);

    Transaction* linearSearch(int*, Transaction*, const string&, const string&, const string&, const string&);
    Review* linearSearch(int*, Review*, const string&, const string&);

    Transaction* recursiveSearch(int*, Transaction*, const string&, const string&, const string&, const string&);
    Review* recursiveSearch(int*, Review*, const string&, const string&);

    Transaction* sentinelSearch(int*, Transaction*, const string&, const string&, const string&, const string&);
    Review* sentinelSearch(int*, Review*, const string&, const string&);
    // ------------------------------------------
};

/* Sequential Search Implementation - Linked List
- Time Complexity: O(1) [Best Case], O(n) [Worst Case]
- Space Complexity: O(1)
*/
Transaction* LinkedList_Search::sequentialSearch(int* sizePtr, Transaction* head, const string& field1, const string& text1, const string& field2, const string& text2)
{
    int size = 0;
    Transaction* current = head;
    Transaction* prev = nullptr;  // Keep track of previous node
    
    while (current != nullptr)
    {
        // Check first & second condition together
        if ((field1 == "category" && current->category == text1) && (field2 == "paymentMethod" && current->paymentMethod == text2))
        {
            size++;
            prev = current;
            current = current->next;
        }
        else
        {
            Transaction* temp = current;
            current = current->next;
            if (prev != nullptr)
            {
                prev->next = current;
            }
            else
            {
                head = current;
            }
            delete temp;
        }
    }          
    *sizePtr = size;
    return head;
}
Review* LinkedList_Search::sequentialSearch(int* sizePtr, Review* head, const string& field1, const string& text1)
{
    int size = 0;
    Review* current = head;
    Review* prev = nullptr;  // Keep track of previous node
    
    while (current != nullptr)
    {
        if (field1 == "rating" && to_string(current->rating) == text1)
        {
            size++;
            prev = current;
            current = current->next;
        }          
        else
        {
            Review* temp = current;
            current = current->next;
            if (prev != nullptr)
            {
                prev->next = current;
            }
            else
            {
                head = current;
            }
            delete temp;
        }
    }
    *sizePtr = size;
    return head;
}

/* Linear Search Implementation - Linked List
- Time Complexity: O(1) [Best Case], O(n) [Average & Worst Case]
- Space Complexity: O(1)
*/
Transaction* LinkedList_Search::linearSearch(int* sizePtr, Transaction* head, const string& field1, const string& text1, const string& field2, const string& text2)
{
    int count = 0;
    Transaction* current = head;
    Transaction* filtered = nullptr;  // Head of filtered list
    Transaction* filteredTail = nullptr;  // Tail of filtered list for easy appending
    
    while (current != nullptr)
    {
        Transaction* next = current->next;  // Save next pointer before potentially modifying current
        bool condition1 = false;
        bool condition2 = true;  // Default to true if field2 is empty
        
        if (field1 == "category")
        {
            condition1 = (current->category == text1);
        }

        if (!field2.empty())
        {
            if (field2 == "paymentMethod")
            {
                condition2 = (current->paymentMethod == text2);
            }
        }
        
        if (condition1 && condition2)
        {
            count++;
            
            // Move this node to filtered list (no need to create new node)
            current->next = nullptr;
            
            // Add to filtered list
            if (filtered == nullptr)
            {
                filtered = current;
                filteredTail = current;
            }
            else
            {
                filteredTail->next = current;
                filteredTail = current;
            }
        }
        else
        {
            // Free the node that doesn't match
            delete current;
        }
        current = next;
    }
    // Update head to filtered list
    *sizePtr = count;
    return filtered;
}
Review* LinkedList_Search::linearSearch(int* sizePtr, Review* head, const string& field1, const string& text1)
{
    int count = 0;
    Review* current = head;
    Review* filtered = nullptr;  // Head of filtered list
    Review* filteredTail = nullptr;  // Tail of filtered list for easy appending
    
    while (current != nullptr)
    {
        Review* next = current->next;  // Save next pointer before potentially modifying current
        bool condition1 = false;

        if (field1 == "rating")
        {
            condition1 = (to_string(current->rating) == text1);
        }
        
        if (condition1)
        {
            count++;
            
            // Move this node to filtered list (no need to create new node)
            current->next = nullptr;
            
            // Add to filtered list
            if (filtered == nullptr)
            {
                filtered = current;
                filteredTail = current;
            }
            else
            {
                filteredTail->next = current;
                filteredTail = current;
            }
        }
        else
        {
            // Free the node that doesn't match
            delete current;
        }
        
        current = next;
    }
    // Update head to filtered list
    *sizePtr = count;
    return filtered;
}

/* Recursive Search Implementation - Linked List
- Time Complexity: O(n)
- Space Complexity: O(n)
*/
Transaction* LinkedList_Search::recursiveSearch(int* sizePtr, Transaction* head, const string& field1, const string& text1, const string& field2, const string& text2)
{
    // Base case: end of list
    if (head == nullptr)
    {
        *sizePtr = 0;
        return nullptr;
    }
    Transaction* nextNode = head->next;
    
    // Check match condition
    bool match1 = (field1 == "category" && head->category == text1) ||
                    (field1 == "paymentMethod" && head->paymentMethod == text1);

    bool match2 = true;
    if (!field2.empty()) 
    {
        match2 = (field2 == "category" && head->category == text2) ||
                (field2 == "paymentMethod" && head->paymentMethod == text2);
    }
    
    // Recursive call for the rest of the list
    Transaction* filteredNext = recursiveSearch(sizePtr, nextNode, field1, text1, field2, text2);

    if (match1 && match2)
    {
        // Keep this node and add it to the count
        head->next = filteredNext;
        (*sizePtr)++;
        return head;    
    }
    else
    {
        // Remove this node from the list
        delete head;
        return filteredNext;
    }
}
Review* LinkedList_Search::recursiveSearch(int* sizePtr, Review* head, const string& field1, const string& text1)
{ 
    // Base case: end of list
    if (head == nullptr)
    {
        *sizePtr = 0;
        return nullptr;
    }
    Review* nextNode = head->next;

    // Check match condition
    bool match = false;
    if (field1 == "rating")
    {
        match = (to_string(head->rating) == text1);
    }

    // Recursive call for the rest of the list
    Review* filteredNext = recursiveSearch(sizePtr, nextNode, field1, text1);

    if (match)
    {
        // Keep this node and add it to the count
        head->next = filteredNext;
        (*sizePtr)++;
        return head;
    }
    else
    {
        // Remove this node from the list
        delete head;
        return filteredNext;
    }
}      

/* Sentinel Search Implementation - Linked List
- Time Complexity: O(n)
- Space Complexity: O(1)
*/
Transaction* LinkedList_Search::sentinelSearch(int* pointerSize, Transaction* head, const string& field1, const string& value1, const string& field2, const string& value2) 
{
    int count = 0;
    
    // Handle empty list case
    if (head == nullptr) 
    {
        *pointerSize = 0;
        return nullptr;
    }
    
    // Create a sentinel node at the end of the list
    Transaction* sentinel = new Transaction();
    
    // Set sentinel fields to match search criteria
    if (field1 == "category") 
    {
        sentinel->category = value1;
    } else if (field1 == "paymentMethod") 
    {
        sentinel->paymentMethod = value1;
    }
    
    if (!field2.empty()) 
    {
        if (field2 == "category") 
        {
            sentinel->category = value2;
        } else if (field2 == "paymentMethod") 
        {
            sentinel->paymentMethod = value2;
        }
    }
    
    // Find the end of the list and attach sentinel
    Transaction* last = head;
    while (last->next != nullptr) 
    {
        last = last->next;
    }
    last->next = sentinel;
    sentinel->next = nullptr;
    
    // Start the search
    Transaction* current = head;
    Transaction* prev = nullptr;
    
    // With sentinel, we can guarantee we'll eventually find a match
    while (true) 
    {
        bool match1 = false;
        bool match2 = true;

        // Handle field1
        if (field1 == "category") 
        {
            match1 = (current->category == value1);
        } else if (field1 == "paymentMethod") 
        {
            match1 = (current->paymentMethod == value1);
        }

        // Handle field2
        if (match1 && !field2.empty()) 
        {
            match2 = false;
            if (field2 == "category") 
            {
                match2 = (current->category == value2);
            } else if (field2 == "paymentMethod") 
            {
                match2 = (current->paymentMethod == value2);
            }
        }

        // Check if we've reached the sentinel node
        bool isSentinel = (current == sentinel);
        
        if (isSentinel) 
        {
            // Remove sentinel before returning
            if (prev != nullptr) 
            {
                prev->next = nullptr;
            } else 
            {
                head = nullptr; // List was only sentinel
            }
            delete sentinel;
            break;
        }

        if (match1 && match2) 
        {
            count++;
            prev = current;
            current = current->next;
        } else 
        {
            // If no match, remove the current node from the Linked List
            Transaction* temp = current;
            current = current->next;
            if (prev != nullptr) 
            {
                prev->next = current;
            } else 
            {
                head = current;
            }
            delete temp;
        }
    }
    *pointerSize = count;
    return head;
}
Review* LinkedList_Search::sentinelSearch(int* pointerSize, Review* head, const string& field1, const string& value1) 
{
    int count = 0;
    
    // Handle empty list case
    if (head == nullptr) 
    {
        *pointerSize = 0;
        return nullptr;
    }
    
    // Create a sentinel node
    Review* sentinel = new Review();
    
    // Set sentinel fields to match search criteria
    if (field1 == "rating") 
    {
        // Convert string to int for the rating field
        sentinel->rating = stoi(value1);
    }
    
    // Find the end of the list and attach sentinel
    Review* last = head;
    while (last->next != nullptr) 
    {
        last = last->next;
    }
    last->next = sentinel;
    sentinel->next = nullptr;
    
    // Start the search
    Review* current = head;
    Review* prev = nullptr;
    
    // With sentinel, we can simplify our loop condition
    while (true) 
    {
        bool match1 = false;

        if (field1 == "rating") 
        {
            match1 = (to_string(current->rating) == value1);
        }
        
        // Check if we've reached the sentinel node
        bool isSentinel = (current == sentinel);
        
        if (isSentinel) 
        {
            // Remove sentinel before returning
            if (prev != nullptr) 
            {
                prev->next = nullptr;
            } 
            else 
            {
                head = nullptr; // List was only sentinel
            }
            delete sentinel;
            break;
        }
    
        if (match1) 
        {
            count++;
            prev = current;
            current = current->next;
        } 
        else 
        {
            // If no match, remove the current node from the Linked List
            Review* temp = current;
            current = current->next;
            if (prev != nullptr) 
            {
                prev->next = current;
            } 
            else 
            {
                head = current;
            }
            delete temp;
        }
    }
    *pointerSize = count;
    return head;
}
