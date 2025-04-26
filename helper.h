#include "array.h"
#include "linkedlist.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Helper
{
public:
    // Q1: Parse Date
    static void parseDate(string& dateStr, int& day, int& month, int& year)
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
    static bool compareDate(string& date1, string& date2)
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
    static double calculatePercentage(int filteredCount, int totalCount) 
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
};

    // Q3: Frequency
//     void frequencyArray(Array& arr, string& field) 
//     {
//         Bucket<Frequency> frequencies = Bucket<Frequency>();
    
//         int total = (field == "reviewText") ? arr.reviews.size : arr.both.size;
    
//         for (int i = 0; i < total; ++i) 
//         {
//             string text;
//             if (field == "reviewText") 
//             {
//                 text = arr.reviews.data[i].reviewText;
//             } 
//             else if (field == "date") 
//             {
//                 text = arr.both.data[i].date;
//             }
    
//             if (text.empty())
//             {
//                 continue;
//             }
    
//             bool found = false;
//             for (int j = 0; j < frequencies.size; ++j) 
//             {
//                 if (frequencies.data[j].text == text) 
//                 {
//                     frequencies.data[j].count++;
//                     found = true;
//                     break;
//                 }
//             }
//             if (!found) 
//             {
//                 frequencies.add(Frequency{text, 1});
//             }
//         }
    
//         cout << "\n[ARRAY] Frequency Summary for '" << field << "':\n";
//         int mostRepeatedIndex = 0;
//         for (int i = 0; i < frequencies.size; ++i) 
//         {
//             cout << "\"" << frequencies.data[i].text << "\" was repeated " << frequencies.data[i].count << " time(s).\n";
//             if (frequencies.data[i].count > frequencies.data[mostRepeatedIndex].count) {
//                 mostRepeatedIndex = i;
//             }
//         }
    
//         if (frequencies.size > 0)
//         {
//             cout << "\nMost repeated \"" << field << "\":\n\""
//                  << frequencies.data[mostRepeatedIndex].text
//                  << "\" repeated "
//                  << frequencies.data[mostRepeatedIndex].count
//                  << " time(s)." << endl;
//         }
//     }

//     template<typename NodeType>
//     void frequencyLinkedList(NodeType* head, string field) 
//     {
//         FrequencyNode* freqHead = nullptr;

//         string NodeType::* fieldPtr;

//         if (field == "reviewText") 
//         {
//             fieldPtr = &NodeType::reviewText;
//         } 
//         else if (field == "date") 
//         {
//             fieldPtr = &NodeType::date;
//         } 
//         else 
//         {
//             cout << "Invalid field specified.\n";
//             return;
//         }

//         for (NodeType* current = head; current != nullptr; current = current->next) 
//         {
//             string text = current->*fieldPtr;
//             if (!text.empty()) 
//             {
//                 insertOrUpdate(freqHead, text);
//             }
//         }

//         cout << "\n[LINKED LIST] Frequency Summary for '" << field << "':\n";
//         FrequencyNode* mostRepeated = nullptr;
//         for (FrequencyNode* curr = freqHead; curr != nullptr; curr = curr->next) 
//         {
//             cout << "\"" << curr->text << "\" was repeated " << curr->count << " time(s).\n";
//             if (mostRepeated == nullptr || curr->count > mostRepeated->count) 
//             {
//                 mostRepeated = curr;
//             }
//         }

//         if (mostRepeated != nullptr) 
//         {
//             cout << "\nMost repeated \"" << field << "\":\n\""
//                 << mostRepeated->text
//                 << "\" repeated "
//                 << mostRepeated->count
//                 << " time(s)." << endl;
//         }

//         // Clean up FrequencyNode linked list
//         while (freqHead) 
//         {
//             FrequencyNode* temp = freqHead;
//             freqHead = freqHead->next;
//             delete temp;
//         }
//     }
// };
