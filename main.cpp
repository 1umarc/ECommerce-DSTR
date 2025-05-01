#include "algorithms.h"
#include <chrono>
#include <iomanip>
#include <iostream>

using namespace std;
using namespace std::chrono;

// ----------- Function Prototypes ----------
void displayMenu();
void displayArraySortMenu();
void displayArraySearchMenu();
void displayLinkedListSortMenu();
void displayLinkedListSearchMenu();
void displayBothMenu(bool);
void displaySearchChoiceMenu(bool);
void displayQuestionsMenu();
void loadArray(Array&);
void loadLinkedList(LinkedList&);
void displayArrayDataMenu(Array&);
void displayLinkedListDataMenu(LinkedList&);
void solveQ1_Array(Array&, Array_Sort&, Helper&, int);
void solveQ2_Array(Array&, Array_Search&, Helper&, int);
void solveQ3_Array(Array&, Array_Sort&, Array_Search&, Helper&, int, int);
void solveQ1_LinkedList(LinkedList&, LinkedList_Sort&, Helper&, int);
void solveQ2_LinkedList(LinkedList&, LinkedList_Search&, Helper&, int);
void solveQ3_LinkedList(LinkedList&, LinkedList_Sort&, LinkedList_Search&, Helper&, int, int);
// ------------------------------------------

void displayMenu() 
{
    cout << "=================================================================" << endl;
    cout << "        E-COMMERCE CUSTOMER BEHAVIOUR ANALYZER by Group 9        " << endl;
    cout << "=================================================================" << endl;
    cout << "Select Data Structure Implementation:" << endl;
    cout << "1. Array" << endl;
    cout << "2. Linked List" << endl;
    cout << "0 - Exit" << endl;
    cout << "Enter your choice: ";
}

void displayArraySortMenu() 
{
    cout << "Select Sort Algorithm for Question 1:" << endl;
    cout << "1. Merge Sort (Luven)" << endl;
    cout << "2. Insertion Sort (Chun Kit)" << endl;
    cout << "3. Heap Sort (Nesya)" << endl;
    cout << "4. Quick Sort (Xiao Wen)" << endl;
    cout << "Enter your choice: ";
}

void displayArraySearchMenu() 
{
    cout << "Select Search Algorithm for Question 2:" << endl;
    cout << "1. Sequential Search (Luven)" << endl;
    cout << "2. Linear Search (Chun Kit)" << endl;
    cout << "3. Binary Search (Nesya)" << endl;
    cout << "4. Jump Search (Xiao Wen)" << endl;
    cout << "Enter your choice: ";
}

void displayLinkedListSortMenu() 
{
    cout << "Select Sort Algorithm for Question 1:" << endl;
    cout << "1. Merge Sort (Luven)" << endl;
    cout << "2. Insertion Sort (Chun Kit)" << endl;
    cout << "3. Bubble Sort (Nesya)" << endl;
    cout << "4. Selection Sort (Xiao Wen)" << endl;
    cout << "Enter your choice: ";
}

void displayLinkedListSearchMenu() 
{
    cout << "Select Search Algorithm for Question 2:" << endl;
    cout << "1. Sequential Search (Luven)" << endl;
    cout << "2. Linear Search (Chun Kit)" << endl;
    cout << "3. Recursive Search (Nesya)" << endl;
    cout << "4. Sentinel Search (Xiao Wen)" << endl;
    cout << "Enter your choice: ";
}

void displayBothMenu(bool isArray) 
{
    cout << "Select Combined Algorithm for Question 3:" << endl;
    cout << "Sort Algorithm:" << endl;
    if (isArray) 
    {
        cout << "1. Merge Sort (Luven)" << endl;
        cout << "2. Insertion Sort (Chun Kit)" << endl;
        cout << "3. Heap Sort (Nesya)" << endl;
        cout << "4. Quick Sort (Xiao Wen)" << endl;
    } else 
    {
        cout << "1. Merge Sort (Luven)" << endl;
        cout << "2. Insertion Sort (Chun Kit)" << endl;
        cout << "3. Bubble Sort (Nesya)" << endl;
        cout << "4. Selection Sort (Xiao Wen)" << endl;
    }
    cout << "Enter your choice for sort: ";
}

void displaySearchChoiceMenu(bool isArray) 
{
    cout << "\nSearch Algorithm:" << endl;
    if (isArray) 
    {
        cout << "1. Sequential Search (Luven)" << endl;
        cout << "2. Linear Search (Chun Kit)" << endl;
        cout << "3. Binary Search (Nesya)" << endl;
        cout << "4. Jump Search (Xiao Wen)" << endl;
    } 
    else 
    {
        cout << "1. Sequential Search (Luven)" << endl;
        cout << "2. Linear Search (Chun Kit)" << endl;
        cout << "3. Recursive Search (Nesya)" << endl;
        cout << "4. Sentinel Search (Xiao Wen)" << endl;
    }
    cout << "Enter your choice for search: ";
}

void displayQuestionsMenu() 
{
    cout << "\nSelect Question to Solve:" << endl;
    cout << "1. Q1: Sort customer transactions by date using both datasets, and display total number of both transactions." << endl;
    cout << "2. Q2: Calculate percentage of Electronics purchases made using Credit Card." << endl;
    cout << "3. Q3: Find most frequently used set-of-words in 1-star reviews." << endl;
    cout << "4 - Extra: Display Selected Dataset." << endl;
    cout << "0 - Return" << endl;
    cout << "Enter your choice: ";
}


void loadArray(Array& a)
{
    a.delArray();

    string reviewFile = "reviewsCleaned.csv";
    string transactionFile = "transactionsCleaned.csv";

    // Load data
    cout << "\nLoading data into Array structures..." << endl;
    a.initializeBuckets(reviewFile, transactionFile);
    a.customerArray(reviewFile, transactionFile);
    a.reviewArray(reviewFile);
    a.transaction_bothArray(transactionFile);
    cout << "Data loaded successfully!" << endl;
}

void loadLinkedList(LinkedList& ll)
{
    ll.delLinkedList();

    string reviewFile = "reviewsCleaned.csv";
    string transactionFile = "transactionsCleaned.csv";
    
    // Load data
    cout << "\nLoading data into Linked List structures..." << endl;
    ll.customerLinkedList(reviewFile, transactionFile);
    ll.reviewLinkedList(reviewFile);
    ll.transaction_bothLinkedList(transactionFile);
    cout << "Data loaded successfully!" << endl;
}

void displayArrayDataMenu(Array& a)
{
    loadArray(a);  // Ensure fresh data is loaded
    int choice = -1;

    do 
    {
        cout << "====================== Array Data Display Menu ======================" << endl;
        cout << "1. Display Transactions" << endl;
        cout << "2. Display Reviews" << endl;
        cout << "3. Display Both (Transactions + Review)" << endl;
        cout << "0. Return" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1: a.displayTransactions(); break;
            case 2: a.displayReviews(); break;
            case 3: a.displayBoth(); break;
            case 0: break;
            default: cout << "Invalid choice. Try again.\n"; break;
        }

    } while (choice != 0);
}

void displayLinkedListDataMenu(LinkedList& ll)
{
    loadLinkedList(ll);  // Ensure fresh data is loaded
    int choice = -1;

    do {
        cout << "\n====================== Linked List Display Menu ======================" << endl;
        cout << "1. Display Transactions" << endl;
        cout << "2. Display Reviews" << endl;
        cout << "3. Display Both (Transactions + Review)" << endl;
        cout << "0. Return" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1: ll.displayTransactions(); break;
            case 2: ll.displayReviews(); break;
            case 3: ll.displayBoth(); break;
            case 0: break;
            default: cout << "Invalid choice. Try again.\n"; break;
        }

    } while (choice != 0);
}

// Array implementation functions
void solveQ1_Array(Array& a, Array_Sort& aso, Helper& h, int sortChoice) 
{
    auto start = high_resolution_clock::now();
    loadArray(a);
    string sortName;

    switch (sortChoice) 
    {
        case 1:
            sortName = "Merge Sort";
            cout << "\nUsing Merge Sort..." << endl;
            aso.mergeSort(a.both);
            break;
        case 2:
            sortName = "Insertion Sort";
            cout << "\nUsing Insertion Sort..." << endl;
            aso.insertionSort(a.both);
            break;
        case 3:
            sortName = "Heap Sort";
            cout << "\nUsing Heap Sort..." << endl;
            aso.heapSort(a.both);
            break;
        case 4:
            sortName = "Quick Sort";
            cout << "\nUsing Quick Sort..." << endl;
            aso.quickSort(a.both);
            break;
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    
    // Display results
    FrequencyBucket frequencies = h.frequencyArray(a.both.data, "date", "Both", a.both.size);
    cout << "\n====================== Q1 Results - Array ======================" << endl;
    h.displayFrequencyA(frequencies, "date");
    cout << "Number of Both (Transaction + Review): " << a.both.size << endl;
    cout << sortName << " Execution Time: " << fixed << setprecision(10) << duration.count() / 1000000000.0 << " seconds" << endl;
}

void solveQ2_Array(Array& a, Array_Search& ase, Helper& h, int searchChoice) 
{
    auto start = high_resolution_clock::now();
    loadArray(a);
    string searchName;
    
    int transactionSize = a.transactions.size;
    int filteredSize = 0;
    
    switch (searchChoice) 
    {
        case 1:
            searchName = "Sequential Search";
            cout << "\nUsing Sequential Search..." << endl;
            filteredSize = ase.sequentialSearch(a.transactions, "category", "Electronics", "paymentMethod", "Credit Card");
            break;
        case 2:
            searchName = "Linear Search";
            cout << "\nUsing Linear Search..." << endl;
            filteredSize = ase.linearSearch(a.transactions, "category", "Electronics", "paymentMethod", "Credit Card");
            break;
        case 3:
            searchName = "Binary Search";
            cout << "\nUsing Binary Search..." << endl;
            filteredSize = ase.binarySearch(a.transactions, "category", "Electronics", "paymentMethod", "Credit Card");
            break;
        case 4:
            searchName = "Jump Search";
            cout << "\nUsing Jump Search..." << endl;
            filteredSize = ase.jumpSearch(a.transactions, "category", "Electronics", "paymentMethod", "Credit Card");
            break;
    }
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    
    // Display results
    cout << "\n====================== Q2 Results - Array ======================" << endl;
    cout << "Total Transactions: " << transactionSize << endl;
    cout << "Electronics with Credit Card: " << filteredSize << endl;
    double percentage = h.calculatePercentage(filteredSize, transactionSize);
    cout << "Percentage: " << percentage << "%" << endl;
    
    cout << searchName << " Execution Time: " << fixed << setprecision(10) << duration.count() / 1000000000.0 << " seconds" << endl;
}

void solveQ3_Array(Array& a, Array_Sort& aso, Array_Search& ase, Helper& h, int sortChoice, int searchChoice) 
{
    auto start = high_resolution_clock::now();
    loadArray(a);
    string searchName;
    string sortName;
    
    // First use search to find 1-star reviews
    int reviewSize = 0;
    switch (searchChoice) 
    {
        case 1:
            searchName = "Sequential Search";
            cout << "\nUsing Sequential Search for 1-star reviews..." << endl;
            reviewSize = ase.sequentialSearch(a.reviews, "rating", "1");
            break;
        case 2:
            searchName = "Linear Search";
            cout << "\nUsing Linear Search for 1-star reviews..." << endl;
            reviewSize = ase.linearSearch(a.reviews, "rating", "1");
            break;
        case 3:
            searchName = "Binary Search";
            cout << "\nUsing Binary Search for 1-star reviews..." << endl;
            reviewSize = ase.binarySearch(a.reviews, "rating", "1");
            break;
        case 4:
            searchName = "Jump Search";
            cout << "\nUsing Jump Search for 1-star reviews..." << endl;
            reviewSize = ase.jumpSearch(a.reviews, "rating", "1");
            break;
    }
    
    // Get word frequency
    FrequencyBucket frequencies = h.frequencyArray(a.reviews.data, "reviewText", "Review", reviewSize);
    
    // Sort by frequency
    switch (sortChoice) 
    {
        case 1:
            sortName = "Merge Sort";
            cout << "Using Merge Sort for word frequencies..." << endl;
            aso.mergeSort(frequencies);
            break;
        case 2:
            sortName = "Insertion Sort";
            cout << "Using Insertion Sort for word frequencies..." << endl;
            aso.insertionSort(frequencies);
            break;
        case 3:
            sortName = "Heap Sort";
            cout << "Using Heap Sort for word frequencies..." << endl;
            aso.heapSort(frequencies);
            break;
        case 4:
            sortName = "Quick Sort";
            cout << "Using Quick Sort for word frequencies..." << endl;
            aso.quickSort(frequencies);
            break;
    }
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    
    // Display results
    cout << "\n====================== Q3 Results - Array ======================" << endl;
    cout << "Number of 1-star reviews: " << reviewSize << endl;
    h.displayFrequencyA(frequencies, "reviewText");

    cout << searchName << " + " << sortName << " Execution Time: " << fixed << setprecision(10) << duration.count() / 1000000000.0 << " seconds" << endl;
}

// Linked List implementation functions
void solveQ1_LinkedList(LinkedList& ll, LinkedList_Sort& llso, Helper& h, int sortChoice) 
{
    auto start = high_resolution_clock::now();
    loadLinkedList(ll);
    string sortName;
    
    switch (sortChoice) 
    {
        case 1:
            sortName = "Merge Sort";
            cout << "\nUsing Merge Sort..." << endl;
            llso.mergeSort(ll.bothHead);
            break;
        case 2:
            sortName = "Insertion Sort";
            cout << "\nUsing Insertion Sort..." << endl;
            llso.insertionSort(ll.bothHead);
            break;
        case 3:
            sortName = "Bubble Sort";
            cout << "\nUsing Bubble Sort..." << endl;
            llso.bubbleSort(ll.bothHead);
            break;
        case 4:
            sortName = "Selection Sort";
            cout << "\nUsing Selection Sort..." << endl;
            llso.selectionSort(ll.bothHead);
            break;
    }
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);;
    
    // Display results
    Frequency* freqHead = h.frequencyLinkedList(ll.bothHead, "date", "Both");
    cout << "\n====================== Q1 Results - Linked List ======================" << endl;
    h.displayFrequencyLL(freqHead, "date");
    cout << "Number of Both (Transaction + Review): " << ll.bothSize << endl;
    cout << sortName << " Execution Time: " << fixed << setprecision(10) << duration.count() / 1000000000.0 << " seconds" << endl;
}

void solveQ2_LinkedList(LinkedList& ll, LinkedList_Search& llse, Helper& h, int searchChoice) 
{
    auto start = high_resolution_clock::now();
    loadLinkedList(ll);
    string searchName;
    
    int filteredSize = 0;
    switch (searchChoice) 
    {
        case 1:
            searchName = "Sequential Search";
            cout << "\nUsing Sequential Search..." << endl;
            ll.transactionHead = llse.sequentialSearch(&filteredSize, ll.transactionHead, "category", "Electronics", "paymentMethod", "Credit Card");
            break;
        case 2:
            searchName = "Linear Search";
            cout << "\nUsing Linear Search..." << endl;
            ll.transactionHead = llse.linearSearch(&filteredSize, ll.transactionHead, "category", "Electronics", "paymentMethod", "Credit Card");
            break;
        case 3:
            searchName = "Recursive Search";
            cout << "\nUsing Recursive Search..." << endl;
            ll.transactionHead = llse.recursiveSearch(&filteredSize, ll.transactionHead, "category", "Electronics", "paymentMethod", "Credit Card");
            break;
        case 4:
            searchName = "Sentinel Search";
            cout << "\nUsing Sentinel Search..." << endl;
            ll.transactionHead = llse.sentinelSearch(&filteredSize, ll.transactionHead, "category", "Electronics", "paymentMethod", "Credit Card");
            break;
    }
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    
    // Display results
    cout << "\n====================== Q2 Results - Linked List ======================" << endl;
    cout << "Total Transactions: " << ll.transactionSize << endl;
    cout << "Electronics with Credit Card: " << filteredSize << endl;
    double percentage = h.calculatePercentage(filteredSize, ll.transactionSize);
    cout << "Percentage: " << percentage << "%" << endl;
    
    cout << searchName << " Execution Time: " << fixed << setprecision(10) << duration.count() / 1000000000.0 << " seconds" << endl;
}

void solveQ3_LinkedList(LinkedList& ll, LinkedList_Sort& llso, LinkedList_Search& llse, Helper& h, int sortChoice, int searchChoice) 
{
    auto start = high_resolution_clock::now();
    loadLinkedList(ll);
    string sortName;
    string searchName;
    
    // First use search to find 1-star reviews
    int reviewSize = 0;
    switch (searchChoice) 
    {
        case 1:
            searchName = "Sequential Search";
            cout << "\nUsing Sequential Search for 1-star reviews..." << endl;
            ll.reviewHead = llse.sequentialSearch(&reviewSize, ll.reviewHead, "rating", "1");
            break;
        case 2:
            searchName = "Linear Search";
            cout << "\nUsing Linear Search for 1-star reviews..." << endl;
            ll.reviewHead = llse.linearSearch(&reviewSize, ll.reviewHead, "rating", "1");
            break;
        case 3:
            searchName = "Recursive Search";
            cout << "\nUsing Recursive Search for 1-star reviews..." << endl;
            ll.reviewHead = llse.recursiveSearch(&reviewSize, ll.reviewHead, "rating", "1");
            break;
        case 4:
            searchName = "Sentinel Search";
            cout << "\nUsing Sentinel Search for 1-star reviews..." << endl;
            ll.reviewHead = llse.sentinelSearch(&reviewSize, ll.reviewHead, "rating", "1");
            break;
    }
    
    // Get word frequency
    Frequency* freqHead = h.frequencyLinkedList(ll.reviewHead, "reviewText", "Review");
    
    // Sort by frequency
    switch (sortChoice) 
    {
        case 1:
            sortName = "Merge Sort";
            cout << "Using Merge Sort for word frequencies..." << endl;
            llso.mergeSort(freqHead);
            break;
        case 2:
            sortName = "Insertion Sort";
            cout << "Using Insertion Sort for word frequencies..." << endl;
            llso.insertionSort(freqHead);
            break;
        case 3:
            sortName = "Bubble Sort";
            cout << "Using Bubble Sort for word frequencies..." << endl;
            llso.bubbleSort(freqHead);
            break;
        case 4:
            sortName = "Selection Sort";
            cout << "Using Quick Sort for word frequencies..." << endl;
            llso.selectionSort(freqHead);
            break;
    }
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    
    // Display results
    cout << "\n====================== Q3 Results - Linked List ======================" << endl;
    cout << "Number of 1-star reviews: " << reviewSize << endl;
    h.displayFrequencyLL(freqHead, "reviewText");
    cout << searchName << " + " << sortName << " Execution Time: " << fixed << setprecision(10) << duration.count() / 1000000000.0 << " seconds" << endl;
}


int main() 
{
    int mainChoice = 0;
    
    do 
    {
        system("cls");  // Clear screen
        displayMenu();
        cin >> mainChoice;
        
        if (mainChoice == 1) 
        {  // Array Implementation
            Array a;
            Array_Sort aso;
            Array_Search ase;
            Helper h;
                        
            int questionChoice = 0;
            do {
                displayQuestionsMenu();
                cin >> questionChoice;
                
                switch (questionChoice) {
                    case 1: 
                    {  // Q1 - Sort
                        int sortChoice;
                        displayArraySortMenu();
                        cin >> sortChoice;
                        solveQ1_Array(a, aso, h, sortChoice);
                        break;
                    }
                    case 2: 
                    {  // Q2 - Search
                        int searchChoice;
                        displayArraySearchMenu();
                        cin >> searchChoice;
                        solveQ2_Array(a, ase, h, searchChoice);
                        break;
                    }
                    case 3: 
                    {  // Q3 - Both
                        int sortChoice, searchChoice;
                        displayBothMenu(true);
                        cin >> sortChoice;
                        displaySearchChoiceMenu(true);
                        cin >> searchChoice;
                        solveQ3_Array(a, aso, ase, h, sortChoice, searchChoice);
                        break;
                    }
                    case 4:
                        displayArrayDataMenu(a);
                        break;
                    case 0:
                        cout << "Returning..." << endl;
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                }
                
                if (questionChoice != 0) 
                {
                    cout << "\nPress Enter to continue...";
                    cin.ignore();
                    cin.get();
                }
                
            } while (questionChoice != 0);
        }
        else if (mainChoice == 2) 
        { 
            LinkedList ll;
            LinkedList_Sort llso;
            LinkedList_Search llse;
            Helper h;
          
            int questionChoice = 0;
            do 
            {
                displayQuestionsMenu();
                cin >> questionChoice;
                
                switch (questionChoice) 
                {
                    case 1: 
                    {  // Q1 - Sort
                        int sortChoice;
                        displayLinkedListSortMenu();
                        cin >> sortChoice;
                        solveQ1_LinkedList(ll, llso, h, sortChoice);
                        break;
                    }
                    case 2: 
                    {  // Q2 - Search
                        int searchChoice;
                        displayLinkedListSearchMenu();
                        cin >> searchChoice;
                        solveQ2_LinkedList(ll, llse, h, searchChoice);
                        break;
                    }
                    case 3: 
                    {  // Q3 - Both
                        int sortChoice, searchChoice;
                        displayBothMenu(false);
                        cin >> sortChoice;
                        displaySearchChoiceMenu(false);
                        cin >> searchChoice;
                        solveQ3_LinkedList(ll, llso, llse, h, sortChoice, searchChoice);
                        break;
                    }
                    case 4:
                        displayLinkedListDataMenu(ll);
                        break;
                    case 0:
                        cout << "Returning..." << endl;
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                }
                
                if (questionChoice != 0) 
                {
                    cout << "\nPress Enter to continue...";
                    cin.ignore();
                    cin.get();
                }
                
            } while (questionChoice != 0);
        }
        else if (mainChoice != 0) 
        {
            cout << "Invalid choice. Please try again." << endl;
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
        }
        
    } while (mainChoice != 0);
    
    cout << "Thank you for using this E-Commerce Customer Behaviour Analyzer by Group9!" << endl;
    return 0;
}
