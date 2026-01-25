#ifndef RESTAURANTSYSTEM_H
#define RESTAURANTSYSTEM_H

#include "MenuList.h"
#include "KitchenQueue.h"
#include "OrderList.h"
#include "Order.h"
#include "FoodItem.h"
#include <string>

class RestaurantSystem {
private:
    MenuList menu;
    KitchenQueue kitchen;      // Circular queue for kitchen processing
    OrderList allOrders;       // Linked list for all orders (billing)
    int nextOrderID;
    int nextOrderItemID;
    
    // Sales Tracking
    double dailyRevenue;
    int totalOrdersServed;

    // UI Helper Functions
    void clearScreen();
    void pauseSystem();

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
    // Order Management
    void createOrder(int tableNo);
    void viewMyOrders(int tableNo);
    void cancelOrder();

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

    // Reports
    void generateDailySalesReport();

    // Main Program Flow
    void run();
};

#endif
