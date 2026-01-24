#include "KitchenQueue.h"

KitchenQueue::KitchenQueue() : front(nullptr), rear(nullptr) {}

KitchenQueue::~KitchenQueue() {
    while (!isEmpty()) {
        dequeueOrder();
    }
}

void KitchenQueue::enqueueOrder(Order* o) {
    if (o == nullptr) return;

    // Resetting the next pointer of the incoming order to ensure cleanliness
    o->setNext(nullptr);

    if (isEmpty()) {
        front = o;
        rear = o;
        // Circular Linked List: rear points to front
        rear->setNext(front);
    } else {
        rear->setNext(o);
        rear = o;
        // Circular Linked List: rear always points back to front
        rear->setNext(front);
    }
    cout << "Order " << o->getOrderID() << " added to kitchen queue." << endl;
}

void KitchenQueue::dequeueOrder() {
    if (isEmpty()) {
        cout << "Kitchen queue is empty." << endl;
        return;
    }

    Order* temp = front;

    // If there is only one node
    if (front == rear) {
        front = nullptr;
        rear = nullptr;
    } else {
        front = front->getNext();
        rear->setNext(front); // Maintain circular link
    }

    cout << "Order " << temp->getOrderID() << " removed from kitchen queue." << endl;
    // Note: We do NOT delete the Order object itself, as it might be needed for history/reports.
    // Ideally, the system should manage the lifecycle of Order objects.
    // But for this queue operation, we just remove it from the queue structure.
}

void KitchenQueue::viewNextOrder() const {
    if (isEmpty()) {
        cout << "No pending orders." << endl;
    } else {
        front->printReceipt(); // Using printReceipt to show details
    }
}

bool KitchenQueue::isEmpty() const {
    return front == nullptr;
}

void KitchenQueue::displayQueue() const {
    if (isEmpty()) {
        cout << "\n========================================================" << endl;
        cout << "             NO ACTIVE ORDERS                         " << endl;
        cout << "========================================================" << endl;
        return;
    }

    cout << "\n========================================================" << endl;
    cout << "                 CURRENT ORDERS                        " << endl;
    cout << "========================================================" << endl;

    Order* current = front;
    int orderCount = 0;

    do {
        orderCount++;
        cout << "\n- ORDER #" << orderCount << " -" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "Order ID: " << current->getOrderID() << endl;
        cout << "Table: " << current->getTableNo() << endl;
        cout << "Status: " << current->getStatus() << endl;
        cout << "--------------------------------------------------------" << endl;

        // Show food items if order has them
        if (current->hasItems()) {
            current->displayPendingItems();
        } else {
            cout << "No food items in this order." << endl;
        }

        cout << "--------------------------------------------------------" << endl;

        current = current->getNext();
    } while (current != front);

    cout << "\nTotal Active Orders: " << orderCount << endl;
    cout << "========================================================" << endl;
}

Order* KitchenQueue::findOrder(int orderID) const {
    if (isEmpty()) {
        return nullptr;
    }

    Order* current = front;
    do {
        if (current->getOrderID() == orderID) {
            return current;
        }
        current = current->getNext();
    } while (current != front);

    return nullptr;
}

bool KitchenQueue::updateOrderStatus(int orderID, const string& newStatus) {
    Order* order = findOrder(orderID);
    if (order != nullptr) {
        order->setStatus(newStatus);
        return true;
    }
    return false;
}

void KitchenQueue::displayOrdersForTable(int tableNo) const {
    if (isEmpty()) {
        cout << "\n--------------------------------------------------------" << endl;
        cout << "          No active orders in the kitchen.            " << endl;
        cout << "--------------------------------------------------------" << endl;
        return;
    }

    bool found = false;
    Order* current = front;
    
    cout << "\n========================================================" << endl;
    cout << "           ORDERS FOR TABLE " << tableNo << "                     " << endl;
    cout << "========================================================" << endl;

    do {
        if (current->getTableNo() == tableNo) {
            found = true;
            cout << "\nOrder ID: " << current->getOrderID() << endl;
            cout << "Status: " << current->getStatus() << endl;
            cout << "--------------------------------------------------------" << endl;
            
            if (current->hasItems()) {
                current->displayOrderSummary();
            }
            cout << "--------------------------------------------------------" << endl;
        }
        current = current->getNext();
    } while (current != front);

    if (!found) {
        cout << "\nNo active orders found for Table " << tableNo << "." << endl;
    }
    cout << "========================================================" << endl;
}

Order* KitchenQueue::findPendingOrder(int tableNo) const {
    if (isEmpty()) return nullptr;

    Order* current = front;
    do {
        if (current->getTableNo() == tableNo && current->getStatus() == "pending") {
            return current;
        }
        current = current->getNext();
    } while (current != front);

    return nullptr;
}

Order* KitchenQueue::getFront() const {
    return front;
}

bool KitchenQueue::removeOrder(int orderID) {
    if (isEmpty()) return false;

    Order* current = front;
    Order* prev = rear; // In circular queue, prev of front is rear

    do {
        if (current->getOrderID() == orderID) {
            // Found the order to remove
            
            // Case 1: Only one node in queue
            if (front == rear) {
                front = nullptr;
                rear = nullptr;
            }
            // Case 2: Removing the front node
            else if (current == front) {
                front = front->getNext();
                rear->setNext(front);
            }
            // Case 3: Removing the rear node
            else if (current == rear) {
                rear = prev;
                rear->setNext(front);
            }
            // Case 4: Removing a middle node
            else {
                prev->setNext(current->getNext());
            }

            cout << "Order " << orderID << " removed from kitchen queue." << endl;
            // DO NOT delete the Order object - it is managed by OrderList/RestaurantSystem
            return true;
        }

        prev = current;
        current = current->getNext();
    } while (current != front);

    return false; // Order not found
}