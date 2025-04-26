#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct Review {
    string productID;
    string customerID;
    int rating;
    string reviewText;
};

bool isEmpty(const string& str) {
    return str.empty() || str == "\"\"" || str == " ";
}

// Ensure reviewText is wrapped in double quotes if not already
string ensureQuoted(const string& str) {
    if (str.length() >= 2 && str.front() == '"' && str.back() == '"') {
        return str;
    }
    return "\"" + str + "\"";
}

int main() {
    ifstream file("reviews.csv");
    ofstream cleaned("reviews_myVersion(CLEAN2).csv");

    if (!file.is_open() || !cleaned.is_open()) {
        cerr << "File error." << endl;
        return 1;
    }

    string line;
    int count = 0;
    Review reviews[6000];

    getline(file, line); // Get and write the header
    cleaned << line << endl;

    while (getline(file, line) && count < 6000) {
        stringstream ss(line);
        string ratingStr;
        string productID, customerID, reviewText;

        getline(ss, productID, ',');
        getline(ss, customerID, ',');
        getline(ss, ratingStr, ',');
        getline(ss, reviewText); // rest of the line

        if (isEmpty(productID) || isEmpty(customerID) || isEmpty(ratingStr) || isEmpty(reviewText)) {
            continue;
        }

        int rating = -1;
        try {
            rating = stoi(ratingStr);
        } catch (...) {
            continue;
        }

        // Write line with quote-handled reviewText
        cleaned << productID << "," << customerID << "," << rating << "," << ensureQuoted(reviewText) << endl;

        // Optional: store in memory
        reviews[count].productID = productID;
        reviews[count].customerID = customerID;
        reviews[count].rating = rating;
        reviews[count].reviewText = reviewText;
        count++;
    }

    file.close();
    cleaned.close();

    cout << "Cleaning complete. Valid rows stored: " << count << endl;
    return 0;
}
