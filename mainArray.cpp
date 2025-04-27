#include "algorithms_lm.h"

using namespace std;

int main() 
{
    Array a;

    string reviewFile = "reviews_lecturer.csv";
    string transactionFile = "transactions_lecturer.csv";

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
    aso.mergeSort(a.both);
    //a.displayBoth();
    h.frequencyArray(a.both, "date"); // END: just to display the total number by date
    
    // Q2 - use all of search algorithm
    int transSize = ase.sequentialSearch(a.transactions, "category", "Electronics", "paymentMethod", "Credit Card");
    cout << "Size: " << transSize << endl;
    double num = h.calculatePercentage(transSize, a.transactions.size); //END: just to display percentage
    cout << num << "%" << endl;

    // Q3 - use all sort + search algorithm;
    int reviewSize = ase.sequentialSearch(a.reviews, "rating", "1");
    cout << "Size: " << reviewSize << endl;
    Bucket<Frequency> frequencies = h.frequencyArray(a.reviews, "reviewText"); // BETWEEN: returns a frequency array, to be sorted by u
    aso.mergeSort(frequencies);
    h.displayFrequencyA(frequencies, "reviewText");

    return 0;
}