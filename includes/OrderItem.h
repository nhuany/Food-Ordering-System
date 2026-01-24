#ifndef ORDERITEM_H
#define ORDERITEM_H

#include <iostream>
#include <iomanip>
#include "FoodItem.h"

using namespace std;

class OrderItem {
private:
    int OrderItemID;
    FoodItem* food; // Pointer to the FoodItem to access details
    int Quantity;
    string status; // "pending", "served"
    
    OrderItem* next; // Pointer to next OrderItem in the Order list

public:
    OrderItem();
    OrderItem(int id, FoodItem* f, int qty);

    int getOrderItemID() const;
    void setItemDetails(int id, FoodItem* f, int qty);
    
    string getStatus() const;
    void setStatus(string s);

    double calculateSubtotal() const;
    void displayItemLine() const;
    
    OrderItem* getNext() const;
    void setNext(OrderItem* n);
};

#endif
