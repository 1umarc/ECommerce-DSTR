#include "helper.h"
#include <iostream>
#include <cmath>

using namespace std;

class Array_Search
{
public:
    // ----------- Function Prototypes ----------
    int sequentialSearch(TransactionBucket&, const string&, const string&, const string&, const string&);
    int sequentialSearch(ReviewBucket&, const string&, const string&);

    int linearSearch(TransactionBucket&, const string&, const string&, const string&, const string&);
    int linearSearch(ReviewBucket&, const string&, const string&);

    int binarySearch(TransactionBucket&, const string&, const string&, const string&, const string&);
    int binarySearch(ReviewBucket&, const string&, const string&);
    
    int jumpSearch(TransactionBucket&, const string&, const string&, const string&, const string&);
    int jumpSearch(ReviewBucket&, const string&, const string&);
    // ------------------------------------------
};

/* Sequential Search Implementation - Array
- Time Complexity: O(1) [Best Case], O(n) [Average & Worst Case]
- Space Complexity: O(1)
*/
int Array_Search::sequentialSearch(TransactionBucket& bucket, const string& field1, const string& text1, const string& field2, const string& text2)
{
    int size = 0;
    int readInd = 0;  // Index for reading elements
    int writeInd = 0; // Index for writing matching elements
    
    // Iterate through all elements
    while (readInd < bucket.size)
    {         
        if (field1 == "category" && bucket.data[readInd].category == text1)
        {
            // If first condition matches, check second condition
            if(field2 == "paymentMethod" && bucket.data[readInd].paymentMethod == text2)
            {
                // Write matching elements
                if (writeInd != readInd)
                {
                    bucket.data[writeInd] = bucket.data[readInd];
                }
                size++;     // Increment size for matching element
                writeInd++; // Move write index forward
            }
        }            
        readInd++; // Move read index forward 
    }  
    bucket.size = size;   
    return size;
}
int Array_Search::sequentialSearch(ReviewBucket& bucket, const string& field1, const string& text1)
{
    int size = 0;
    int readInd = 0;  // Index for reading elements
    int writeInd = 0; // Index for writing matching elements
    
    // Iterate through all elements
    while (readInd < bucket.size)
    {
        if (field1 == "rating" && to_string(bucket.data[readInd].rating) == text1)
        {
            // Write matching elements
            if (writeInd != readInd)
            {
                bucket.data[writeInd] = bucket.data[readInd];
            }
            size++;     // Increment size for matching element
            writeInd++; // Move write index forward
        }   
        readInd++; // Move read index forward
    }  
    bucket.size = size;   
    return size;
}

/* Linear Search Implementation - Array
- Time Complexity: O(1) [Best Case], O(n) [Average & Worst Case]
- Space Complexity: O(n) due to creating filtered array
*/
int Array_Search::linearSearch(TransactionBucket& bucket, const string& field1, const string& text1, const string& field2, const string& text2)
{
    int count = 0;
    TransactionBucket filteredBucket;
    
    for (int i = 0; i < bucket.size; i++)
    {
        bool condition1 = false;
        bool condition2 = true;  // Default to true if field2 is empty 

        if (field1 == "category")
        {
            condition1 = (bucket.data[i].category == text1);
        }
        if (!field2.empty())
        {
            if (field2 == "paymentMethod")
            {
                condition2 = (bucket.data[i].paymentMethod == text2);
            }
        }
        bool match = condition1 && condition2;
        
        if (match)
        {
            count++;
            filteredBucket.add(bucket.data[i]);
        }
    }
    
    // Replace the original bucket with the filtered bucket if any matches were found
    if (count > 0)
    {
        // Clean up original bucket
        delete[] bucket.data;
        
        // Copy filtered data to original bucket
        bucket.size = filteredBucket.size;
        bucket.capacity = filteredBucket.capacity;
        bucket.data = new Transaction[bucket.capacity];

        for (int i = 0; i < bucket.size; i++)
        {
            bucket.data[i] = filteredBucket.data[i];
        }
        
        // Set filtered bucket's data to nullptr to prevent deletion when it goes out of scope
        filteredBucket.data = nullptr;
    }
    else
    {
        // If no matches, empty the bucket
        delete[] bucket.data;
        bucket.data = new Transaction[bucket.capacity];
        bucket.size = 0;
    }
    return count;
}
int Array_Search::linearSearch(ReviewBucket& bucket, const string& field1, const string& text1)
{
    int count = 0;
    ReviewBucket filteredBucket;
    
    for (int i = 0; i < bucket.size; i++)
    {
        bool condition1 = false;

        if (field1 == "rating" && to_string(bucket.data[i].rating) == text1)
        {
            filteredBucket.add(bucket.data[i]);
            count++;
        }
    }
    
    // Replace the original bucket with the filtered bucket if any matches were found
    if (count > 0)
    {
        // Clean up original bucket
        delete[] bucket.data;
        
        // Copy filtered data to original bucket
        bucket.size = filteredBucket.size;
        bucket.capacity = filteredBucket.capacity;
        bucket.data = new Review[bucket.capacity];

        for (int i = 0; i < bucket.size; i++)
        {
            bucket.data[i] = filteredBucket.data[i];
        }
        
        // Set filtered bucket's data to nullptr to prevent deletion when it goes out of scope
        filteredBucket.data = nullptr;
    }
    else
    {
        // If no matches, empty the bucket
        delete[] bucket.data;
        bucket.data = new Review[bucket.capacity];
        bucket.size = 0;
    }
    return count;
}

/* Binary Search Implementation - Array
- Time Complexity: O(log n) [Best Case], O(n) [Average & Worst Case]
- Space Complexity: O(1)
*/
int Array_Search::binarySearch(TransactionBucket& bucket, const string& field1, const string& value1, const string& field2, const string& value2) 
{
    int count = 0;
    
    for (int i = 0; i < bucket.size; i++) 
    {
        bool match1 = false;
        bool match2 = true;

        if (field1 == "category")
        {
            match1 = (bucket.data[i].category == value1);
        }
        else if (field1 == "paymentMethod")
        {
            match1 = (bucket.data[i].paymentMethod == value1);
        }

        if (match1 && !field2.empty())
        {
            match2 = false;
            if (field2 == "category")
            {
                match2 = (bucket.data[i].category == value2);
            }
            else if (field2 == "paymentMethod")
            {
                match2 = (bucket.data[i].paymentMethod == value2);
            }
        }

        if (match1 && match2)
        {
            count++;
        }
    }
    return count;
}
int Array_Search::binarySearch(ReviewBucket& bucket, const string& field1, const string& value1) 
{
    int count = 0;
    
    for (int i = 0; i < bucket.size; i++) 
    {
        bool match1 = false;

        if (field1 == "rating")
        {
            match1 = (to_string(bucket.data[i].rating) == value1);
        }
    
        if (match1) 
        {
            count++;
        }
    }
    return count;
}

/* Jump Search Implementation - Array
- Time Complexity: O(sqrt(n)) [Best Case], O(n) [Average & Worst Case]
- Space Complexity: O(1)
*/
int Array_Search::jumpSearch(TransactionBucket& bucket, const string& field1, const string& text1, const string& field2, const string& text2)
{
    int size = 0;
    int readInd = 0;  // Index for reading elements
    int writeInd = 0; // Index for writing matching elements
    
    // Jump search block size
    int blockSize = sqrt(bucket.size);
    if (blockSize < 1)
    {
        blockSize = 1;
    }
    
    // Process the data in blocks
    while (readInd < bucket.size)
    {
        // Determine the end of the current block
        int blockEnd = min(readInd + blockSize, bucket.size);
        
        // Process all elements in this block
        for (int i = readInd; i < blockEnd; i++)
        {
            bool match = false;
            bool condition1 = (field1 == "category" && bucket.data[i].category == text1);
            bool condition2 = (field2 == "paymentMethod" && bucket.data[i].paymentMethod == text2);
                
            // If first condition matches & second condition exists, check second condition
            if (condition1 && !field2.empty())
            {
                match = false;
                if (condition2)
                {
                    match = true;
                }
            }
            
            if (match)
            {
                // Write matching elements
                if (writeInd != i)
                {
                    bucket.data[writeInd] = bucket.data[i];
                }
                size++;     // Increment size for matching element
                writeInd++; // Move write index forward
            }
        }   
        // Jump to the next block
        readInd = blockEnd;
    }   
    bucket.size = size;
    return size;
}
int Array_Search::jumpSearch(ReviewBucket& bucket, const string& field1, const string& text1)
{
    int size = 0;
    int readInd = 0;  // Index for reading elements
    int writeInd = 0; // Index for writing matching elements
    
    // Jump search block size
    int blockSize = sqrt(bucket.size);
    if (blockSize < 1)
    {
        blockSize = 1;
    }
    
    // Process the data in blocks
    while (readInd < bucket.size)
    {
        // Determine the end of the current block
        int blockEnd = min(readInd + blockSize, bucket.size);
        
        // Process all elements in this block
        for (int i = readInd; i < blockEnd; i++)
        {
            bool match = false;
            bool condition1 = (field1 == "rating" && to_string(bucket.data[i].rating) == text1);
                
            // Check if statement matches
            if (condition1)
            {
                match = true;
            }
            if (match)
            {
                // Write matching elements
                if (writeInd != i)
                {
                    bucket.data[writeInd] = bucket.data[i];
                }
                size++;     // Increment size for matching element
                writeInd++; // Move write index forward
            }
        }   
        // Jump to the next block
        readInd = blockEnd;
    }   
    bucket.size = size;
    return size;
}