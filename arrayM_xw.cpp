#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "array_xw.cpp"

using namespace std;

// Define file types as an enum for type safety
enum FileType 
{
    TRANSACTION,
    REVIEW
};

struct Date
{
    int date;
    int months;
    int year;
};

// Define maximum rows and columns for our 2D arrays
const int MAX_ROWS = 5100;
const int MAX_COLS = 6; // Max columns for transactions (6 fields)
const int MAX_COLS_REVIEW = 4; // Max columns for reviews (4 fields)

class Array
{
private:
    string transactionData[MAX_ROWS][MAX_COLS]; // 2D array for transaction data
    string reviewData[MAX_ROWS][MAX_COLS_REVIEW]; // 2D array for review data
    int transactionRows = 0; // Actual number of rows read
    int reviewRows = 0; // Actual number of rows read
    Date parsedDates[MAX_ROWS]; // Array to store parsed dates

public:
    bool read(FileType type)
    {   
        ifstream file;
        string filePath;
        
        if (type == REVIEW)
        {
            filePath = "reviews.csv";
        }
        else // TRANSACTION
        {
            filePath = "transactions_lecturer.csv";
        }
        
        file.open(filePath);
        if (!file.is_open())
        {
            cout << "Error opening " << filePath << endl;
            return false;
        }  

        string line;
        getline(file, line); // Skip the header

        // Read and store data in appropriate 2D array
        if (type == TRANSACTION)
        {
            transactionRows = 0;
            while (getline(file, line) && transactionRows < MAX_ROWS) 
            {   
                stringstream fileContent(line);
                string value;
                int col = 0;
                
                for(int i=0 ; i<6 ;i++)
                {
                    if(i<5)
                    {
                        getline(fileContent, value, ',');
                    }
                    else 
                    {
                        getline(fileContent,value);
                    }
                    transactionData[transactionRows][col++] = value;
                }
                transactionRows++;
            }
        }
        else // REVIEW
        {
            reviewRows = 0;
            while (getline(file, line) && reviewRows < MAX_ROWS) 
            {
                stringstream fileContent(line);
                string value;
                int col = 0;
                
                for(int j=0 ; j<4 ;j++)
                {   
                    if(j<3)
                    {
                        getline(fileContent, value, ',');    
                    }
                    else 
                    {
                        getline(fileContent,value);
                    }
                    reviewData[reviewRows][col++] = value; 
                }  
                reviewRows++;
            }
        }
        
        file.close();
        cout << "File opened and data stored successfully." << endl;
        return true;
    }
    
    void display(FileType type)
    {   
        if(type == TRANSACTION)
        {   
            cout << "Contents of transaction.csv:" << endl;
            cout << "=================================================================================================================================\n";
            cout << "|No     |Customer ID\t|Product\t\t|Category\t\t|Price\t\t|Date\t\t|Payment Method\t\t|\n";
            cout << "=================================================================================================================================\n";
           
            for (int i = 0; i < transactionRows; i++) 
            {
                // Convert price string to double for formatting
                double price = 0.0;
                if (transactionData[i][3] != "NaN" && !transactionData[i][3].empty()) 
                {
                    price = stod(transactionData[i][3]);
                }
                
                cout << "|" << left << setw(7) << (i+1) 
                     << "|" << left << setw(15) << transactionData[i][0] 
                     << "|" << setw(23) << transactionData[i][1] 
                     << "|" << setw(23) << transactionData[i][2] 
                     << "|RM" << setw(13) << price 
                     << "|" << setw(15) << transactionData[i][4] 
                     << "|" << setw(23) << transactionData[i][5] 
                     << "|\n";
            }
            cout << "=================================================================================================================================\n";
        }
        else // REVIEW
        {
            cout << "\nContents of reviews.csv:" << endl;
            cout << "=================================================================================================================================\n";
            cout << "|No     |Product ID\t|Customer ID\t\t|Rating\t\t|Review Text\t\t\t\t\t\t\t|\n";
            cout << "=================================================================================================================================\n";
        
            for (int i = 0; i < reviewRows; i++) 
            {
                cout << "|" << left << setw(7) << (i+1) 
                     << "|" << left << setw(15) << reviewData[i][0] 
                     << "|" << setw(23) << reviewData[i][1] 
                     << "|" << setw(15) << reviewData[i][2] 
                     << "|" << setw(63) << reviewData[i][3] 
                     << "|\n";
            }
            cout << "=================================================================================================================================\n";
        }
    }    

    void clean()
    {
        // Implementation for clean function
    }

    void parseData()
    {
        cout << "Parsing dates from transaction data..." << endl;
        
        for (int i = 0; i < transactionRows; i++)
        {
            string dateStr = transactionData[i][4]; // Get the date string
            
            // Initialize with default values
            parsedDates[i].date = 0;
            parsedDates[i].months = 0;
            parsedDates[i].year = 0;
            
            // Check if date string is not empty and has a valid format
            if (!dateStr.empty() && dateStr.find('/') != string::npos)
            {
                try
                {
                    // Assuming date format is DD/MM/YYYY
                    stringstream ss(dateStr);
                    string dayStr, monthStr, yearStr;
                    
                    getline(ss, dayStr, '/');
                    getline(ss, monthStr, '/');
                    getline(ss, yearStr);
                    
                    // Convert strings to integers
                    parsedDates[i].date = stoi(dayStr);
                    parsedDates[i].months = stoi(monthStr);
                    parsedDates[i].year = stoi(yearStr);
                }
                catch (const exception& e)
                {
                    cout << "Error parsing date '" << dateStr << "' at row " << i+1 << ": " << e.what() << endl;
                }
            }
            else
            {
                cout << "Warning: Empty or invalid date format at row " << i+1 << endl;
            }
        }
        
        cout << "Date parsing completed." << endl;
    }
    
    void displayParsedDates()
    {
        cout << "\nParsed Dates (showing first " << transactionRows << " entries):" << endl;
        cout << "======================================================\n";
        cout << "|No     |Original Date\t|Day\t|Month\t|Year\t|\n";
        cout << "======================================================\n";
        
        for (int i = 0; i < transactionRows; i++)
        {
            cout << "|" << left << setw(7) << (i+1)
                 << "|" << left << setw(15) << transactionData[i][4]
                 << "|" << setw(7) << parsedDates[i].date
                 << "|" << setw(7) << parsedDates[i].months
                 << "|" << setw(7) << parsedDates[i].year
                 << "|\n";
        }
        cout << "======================================================\n";
    }  

    void quicksort()
    {
        cout << "Sorting transactions by date using quicksort..." << endl;
        
        // Initialize sortedIndices array with original indices before sorting
        for (int i = 0; i < transactionRows; i++)
        {
            sortedIndices[i] = i;
        }
        
        // Call the quicksortArray function from array_xw.cpp
        quicksortArray(parsedDates, sortedIndices, transactionRows);
        
        cout << "Sorting completed." << endl;
    }
    
    void displaySortedTransactions()
    {
        cout << "\nTransactions Sorted by Date:" << endl;
        cout << "=================================================================================================================================\n";
        cout << "|No     |Customer ID\t|Product\t\t|Category\t\t|Price\t\t|Date\t\t|Payment Method\t\t|\n";
        cout << "=================================================================================================================================\n";
        
        for (int i = 0; i < transactionRows; i++) 
        {
            // Get the original index from the sortedIndices array
            int originalIndex = sortedIndices[i];
            
            // Convert price string to double for formatting
            double price = 0.0;
            if (transactionData[originalIndex][3] != "NaN" && !transactionData[originalIndex][3].empty()) 
            {
                price = stod(transactionData[originalIndex][3]);
            }
            
            cout << "|" << left << setw(7) << (i+1) 
                 << "|" << left << setw(15) << transactionData[originalIndex][0] 
                 << "|" << setw(23) << transactionData[originalIndex][1] 
                 << "|" << setw(23) << transactionData[originalIndex][2] 
                 << "|RM" << setw(13) << price 
                 << "|" << setw(15) << transactionData[originalIndex][4] 
                 << "|" << setw(23) << transactionData[originalIndex][5] 
                 << "|\n";
        }
        cout << "=================================================================================================================================\n";
    }

    //2
    void percentage()
    {
        // Implementation for percentage function
    }

    //3
    void textFrequency()
    { 
        // Implementation for textFrequency function
    }
};

int main()
{
    Array xw;
    // Read transaction data
    xw.read(TRANSACTION);
    
    // Parse the dates
    xw.parseData();
    // Sort transactions by date using quicksort
    xw.quicksort();

    // Display sorted transactions
    xw.displaySortedTransactions();

    //1
    // use all sort algorithm to sort by date

    //2
    // use all of search algorithm

    //3
    // use all sort + search algorithm

    return 0;
}