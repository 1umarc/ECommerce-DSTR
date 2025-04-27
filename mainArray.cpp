//#include "algorithms_lm.h"
#include "helper.h"

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
    bool test = Helper::compareDate(a.both.data[0].date, a.both.data[1].date); // START: returns true/false to compare date
    cout << test << endl;
    Helper::frequencyArray(a.both, "date"); // END: just to display the total number by date
    
    //2
    // use all of search algorithm
    double num = Helper::calculatePercentage(153, 502); //END: just to display percentage
    cout << num << "%" << endl;

    //3
    // use all sort + search algorithm
    Helper::frequencyArray(a.reviews, "reviewText"); // BETWEEN: returns a frequency array, to be sorted by u

    return 0;
}