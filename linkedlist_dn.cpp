#include <iostream>
#include <string>
using namespace std;

struct Node {
    string data;
    Node* next;
};

class LinkedList {
    Node* head;

public:
    LinkedList() : head(NULL) {}

    void insertAtBeginning(const string& value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = head;
        head = newNode;
    }

    void insertAtEnd(const string& value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = NULL;

        if (!head) {
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void insertAtPosition(const string& value, int position) {
        if (position < 1) {
            cout << "Position should be >= 1." << endl;
            return;
        }

        if (position == 1) {
            insertAtBeginning(value);
            return;
        }

        Node* newNode = new Node();
        newNode->data = value;

        Node* temp = head;
        for (int i = 1; i < position - 1 && temp; ++i) {
            temp = temp->next;
        }

        if (!temp) {
            cout << "Position out of range." << endl;
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    void deleteFromBeginning() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = head;
        head = head->next;
        delete temp;
    }

    void deleteFromEnd() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        if (!head->next) {
            delete head;
            head = NULL;
            return;
        }

        Node* temp = head;
        while (temp->next->next) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = NULL;
    }

    void deleteFromPosition(int position) {
        if (position < 1) {
            cout << "Position should be >= 1." << endl;
            return;
        }

        if (position == 1) {
            deleteFromBeginning();
            return;
        }

        Node* temp = head;
        for (int i = 1; i < position - 1 && temp; ++i) {
            temp = temp->next;
        }

        if (!temp || !temp->next) {
            cout << "Position out of range." << endl;
            return;
        }

        Node* nodeToDelete = temp->next;
        temp->next = temp->next->next;
        delete nodeToDelete;
    }

    void display() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = head;
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    int recursiveSearch(Node* node, const string& key, int index) {
        if (!node) {
            return -1; // Key not found
        }
        if (node->data == key) {
            return index; // Key found
        }
        return recursiveSearch(node->next, key, index + 1); // Recur for the next node
    }

    // Public method to initiate the recursive search
    int search(const string& key) {
        return recursiveSearch(head, key, 0);
    }

    // Bubble sort for linked list
    void bubbleSort() {
        if (!head) return; // Empty list

        bool swapped;
        do {
            swapped = false;
            Node* current = head;
            Node* nextNode = head->next;

            while (nextNode) {
                if (current->data > nextNode->data) {
                    // Swap data
                    string temp = current->data;
                    current->data = nextNode->data;
                    nextNode->data = temp;
                    swapped = true;
                }
                current = nextNode;
                nextNode = nextNode->next;
            }
        } while (swapped);
    }
};

int main() {
// Initialize a new linked list
LinkedList LL;

// Insert string elements at the end
LL.insertAtEnd("apple");
LL.insertAtEnd("orange");
LL.insertAtEnd("mango");
LL.insertAtEnd("blueberry");
LL.insertAtEnd("cherry");

cout << "Original List:\n";
LL.display();

// Sort the list using bubble sort
LL.bubbleSort();

cout << "Sorted List in Ascending Order:\n";
LL.display();

// Search for a specific string
string key = "mango";
int result = LL.search(key);
if (result != -1) {
    cout << "String \"" << key << "\" found at index " << result << "." << endl;
} else {
    cout << "String \"" << key << "\" not found in the list." << endl;
}

return 0;
}