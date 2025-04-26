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

    // Array_Sort as;
    // as.mergeSort(a.both); // Q1
    // as.mergeSort(a.transactions); // Q2
    // as.mergeSort(a.reviews); // Q3

    //1
    // use all sort algorithm
    
    //2
    // use all of search algorithm

    //3
    // use all sort + search algorithm

    return 0;
}