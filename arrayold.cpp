#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

// Define file types as an enum for type safety
enum FileType {
    TRANSACTION,
    REVIEW
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
            filePath = "transactions.csv";
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

    }

    //1
    void parseDate()
    {
        // arr[4] = date.substr(0, 2);
    }

    //2
    void percentage()
    {

    }

    //3
    void textFrequency()
    {
        
    }
    
};

int main()
{
    Array xw;
    // Read transaction data
    xw.read(REVIEW);
    xw.display(REVIEW);

    //1

    // use all sort algorithm to sort by date

    //2
 
    // use all of search algorithm

    //3

    // use all sort + search algorithm

}