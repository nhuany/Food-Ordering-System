#ifndef RESTAURANTSYSTEM_H
#define RESTAURANTSYSTEM_H

#include "MenuList.h"
#include "KitchenQueue.h"
#include "Order.h"
#include "FoodItem.h"
#include <string>

class RestaurantSystem {
private:
    MenuList menu;
    KitchenQueue kitchen;
    int nextOrderID;
    int nextOrderItemID;

public:
    RestaurantSystem();
    ~RestaurantSystem();

    // Menu Management
    void initializeMenu();
    void saveMenuData();
    void displayMenu();
    void addMenuItem();
    void removeMenuItem();
    void editMenuItem();
    void searchMenuItem();

    // Order Management
    void createOrder();
    void viewOrders();
    void updateOrderStatus();

    // Kitchen Management
    void viewKitchenQueue();
    void processNextOrder();

    // Menu Display Functions
    void displayMainMenu();
    void displayCustomerMenu();
    void displayAdminMenu();
    void displayMenuManagement();

    // Authentication
    bool authenticateAdmin();

    // Main Program Flow
    void run();
};

#endif
