#include "helper.h"
#include <iostream>

using namespace std;

class LinkedList_SortDN
{
    private:
    template <typename NodeType>
    NodeType* split(NodeType* first, NodeType* second) {
        if (first == nullptr) {
            return second;
        }
        if (second == nullptr) {
            return first;
        }

        NodeType* result = nullptr;
        bool condition = false;

        if constexpr (is_same<NodeType, Both>::value) {
            condition = Helper::compareDate(first->date, second->date);
        }
        else if constexpr (is_same<NodeType, Frequency>::value){
            condition = first->count < second->count;
        }

        if(condition) {
            result = first;
            result->next = split(first->next, second);
        }
        else {
            result = second;
            result->next = split(first, second->next);
        }
        return result;
    }

    public:
    template <typename NodeType>
    void bubbleSort(NodeType*& head)
    {
        if (head == nullptr || head->next == nullptr) return; // Empty or single-node list

        bool swapped;
        do {
            swapped = false;
            NodeType* current = head;
            NodeType* nextNode = head->next;

            while (nextNode) {
                bool shouldSwap = false;
                
                if constexpr (is_same<NodeType, Both>::value) {
                    // Compare dates: if current is older than next, swap
                    shouldSwap = Helper::compareDate(current->date, nextNode->date);
                }
                else if constexpr (is_same<NodeType, Frequency>::value) {
                    // For frequency nodes, sort by count in ascending order
                    shouldSwap = current->count < nextNode->count;
                }
                
                if (shouldSwap) {
                    if constexpr (is_same<NodeType, Both>::value) {
                        // Swap Both node data
                        swap(current->customerID, nextNode->customerID);
                        swap(current->productID, nextNode->productID);
                        swap(current->category, nextNode->category);
                        swap(current->price, nextNode->price);
                        swap(current->date, nextNode->date);
                        swap(current->paymentMethod, nextNode->paymentMethod);
                        swap(current->productID, nextNode->productID);
                        swap(current->rating, nextNode->rating);
                        swap(current->reviewText, nextNode->reviewText);
                    }
                    else if constexpr (is_same<NodeType, Frequency>::value) {
                        swap(current->text, nextNode->text);
                        swap(current->count, nextNode->count);
                    }
                    swapped = true;
                }
                current = nextNode;
                nextNode = nextNode->next;
            }
        } while (swapped);
    }

};

class Array_SortDN
{
    public:
    template <typename ArrayType>
    void heapSort(ArrayType ar[], int size) {
        // Build max heap
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify(ar, size, i);
        }

        // Heap sort
        for (int i = size - 1; i >= 0; i--) {
            swap(ar[0], ar[i]);
            heapify(ar, i, 0);
        }
    }

    void heapSortDatesDescending(Bucket<Both>& bucket) {
        // Build max heap for newest dates first
        for (int i = bucket.size / 2 - 1; i >= 0; i--) {
            heapifyDatesDescending(bucket, bucket.size, i);
        }

        // Heap sort
        for (int i = bucket.size - 1; i > 0; i--) {
            // Swap root (newest date) with the last element
            swap(bucket.data[0], bucket.data[i]);
            // Call heapify on the reduced heap
            heapifyDatesDescending(bucket, i, 0);
        }
    }

    void heapSortByFrequency(Bucket<Frequency>& bucket) {
        // Build max heap based on frequency counts
        for (int i = bucket.size / 2 - 1; i >= 0; i--) {
            heapifyFrequency(bucket, bucket.size, i);
        }

        // Heap sort
        for (int i = bucket.size - 1; i > 0; i--) {
            // Swap root (highest frequency) with the last element
            swap(bucket.data[0], bucket.data[i]);
            // Call heapify on the reduced heap
            heapifyFrequency(bucket, i, 0);
        }
    }

    private:
    template <typename ArrayType>

    void heapify(ArrayType ar[], int size, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && ar[left] > ar[largest]) {
            largest = left;
        }
        if (right < size && ar[right] > ar[largest]) {
            largest = right;
        }
        if (largest != i) {
            swap(ar[i], ar[largest]);
            heapify(ar, size, largest);
        }
    }

    void heapifyDatesDescending(Bucket<Both>& bucket, int size, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        // Compare based on date (descending order)
        // Note the reversed comparison: we want newer dates to be "larger"
        // So if left.date is newer than largest.date, largest should become left
        if (left < size && Helper::compareDate(bucket.data[left].date, bucket.data[largest].date)) {
            largest = left;
        }
        if (right < size && Helper::compareDate(bucket.data[right].date, bucket.data[largest].date)) {
            largest = right;
        }
        
        if (largest != i) {
            swap(bucket.data[i], bucket.data[largest]);
            heapifyDatesDescending(bucket, size, largest);
        }
    }

    void heapifyFrequency(Bucket<Frequency>& bucket, int size, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        // Compare based on count (max heap for descending order)
        if (left < size && bucket.data[left].count > bucket.data[largest].count) {
            largest = left;
        }
        if (right < size && bucket.data[right].count > bucket.data[largest].count) {
            largest = right;
        }
        
        if (largest != i) {
            swap(bucket.data[i], bucket.data[largest]);
            heapifyFrequency(bucket, size, largest);
        }
    }

};

class LinkedList_SearchDN
{
    public:
    // Finds the index of a node matching a key or returns -1 if not found
    template <typename NodeType>
    int recursiveSearchIndex(NodeType* node, const string& key, int index = 0) 
    {
        if (!node) {
            return -1; // Key not found
        }
        
        // Generic comparison based on node type
        bool match = false;
        if constexpr (std::is_same<NodeType, Transaction>::value) {
            match = (node->category == key || node->paymentMethod == key);
        }
        else if constexpr (std::is_same<NodeType, Review>::value) {
            match = (to_string(node->rating) == key);
        }
        else {
            match = (node->data == key); // For standard Node type
        }
        
        if (match) {
            return index; // Key found
        }
        
        return recursiveSearchIndex(node->next, key, index + 1); // Recur for the next node
    }
    
    // Public method to initiate the recursive index search
    template <typename NodeType>
    int search(NodeType* head, const string& key) 
    {
        return recursiveSearchIndex(head, key, 0);
    }

    // Filters nodes based on one or two conditions and returns count of matching nodes
    template <typename NodeType>
    int recursiveSearch(NodeType*& head, const string& field1, const string& value1, 
                        const string& field2 = "", const string& value2 = "")
    {
        // Base case: empty list
        if (head == nullptr)
        {
            return 0;
        }
        
        bool match = false;
        bool condition1 = false;
        bool condition2 = false;
        
        // Check conditions based on node type
        if constexpr (std::is_same<NodeType, Transaction>::value)
        {
            if (field1 == "category") condition1 = (head->category == value1);
            else if (field1 == "paymentMethod") condition1 = (head->paymentMethod == value1);
            
            if (field2 == "category") condition2 = (head->category == value2);
            else if (field2 == "paymentMethod") condition2 = (head->paymentMethod == value2);
        }
        else if constexpr (std::is_same<NodeType, Review>::value)
        {
            if (field1 == "rating") condition1 = (to_string(head->rating) == value1);
            if (field2 == "rating") condition2 = (to_string(head->rating) == value2);
        }
        else // Generic Node with data
        {
            condition1 = (head->data == value1);
            condition2 = (field2.empty() ? true : (head->data == value2));
        }
        
        if (condition1)
        {
            match = true;
        }
        
        // If first condition matches & second condition exists, check second condition
        if (match && !field2.empty())
        {
            match = condition2;
        }
        
        NodeType* nextNode = head->next;
        int restCount = recursiveSearch(nextNode, field1, value1, field2, value2);

        if (match)
        {
            // Keep this node and add it to the count
            head->next = nextNode;
            return 1 + restCount;
        }
        else
        {
            // Remove this node from the list
            NodeType* temp = head;
            head = nextNode;
            delete temp;
            return restCount;
        }
    }
};

class Array_SearchDN {
    private:
        // Helper function to get string field value from Transaction or Review by field name
        template<typename DataType>
        string getFieldValue(const DataType& obj, const string& fieldName) {
            if constexpr (std::is_same<DataType, Transaction>::value) {
                if (fieldName == "category") return obj.category;
                else if (fieldName == "paymentMethod") return obj.paymentMethod;
            } else if constexpr (std::is_same<DataType, Review>::value) {
                if (fieldName == "rating") return to_string(obj.rating);
                else if (fieldName == "reviewText") return obj.reviewText;
            }
            return "";
        }
    
        // Binary search on array of DataType for fieldName == value
        template<typename DataType>
        int binarySearchField(DataType* arr, int size, const string& fieldName, const string& value) {
            int first = 0;
            int last = size - 1;
    
            while (first <= last) {
                int mid = first + (last - first) / 2;
                string midVal = getFieldValue(arr[mid], fieldName);
    
                if (midVal == value) {
                    return mid;
                } else if (midVal < value) {
                    first = mid + 1;
                } else {
                    last = mid - 1;
                }
            }
            return -1;
        }
    
    public:
        template <typename DataType>
        int binarySearch(Bucket<DataType>& bucket, const string& field1, const string& value1,
                         const string& field2 = "", const string& value2 = "") {
            if (bucket.size == 0) return 0;
    
            int idx = binarySearchField(bucket.data, bucket.size, field1, value1);
            if (idx == -1) return 0;
    
            // We found one match; count all matches by scanning neighbors for duplicates on field1
            int count = 0;
    
            // Scan left
            int i = idx;
            while (i >= 0 && getFieldValue(bucket.data[i], field1) == value1) {
                i--;
            }
            i++; // adjust to first match on left
    
            // Scan right and count with checking field2 if provided
            while (i < bucket.size && getFieldValue(bucket.data[i], field1) == value1) {
                bool match2 = true;
                if (!field2.empty()) {
                    match2 = (getFieldValue(bucket.data[i], field2) == value2);
                }
                if (match2) {
                    count++;
                }
                i++;
            }
    
            return count;
        }
    };