#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAX_SIZE = 5000;

// Struct for transaction.csv
struct Transaction {
    // string** data;
    string customerID;
    string product;
    string category;
    double price;
    string dateStr;
    int sortableDate;
    string paymentMethod;
};

// Node for the linked list
struct Node {
    Transaction data;
    Node* next;
    string text;
    int count;
};

struct ReviewCount {
    string text;
    int count;
};

// Struct for review.csv /////
struct Review {
    string productID;
    string customerID;
    int rating;
    string reviewText;
};

// Struct for combined data
struct CombinedBothDataset {
    string customerID;
    string product;
    string category;
    double price;
    string dateStr;
    int sortableDate;
    string paymentMethod;
    int rating;
    string reviewText;
};

// Struct combining transaction and review
struct CombinedData {
    string customerID;
    string reviewText;
    string dateStr;
    int sortableDate;
};

// Trim whitespace from string
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");
    return (first == string::npos) ? "" : str.substr(first, last - first + 1);
}

// Convert DD/MM/YYYY to YYYYMMDD int
int convertDate(const string& dateStr) {
    stringstream ss(dateStr);
    string day, month, year;
    getline(ss, day, '/');
    getline(ss, month, '/');
    getline(ss, year);

    if (day.length() == 1) day = "0" + day;
    if (month.length() == 1) month = "0" + month;

    return stoi(year + month + day);
}

// Insertion sort by date
void insertionSortCombined(CombinedData arr[], int size) {
    for (int i = 1; i < size; i++) {
        CombinedData key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].sortableDate > key.sortableDate) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Load transaction data
int loadTransactions(const string& filename, Transaction transactions[]) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open " << filename << endl;
        return 0;
    }

    string line;
    getline(file, line); // Skip header
    int count = 0;

    while (getline(file, line) && count < MAX_SIZE) {
        stringstream ss(line);
        Transaction t;
        string priceStr;

        getline(ss, t.customerID, ',');
        getline(ss, t.product, ',');
        getline(ss, t.category, ',');
        getline(ss, priceStr, ',');
        getline(ss, t.dateStr, ',');
        getline(ss, t.paymentMethod);

        // Trim values
        t.customerID = trim(t.customerID);
        t.dateStr = trim(t.dateStr);
        t.sortableDate = convertDate(t.dateStr);
        t.price = stod(priceStr);

        transactions[count++] = t;
    }

    file.close();
    return count;
}

// Load review data
int loadReviews(const string& filename, Review reviews[]) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open " << filename << endl;
        return 0;
    }

    string line;
    getline(file, line); // Skip header
    int count = 0;

    while (getline(file, line) && count < MAX_SIZE) {
        stringstream ss(line);
        Review r;
        string ratingStr;

        getline(ss, r.productID, ',');
        getline(ss, r.customerID, ',');
        getline(ss, ratingStr, ',');
        getline(ss, r.reviewText);

        r.customerID = trim(r.customerID);
        r.reviewText = trim(r.reviewText);
        r.rating = stoi(ratingStr);

        reviews[count++] = r;
    }

    file.close();
    return count;
}

// Merge data by customerID
int mergeData(Transaction transactions[], int tCount, Review reviews[], int rCount, CombinedData combined[]) {
    int combinedCount = 0;

    for (int i = 0; i < tCount; i++) {
        CombinedData entry;
        entry.customerID = transactions[i].customerID;
        entry.dateStr = transactions[i].dateStr;
        entry.sortableDate = transactions[i].sortableDate;
        entry.reviewText = "No Review"; // Default

        // Match review by customerID
        for (int j = 0; j < rCount; j++) {
            if (transactions[i].customerID == reviews[j].customerID) {
                entry.reviewText = reviews[j].reviewText;
                break;
            }
        }

        combined[combinedCount++] = entry;
    }

    return combinedCount;
}

// // Display merged data
// void displayCombined(CombinedData combined[], int count) {
//     cout << "\nCombined Data (Sorted by Date):\n";
//     for (int i = 0; i < count; i++) {
//         cout << combined[i].dateStr << " | " << combined[i].customerID
//              << " | Review: " << combined[i].reviewText << endl;
//     }
// }

// Display merged data (only first 100 lines)
void displayCombined(CombinedData combined[], int count) {
    cout << "\nCombined Data (Sorted by Date[100]):\n";
    int displayCount = min(count, 100);  // Display only up to 100 entries
    for (int i = 0; i < displayCount; i++) {
        cout << combined[i].dateStr << " | " << combined[i].customerID
             << " | Review: " << combined[i].reviewText << endl;
    }
    if (count > 100) {
        cout << "...Only showing first 100 entries out of " << count << "...\n";
    }
}

////////////////////////////////////////////////////////////////////////////////////
//////Q2/////////////
// Build linked list from transaction array
Node* buildLinkedList(const Transaction transactions[], int size) {
    Node* head = nullptr;
    for (int i = 0; i < size; ++i) {
        Node* newNode = new Node{transactions[i], head};
        head = newNode;
    }
    return head;
}

// Count Electronics purchases with Credit Card
int countElectronicsWithCreditCard(int mode, Node* head, const Transaction transactions[], int size) {
    int count = 0;

    if (mode == 1) { // linked list
        Node* current = head;
        while (current != nullptr) {
            if (current->data.category == "Electronics" && current->data.paymentMethod == "Credit Card") {
                count++;
            }
            current = current->next;
        }
    } else if (mode == 2) { // array
        for (int i = 0; i < size; i++) {
            if (transactions[i].category == "Electronics" && transactions[i].paymentMethod == "Credit Card") {
                count++;
            }
        }
    }

    return count;
}



// int countElectronicsWithCreditCard(int mode, Node* head, const Transaction transactions[], int size) {
//     int count = 0;
//     Transaction* t = &current->data;
//     const Transaction* t = &transactions[i];
//     if (mode == 1) { // linked list
//         for (Node* current = head; current != nullptr; current = current->next) {
//             if (t->category == "Electronics" && t->paymentMethod == "Credit Card") {
//             }
//         }
//     } 
//     else if (mode == 2) { // array
//         for (int i = 0; i < size; i++) {
//             if (t->category == "Electronics" && t->paymentMethod == "Credit Card") {
//             }
//         } count++;
//     }

//     return count;
// }

// Percentage calculation
int calculatePercentage(int electronicsWithCreditCard, int totalElectronics) {
    if (totalElectronics == 0) return 0;
    double percentage = (static_cast<double>(electronicsWithCreditCard) / totalElectronics) * 100;
    return static_cast<int>(round(percentage));
}
////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////FREQ WORD COUNT VERSION (Q3) ////////////////////////////

//////////////////////////// ARRAY VERSION ////////////////////////////

void displayRepeatedReviewTextsArray(Review reviews[], int count) {
    ReviewCount reviewCounts[MAX_SIZE];
    int reviewCountsSize = 0;

    for (int i = 0; i < count; ++i) {
        bool found = false;
        for (int j = 0; j < reviewCountsSize; ++j) {
            if (reviewCounts[j].text == reviews[i].reviewText) {
                reviewCounts[j].count++;
                found = true;
                break;
            }
        }
        if (!found) {
            reviewCounts[reviewCountsSize++] = {reviews[i].reviewText, 1};
        }
    }

    cout << "\n[ARRAY] Review Text Repetition Summary:\n";
    int mostRepeatedIndex = 0;
    for (int i = 0; i < reviewCountsSize; ++i) {
        cout << "\"" << reviewCounts[i].text << "\" was repeated " << reviewCounts[i].count << " time(s)." << endl;
        
        if (reviewCounts[i].count > reviewCounts[mostRepeatedIndex].count) {
            mostRepeatedIndex = i;
        }
    }

    if (reviewCountsSize > 0) {
        cout << "\nMost repeated review:\n\""
             << reviewCounts[mostRepeatedIndex].text
             << "\" repeated "
             << reviewCounts[mostRepeatedIndex].count
             << " time(s)." << endl;
    }
}

//////////////////////////// LINKED LIST VERSION ////////////////////////////

void insertOrUpdate(Node*& head, const string& reviewText) {
    for (Node* current = head; current != nullptr; current = current->next) {
        if (current->text == reviewText) {
            current->count++;
            return;
        }
    }

    head = new Node{reviewText, 1, head};
}

void displayRepeatedReviewTextsLinkedList(Review reviews[], int count) {
    Node* head = nullptr;

    for (int i = 0; i < count; ++i) {
        insertOrUpdate(head, reviews[i].reviewText);
    }

    cout << "\n[LINKED LIST] Review Text Repetition Summary:\n";
    Node* mostRepeated = nullptr;
    for (Node* current = head; current != nullptr; current = current->next) {
        cout << "\"" << current->text << "\" was repeated " << current->count << " time(s)." << endl;
        if (mostRepeated == nullptr || current->count > mostRepeated->count) {
            mostRepeated = current;
        }
    }

    if (mostRepeated != nullptr) {
        cout << "\nMost repeated review:\n\"" << mostRepeated->text << "\" repeated " << mostRepeated->count << " time(s)." << endl;
    }

}
//////////////////////////////////////////////

int main() {
    Transaction transactions[MAX_SIZE];
    Review reviews[MAX_SIZE];
    CombinedData combined[MAX_SIZE];

    // Load data
    int transactionCount = loadTransactions("transactions_myVersion(CLEAN).csv", transactions);
    int reviewCount = loadReviews("reviews_myVersion(CLEAN2).csv", reviews);

    cout << "Loaded " << transactionCount << " transactions.\n";
    cout << "Loaded " << reviewCount << " reviews.\n";

    // Merge
    int combinedCount = mergeData(transactions, transactionCount, reviews, reviewCount, combined);
    cout << "Merged into " << combinedCount << " combined entries.\n";

    // Sort
    insertionSortCombined(combined, combinedCount);

    // Display
    if (combinedCount > 0) {
        displayCombined(combined, combinedCount);
    } else {
        cout << "No data to display. Make sure customerIDs match in both files.\n";
    }



///////////////////////////////////////////// Q2 ////////////////////////////////////////////////////
    // Count total electronics
    int electronicsCount = 0;
    for (int i = 0; i < transactionCount; ++i) {
        if (transactions[i].category == "Electronics") {
            electronicsCount++;
        }
    }

    // Build linked list
    Node* head = buildLinkedList(transactions, transactionCount);

    // Count electronics with credit card (Linked List)
    int electronicsWithCreditCard = countElectronicsWithCreditCard(1, head, transactions, transactionCount);

    // Count electronics with credit card (Array)
    int electronicsWithCreditCard = countElectronicsWithCreditCard(2, head, transactions, transactionCount);

    // Calculate percentage
    int percentage = calculatePercentage(electronicsWithCreditCard, electronicsCount);

    cout << "Percentage of 'Electronics' purchases made with 'Credit Card': " << percentage << "%" << endl;

    return 0;

///////////////////////////////////////////// Q3 ////////////////////////////////////////////////////
}