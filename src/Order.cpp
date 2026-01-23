#include "Order.h"

Order::Order() : orderID(0), tableNo(0), status("pending"), head(nullptr), next(nullptr) {}

Order::Order(int id, int table) : orderID(id), tableNo(table), status("pending"), head(nullptr), next(nullptr) {}

Order::~Order() {
    OrderItem* current = head;
    while (current != nullptr) {
        OrderItem* temp = current;
        current = current->getNext();
        delete temp;
    }
}

int Order::getOrderID() const {
    return orderID;
}

int Order::getTableNo() const { //
    return tableNo;
}

string Order::getStatus() const {
    return status;
}

void Order::setStatus(string s) {
    status = s;
}

void Order::addFoodOrder(int orderItemID, FoodItem* f, int qty) {
    OrderItem* newItem = new OrderItem(orderItemID, f, qty);
    if (head == nullptr) {
        head = newItem;
    } else {
        OrderItem* current = head;
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }
        current->setNext(newItem);
    }
}

void Order::removeFoodFromOrder(int orderItemID) {
    if (status == "served") {
        cout << "Cannot remove item. Order already served." << endl;
        return;
    }

    if (head == nullptr) return;

    if (head->getOrderItemID() == orderItemID) {
        OrderItem* temp = head;
        head = head->getNext();
        delete temp;
        cout << "Item removed successfully." << endl;
        return;
    }

    OrderItem* current = head;
    while (current->getNext() != nullptr && current->getNext()->getOrderItemID() != orderItemID) {
        current = current->getNext();
    }

    if (current->getNext() != nullptr) {
        OrderItem* temp = current->getNext();
        current->setNext(temp->getNext());
        delete temp;
        cout << "Item removed successfully." << endl;
    } else {
        cout << "Item not found in order." << endl;
    }
}

double Order::calculateTotal() const {
    double total = 0.0;
    OrderItem* current = head;
    while (current != nullptr) {
        total += current->calculateSubtotal();
        current = current->getNext();
    }
    // Assuming tax is 10% for example, or just return subtotal if not specified.
    // Spec says "add tax". Let's add 6% tax.
    return total * 1.06;
}

void Order::printReceipt() const {
    cout << "========================================" << endl;
    cout << "              RECEIPT                   " << endl;
    cout << "========================================" << endl;
    cout << "Order ID: " << orderID << "   Table: " << tableNo << endl;
    cout << "Status: " << status << endl;
    cout << "----------------------------------------" << endl;

    OrderItem* current = head;
    while (current != nullptr) {
        current->displayItemLine();
        current = current->getNext();
    }

    cout << "----------------------------------------" << endl;
    cout << "Total (inc 6% tax): RM" << fixed << setprecision(2) << calculateTotal() << endl;
    cout << "========================================" << endl;
}

Order* Order::getNext() const {
    return next;
}

void Order::setNext(Order* n) {
    next = n;
}

bool Order::hasItems() const {
    return head != nullptr;
}

void Order::displayOrderSummary() const {
    if (head == nullptr) {
        cout << "No items in order." << endl;
        return;
    }

    OrderItem* current = head;
    int itemCount = 0;

    cout << "Food Items:" << endl;
    cout << "--------------------------------------------------------" << endl;

    while (current != nullptr) {
        itemCount++;
        cout << itemCount << ". ";
        current->displayItemLine();
        current = current->getNext();
    }

    cout << "--------------------------------------------------------" << endl;
    cout << "Total items: " << itemCount << endl;
}
