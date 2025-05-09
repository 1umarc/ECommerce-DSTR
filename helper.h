#pragma once
#include "array.h"
#include "linkedlist.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Helper
{
public:
    // ----------- Function Prototypes ----------
    static void parseDate(string&, int&, int&, int&);
    static bool compareDate(string&, string&);
    static double calculatePercentage(double, double);
    static FrequencyBucket frequencyArray(void*, string, string, int);
    static void displayFrequencyA(FrequencyBucket&, const string&);
    static Frequency* frequencyLinkedList(void*, string, string);
    static void displayFrequencyLL(Frequency*, const string&);
    // ------------------------------------------
};


// Q1: Parse Date
void Helper::parseDate(string& dateStr, int& day, int& month, int& year)
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
bool Helper::compareDate(string& date1, string& date2)
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


// Q2: Percentage
double Helper::calculatePercentage(double filteredCount, double totalCount) 
{
    if (totalCount == 0)
    {
        // Prevent division by zero
        return 0.0;
    }
    else
    {
        return (filteredCount * 100.0) / totalCount;
    }
}


//Q3: Frequency
// Array Version - To return Array
FrequencyBucket Helper::frequencyArray(void* bucket, string field, string bucketType, int total) 
{
    FrequencyBucket frequencies;
    frequencies.initialize(total);
        
    for (int i = 0; i < total; ++i) 
    {
        string text;
        if (bucketType == "Review" && field == "reviewText") 
        {
            Review* arr = (Review*) bucket;
            text = arr[i].reviewText;
        } 
        else if (bucketType == "Both" && field == "date") 
        {
            Both* arr = (Both*) bucket;
            text = arr[i].date;
        }

        if (text.empty())
        {
            continue;
        }

        bool found = false;
        for (int j = 0; j < frequencies.size; ++j) 
        {
            if (frequencies.data[j].text == text) 
            {
                frequencies.data[j].count++;
                found = true;
                break;
            }
        }
        if (!found) 
        {
            frequencies.add(Frequency{text, 1});
        }
    }
    return frequencies;
}

void Helper::displayFrequencyA(FrequencyBucket& frequencies, const string& field)
{
    cout << "Array Frequency Summary for '" << field << "':\n";
    cout << left << setw(5) << "No." << setw(55) << "Data" << setw(15) << "Frequency" << endl;
    cout << string(70, '-') << endl;

    int mostRepeatedIndex = 0;
    for (int i = 0; i < frequencies.size; ++i) 
    {
        cout << left << setw(5) << (i + 1)
            << setw(55) << frequencies.data[i].text
            << setw(15) << frequencies.data[i].count << endl;

        if (frequencies.data[i].count > frequencies.data[mostRepeatedIndex].count) 
        {
            mostRepeatedIndex = i;
        }
    }

    if (frequencies.size > 0)
    {
        cout << "\nMost Frequent '" << field << "': \"" << frequencies.data[mostRepeatedIndex].text << "\" occurred " << frequencies.data[mostRepeatedIndex].count << " time(s)." << endl;
    }
}


// Linked List Version - To return Linked List
Frequency* Helper::frequencyLinkedList(void* head, string field, string nodeType) 
{
    Frequency* freqHead = nullptr;

    // Start with current pointing to the head, traverse the linked list
    for (void* current = head; current != nullptr;) 
    {
        string text;

        if (nodeType == "Review") 
        {
            Review* reviewNode = (Review*) current;
            text = reviewNode->reviewText;
            current = (void*) reviewNode->next;  // Move to next Review node
        } 
        else if (nodeType == "Both") 
        {
            Both* bothNode = (Both*)current;
            if (field == "reviewText") 
            {
                text = bothNode->reviewText;
            } 
            else if (field == "date") 
            {
                text = bothNode->date;
            }
            current = (void*) bothNode->next;  // Move to next Both node
        }
        
        if (!text.empty()) 
        {
            Frequency* temp = freqHead;
            while (temp != nullptr) 
            {
                if (temp->text == text) 
                {
                    temp->count++;
                    break;
                }
                temp = temp->next;
            }
            if (temp == nullptr) 
            {
                Frequency* newNode = new Frequency{text, 1, nullptr};
                // If the list is empty, new node becomes the head
                if (freqHead == nullptr) 
                {
                    freqHead = newNode;
                } 
                else 
                {
                    // Traverse to the end and add the new node there
                    Frequency* current = freqHead;
                    while (current->next != nullptr) 
                    {
                        current = current->next;
                    }
                    current->next = newNode;
                }
            }
        }
    }
    return freqHead;
}

void Helper::displayFrequencyLL(Frequency* freqHead, const string& field)
{
    cout << "Linked List Frequency Summary for '" << field << "':\n";
    cout << left << setw(5) << "No." << setw(55) << "Data" << setw(15) << "Frequency" << endl;
    cout << string(70, '-') << endl;

    int index = 1;
    Frequency* mostRepeated = nullptr;
    for (Frequency* curr = freqHead; curr != nullptr; curr = curr->next, ++index) 
    {
        cout << left << setw(5) << index
            << setw(55) << curr->text
            << setw(15) << curr->count << endl;

        if (mostRepeated == nullptr || curr->count > mostRepeated->count) 
        {
            mostRepeated = curr;
        }
    }

    if (mostRepeated != nullptr) 
    {
        cout << "\nMost Frequent '" << field << "': \"" << mostRepeated->text << "\" occurred " << mostRepeated->count << " time(s)." << endl;
    }
}

