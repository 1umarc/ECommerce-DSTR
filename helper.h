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


    // Q3: Frequency
};
