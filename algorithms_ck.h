#include "helper.h"
#include <iostream>

using namespace std;

class LinkedList_Sort
{
public:
    /* Insertion Sort Implementation - Linked List
    - Time Complexity: O(n) [Best Case], O(n²) [Average & Worst Case]
    - Space Complexity: O(1)
    */
    template <typename NodeType>
    void insertionSort(NodeType*& head)
    {
        // Base case - empty list or list with only one node
        if (head == nullptr || head->next == nullptr)
        {
            return;
        }

        NodeType* sorted = nullptr;  // Initialize sorted linked list
        NodeType* current = head;    // Current node to be inserted

        // Traverse the original list
        while (current != nullptr)
        {
            // Store next for next iteration
            NodeType* next = current->next;

            // Insert current in sorted linked list
            if (sorted == nullptr || shouldComeBefore(current, sorted))
            {
                // Insert at beginning
                current->next = sorted;
                sorted = current;
            }
            else
            {
                // Locate node before point of insertion
                NodeType* temp = sorted;
                while (temp->next != nullptr && !shouldComeBefore(current, temp->next))
                {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }

            current = next;  // Move to next node
        }

        head = sorted;  // Update head to point to sorted list
    }

private:
    // Helper function to determine insertion order
    template <typename NodeType>
    bool shouldComeBefore(NodeType* node1, NodeType* node2)
    {
        if constexpr (std::is_same<NodeType, Both>::value)
        {
            // For Both nodes, compare by date
            return !Helper::compareDate(node1->date, node2->date);  // node1 date is earlier than node2
        }
        else if constexpr (std::is_same<NodeType, Frequency>::value)
        {
            // For Frequency nodes, compare by count (higher count comes first)
            return node1->count > node2->count;
        }
        
        // Default comparison (should not reach here in your use cases)
        return false;
    }
};

class Array_Sort
{
public:
    /* Insertion Sort Implementation - Array
    - Time Complexity: O(n) [Best Case], O(n²) [Average & Worst Case]
    - Space Complexity: O(1)
    */
    template <typename ArrayType>
    void insertionSort(Bucket<ArrayType>& bucket)
    {
        int n = bucket.size;
        
        for (int i = 1; i < n; i++)
        {
            ArrayType key = bucket.data[i];
            int j = i - 1;
            
            // Compare based on type
            while (j >= 0 && shouldComeBefore(key, bucket.data[j]))
            {
                bucket.data[j + 1] = bucket.data[j];
                j--;
            }
            
            bucket.data[j + 1] = key;
        }
    }

private:
    // Helper function to determine insertion order
    template <typename ArrayType>
    bool shouldComeBefore(ArrayType& element1, ArrayType& element2)
    {
        if constexpr (std::is_same<ArrayType, Both>::value)
        {
            // For Both elements, compare by date
            return !Helper::compareDate(element1.date, element2.date);  // element1 date is earlier than element2
        }
        else if constexpr (std::is_same<ArrayType, Frequency>::value)
        {
            // For Frequency elements, compare by count (higher count comes first)
            return element1.count > element2.count;
        }
        
        // Default comparison (should not reach here in your use cases)
        return false;
    }
};

class LinkedList_Search
{
public:
    /* Linear Search Implementation - Linked List
    - Time Complexity: O(1) [Best Case], O(n) [Average & Worst Case]
    - Space Complexity: O(1)
    */
    template <typename NodeType>
    int linearSearch(NodeType*& head, const string& field1, const string& text1, const string& field2 = "", const string& text2 = "")
    {
        int count = 0;
        NodeType* current = head;
        NodeType* filtered = nullptr;  // Head of filtered list
        NodeType* filteredTail = nullptr;  // Tail of filtered list for easy appending
        
        while (current != nullptr)
        {
            NodeType* next = current->next;  // Save next pointer before potentially modifying current
            bool match = checkConditions(current, field1, text1, field2, text2);
            
            if (match)
            {
                count++;
                
                // Move this node to filtered list (no need to create new node)
                current->next = nullptr;
                
                // Add to filtered list
                if (filtered == nullptr)
                {
                    filtered = current;
                    filteredTail = current;
                }
                else
                {
                    filteredTail->next = current;
                    filteredTail = current;
                }
            }
            else
            {
                // Free the node that doesn't match
                delete current;
            }
            
            current = next;
        }
        
        // Update head to filtered list
        head = filtered;
        
        return count;
    }

private:
    // Helper function to check conditions based on node type
    template <typename NodeType>
    bool checkConditions(NodeType* node, const string& field1, const string& text1, 
                        const string& field2, const string& text2)
    {
        bool condition1 = false;
        bool condition2 = true;  // Default to true if field2 is empty
        
        if constexpr (std::is_same<NodeType, Transaction>::value)
        {
            if (field1 == "category")
                condition1 = (node->category == text1);
            else if (field1 == "paymentMethod")
                condition1 = (node->paymentMethod == text1);
                
            if (!field2.empty())
            {
                if (field2 == "category")
                    condition2 = (node->category == text2);
                else if (field2 == "paymentMethod")
                    condition2 = (node->paymentMethod == text2);
            }
        }
        else if constexpr (std::is_same<NodeType, Review>::value)
        {
            if (field1 == "rating")
                condition1 = (to_string(node->rating) == text1);
                
            if (!field2.empty())
            {
                if (field2 == "productID")
                    condition2 = (node->productID == text2);
            }
        }
        else if constexpr (std::is_same<NodeType, Both>::value)
        {
            if (field1 == "category")
                condition1 = (node->category == text1);
            else if (field1 == "paymentMethod")
                condition1 = (node->paymentMethod == text1);
            else if (field1 == "rating")
                condition1 = (to_string(node->rating) == text1);
                
            if (!field2.empty())
            {
                if (field2 == "category")
                    condition2 = (node->category == text2);
                else if (field2 == "paymentMethod")
                    condition2 = (node->paymentMethod == text2);
            }
        }
        
        return condition1 && condition2;
    }
};

class Array_Search
{
public:
    /* Linear Search Implementation - Array
    - Time Complexity: O(1) [Best Case], O(n) [Average & Worst Case]
    - Space Complexity: O(n) due to creating filtered array
    */
    template <typename DataType>
    int linearSearch(Bucket<DataType>& bucket, const string& field1, const string& text1, const string& field2 = "", const string& text2 = "")
    {
        int count = 0;
        Bucket<DataType> filteredBucket;
        
        for (int i = 0; i < bucket.size; i++)
        {
            bool match = checkConditions(bucket.data[i], field1, text1, field2, text2);
            
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
            bucket.data = new DataType[bucket.capacity];
            
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
            bucket.data = new DataType[bucket.capacity];
            bucket.size = 0;
        }
        
        return count;
    }

private:
    // Helper function to check conditions based on data type
    template <typename DataType>
    bool checkConditions(DataType& data, const string& field1, const string& text1, 
                        const string& field2, const string& text2)
    {
        bool condition1 = false;
        bool condition2 = true;  // Default to true if field2 is empty
        
        if constexpr (std::is_same<DataType, Transaction>::value)
        {
            if (field1 == "category")
                condition1 = (data.category == text1);
            else if (field1 == "paymentMethod")
                condition1 = (data.paymentMethod == text1);
                
            if (!field2.empty())
            {
                if (field2 == "category")
                    condition2 = (data.category == text2);
                else if (field2 == "paymentMethod")
                    condition2 = (data.paymentMethod == text2);
            }
        }
        else if constexpr (std::is_same<DataType, Review>::value)
        {
            if (field1 == "rating")
                condition1 = (to_string(data.rating) == text1);
                
            if (!field2.empty())
            {
                if (field2 == "productID")
                    condition2 = (data.productID == text2);
            }
        }
        else if constexpr (std::is_same<DataType, Both>::value)
        {
            if (field1 == "category")
                condition1 = (data.category == text1);
            else if (field1 == "paymentMethod")
                condition1 = (data.paymentMethod == text1);
            else if (field1 == "rating")
                condition1 = (to_string(data.rating) == text1);
                
            if (!field2.empty())
            {
                if (field2 == "category")
                    condition2 = (data.category == text2);
                else if (field2 == "paymentMethod")
                    condition2 = (data.paymentMethod == text2);
            }
        }
        
        return condition1 && condition2;
    }
};

// mainArray.cpp
/*
    Array a;

    string reviewFile = "reviews_lecturer.csv";
    string transactionFile = "transactions_lecturer.csv";

    a.customerArray(reviewFile, transactionFile);
    a.reviewArray(reviewFile);
    a.transaction_bothArray(transactionFile);

    //a.displayTransactions();
    //a.displayBoth();
    //a.displayReviews();

    Array_Sort aso;
    Array_Search ase;
    Helper h;

    // Q1 - Sort customer transactions by date using insertionSort
    cout << "\n--- Q1: Sorting transactions by date ---\n";
    aso.insertionSort(a.both);  // Sort Both elements by date
    cout << "Frequency of transactions by date:\n";
    h.frequencyArray(a.both, "date");  // Display frequency by date
    
    // Q2 - Find percentage of Electronics purchases with Credit Card
    cout << "\n--- Q2: Percentage of Electronics purchases with Credit Card ---\n";
    // Create a new Array for Q2 since the search modifies the array
    Array q2a;
    q2a.customerArray(reviewFile, transactionFile);
    q2a.reviewArray(reviewFile);
    q2a.transaction_bothArray(transactionFile);
    
    int electronicsWithCreditCard = ase.linearSearch(q2a.transactions, 
                                                        "category", "Electronics", 
                                                        "paymentMethod", "Credit Card");
    cout << "Number of Electronics purchases with Credit Card: " << electronicsWithCreditCard << endl;
    double percentage = h.calculatePercentage(electronicsWithCreditCard, q2a.transactions.size);
    cout << "Percentage: " << percentage << "%" << endl;
    
    // Q3 - Find most frequent words in 1-star reviews
    cout << "\n--- Q3: Most frequent words in 1-star reviews ---\n";
    // Create a new Array for Q3 since the search modifies the array
    Array q3a;
    q3a.customerArray(reviewFile, transactionFile);
    q3a.reviewArray(reviewFile);
    q3a.transaction_bothArray(transactionFile);
    
    int oneStarReviews = ase.linearSearch(q3a.reviews, "rating", "1");
    cout << "Number of 1-star reviews: " << oneStarReviews << endl;
    
    // Extract and count frequency of words in filtered reviews
    Bucket<Frequency> wordFrequency = h.frequencyArray(q3a.reviews, "reviewText");
    
    // Sort frequencies using insertionSort (highest count first)
    aso.insertionSort(wordFrequency);
    
    // Display most frequent words
    cout << "Most frequent words in 1-star reviews:\n";
    h.displayFrequencyA(wordFrequency, "reviewText");

*/



// mainLinkedList.cpp
/*
    LinkedList ll;

    string reviewFile = "reviews_lecturer.csv";
    string transactionFile = "transactions_lecturer.csv";

    ll.customerLinkedList(reviewFile, transactionFile);
    ll.reviewLinkedList(reviewFile);
    ll.transaction_bothLinkedList(transactionFile);
    
    LinkedList_Sort llso;
    LinkedList_Search llse;
    Helper h;
  
    // Q1 - Sort customer transactions by date using insertionSort
    cout << "\n--- Q1: Sorting transactions by date ---\n";
    llso.insertionSort(ll.bothHead);  // Sort Both nodes by date
    cout << "Frequency of transactions by date:\n";
    h.frequencyLinkedList(ll.bothHead, "date");  // Display frequency by date
    
    // Q2 - Find percentage of Electronics purchases with Credit Card
    cout << "\n--- Q2: Percentage of Electronics purchases with Credit Card ---\n";
    // Create a new LinkedList for Q2 since the search modifies the list
    LinkedList ll1;
    ll1.customerLinkedList(reviewFile, transactionFile);
    ll1.reviewLinkedList(reviewFile);
    ll1.transaction_bothLinkedList(transactionFile);
    
    int electronicsWithCreditCard = llse.linearSearch(ll1.transactionHead, 
                                                      "category", "Electronics", 
                                                      "paymentMethod", "Credit Card");
    cout << "Number of Electronics purchases with Credit Card: " << electronicsWithCreditCard << endl;
    double percentage = h.calculatePercentage(electronicsWithCreditCard, ll1.transactionSize);
    cout << "Percentage: " << percentage << "%" << endl;
    
    // Q3 - Find most frequent words in 1-star reviews
    cout << "\n--- Q3: Most frequent words in 1-star reviews ---\n";
    // Create a new LinkedList for Q3 since the search modifies the list
    LinkedList ll2;
    ll2.customerLinkedList(reviewFile, transactionFile);
    ll2.reviewLinkedList(reviewFile);
    ll2.transaction_bothLinkedList(transactionFile);
    
    // Filter to get only 1-star reviews
    int oneStarReviews = llse.linearSearch(ll2.reviewHead, "rating", "1");
    cout << "Number of 1-star reviews: " << oneStarReviews << endl;
    
    // Calculate frequency from the filtered list of reviews
    Frequency* wordFrequency = h.frequencyLinkedList(ll2.reviewHead, "reviewText");
    
    // Sort frequencies using insertionSort (highest count first)
    llso.insertionSort(wordFrequency);
    
    // Display most frequent words
    cout << "Most frequent words in 1-star reviews:\n";
    h.displayFrequencyLL(wordFrequency, "reviewText");
*/