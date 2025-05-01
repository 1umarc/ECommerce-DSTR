#include "algorithms.h"

using namespace std;

int main() 
{
    Array a;

    string reviewFile = "reviewsCleaned.csv";
    string transactionFile = "transactionsCleaned.csv";

    a.initializeBuckets(reviewFile, transactionFile);
    a.customerArray(reviewFile, transactionFile);
    a.reviewArray(reviewFile);
    a.transaction_bothArray(transactionFile);

    //a.displayTransactions();
    //a.displayBoth();
    //a.displayReviews();

    Array_Sort aso;
    Array_Search ase;
    Helper h;

    // Q1 - use all sort algorithm
    aso.heapSort(a.both);  
    FrequencyBucket frequencies = h.frequencyArray(a.both.data, "date", "Both", a.both.size);
    h.displayFrequencyA(frequencies, "date");
    
    // Q2 - use all of search algorithm
    double transactionSize = a.transactions.size;
    int filteredSize = ase.jumpSearch(a.transactions, "category", "Electronics", "paymentMethod", "Credit Card");
    cout << "Filtered Size: " << filteredSize << endl;
    double num = h.calculatePercentage(filteredSize, transactionSize); //END: just to display percentage
    cout << num << "%" << endl;

    // Q3 - use all sort + search algorithm;
    int reviewSize = ase.jumpSearch(a.reviews, "rating", "1");
    cout << "Filtered Size: " << reviewSize << endl;
    FrequencyBucket frequencies = h.frequencyArray(a.reviews.data, "reviewText", "Review", reviewSize); // BETWEEN: returns a frequency array, to be sorted by u
    aso.insertionSort(frequencies);
    h.displayFrequencyA(frequencies, "reviewText");

    return 0;
}