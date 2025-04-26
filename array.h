#include "structs.h"
#include <iostream>
#include <fstream>  
#include <sstream>
#include <string>

using namespace std;

// Bucket as a 2D Array Container
template <typename Array>
struct Bucket 
{
    Array* data;
    int size;
    int capacity;

    // Constructor - Initializes with capacity
    Bucket(int initial_capacity = 10) 
    {
        size = 0;
        capacity = initial_capacity;
        data = new Array[capacity];
    }

    // Deconstructor - Cleans up dynamically allocated memory
    ~Bucket() 
    {
        delete[] data;
    }

    // Adds a data to the bucket
    void add(const Array& newData) 
    {
        if (size >= capacity) 
        {
            resize();
        }
        data[size++] = newData;
    }
    
    // Resizes the bucket
    void resize() 
    {
        capacity *= 2;
        Array* new_data = new Array[capacity];
        for (int i = 0; i < size; ++i) 
        {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
    }
};

// Array class
class Array 
{
public:
    // Instance Bucket objects
    Bucket<Customer> customers = Bucket<Customer>();
    Bucket<Review> reviews = Bucket<Review>();
    Bucket<Transaction> transactions = Bucket<Transaction>();
    Bucket<Both> both = Bucket<Both>();

    // Check if customer ID exists
    bool customerExists(string& id) 
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
    void addCustomer(string& id) 
    {
        if (!customerExists(id)) 
        {
            customers.add(Customer{id});
        }
    }

    // Build customer Array from both CSV files
    void customerArray(string& reviewFile, string& transactionFile) 
    {
        ifstream file;
        string line;

        // Review
        file.open(reviewFile);
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
    void reviewArray(string& reviewFile) 
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
    Review findReview(string& id) 
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
    void transaction_bothArray(string& transactionFile) 
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

            // Check if this customerID exists in Customer Array
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

    void displayBoth() 
    {
        for (int i = 0; i < both.size; ++i) 
        {
            cout << "==== Transaction + Review: " << i + 1 << " ====\n";
            cout << "Customer ID: " << both.data[i].customerID << "\n";
            cout << "Product: " << both.data[i].product << "\n";
            cout << "Category: " << both.data[i].category << "\n";
            cout << "Price: " << both.data[i].price << "\n";
            cout << "Date: " << both.data[i].date << "\n";
            cout << "Payment: " << both.data[i].paymentMethod << "\n";
            cout << "Rating: " << (both.data[i].rating >= 0 ? to_string(both.data[i].rating) : "N/A") << "\n";
            cout << "Review: " << (both.data[i].reviewText.empty() ? "N/A" : both.data[i].reviewText) << "\n";
            cout << "--------------------------\n";
        }
    }

    void displayTransactions() 
    {
        for (int i = 0; i < transactions.size; ++i) 
        {
            cout << "===== Transaction: " << i + 1 << " =====\n";
            cout << "Customer ID: " << transactions.data[i].customerID << "\n";
            cout << "Product: " << transactions.data[i].product << "\n";
            cout << "Category: " << transactions.data[i].category << "\n";
            cout << "Price: " << transactions.data[i].price << "\n";
            cout << "Date: " << transactions.data[i].date << "\n";
            cout << "Payment Method: " << transactions.data[i].paymentMethod << "\n";
            cout << "--------------------------\n";
        }
    }

    void displayReviews() 
    {
        for (int i = 0; i < reviews.size; ++i) 
        {
            cout << "===== Review: " << i + 1 << " =====\n";
            cout << "Product ID: " << reviews.data[i].productID << "\n";
            cout << "Customer ID: " << reviews.data[i].customerID << "\n";
            cout << "Rating: " << reviews.data[i].rating << "\n";
            cout << "Review Text: " << (reviews.data[i].reviewText.empty() ? "N/A" : reviews.data[i].reviewText) << "\n";
            cout << "--------------------------\n";
        }
    }

    void clean()
    {

    }
};
