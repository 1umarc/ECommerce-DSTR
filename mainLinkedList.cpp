#include "algorithms_lm.h"

using namespace std;

int main()
{
    LinkedList ll;

    string reviewFile = "reviews_lecturer.csv";               // TO DO: can't run reviews
    string transactionFile = "transactions_lecturer.csv";

    ll.customerLinkedList(reviewFile, transactionFile);
    ll.reviewLinkedList(reviewFile);
    ll.transaction_bothLinkedList(transactionFile);
    
    //ll.displayReviews();  
    //ll.displayTransactions();

    LinkedList_Sort llso;
    LinkedList_Search llse;
    Helper h;
  
    // Q1 - use all sort algorithm
    llso.mergeSort(ll.bothHead);
    //ll.displayBoth();
    h.frequencyLinkedList(ll.bothHead, "date");
    
    // Q2 - use all of search algorithm
    int transSize = llse.sequentialSearch(ll.transactionHead, "category", "Electronics", "paymentMethod", "Credit Card");
    cout << "Size: " << transSize << endl;
    double num = h.calculatePercentage(transSize, ll.transactionSize);
    cout << num << "%" << endl;

    // Q3 - use all sort + search algorithm
    int reviewSize = llse.sequentialSearch(ll.reviewHead, "rating", "1");
    cout << "Size: " << reviewSize << endl;
    Frequency* freqHead = h.frequencyLinkedList(ll.reviewHead, "reviewText");
    llso.mergeSort(freqHead);
    h.displayFrequencyLL(freqHead, "reviewText");

    return 0;
}
