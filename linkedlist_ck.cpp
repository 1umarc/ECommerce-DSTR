#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Node structure for Singly Linked List
struct Node {
    int data;
    Node* next; // Pointer to the next node
};

// Linked List class
class LinkedList {
public:
    Node* head;

    // Constructor - Initializes an empty list
    LinkedList() 
    { 
        head = nullptr; 
    }

    // Destructor - Frees allocated memory
    ~LinkedList() 
    {
        Node* delNode = head;
        while (delNode != nullptr) {
            Node* next = delNode->next;
            delete delNode;
            delNode = next;
        }
    }

    // Inserts nodes at the beginning - O(1)
    void insert(int data) {
        Node* newHead = new Node();
        newHead->data = data;
        newHead->next = head;
        head = newHead;
    }

    // Function to display the linked list
    void display() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    // Function call for Insertion Sort
    void insertionSort() {
        head = insertionSort(head);
    }

private:
    /* Insertion Sort Implementation
    - Time Complexity: O(n^2) [Worst & Average Case], O(n) [Best Case if already sorted]
    - Space Complexity: O(1)
    - Stable sorting algorithm
    */
    Node* insertionSort(Node* head) {
        if (!head || !head->next) return head; // Base case: List is empty or has only one element

        Node* sorted = nullptr; // New sorted list
        Node* current = head;

        while (current) {
            Node* next = current->next; // Save next node

            // Insert current node into sorted list
            if (!sorted || sorted->data > current->data) {
                current->next = sorted;
                sorted = current;
            } else {
                Node* temp = sorted;
                while (temp->next && temp->next->data < current->data) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
            current = next;
        }
        return sorted; // Return new sorted head
    }
};

// Main function
int main() {
    LinkedList list; // Create LinkedList object

    // Insert nodes into the list
    list.insert(10);
    list.insert(14);
    list.insert(13);
    list.insert(12);

    cout << "Original list: ";
    list.display(); // Display original list

    // Sort the list using Insertion Sort
    list.insertionSort();
    
    cout << "Sorted list: ";
    list.display(); // Display sorted list

    return 0;
}
