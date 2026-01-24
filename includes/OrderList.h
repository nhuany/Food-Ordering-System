#ifndef ORDERLIST_H
#define ORDERLIST_H

#include <iostream>
#include "Order.h"

using namespace std;

// Node for the OrderList linked list
struct OrderNode {
    Order* order;
    OrderNode* next;
    
    OrderNode(Order* o) : order(o), next(nullptr) {}
};

class OrderList {
private:
    OrderNode* head;
    int count;

public:
    OrderList();
    ~OrderList();

    // Add order to the list
    void addOrder(Order* order);
    
    // Find order by ID
    Order* findOrderByID(int orderID);
    
    // Display all orders for a specific table
    void displayOrdersForTable(int tableNo) const;
    
    // Calculate total for a table's orders
    double calculateTableTotal(int tableNo) const;
    
    // Get count of orders for a table
    int getOrderCountForTable(int tableNo) const;
    
    // Remove order by ID
    bool removeOrder(int orderID);
    
    // Clear all orders for a specific table (e.g. after payment)
    void clearOrdersForTable(int tableNo);
    
    // Check if list is empty
    bool isEmpty() const;
    
    // Get total order count
    int getCount() const;
    
    // Get head (for iteration)
    OrderNode* getHead() const;
};

#endif
