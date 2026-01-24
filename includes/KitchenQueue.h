#ifndef KITCHENQUEUE_H
#define KITCHENQUEUE_H

#include <iostream>
#include "Order.h"

using namespace std;

class KitchenQueue {
private:
    Order* front;
    Order* rear;

public:
    KitchenQueue();
    ~KitchenQueue();

    void enqueueOrder(Order* o);
    void dequeueOrder();
    void viewNextOrder() const;
    bool isEmpty() const;
    void displayQueue() const;
    void displayOrdersForTable(int tableNo) const;
    Order* findPendingOrder(int tableNo) const;
    bool updateOrderStatus(int orderID, const string& newStatus);
    Order* findOrder(int orderID) const;
    bool removeOrder(int orderID);
    Order* getFront() const;
};

#endif
