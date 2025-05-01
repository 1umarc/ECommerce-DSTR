#include "structs.h"
#include <iostream>
#include <string>

using namespace std;

// Buckets as 2D Array Containers
struct CustomerBucket 
{
    Customer* data = NULL;
    int size = 0, capacity = 0;

    ~CustomerBucket()
    {
        delete[] data;
    }
    void initialize(int count)
    {
        capacity = count; 
        data = new Customer[count]; 
        size = 0; 
    }
    void add(const Customer& c)
    { 
        if (size < capacity)
        {
            data[size++] = c;
        }
    }
};

struct ReviewBucket 
{
    Review* data = NULL;
    int size = 0, capacity = 0;

    ~ReviewBucket()
    { 
        delete[] data; 
    }
    void initialize(int count)
    {
        capacity = count; 
        data = new Review[count];
        size = 0;
    }
    void add(const Review& r)
    { 
        if (size < capacity)
        {
            data[size++] = r;
        }
    }
};

struct TransactionBucket 
{
    Transaction* data = NULL;
    int size = 0, capacity = 0;

    ~TransactionBucket()
    {
        delete[] data;
    }
    void initialize(int count)
    { 
        capacity = count; 
        data = new Transaction[count]; 
        size = 0; 
    }
    void add(const Transaction& t)
    { 
        if (size < capacity)
        {
            data[size++] = t;
        }
    }
};

struct BothBucket 
{
    Both* data = NULL;
    int size = 0, capacity = 0;

    ~BothBucket()
    {
        delete[] data;
    }
    void initialize(int count) 
    {
        capacity = count;
        data = new Both[count];
        size = 0;
    }
    void add(const Both& b)
    { 
        if (size < capacity)
        {
            data[size++] = b;
        }
    }
};

struct FrequencyBucket 
{
    Frequency* data = NULL;
    int size = 0, capacity = 0;

    ~FrequencyBucket()
    {
        delete[] data;
    }
    void initialize(int count) 
    {
        capacity = count;
        data = new Frequency[count];
        size = 0;
    }
    void add(const Frequency& f)
    { 
        if (size < capacity)
        {
            data[size++] = f;
        }
    }
};