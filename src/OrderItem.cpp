#include "OrderItem.h"

OrderItem::OrderItem() : OrderItemID(0), food(nullptr), Quantity(0), next(nullptr) {}

OrderItem::OrderItem(int id, FoodItem* f, int qty) : OrderItemID(id), food(f), Quantity(qty), next(nullptr) {}

int OrderItem::getOrderItemID() const {
    return OrderItemID;
}

void OrderItem::setItemDetails(int id, FoodItem* f, int qty) {
    OrderItemID = id;
    food = f;
    Quantity = qty;
}

double OrderItem::calculateSubtotal() const {
    if (food) {
        return food->getPrice() * Quantity;
    }
    return 0.0;
}

void OrderItem::displayItemLine() const {
    if (food) {
        // Format: Name xQty ........ Subtotal
        cout << left << setw(20) << food->getName() 
             << " x" << setw(3) << Quantity 
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
