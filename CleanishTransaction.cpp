#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Transaction {
    string customerID;
    string product;
    string category;
    double price;
    string date;
    string paymentMethod;
};

bool isEmpty(const string& str) {
    return str.empty() || str.find_first_not_of(' ') == string::npos;
}

bool isPriceValid(const string& priceStr) {
    if (priceStr == "NaN") return false;
    try {
        stod(priceStr);
        return true;
    } catch (...) {
        return false;
    }
}

bool isDateValid(const string& dateStr) {
    if (dateStr == "Invalid Date") return false;
    
    // Simple check for MM/DD/YYYY format
    size_t firstSlash = dateStr.find('/');
    if (firstSlash == string::npos) return false;
    
    size_t secondSlash = dateStr.find('/', firstSlash + 1);
    if (secondSlash == string::npos) return false;
    
    return true;
}

int main() {
    ifstream file("transactions.csv");
    ofstream cleaned("transactions_myVersion(CLEAN).csv");

    if (!file.is_open() || !cleaned.is_open()) {
        cerr << "File error." << endl;
        return 1;
    }

    string line;
    int count = 0;
    int skipped = 0;
    vector<Transaction> transactions;

    // Write header
    getline(file, line);
    cleaned << line << endl;

    while (getline(file, line)) {
        stringstream ss(line);
        string field;
        vector<string> fields;

        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }

        // Skip if not enough fields
        if (fields.size() < 6) {
            skipped++;
            continue;
        }

        Transaction t;
        t.customerID = fields[0];
        t.product = fields[1];
        t.category = fields[2];
        string priceStr = fields[3];
        t.date = fields[4];
        t.paymentMethod = fields[5];

        // Skip rows with missing customer ID
        if (isEmpty(t.customerID)) {
            skipped++;
            continue;
        }

        // Skip rows with invalid price
        if (!isPriceValid(priceStr)) {
            skipped++;
            continue;
        }

        // Skip rows with invalid date
        if (!isDateValid(t.date)) {
            skipped++;
            continue;
        }

        // Convert price
        try {
            t.price = stod(priceStr);
        } catch (...) {
            skipped++;
            continue;
        }

        // Write cleaned transaction
        cleaned << t.customerID << ","
                << t.product << ","
                << t.category << ","
                << t.price << ","
                << t.date << ","
                << t.paymentMethod << endl;

        transactions.push_back(t);
        count++;
    }

    file.close();
    cleaned.close();

    cout << "Cleaning complete." << endl;
    cout << "Valid transactions: " << count << endl;
    cout << "Skipped transactions: " << skipped << endl;

    return 0;
}