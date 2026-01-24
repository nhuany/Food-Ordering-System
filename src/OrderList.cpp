#include "OrderList.h"

OrderList::OrderList() : head(nullptr), count(0) {}

OrderList::~OrderList() {
    OrderNode* current = head;
    while (current != nullptr) {
        OrderNode* temp = current;
        current = current->next;
        // Note: We don't delete the Order itself as it may be shared with KitchenQueue
        delete temp;
    }
}

void OrderList::addOrder(Order* order) {
    OrderNode* newNode = new OrderNode(order);
    
    if (head == nullptr) {
        head = newNode;
    } else {
        // Add to end of list
        OrderNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    count++;
}

Order* OrderList::findOrderByID(int orderID) {
    OrderNode* current = head;
    while (current != nullptr) {
        if (current->order->getOrderID() == orderID) {
            return current->order;
        }
        current = current->next;
    }
    return nullptr;
}

void OrderList::displayOrdersForTable(int tableNo) const {
    if (head == nullptr) {
        cout << "\nNo orders found." << endl;
        return;
    }

    OrderNode* current = head;
    bool found = false;
    
    while (current != nullptr) {
        if (current->order->getTableNo() == tableNo) {
            found = true;
            cout << "\n--------------------------------------------------------" << endl;
            cout << "Order #" << current->order->getOrderID() 
                 << " | Status: " << current->order->getStatus() << endl;
            cout << "--------------------------------------------------------" << endl;
            if (current->order->hasItems()) {
                current->order->displayOrderSummary();
            }
        }
        current = current->next;
    }

    if (!found) {
        cout << "\nNo orders found for Table " << tableNo << "." << endl;
    }
}

double OrderList::calculateTableTotal(int tableNo) const {
    double total = 0.0;
    OrderNode* current = head;
    
    while (current != nullptr) {
        if (current->order->getTableNo() == tableNo) {
            total += current->order->calculateTotal();
        }
        current = current->next;
    }
    
    return total;
}

int OrderList::getOrderCountForTable(int tableNo) const {
    int count = 0;
    OrderNode* current = head;
    
    while (current != nullptr) {
        if (current->order->getTableNo() == tableNo) {
            count++;
        }
        current = current->next;
    }
    
    return count;
}

bool OrderList::removeOrder(int orderID) {
    if (head == nullptr) return false;

    // If head is the order to remove
    if (head->order->getOrderID() == orderID) {
        OrderNode* temp = head;
        head = head->next;
        delete temp;
        count--;
        return true;
    }

    // Search for the order
    OrderNode* current = head;
    while (current->next != nullptr && current->next->order->getOrderID() != orderID) {
        current = current->next;
    }

    if (current->next != nullptr) {
        OrderNode* temp = current->next;
        current->next = temp->next;
        delete temp;
        count--;
        return true;
    }

    return false;
}

void OrderList::clearOrdersForTable(int tableNo) {
    OrderNode* current = head;
    OrderNode* prev = nullptr;
    
    while (current != nullptr) {
        if (current->order->getTableNo() == tableNo) {
            OrderNode* toDelete = current;
            
            // Unlink node
            if (prev == nullptr) {
                head = current->next;
                current = head;
            } else {
                prev->next = current->next;
                current = prev->next;
            }
            
            // Clean up memory
            // IMPORTANT: We delete the Order object here because the transaction is done
            delete toDelete->order; 
            delete toDelete;
            count--;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

bool OrderList::isEmpty() const {
    return head == nullptr;
}

int OrderList::getCount() const {
    return count;
}

OrderNode* OrderList::getHead() const {
    return head;
}
