#include <iostream>
#include "FoodItem.h"
#include "Order.h"
#include "KitchenQueue.h"
#include "MenuList.h"

using namespace std;

int main() {
    cout << "=== Food Ordering System Test ===" << endl;

    // -------------------------------
    // 1. Create and Test MenuList
    // -------------------------------
    MenuList menu;

    cout << "\n--- Building Menu ---" << endl;
    menu.addFoodItem(new FoodItem(101, "Burger", "Main Course", 5.99));
    menu.addFoodItem(new FoodItem(102, "Fries", "Side", 2.50));
    menu.addFoodItem(new FoodItem(103, "Coke", "Beverage", 1.50));

    menu.displayMenu();

    cout << "\nSearching for Fries..." << endl;
    menu.searchFoodByName("Fries");

    cout << "\nEditing Coke -> Diet Coke..." << endl;
    menu.editFoodItem(103, "Diet Coke", "Beverage", 1.75);
    menu.displayMenu();

    cout << "\nSorting Menu by Price..." << endl;
    menu.sortMenuByPrice();
    menu.displayMenu();

    cout << "\nDeleting Fries..." << endl;
    menu.deleteFoodItem(102);
    menu.displayMenu();

    // -------------------------------
    // 2. Create Orders
    // -------------------------------
    cout << "\n--- Creating Orders ---" << endl;
    FoodItem* burger = new FoodItem(201, "Burger", "Main Course", 5.99);
    FoodItem* fries = new FoodItem(202, "Fries", "Side", 2.50);
    FoodItem* coke = new FoodItem(203, "Coke", "Beverage", 1.50);

    Order* order1 = new Order(1, 5); // Order ID 1, Table 5
    order1->addFoodOrder(1, burger, 2); // 2 Burgers
    order1->addFoodOrder(2, fries, 1);  // 1 Fries
    order1->addFoodOrder(3, coke, 3);   // 3 Cokes

    cout << "\nReceipt for Order 1:" << endl;
    order1->printReceipt();

    cout << "\nRemoving Item 2 (Fries) from Order 1..." << endl;
    order1->removeFoodFromOrder(2);
    order1->printReceipt();

    // -------------------------------
    // 3. Kitchen Queue
    // -------------------------------
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

    // -------------------------------
    // 4. Clean up
    // -------------------------------
    delete burger;
    delete fries;
    delete coke;
    delete order1;
    delete order2;

    return 0;
}
