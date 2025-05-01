#include "structs.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

// Linked List class
class LinkedList
{
public:
    // ----------- Function Prototypes ----------
    void delLinkedList();
    void clearCustomerList(Customer*&, int&);
    void clearReviewList(Review*&, int&);
    void clearTransactionList(Transaction*&, int&);
    void clearBothList(Both*&, int&);
    bool customerCheck(Customer*, string&);
    void uniqueAdd(Customer*&, string&);
    void customerLinkedList(string&, string&);
    void reviewLinkedList(string&);
    void transaction_bothLinkedList(string&);
    Review* reviewFinder(Review*, string&);
    void displayBoth();
    void displayTransactions();
    void displayReviews();
    // ------------------------------------------

    // Points to the first node
    Customer* customerHead;
    Review* reviewHead;
    Transaction* transactionHead;
    Both* bothHead;

    int customerSize;
    int reviewSize;
    int transactionSize;
    int bothSize;

    // Constructor - Initializes empty first node
    LinkedList()
    {
        customerHead = nullptr;
        reviewHead = nullptr;
        transactionHead = nullptr;
        bothHead = nullptr;
        customerSize = reviewSize = transactionSize = bothSize = 0;
    } 

    // Deconstructor - Mandatory to free memory as using heap
    ~LinkedList()
    {
        clearCustomerList(customerHead, customerSize);
        clearReviewList(reviewHead, reviewSize);
        clearTransactionList(transactionHead, transactionSize);
        clearBothList(bothHead, bothSize);
    }
};

// Clear Linked Lists
void LinkedList::delLinkedList() 
{
    clearCustomerList(customerHead, customerSize);
    clearReviewList(reviewHead, reviewSize);
    clearTransactionList(transactionHead, transactionSize);
    clearBothList(bothHead, bothSize);
}

void LinkedList::clearCustomerList(Customer*& head, int& size)
{
    while (head) 
    {
        Customer* next = head->next;
        delete head;
        head = next;
    }
    size = 0;
}

void LinkedList::clearReviewList(Review*& head, int& size) 
{
    while (head) 
    {
        Review* next = head->next;
        delete head;
        head = next;
    }
    size = 0;
}

void LinkedList::clearTransactionList(Transaction*& head, int& size) 
{
    while (head) 
    {
        Transaction* next = head->next;
        delete head;
        head = next;
    }
    size = 0;
}

void LinkedList::clearBothList(Both*& head, int& size) 
{
    while (head) 
    {
        Both* next = head->next;
        delete head;
        head = next;
    }
    size = 0;
}


// Check if customer ID exists
bool LinkedList::customerCheck(Customer* head, string& id) 
{
    Customer* current = head;
    while (current) 
    {
        if (current->customerID == id)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Add customerID to customer LinkedList if unique
void LinkedList::uniqueAdd(Customer*& head, string& id) 
{
    if (!customerCheck(head, id)) 
    {
        Customer* newNode = new Customer{id, nullptr};

        // If LinkedList is empty, new node becomes head
        if (head == nullptr) 
        {
            head = newNode;
        }
        else 
        {
            // Traverse to the end of the list
            Customer* current = head;
            while (current->next != nullptr) 
            {
                current = current->next;
            }
            // Add the new node at the end
            current->next = newNode;
        }
        customerSize++;
    }
}

// Build customer Linked List from both CSV files
void LinkedList::customerLinkedList(string& reviewFile, string& transactionFile) 
{
    ifstream file;
    string line;

    // Review
    file.open(reviewFile);
    if (!file.is_open()) 
    {
        cerr << "reviewsCleaned.csv has not been generated. Run clean.cpp! Terminating...\n";
        exit(1);
    }
    getline(file, line);
    while (getline(file, line)) 
    {
        stringstream ss(line);
        string productID, customerID;
        getline(ss, productID, ',');
        getline(ss, customerID, ',');
        uniqueAdd(customerHead, customerID);
    }
    file.close();

    // Read transaction file
    file.open(transactionFile);
    if (!file.is_open()) 
    {
        cerr << "transactionsCleaned.csv has not been generated. Run clean.cpp! Terminating...\n";
        exit(1);
    }
    getline(file, line);
    while (getline(file, line)) 
    {
        stringstream ss(line);
        string customerID;
        getline(ss, customerID, ',');
        uniqueAdd(customerHead, customerID);
    }
    file.close();
}

// Build Review List from CSV file
void LinkedList::reviewLinkedList(string& reviewFile) 
{
    ifstream file(reviewFile);
    string line;
    getline(file, line);

    while (getline(file, line)) 
    {
        stringstream ss(line);
        string productID, customerID, ratingStr, reviewText;
        getline(ss, productID, ',');
        getline(ss, customerID, ',');
        getline(ss, ratingStr, ',');
        getline(ss, reviewText);

        int rating = stoi(ratingStr);

        Review* newNode = new Review{productID, customerID, rating, reviewText, nullptr};

        if (reviewHead == nullptr) 
        {
            reviewHead = newNode;
        } 
        else 
        {
            Review* current = reviewHead;
            while (current->next != nullptr) 
            {
                current = current->next;
            }
            current->next = newNode;
        }
        reviewSize++;
    }
    file.close();
}

// Search Review by customerID
Review* LinkedList::reviewFinder(Review* current, string& id) 
{
    while (current) 
    {
        if (current->customerID == id)
        { 
            return current; 
        }
        current = current->next;
    }
    return nullptr;
}   

// Build Transaction & Both Linked Lists using Customer Linked List (Check & Balance)
void LinkedList::transaction_bothLinkedList(string& transactionFile) 
{
    ifstream file(transactionFile);
    string line;
    getline(file, line);

    while (getline(file, line)) 
    {
        stringstream ss(line);
        string customerID, product, category, priceStr, date, paymentMethod;
        getline(ss, customerID, ',');
        getline(ss, product, ',');
        getline(ss, category, ',');
        getline(ss, priceStr, ',');
        getline(ss, date, ',');
        getline(ss, paymentMethod);

        double price = stod(priceStr);

        // Check if this customerID exists
        if (customerCheck(customerHead, customerID)) 
        {
            // Search for a matching review
            Review* match = reviewFinder(reviewHead, customerID);

            // Add to the transaction Linked List
            Transaction* transNode = new Transaction{customerID, product, category, price, date, paymentMethod, nullptr};
            if (transactionHead == nullptr) 
            {
                transactionHead = transNode;
            } 
            else 
            {
                Transaction* current = transactionHead;
                while (current->next != nullptr) 
                {
                    current = current->next;
                }
                current->next = transNode;
            }
            transactionSize++;

            // Add to the both Linked List
            Both* bothNode = new Both;
            bothNode->customerID = customerID;
            bothNode->product = product;
            bothNode->category = category;
            bothNode->price = price;
            bothNode->date = date;
            bothNode->paymentMethod = paymentMethod;
            bothNode->next = nullptr;

            if (match) 
            {
                bothNode->productID = match->productID;
                bothNode->rating = match->rating;
                bothNode->reviewText = match->reviewText;
                //cout << "Match: " << customerID << endl;
            } 
            else 
            {
                bothNode->productID = "";
                bothNode->rating = -1;
                bothNode->reviewText = "";
            }

            if (bothHead == nullptr) 
            {
                bothHead = bothNode;
            } 
            else 
            {
                Both* current = bothHead;
                while (current->next != nullptr) 
                {
                    current = current->next;
                }
                current->next = bothNode;
            }
            bothSize++;
        }
    }
    file.close();
}


void LinkedList::displayBoth() 
{
    int count = 0;
    Both* current = bothHead;

    cout << "\n============================== Both Transaction + Review Linked List ==============================\n";
    cout << left << setw(7)  << "Node"
         << setw(10) << "CustomerID"
         << setw(16) << "Product"
         << setw(16) << "Category"
         << setw(10) << "Price"
         << setw(12) << "Date"
         << setw(20) << "Payment"
         << setw(12) << "ProductID"
         << setw(10) << "Rating"
         << "Review Text" << endl;

    cout << string(140, '-') << endl;

    while (current) 
    {
        cout << left << setw(7) << ("N." + to_string(++count))
             << setw(10) << current->customerID
             << setw(16) << current->product
             << setw(16) << current->category
             << setw(10) << fixed << setprecision(2) << current->price
             << setw(12) << current->date
             << setw(20) << current->paymentMethod
             << setw(12) << (current->productID.empty() ? "N/A" : current->productID)
             << setw(10) << (current->rating >= 0 ? to_string(current->rating) : "N/A")
             << (current->reviewText.empty() ? "N/A" : current->reviewText)
             << endl;
        current = current->next;
    }

    if (count == 1)
    {
        cout << "The Transaction + Review Linked List is NULL!" << endl;
    }
    else
    {
        cout << "Total Transaction + Review Size: " << bothSize << endl;
    }
}

void LinkedList::displayTransactions() 
{
    int count = 0;
    Transaction* current = transactionHead;

    cout << "\n============================== Transaction Linked List ==============================\n";
    cout << left << setw(7) << "Node"    
         << setw(15) << "CustomerID" 
         << setw(20) << "Product" 
         << setw(16) << "Category" 
         << setw(10) << "Price" 
         << setw(15) << "Date" 
         << setw(20) << "Payment Method" << endl;
    cout << string(100, '-') << endl;

    while (current != nullptr) 
    {
        cout << left << setw(7) << ("N." + to_string(++count))
             << setw(15) << current->customerID
             << setw(20) << current->product
             << setw(16) << current->category
             << setw(10) << fixed << setprecision(2) << current->price
             << setw(15) << current->date
             << setw(20) << current->paymentMethod << endl;
        current = current->next;
    }

    if (count == 1)
    {
        cout << "The Transaction Linked List is NULL!" << endl;
    }
    else
    {
        cout << "Total Transaction Size: " << transactionSize << endl;
    }
}

void LinkedList::displayReviews() 
{
    int count = 0;
    Review* current = reviewHead;

    cout << "\n============================== Review Linked List ==============================\n";
    cout << left << setw(7) << "Node"
         << setw(15) << "CustomerID"
         << setw(15) << "ProductID"
         << setw(10) << "Rating"
         << "Review Text" << endl;
    cout << string(80, '-') << endl;

    while (current != nullptr) 
    {
        cout << left << setw(7) << ("N." + to_string(++count))
             << setw(15) << current->customerID
             << setw(15) << current->productID
             << setw(10) << current->rating
             << current->reviewText << endl;
        current = current->next;
    }

    if (count == 1)
    {
        cout << "The Review Linked List is NULL!" << endl;
    }
    else
    {
        cout << "Total Review Size: " << reviewSize << endl;
    }
}

