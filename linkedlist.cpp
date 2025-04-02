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


    void sort_lm(int);
    void search_lm(int);
    void sort_ck(int);
    void search_ck(int);
    void sort_xw(int);
    void search_xw(int);
    void sort_dn(int);
    void search_dn(int);
};

void LinkedList::sort_lm(int a)
{
    // Implementation
}

void LinkedList::search_lm(int a)
{
    // Implementation
}

void LinkedList::sort_ck(int a)
{
    // Implementation
}

void LinkedList::search_ck(int a)
{
    // Implementation
}

void LinkedList::sort_xw(int a)
{
    // Implementation
}

void LinkedList::search_xw(int a)
{
    // Implementation
}

void LinkedList::sort_dn(int a)
{
    // Implementation
}

void LinkedList::search_dn(int a)
{
    // Implementation
}


int main()
{
    // LinkedList transactions;
    // ifstream file("transactions.csv");
    // .
    // string line;
    // while (getline(file, line)) 
    // {
    //     stringstream ss(line);
    //     int value;
    //     if (ss >> value)
    //     {
    //         transactions.insert(value);
    //     }
    // }
    // file.close();
    
    // transactions.display();

    LinkedList l;
    l.insert(10);
    l.insert(14);
    l.insert(13);
    l.insert(12);
    l.display();

    l.mergeSort();
    l.display();
    //LM
    // #1
    // #2
    // #3

    //CK
    // #1
    // #2
    // #3

    //XW
    // #1
    // #2
    // #3

    //DN
    // #1
    // #2
    // #3
    
    return 0;
}
