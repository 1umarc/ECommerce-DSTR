#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

const int MAX_SIZE = 5000;

struct Node {
    string text;
    int count;
    Node* next;
};

struct Review {
    string productID;
    string customerID;
    int rating; // rating (1 to 5)
    string text; // the actual review text
};

struct ReviewCount {
    string text;
    int count;
};

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n\"");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n\"");
    return str.substr(first, last - first + 1);
}

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
        getline(ss, r.text);

        r.productID = trim(r.productID);
        r.customerID = trim(r.customerID);
        r.text = trim(r.text);

        r.rating = stoi(ratingStr);
        reviews[count++] = r;
    }

    file.close();
    return count;
}

/////////////////////////////FREQ WORD COUNT VERSION (Q3) ////////////////////////////

//////////////////////////// ARRAY VERSION ////////////////////////////

void displayRepeatedReviewTextsArray(Review reviews[], int count) {
    ReviewCount reviewCounts[MAX_SIZE];
    int reviewCountsSize = 0;

    for (int i = 0; i < count; ++i) {
        bool found = false;
        for (int j = 0; j < reviewCountsSize; ++j) {
            if (reviewCounts[j].text == reviews[i].text) {
                reviewCounts[j].count++;
                found = true;
                break;
            }
        }
        if (!found) {
            reviewCounts[reviewCountsSize++] = {reviews[i].text, 1};
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
        insertOrUpdate(head, reviews[i].text);
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

//////////////////////////// MAIN ////////////////////////////

int main() {
    Review reviews[MAX_SIZE];
    int reviewCount = loadReviews("reviews_myVersion(CLEAN2).csv", reviews);

    if (reviewCount == 0) {
        cout << "No reviews loaded." << endl;
        return 1;
    }

    displayRepeatedReviewTextsArray(reviews, reviewCount);
    cout << "\n\n";
    displayRepeatedReviewTextsLinkedList(reviews, reviewCount);

    return 0;
}
