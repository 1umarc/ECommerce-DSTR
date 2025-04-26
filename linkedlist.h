#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Review
struct Review 
{
    string customerID;
    string productID;
    int rating;
    string reviewText;
    Review* next;
};

// Transaction
struct Transaction 
{
    string customerID;
    string product;
    string category;
    double price;
    string date;
    string paymentMethod;
    Transaction* next;
};

// Both (Transaction + Review)
struct Both 
{
    string customerID;
    string product;
    string category;
    double price;
    string date;
    string paymentMethod;
    string productID;
    int rating;
    string reviewText;
    Both* next;
};

// Customer
struct Customer 
{
    string customerID;
    Customer* next;
};


// Linked List class
class LinkedList
{
public:
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
        clearList(customerHead, customerSize);
        clearList(reviewHead, reviewSize);
        clearList(transactionHead, transactionSize);
        clearList(bothHead, bothSize);
    }   

    template<typename Node>
    void clearList(Node*& delNode, int& size) 
    {
        // Retrieves head, store address of next node, deletes, then repeats
        while (delNode) 
        {
            Node* next = delNode->next;
            delete delNode;
            delNode = next;
        }
        size = 0;
    }

    // Check if customer ID exists
    bool customerCheck(Customer* head, string& id) 
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
    void uniqueAdd(Customer*& head, string& id) 
    {
        if (!customerCheck(head, id)) 
        {
            Customer* newNode = new Customer{id, head};
            head = newNode;
            customerSize++;
        }
    }

    // Build customer Linked List from both CSV files
    void customerLinkedList(string& review, string& transaction) 
    {
        ifstream file;
        string line;

        // Review
        file.open(review);
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
        file.open(transaction);
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
    void reviewLinkedList(string& reviewFile) 
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

            Review* newNode = new Review{customerID, productID, rating, reviewText, reviewHead};
            reviewHead = newNode;
            reviewSize++;
        }
        file.close();
    }

    // Search Review by customerID
    Review* reviewFinder(Review* current, string& id) 
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
    void transaction_bothLinkedList(string& transactionFile) 
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

            // Check if this customerID exists in Customer Linked List
            if (customerCheck(customerHead, customerID)) 
            {
                // Search for a matching review
                Review* match = reviewFinder(reviewHead, customerID);

                // Add to the transaction Linked List
                Transaction* transNode = new Transaction{customerID, product, category, price, date, paymentMethod, transactionHead};
                transactionHead = transNode;
                transactionSize++;

                // Add to the both Linked List
                Both* bothNode = new Both;
                bothNode->customerID = customerID;
                bothNode->product = product;
                bothNode->category = category;
                bothNode->price = price;
                bothNode->date = date;
                bothNode->paymentMethod = paymentMethod;

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
                bothNode->next = bothHead;
                bothHead = bothNode;
                bothSize++;
            }
        }
        file.close();
    }

    // Print the both Linked List
    void displayBoth() 
    {
        int count = 1;
        Both* current = bothHead;
        while (current) 
        {
            cout << "==== Transaction + Review Node: " << count++ << " ====\n";
            cout << "Customer ID: " << current->customerID << endl;
            cout << "Product: " << current->product << endl;
            cout << "Category: " << current->category << endl;
            cout << "Price: " << current->price << endl;
            cout << "Date: " << current->date << endl;
            cout << "Payment Method: " << current->paymentMethod << endl;
            cout << "Review Rating: " << (current->rating >= 0 ? to_string(current->rating) : "N/A") << endl;
            cout << "Review Text: " << (current->reviewText.empty() ? "N/A" : current->reviewText) << endl;
            cout << "--------------------------\n";
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

    // Print the transactions Linked List
    void displayTransactions() 
    {
        int count = 1;
        Transaction* current = transactionHead;
    
        while (current != nullptr) 
        {
            cout << "===== Transaction Node: " << count++ << " =====\n";
            cout << "Customer ID: " << current->customerID << "\n";
            cout << "Product: " << current->product << "\n";
            cout << "Category: " << current->category << "\n";
            cout << "Price: " << current->price << "\n";
            cout << "Date: " << current->date << "\n";
            cout << "Payment Method: " << current->paymentMethod << "\n";
            cout << "--------------------------\n";
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

    // Print the reviews Linked List
    void displayReviews() 
    {
        int count = 1;
        Review* current = reviewHead;

        while (current != nullptr) 
        {
            cout << "===== Review Node: " << count++ << " =====\n";
            cout << "Customer ID: " << current->customerID << "\n";
            cout << "Product ID: " << current->productID << "\n";
            cout << "Rating: " << current->rating << "\n";
            cout << "Review Text: " << current->reviewText << "\n";
            cout << "--------------------------\n";
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

    void clean()
    {

    }
};
