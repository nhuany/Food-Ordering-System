#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <iomanip>
#include "OrderItem.h"

using namespace std;

class Order {
private:
    int orderID;
    int tableNo;
    string status; // pending, preparing, served
    OrderItem* head; // Head of the linked list of OrderItems
    
    // Pointer for KitchenQueue (since Order is a Node in KitchenQueue)
    Order* next; 

public:
    Order();
    Order(int id, int table);
    ~Order(); // Destructor to clean up OrderItems

    int getOrderID() const;
    string getStatus() const;
    void setStatus(string s);

    // List Operations
    void addFoodOrder(int orderItemID, FoodItem* f, int qty);
    void removeFoodFromOrder(int orderItemID);
    double calculateTotal() const;
    void printReceipt() const;

    // Queue Node Operations
    Order* getNext() const;
    void setNext(Order* n);
};

#endif
