#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

// ----------- Function Prototypes ----------
bool isEmpty(string&);
bool isPriceValid(string&);
bool isDateValid(string&);
string ensureQuoted(string&);
int countDataLines(string&);
// ------------------------------------------

// Remove lines with empty values
bool isEmpty(string& str) 
{
    return str.empty() || str == "\"\"" || str.find_first_not_of(' ') == string::npos;
}

// Validation Checks
bool isPriceValid(string& priceStr) 
{
    if (priceStr == "NaN") return false;
    try {
        stod(priceStr);
        return true;
    } catch (...) {
        return false;
    }
}

bool isDateValid(string& dateStr)
{
    if (dateStr == "Invalid Date")
    {
        return false;
    }

    // Simple check for MM/DD/YYYY format
    size_t firstSlash = dateStr.find('/');
    if (firstSlash == string::npos)
    {
        return false;
    }
    size_t secondSlash = dateStr.find('/', firstSlash + 1);
    if (secondSlash == string::npos)
    {
        return false;
    }
    return true;
}

// Ensure reviewText is wrapped in double quotes if not already
string ensureQuoted(string& str) 
{
    if (str.length() >= 2 && str.front() == '"' && str.back() == '"') 
    {
        return str;
    }
    return "\"" + str + "\"";
}

// Validation of amount of lines 
int countDataLines(string& filename)
{
    int count = 0;
    ifstream file(filename);
    string line;
    while (getline(file, line))
    {
        count++;
    }
    file.close();
    return count;
}

int main() 
{
    string reviewFile = "reviews.csv";
    string transactionFile = "transactions.csv";

    ifstream reviewIn(reviewFile);
    ifstream transIn(transactionFile);
    ofstream reviewOut("reviewsCleaned.csv");
    ofstream transOut("transactionsCleaned.csv");

    int oldReviewSize = countDataLines(reviewFile) - 1; // -1 to skip header
    int oldTransSize = countDataLines(transactionFile) - 1;
    int newReviewSize = 0;
    int newTransSize = 0;

    // Clean Reviews
    string line;
    getline(reviewIn, line);
    reviewOut << line << endl;

    while (getline(reviewIn, line)) 
    {
        stringstream ss(line);
        string productID, customerID, ratingStr, reviewText;

        getline(ss, productID, ',');
        getline(ss, customerID, ',');
        getline(ss, ratingStr, ',');
        getline(ss, reviewText);

        if (isEmpty(productID) || isEmpty(customerID) || isEmpty(ratingStr) || isEmpty(reviewText))
        {
            continue;
        }

        int rating;
        try 
        {
            rating = stoi(ratingStr);
        } catch (...) 
        {
            continue;
        }

        reviewOut << productID << "," << customerID << "," << rating << "," << ensureQuoted(reviewText) << endl;
        newReviewSize++;
    }

    // Clean Transactions
    getline(transIn, line);
    transOut << line << endl;

    while (getline(transIn, line)) 
    {
        stringstream ss(line);
        string customerID, product, category, priceStr, date, paymentMethod;

        getline(ss, customerID, ',');
        getline(ss, product, ',');
        getline(ss, category, ',');
        getline(ss, priceStr, ',');
        getline(ss, date, ',');
        getline(ss, paymentMethod);

        if (isEmpty(customerID) || isEmpty(product) || isEmpty(category) || isEmpty(priceStr) || isEmpty(date) || isEmpty(paymentMethod) 
            || !isPriceValid(priceStr) || !isDateValid(date))
        {
            continue;
        }

        double price;
        try 
        {
            price = stod(priceStr);
        } catch (...) 
        {
            continue;
        }

        transOut << customerID << "," << product << "," << category << "," << fixed << setprecision(2) << price << "," << date << "," << paymentMethod << endl;
        newTransSize++;
    }

    reviewIn.close();
    transIn.close();
    reviewOut.close();
    transOut.close();

    cout << "Data Cleaning Complete!\n";
    cout << "Valid reviews stored: " << newReviewSize << " / " << oldReviewSize << endl;
    cout << "Valid transactions stored: " << newTransSize << " / " << oldTransSize << endl;
}

