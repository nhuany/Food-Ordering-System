# Data Structure Implementation Details

This document outlines the data structures chosen for the Food Ordering System, providing detailed explanations and actual code examples from the project to illustrate their implementation.

## 1. Singly Linked List
### Components
- **MenuList** (Stores `FoodItem` nodes)
- **OrderList** (Stores `Order` nodes)
- **Order** (Stores `OrderItem` nodes representing individual dishes)

### Rationale
We chose a **Singly Linked List** because the data requirements are dynamic. A menu can have 10 items or 100, and an order can have 1 dish or 50. Linked lists allow us to:
1.  **Allocate memory dynamically**: Nodes are created only when needed (`new FoodItem(...)`).
2.  **Efficiently Insert/Delete**: Adding a new order is O(1) (appending to tail) without needing to resize an array.

### Code Implementation
The base node structure is defined in `FoodItem` (and similarly in `Order` and `OrderItem`). Note the `next` pointer which links to the subsequent item.

**File: `includes/FoodItem.h`**
```cpp
class FoodItem {
private:
    // Data fields
    int foodID;
    string foodName;
    double foodPrice;
    
    // Pointer to the next node in the list
    FoodItem* next; 

public:
    // ... constructors ...
    FoodItem* getNext() const { return next; }
    void setNext(FoodItem* n) { next = n; }
};
```

Traversal is done by following these next pointers until `nullptr` is reached.

## 2. Circular Linked Queue
### Components
- **KitchenQueue**

### Rationale
We chose a **Circular Linked List** to implement the Kitchen Queue.
1.  **FIFO Fairness**: The Queue data structure enforces First-In-First-Out processing.
2.  **Circular Efficiency**: By having the `rear` node point back to `front`, we create a continuous loop. This structure is particularly useful if we need to iterate through the queue repeatedly (e.g., to constantly update status) without needing to handle a "stop" condition at the end of the list—we simply return to the start.

### Code Implementation
In `KitchenQueue`, we maintain `front` and `rear` pointers. The circular nature is enforced in `enqueueOrder` by strictly setting `rear->next` to `front`.

**File: `src/KitchenQueue.cpp`**
```cpp
void KitchenQueue::enqueueOrder(Order* o) {
    // ...
    if (isEmpty()) {
        front = o;
        rear = o;
        // Circular: rear points to front
        rear->setNext(front); 
    } else {
        rear->setNext(o);
        rear = o;
        // Circular: rear ALWAYS points back to front
        rear->setNext(front); 
    }
}
```

When dequeuing, we must maintain this loop unless the queue becomes empty.

## 3. Dynamic Array of Pointers
### Components
- **Sorting Operations** (`MenuList::displaySortedBy...`)

### Rationale
Since we cannot use STL containers like `std::vector`, we implemented a manual solution for non-destructive sorting.
1.  **Non-Destructive View**: We create a temporary array of **pointers** (`FoodItem**`) that point to the actual nodes in the Linked List.
2.  **Algorithm**: We use a simple **Bubble Sort** on this array of pointers.
3.  **Efficiency**: By swapping pointers in the array instead of swapping full nodes in the Linked List, we avoid complex pointer rewiring and keep the original Linked List intact.

### Code Implementation
We manually allocate an array, fill it, sort it, display, and then delete it.

**File: `src/MenuList.cpp`**
```cpp
void MenuList::displaySortedByPrice() const {
    // 1. Count nodes
    int count = 0;
    // ... traversal to count ...

    // 2. Create dynamic array of pointers
    FoodItem** items = new FoodItem*[count];
    // ... fill array ...

    // 3. Bubble Sort (swapping pointers only)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (items[j]->getPrice() > items[j + 1]->getPrice()) {
                FoodItem* temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }

    // 4. Display and Cleanup
    // ... display ...
    delete[] items; // Free the temporary array
}
```
