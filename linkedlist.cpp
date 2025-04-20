//#include "algorithms.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Node 
{
    // Common field
    string customerID;
    Node* next;

    // Review fields
    string productID;
    int rating;
    string reviewText;

    // Transaction fields
    string product;
    string category;
    double price;
    string date;
    string paymentMethod;

    bool isReview; // Flag to indicate review or transaction node
};


// Linked List class
class LinkedList
{
private:
    // Points to the first node
    Node* head;
    int size;

public:
    // Constructor - Initializes empty first node
    LinkedList()
    {
        head = nullptr;
        size = 0;
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
        size = 0;
    }

    // Inserting nodes from the csv files to form Linked List - O(1)
    void read(bool isReview)
    {   
        string filePath;
        if (isReview)
        {
            filePath = "reviews.csv";
        }
        else
        {
            filePath = "transactions_lecturer.csv";
        }
        ifstream file(filePath);

        string line;
        getline(file, line); // Skips header

        while (getline(file, line))
        {
            stringstream ss(line);
            // Creates new node which is the new head
            Node* newNode = new Node();
            newNode->next = nullptr;
            newNode->isReview = isReview;

            if (isReview)
            {
                string productID, customerID, ratingStr, reviewText;
                getline(ss, productID, ',');
                getline(ss, customerID, ',');
                getline(ss, ratingStr, ',');
                getline(ss, reviewText);

                newNode->productID = productID;
                newNode->customerID = customerID;
                try {
                    newNode->rating = stoi(ratingStr);
                } catch (const std::invalid_argument& e) {
                    cerr << "Invalid rating value: '" << ratingStr << "' in reviews.csv" << endl;
                    delete newNode; // prevent memory leak
                    continue;       // skip this line
                } //convert ratingStr back to int
                newNode->reviewText = reviewText;
            }
            else
            {
                string customerID, product, category, priceStr, date, paymentMethod;
                getline(ss, customerID, ',');
                getline(ss, product, ',');
                getline(ss, category, ',');
                getline(ss, priceStr, ',');
                getline(ss, date, ',');
                getline(ss, paymentMethod);

                newNode->customerID = customerID;
                newNode->product = product;
                newNode->category = category;
                newNode->price = stod(priceStr); //convert ratingStr back to double
                newNode->date = date;
                newNode->paymentMethod = paymentMethod;
            }

            // Inserts from beginning, at head
            newNode->next = head;
            head = newNode;
            size++;
        }
        file.close();
    }


    // Print the Linked List
    void display() 
    {
        // Traverses from head to NULL
        Node* current = head;
        int count = 1;

        while (current != nullptr)
        {
            if (current->isReview)
            {
                cout << "===== Reviews Node: " << count++ << " =====\n";
                cout << "Customer ID: " << current->customerID << "\n";
                cout << "Product ID: " << current->productID << "\n";
                cout << "Rating: " << current->rating << "\n";
                cout << "Review Text: " << current->reviewText << "\n";
            }
            else
            {
                cout << "===== Transactions Node: " << count++ << " =====\n";
                cout << "Customer ID: " << current->customerID << "\n";
                cout << "Product: " << current->product << "\n";
                cout << "Category: " << current->category << "\n";
                cout << "Price: " << current->price << "\n";
                cout << "Date: " << current->date << "\n";
                cout << "Payment Method: " << current->paymentMethod << "\n";
            }
            current = current->next;  
        }
        if (size == 0)
        {
            cout << "The Linked List is NULL!" << endl;
        }
    }

    void clean()
    {

    }

    //Q1
    void parseDate()
    {
        Node->date.substr(0, 2);
    }

    //2
    void percentage()
    {

    }

    //3
    void textFrequency()
    {
        
    }
};

int main()
{
    LinkedList l;
    // Reviews.csv
    l.read(true);
    l.display();

    // Transactions.csv
    l.read(false);
    l.display();  

    //1
    // use all sort algorithm
    // l.read(true);
    // LinkedList_Sort.mergeSort(l);
    // l.display();

    //2
 
    // use all of search algorithm

    //3

    // use all sort + search algorithm
    
    return 0;
}
