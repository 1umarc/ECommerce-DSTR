#include "algorithms.hpp"
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

    void read()
    {
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
    }

    void clean()
    {

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

    //1

    // use all sort algorithm

    //2
 
    // use all of search algorithm

    //3

    // use all sort + search algorithm
    
    return 0;
}
