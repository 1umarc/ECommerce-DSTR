#pragma once
#include <iostream>
#include <string>

using namespace std;

// LinkedList & Array - Review
struct Review 
{
    string productID;
    string customerID;
    int rating;
    string reviewText;
    Review* next;
};

// LinkedList & Array - Transaction
struct Transaction 
{
    string customerID;
    string product;
    string category;
    double price;
    string date;
    string paymentMethod;
    Transaction* next;
};

// LinkedList & Array - Both (Transaction + Review)
struct Both 
{
    string customerID;
    string product;
    string category;
    double price;
    string date;
    string paymentMethod;
    string productID;
    int rating;
    string reviewText;
    Both* next;
};

// LinkedList & Array - Customer
struct Customer 
{
    string customerID;
    Customer* next;
};

// Helper - Frequency
struct Frequency 
{
    string text;
    int count;
    Frequency* next;
};
