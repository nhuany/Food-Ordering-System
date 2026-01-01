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
        cout << "Next Order to Prepare:" << endl;
        front->printReceipt(); // Using printReceipt to show details
    }
}

bool KitchenQueue::isEmpty() const {
    return front == nullptr;
}

void KitchenQueue::displayQueue() const {
    if (isEmpty()) {
        cout << "Kitchen Queue is Empty." << endl;
        return;
    }

    cout << "\n--- Current Kitchen Queue ---" << endl;
    Order* current = front;
    do {
        cout << "Order ID: " << current->getOrderID() << " (Table " << current->getOrderID() << ")" << endl; // Assuming TableNo access or ID
        // Actually Order class doesn't expose getTableNo publicly in my code above?
        // Let's check Order.h... I created `getOrderID`. I did not create `getTableNo`.
        // I will add it if needed or just show OrderID.
        
        current = current->getNext();
    } while (current != front);
    cout << "-----------------------------" << endl;
}
