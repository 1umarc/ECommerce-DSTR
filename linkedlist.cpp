#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Node structure for Singly Linked List
struct Node
{
    int data;
    Node* next;
};


// Linked List class
class LinkedList
{
public:
    Node* head;

    LinkedList()
    {
        head = NULL;
    } 

    void insert(int data)
    {
        Node* newHead = new Node();
        newHead-> data = data;
        newHead->next = head;
        head = newHead;
    }

    void display() 
    {
        Node* temp = head;

        while (temp != NULL) 
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
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
    LinkedList transactions;
    ifstream file("transactions.csv");
    // Gets values but meant for int...
    string line;
    while (getline(file, line)) 
    {
        stringstream ss(line);
        int value;
        if (ss >> value)
        {
            transactions.insert(value);
        }
    }
    file.close();
    
    transactions.display();

    LinkedList l;
    l.insert(10);
    l.insert(14);
    l.insert(13);
    l.insert(12);
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
