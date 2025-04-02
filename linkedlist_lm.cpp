#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Node structure for Singly Linked List
struct Node
{
    int data;
    Node* next; // Pointer to the next node's memory address
};


// Linked List class
class LinkedList
{
public:
    Node* head;

    // Constructor - Initializes empty first node
    LinkedList()
    {
        head = nullptr;
    } 

    // Deconstructor - Mandatory to free memory as using heap
    ~LinkedList()
    {
        // Retrieves head, store address of next node, deletes, then repeats
        Node* delNode = head;
        while (delNode != nullptr) 
        {
            Node* next = delNode->next;
            delete delNode;
            delNode = next;
        }
    }

    // Inserting nodes to form Linked List - O(1)
    void insert(int data)
    {
        // Creates new node which is the new head as it inserts from beginning
        Node* newHead = new Node();
        newHead->data = data;
        newHead->next = head;
        head = newHead;
    }

    // Print the Linked List
    void display() 
    {
        // Traverses from head to NULL
        Node* temp = head;

        while (temp != nullptr) 
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }


    /* Merge Sort Implementation
    - Time Complexity: O(n log n)
    - Space Complexity: O(n)
    - divide & conquer algorithm, same if linear or linked list
    */
    // Merges two sorted Lists - O(n)
    Node* merge(Node *left, Node *right)
    {
        // At Base - If either list is empty, return the other
        if(left == nullptr)
        {
            return right;
        }
        else if (right == nullptr)
        {
            return left;
        }

        // During Recursive - Compare data, smaller node attaches to the bigger node
        if(left->data < right->data)
        {
            left->next = merge(left->next, right);
            return left;
        }
        else
        {
            right->next = merge(left, right->next);
            return right;
        }
    }

    // Finds middle of the List with the slow-fast pointer approach - O(n)
    Node* midSplit(Node *head)
    {
        Node* slow = head;
        Node* fast = head->next;

        // Slow pointer moves 1 step, fast pointer moves 2 steps
        while(fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow; // When fast pointer at the end, slow pointer is at mid-point
    }

    // Function call for Merge Sort
    void mergeSort()
    {
        head = mergeSort(head);
    }


private:
    // Overload function to Sort the List - O(n log n)
    Node* mergeSort(Node *head)
    {
        // At Base - If head or next to head is null, return
        if(head == nullptr || head->next == nullptr)
        {
            return head;
        }

        // During Recursive - Split the list, recursively sort both halves and merge  
        Node* mid = midSplit(head);
        Node* left = head;
        Node* right = mid->next; // mid-point belongs to left, mid->next is the second half
        mid->next = nullptr;
    
        left = mergeSort(left);
        right = mergeSort(right);
    
        return merge(left, right);
    }

public:    
    /* Sequential Search Implementation
    - Time Complexity: O(1) [Best Case], O(n) [Average & Worst Case]
    - Space Complexity: O(1)
    - traverses node-by-node BUT stops early if greater than target, as assumes list is sorted
    */
   Node* sequentialSearch(int target)
   {
       Node* current = head;
   
       while (current != nullptr)
       {
           // If target found, return
           if (current->data == target)
           {
               return current;
           }
           // If current node > target, stop search as its sorted
           else if (current->data > target)
           {
               return nullptr;
           }
           current = current->next;
       }
   
       return nullptr; // Target not found...
   }
};


int main()
{
    LinkedList l;
    l.insert(10);
    l.insert(14);
    l.insert(13);
    l.insert(12);
    l.display();

    l.mergeSort();
    l.display();

    Node* result = l.sequentialSearch(13);
    if (result != nullptr)
    {
        cout << "Found: " << result->data << endl;
    }
    else
    {
        cout << "Not found!" << endl;
    }
   
    return 0;
}
