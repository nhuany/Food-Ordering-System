#include <iostream>
#include "FoodItem.h"
#include "Order.h"
#include "KitchenQueue.h"

using namespace std;

int main() {
    cout << "=== Food Ordering System Test ===" << endl;

    // 1. Create Food Items
    FoodItem* burger = new FoodItem(101, "Burger", "Main Course", 5.99);
    FoodItem* fries = new FoodItem(102, "Fries", "Side", 2.50);
    FoodItem* coke = new FoodItem(103, "Coke", "Beverage", 1.50);

    // 2. Create an Order
    Order* order1 = new Order(1, 5); // Order ID 1, Table 5
    cout << "\nCreating Order 1 (Table 5)..." << endl;

    // 3. Add items to Order
    order1->addFoodOrder(1, burger, 2); // 2 Burgers
    order1->addFoodOrder(2, fries, 1);  // 1 Fries
    order1->addFoodOrder(3, coke, 3);   // 3 Cokes

    // 4. Print Receipt
    order1->printReceipt();

    // 5. Test Removing Item
    cout << "\nRemoving Item 2 (Fries)..." << endl;
    order1->removeFoodFromOrder(2);
    order1->printReceipt();

    // 6. Kitchen Queue
    KitchenQueue kq;
    cout << "\n--- Testing Kitchen Queue ---" << endl;
    
    kq.enqueueOrder(order1);

    Order* order2 = new Order(2, 3); // Order ID 2, Table 3
    order2->addFoodOrder(4, burger, 1);
    kq.enqueueOrder(order2);

    kq.displayQueue();

    cout << "\nChecking next order..." << endl;
    kq.viewNextOrder();

    cout << "\nCompleting first order..." << endl;
    kq.dequeueOrder();
    
    kq.displayQueue();

    cout << "\nCompleting second order..." << endl;
    kq.dequeueOrder();

    kq.displayQueue();

    // Clean up
    delete burger;
    delete fries;
    delete coke;
    delete order1;
    delete order2;

    return 0;
}
