#include "OrderItem.h"

OrderItem::OrderItem() : OrderItemID(0), food(nullptr), Quantity(0), status("pending"), next(nullptr) {}

OrderItem::OrderItem(int id, FoodItem* f, int qty) : OrderItemID(id), food(f), Quantity(qty), status("pending"), next(nullptr) {}

int OrderItem::getOrderItemID() const {
    return OrderItemID;
}

void OrderItem::setItemDetails(int id, FoodItem* f, int qty) {
    OrderItemID = id;
    food = f;
    Quantity = qty;
}

string OrderItem::getStatus() const {
    return status;
}

void OrderItem::setStatus(string s) {
    status = s;
}

double OrderItem::calculateSubtotal() const {
    if (food) {
        return food->getPrice() * Quantity;
    }
    return 0.0;
}

void OrderItem::displayItemLine() const {
    if (food) {
        // Format: Name xQty ... [Status] ... Subtotal
        cout << left << setw(20) << food->getName() 
             << " x" << setw(3) << Quantity 
             << " [" << setw(8) << status << "] "
             << right << setw(10) << fixed << setprecision(2) << calculateSubtotal() << endl;
    } else {
        cout << "Invalid Item" << endl;
    }
}

OrderItem* OrderItem::getNext() const {
    return next;
}

void OrderItem::setNext(OrderItem* n) {
    next = n;
}
