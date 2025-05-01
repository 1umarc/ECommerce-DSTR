#include "buckets.h"
#include <iostream>
#include <fstream>  
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

// Array class
class Array 
{
public:
    // ----------- Function Prototypes ----------
    void delArray();
    void initializeBuckets(string&, string&);
    bool customerExists(string&);
    void addCustomer(string&);
    void customerArray(string&, string&);
    void reviewArray(string&);
    Review findReview(string&);
    void transaction_bothArray(string&);
    void displayBoth();
    void displayTransactions();
    void displayReviews();
    // ------------------------------------------

    // Instance Bucket objects
    CustomerBucket customers;
    ReviewBucket reviews;
    TransactionBucket transactions;
    BothBucket both;
};


void Array::delArray() 
{
    customers.size = 0;
    reviews.size = 0;
    transactions.size = 0;
    both.size = 0;
}

void Array::initializeBuckets(string& reviewFile, string& transactionFile) 
{
    int reviewCount = 0, transactionCount = 0;
    string line;

    ifstream file(reviewFile);
    getline(file, line);
    while (getline(file, line))
    {
        reviewCount++;
    }
    file.close();

    file.open(transactionFile);
    getline(file, line);
    while (getline(file, line))
    {
        transactionCount++;
    }
    file.close();

    // Initialize array sizes to counts
    customers.initialize(reviewCount + transactionCount);
    reviews.initialize(reviewCount);
    transactions.initialize(transactionCount);
    both.initialize(transactionCount);
}

// Check if customer ID exists
bool Array::customerExists(string& id) 
{
    for (int i = 0; i < customers.size; ++i) 
    {
        if (customers.data[i].customerID == id)
        {
            return true;
        }
    }
    return false;
}

// Add customerID to customer Array if unique
void Array::addCustomer(string& id) 
{
    if (!customerExists(id)) 
    {
        customers.add(Customer{id});
    }
}

// Build customer Array from both CSV files
void Array::customerArray(string& reviewFile, string& transactionFile) 
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
        addCustomer(customerID);
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
        addCustomer(customerID);
    }
    file.close();
}

// Build Review Array from CSV file
void Array::reviewArray(string& reviewFile) 
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

        reviews.add({productID, customerID, rating, reviewText});
    }
    file.close();
}

// Search Review by customerID
Review Array::findReview(string& id) 
{
    for (int i = 0; i < reviews.size; ++i) 
    {
        if (reviews.data[i].customerID == id) 
        {
            return reviews.data[i];
        }
    }
    return Review();
}

// Build Transaction & Both Arrays using Customer Array (Check & Balance)
void Array::transaction_bothArray(string& transactionFile) 
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
        if (customerExists(customerID)) 
        {
            // Search for a matching review
            Review match = findReview(customerID);

            // Add to the transaction Array
            transactions.add(Transaction{customerID, product, category, price, date, paymentMethod});

            if (!match.customerID.empty())
            {
                both.add(Both{customerID, product, category, price, date, paymentMethod, match.productID, match.rating, match.reviewText});
                //cout << "Match: " << customerID << endl;
            }
            else
            {
                both.add(Both{customerID, product, category, price, date, paymentMethod, "", -1,""});
            }
        }
    }
    file.close();
}


void Array::displayBoth() 
{
    cout << "\n============================== Both Transaction + Review Array ==============================\n";
    cout << left << setw(6)  << "Row"
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

    for (int i = 0; i < both.size; ++i) 
    {
        const Both& b = both.data[i];

        cout << "[" << left << setw(3) << (i + 1) << "]  "
            << setw(10) << b.customerID
            << setw(16) << b.product
            << setw(16) << b.category
            << setw(10) << fixed << setprecision(2) << b.price
            << setw(12) << b.date
            << setw(20) << b.paymentMethod
            << setw(12) << (b.productID.empty() ? "N/A" : b.productID)
            << setw(10) << (b.rating >= 0 ? to_string(b.rating) : "N/A")
            << (b.reviewText.empty() ? "N/A" : b.reviewText) << endl;
    }
    cout << "\nTotal Transaction + Review Size: " << both.size << endl;
}

void Array::displayTransactions() 
{
    cout << "\n============================== Transaction Array ==============================\n";
    cout << left << setw(6) << "Row"
        << setw(15) << "CustomerID"
        << setw(20) << "Product"
        << setw(16) << "Category"
        << setw(10) << "Price"
        << setw(15) << "Date"
        << setw(20) << "Payment Method" << endl;

    cout << string(110, '-') << endl;

    for (int i = 0; i < transactions.size; ++i) 
    {
        const Transaction& t = transactions.data[i];

        cout << "[" << left << setw(3) << (i + 1) << "]  "
            << setw(15) << t.customerID
            << setw(20) << t.product
            << setw(16) << t.category
            << setw(10) << fixed << setprecision(2) << t.price
            << setw(15) << t.date
            << setw(20) << t.paymentMethod << endl;
    }
    cout << "\nTotal Transaction Size: " << transactions.size << endl;
}

void Array::displayReviews() 
{
    cout << "\n============================== Review Array ==============================\n";
    cout << left << setw(6) << "Row"
        << setw(15) << "CustomerID"
        << setw(15) << "ProductID"
        << setw(10) << "Rating"
        << "Review Text" << endl;

    cout << string(80, '-') << endl;

    for (int i = 0; i < reviews.size; ++i) 
    {
        const Review& r = reviews.data[i];

        cout << "[" << left << setw(3) << (i + 1) << "]  "
            << setw(15) << r.customerID
            << setw(15) << r.productID
            << setw(10) << r.rating
            << (r.reviewText.empty() ? "N/A" : r.reviewText) << endl;
    }
    cout << "\nTotal Review Size: " << reviews.size << endl;
}

