#include <iostream>

// --------------- Utilities ---------------
// Q1: Parse Date
void parseDate(string& dateStr, int& day, int& month, int& year)
{
    stringstream ss(dateStr);
    string num;

    getline(ss, num, '/');
    day = stoi(num);
    getline(ss, num, '/');
    month = stoi(num);
    getline(ss, num);
    year = stoi(num);
}

// IMPORTANT: Returns true if date2 is bigger than date1 (if date1 is earlier than date2)
bool compareDate(string& date1, string& date2)
{
    int day1, month1, year1;
    int day2, month2, year2;

    parseDate(date1, day1, month1, year1);
    parseDate(date2, day2, month2, year2);

    if (year1 < year2) 
    {
        return true;
    } 
    else if (year1 > year2) 
    {
        return false;
    } 
    else 
    {
        if (month1 < month2) 
        {
            return true;
        } 
        else if (month1 > month2) 
        {
            return false;
        } 
        else 
        {
            if (day1 < day2) 
            {
                return true;
            } 
            else 
            {
                return false;
            }
        }
    }
}

// Q2
void percentage()
{

}

// Q3
void textFrequency()
{
    
}

class LinkedList_Sort
{
    public:
        void mergeSort(bothHead)
        {
            if(compareDate(bothHead->date, bothHead->next->date))
            {
                //
            }
            else
            {

            }
        }
        void insertionSort()
        {

        }
        void bubbleSort()
        {

        }
        void selectionSort()
        {

        }
};

class Array_Sort
{
    public:
        void mergeSort(arr)
        {
            if(compareDate(arr.data[1].date, arr.data[0].date))
            {
                //
            }
            else
            {

            }
        }
        void insertionSort()
        {

        }
        void heapSort()
        {

        }
        void quickSort()
        {

        }
};

class LinkedList_Search
{
    public:
        void sequentialSearch(Condition1, Text1, Condition2, Text2)
        {
            if (Condition1 == Text1)
            {

            }
            if (Condition2 =! "")
            {
                if(Condition2 == Text2)
                {

                }
            }
        }
        void linearSearch()
        {

        }
        void recursiveSearch()
        {

        }
        void sentinelSearch()
        {

        }
};

class Array_Search
{
    public:
        void sequentialSearch()
        {
 
        }
        void linearSearch()
        {

        }
        void binarySearch()
        {

        }
        void jumpSearch()
        {

        }
};

