#include "algorithms.h"

using namespace std;    

int main()
{
    LinkedList ll;

    string reviewFile = "reviewsCleaned.csv";        
    string transactionFile = "transactionsCleaned.csv";

    ll.customerLinkedList(reviewFile, transactionFile);
    ll.reviewLinkedList(reviewFile);
    ll.transaction_bothLinkedList(transactionFile);
    
    //a.displayTransactions();
    //a.displayBoth();
    //a.displayReviews();

    LinkedList_Sort llso;
    LinkedList_Search llse;
    Helper h;
  
    // Q1 - use all sort algorithm
    llso.bubbleSort(ll.bothHead);
    Frequency* freqHead = h.frequencyLinkedList(ll.bothHead, "date", "Both");
    h.displayFrequencyLL(freqHead, "date");

    // Q2 - use all of search algorithm
    int filteredSize = 0;
    ll.transactionHead = llse.recursiveSearch(&filteredSize, ll.transactionHead, "category", "Electronics", "paymentMethod", "Credit Card");
    cout << "Filtered Size: " << filteredSize << endl;
    double num = h.calculatePercentage(filteredSize, ll.transactionSize); //END: just to display percentage
    cout << num << "%" << endl;

    // Q3 - use all sort + search algorithm
    int reviewSize = 0;
    ll.reviewHead = llse.recursiveSearch(&reviewSize, ll.reviewHead, "rating", "1");
    cout << "Filtered Size: " << reviewSize << endl;
    Frequency* freqHead = h.frequencyLinkedList(ll.reviewHead, "reviewText", "Review");
    llso.bubbleSort(freqHead);
    h.displayFrequencyLL(freqHead, "reviewText");

    return 0;
}
