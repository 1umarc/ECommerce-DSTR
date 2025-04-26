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
    //ll.displayBoth();

    // LinkedList_Sort lls;
    // lls.mergeSort(ll.bothHead); // Q1
    // lls.mergeSort(ll.transactionHead); // Q2
    // lls.mergeSort(ll.reviewHead); // Q3
    
    //1
    // use all sort algorithm
    
    //2
    // use all of search algorithm

    //3
    // use all sort + search algorithm
    
    return 0;
}
