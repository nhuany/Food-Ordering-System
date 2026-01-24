#include "RestaurantSystem.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <cctype>
using namespace std;

RestaurantSystem::RestaurantSystem() : nextOrderID(1001), nextOrderItemID(1) {
    initializeMenu(); // Load initial menu data
}

RestaurantSystem::~RestaurantSystem() {
    // Save menu data to file on exit
    saveMenuData();
}

void RestaurantSystem::saveMenuData() {
    menu.saveToFile("menu.txt");
}

void RestaurantSystem::initializeMenu() {
    // Load menu from file
    ifstream file("menu.txt");
    bool loaded = false;

    if (file.is_open()) {
        // Check if file is empty
        if (file.peek() == ifstream::traits_type::eof()) {
            // File exists but is empty
            loaded = false;
        } else {
            int id;
            string name, category, priceStr;
            double price;

            // Reading CSV-like format: ID,Name,Category,Price
            while (file >> id) {
                if (file.peek() == ',') file.ignore();
                getline(file, name, ',');
                getline(file, category, ',');
                file >> price;
                
                // Using newlines
                file.ignore(numeric_limits<streamsize>::max(), '\n');

                FoodItem* newItem = new FoodItem(id, name, category, price);
                menu.addFoodItem(newItem);
                loaded = true;
            }
        }
        file.close();
    }

    // If loading failed or file was empty/missing, create defaults
    if (!loaded || menu.isEmpty()) {
        cout << "[System] Initializing default menu items..." << endl;
        
        FoodItem* item1 = new FoodItem(101, "Burger", "Main Course", 12.99);
        FoodItem* item2 = new FoodItem(102, "Fries", "Side", 5.99);
        FoodItem* item3 = new FoodItem(103, "Coke", "Beverage", 3.50);
        FoodItem* item4 = new FoodItem(104, "Pizza", "Main Course", 25.99);
        FoodItem* item5 = new FoodItem(105, "Salad", "Appetizer", 8.99);
        FoodItem* item6 = new FoodItem(106, "Ice Cream", "Dessert", 6.50);

        menu.addFoodItem(item1);
        menu.addFoodItem(item2);
        menu.addFoodItem(item3);
        menu.addFoodItem(item4);
        menu.addFoodItem(item5);
        menu.addFoodItem(item6);
    }
}

// Menu Management Functions
void RestaurantSystem::displayMenu() {
    menu.displayMenu();
}

void RestaurantSystem::addMenuItem() {
    cout << "\n=== ADD NEW MENU ITEM ===" << endl;

    int id;
    string name, category;
    double price;

    // Get Food ID with error checking
    while (true) {
        cout << "Enter Food ID (must be positive integer): ";
        if (cin >> id && id > 0) {
            // Check if ID already exists
            if (menu.getFoodByID(id) != nullptr) {
                cout << "Error: Food ID " << id << " already exists! Please choose another ID." << endl;
            } else {
                break;
            }
        } else {
            cout << "Invalid input! Please enter a positive integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    cin.ignore();

    // Get Food Name
    cout << "Enter Food Name: ";
    getline(cin, name);
    if (name.empty()) {
        cout << "Food name cannot be empty. Using default name." << endl;
        name = "Unnamed Item";
    }

    // Get Category
    cout << "Enter Category: ";
    getline(cin, category);
    if (category.empty()) {
        cout << "Category cannot be empty. Using default category." << endl;
        category = "Uncategorized";
    }

    // Get Price with error checking
    while (true) {
        cout << "Enter Price: RM ";
        if (cin >> price && price >= 0) {
            break;
        } else {
            cout << "Invalid input! Please enter a non-negative number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    FoodItem* newItem = new FoodItem(id, name, category, price);
    menu.addFoodItem(newItem);
    cout << "Menu item added successfully!" << endl;
}

void RestaurantSystem::removeMenuItem() {
    cout << "\n=== REMOVE MENU ITEM ===" << endl;

    // Check if menu is empty using new isEmpty() function
    if (menu.isEmpty()) {
        cout << "Menu is empty. Cannot remove items." << endl;
        return;
    }

    menu.displayMenu();

    int id;
    // Get Food ID with error checking
    while (true) {
        cout << "\nEnter Food ID to remove (0 to cancel): ";
        if (cin >> id) {
            if (id == 0) {
                cout << "Operation cancelled." << endl;
                return;
            }
            if (id > 0) {
                break;
            }
        }
        cout << "Invalid input! Please enter a positive integer." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    menu.deleteFoodItem(id);
}

void RestaurantSystem::editMenuItem() {
    // Header
    cout << "\n========================================================" << endl;
    cout << "                  EDIT MENU ITEM                     " << endl;
    cout << "========================================================" << endl;

    // Check if menu is empty
    if (menu.isEmpty()) {
        cout << "\n========================================================" << endl;
        cout << "               MENU IS EMPTY                        " << endl;
        cout << "========================================================" << endl;
        return;
    }

    // Display current menu
    cout << "\n========================================================" << endl;
    cout << "                   CURRENT MENU                       " << endl;
    cout << "========================================================" << endl;
    cout << " ID   ITEM NAME              CATEGORY       PRICE       " << endl;
    cout << "========================================================" << endl;
    menu.displayMenu(); // This should show the formatted table
    cout << "========================================================" << endl;

    // Get Food ID
    int id;
    while (true) {
        cout << "\n--------------------------------------------------------" << endl;
        cout << " Enter Food ID to edit (0 to cancel): ";
        if (cin >> id) {
            if (id == 0) {
                cout << "\n--------------------------------------------------------" << endl;
                cout << " Operation cancelled." << endl;
                cout << "--------------------------------------------------------" << endl;
                return;
            }
            if (id > 0) {
                break;
            }
        }
        cout << "--------------------------------------------------------" << endl;
        cout << " [!] Invalid input! Enter positive integer." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    // Edit Section
    cout << "\n========================================================" << endl;
    cout << "          EDITING ITEM ID: " << setw(4) << left << id << "          " << endl;
    cout << "========================================================" << endl;

    string name, category;
    double price = -1;

    cout << "\nEnter new details (press Enter to keep current value):" << endl;
    cout << "--------------------------------------------------------" << endl;

    cout << "New Food Name: ";
    getline(cin, name);

    cout << "New Category: ";
    getline(cin, category);

    while (true) {
        cout << "New Price (RM): ";
        string priceInput;
        getline(cin, priceInput);

        if (priceInput.empty()) {
            price = -1; // Keep current price
            break;
        }

        try {
            price = stod(priceInput);
            if (price >= 0) {
                break;
            } else {
                cout << "--------------------------------------------------------" << endl;
                cout << " [!] Price cannot be negative!" << endl;
            }
        } catch (...) {
            cout << "--------------------------------------------------------" << endl;
            cout << " [!] Invalid price format!" << endl;
        }
    }

    // Confirmation
    cout << "\n========================================================" << endl;
    cout << " Confirm update for Item ID " << id << "? (Y/N): ";
    char confirm;
    cin >> confirm;

    if (toupper(confirm) == 'Y') {
        menu.editFoodItem(id, name, category, price);
        cout << "\n========================================================" << endl;
        cout << "      ITEM UPDATED SUCCESSFULLY!                      " << endl;
        cout << "========================================================" << endl;
    } else {
        cout << "\n========================================================" << endl;
        cout << "             Update cancelled.                        " << endl;
        cout << "========================================================" << endl;
    }
}

void RestaurantSystem::searchMenuItem() {
    cout << "\n=== SEARCH MENU ITEM ===" << endl;

    // Check if menu is empty
    if (menu.isEmpty()) {
        cout << "Menu is empty. Cannot search items." << endl;
        return;
    }

    string name;
    cout << "Enter food name to search: ";
    cin.ignore();
    getline(cin, name);

    if (name.empty()) {
        cout << "Search term cannot be empty!" << endl;
        return;
    }

    FoodItem* result = menu.searchFoodByName(name);
    if (result) {
        cout << "Item found!" << endl;
    }
}

// Order Management Functions
void RestaurantSystem::createOrder(int tableNo) {
    // Always create a NEW order to maintain FIFO kitchen queue order
    cout << "\n=== CREATE NEW ORDER (Table " << tableNo << ") ===" << endl;
    Order* newOrder = new Order(nextOrderID, tableNo);

    char addMore = 'Y';
    int itemCount = 0;

    while (toupper(addMore) == 'Y') {
        displayMenu();

        int foodID, quantity;

        while (true) {
            cout << "\nEnter Food ID to order (0 to finish): ";
            if (cin >> foodID) {
                if (foodID == 0) break;
                if (foodID > 0) break;
            }
            cout << "Invalid input! Please enter a positive integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (foodID == 0) break;

        // Lookup Food Item
        FoodItem* food = menu.getFoodByID(foodID);
        if (food == nullptr) {
            cout << "Error: Food ID " << foodID << " not found in menu." << endl;
            continue;
        }

        while (true) {
            cout << "Enter quantity (1-10): ";
            if (cin >> quantity && quantity >= 1 && quantity <= 10) {
                break;
            } else {
                cout << "Invalid input! Please enter quantity between 1-10." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        // Add food item to order
        newOrder->addFoodOrder(nextOrderItemID, food, quantity);
        nextOrderItemID++;
        itemCount++;

        cout << "Added: " << food->getName() << " x" << quantity << endl;

        cout << "Add another item? (Y/N): ";
        cin >> addMore;
    }

    if (itemCount > 0) {
        // Add to BOTH data structures:
        // 1. OrderList (linked list) - for customer billing/viewing
        allOrders.addOrder(newOrder);
        // 2. KitchenQueue (circular queue) - for kitchen processing
        kitchen.enqueueOrder(newOrder);
        
        nextOrderID++;
        cout << "\nOrder " << newOrder->getOrderID() << " created and sent to kitchen!" << endl;
    } else {
        cout << "\nOrder cancelled (no items added)." << endl;
        delete newOrder;
    }
}

void RestaurantSystem::viewMyOrders(int tableNo) {
    cout << "\n========================================================" << endl;
    cout << "           YOUR ORDERS (Table " << tableNo << ")              " << endl;
    cout << "========================================================" << endl;

    // Check OrderList (linked list) - NOT KitchenQueue
    int orderCount = allOrders.getOrderCountForTable(tableNo);
    
    if (orderCount == 0) {
        cout << "\nNo orders found for your table." << endl;
        cout << "\nPress Enter to return to menu...";
        cin.ignore();
        cin.get();
        return;
    }

    // Display orders from OrderList
    allOrders.displayOrdersForTable(tableNo);
    
    // Calculate total from OrderList
    double grandTotal = allOrders.calculateTableTotal(tableNo);

    // Show bill summary
    cout << "\n========================================================" << endl;
    cout << "  TOTAL ORDERS: " << orderCount << endl;
    cout << "  GRAND TOTAL (inc 6% tax): RM" << fixed << setprecision(2) << grandTotal << endl;
    cout << "========================================================" << endl;

    char payChoice;
    cout << "\nWould you like to pay now? (Y/N): ";
    cin >> payChoice;

    if (toupper(payChoice) == 'Y') {
        // Clear all orders for this table from the list (simulating payment and clearing table)
        allOrders.clearOrdersForTable(tableNo);

        cout << "\n========================================================" << endl;
        cout << "          PAYMENT SUCCESSFUL!                          " << endl;
        cout << "          Thank you for dining with us!                " << endl;
        cout << "========================================================" << endl;
    }

    cout << "\nPress Enter to return to menu...";
    cin.ignore();
    cin.get();
}



void RestaurantSystem::cancelOrder() {
    cout << "\n========================================================" << endl;
    cout << "               CANCEL ORDER                             " << endl;
    cout << "========================================================" << endl;

    if (kitchen.isEmpty()) {
        cout << "\n--------------------------------------------------------" << endl;
        cout << "          No orders in kitchen to cancel.              " << endl;
        cout << "--------------------------------------------------------" << endl;
        return;
    }

    cout << "\nCurrent Orders in System:" << endl;
    kitchen.displayQueue();

    int orderID;
    cout << "\nEnter Order ID to modify: ";
    while (!(cin >> orderID)) {
        cout << "Invalid input! Please enter a numeric Order ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    Order* order = allOrders.findOrderByID(orderID);
    if (!order) {
        cout << "Order ID " << orderID << " not found." << endl;
        return;
    }

    // Display order items
    order->displayOrderSummary();

    int itemIndex;
    cout << "\nEnter Item Index to cancel (0 to cancel entire order): ";
    while (!(cin >> itemIndex)) {
        cout << "Invalid input! Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (itemIndex == 0) {
        char confirm;
        cout << "Are you sure you want to cancel the ENTIRE Order " << orderID << "? (Y/N): ";
        cin >> confirm;
        if (toupper(confirm) == 'Y') {
             kitchen.removeOrder(orderID);
             allOrders.removeOrder(orderID);
             cout << "Order " << orderID << " cancelled entirely." << endl;
        }
    } else {
        if (order->removeFoodByIndex(itemIndex)) {
            cout << "Item #" << itemIndex << " removed from order." << endl;
            
            // Check if order is now empty
            if (!order->hasItems()) {
                cout << "Order " << orderID << " is now empty. Removing order from system..." << endl;
                kitchen.removeOrder(orderID);
                allOrders.removeOrder(orderID);
            }
        } else {
             cout << "Failed to remove item. Invalid index or order served." << endl;
        }
    }
}

// Kitchen Management Functions
void RestaurantSystem::viewKitchenQueue() {
    cout << "\n=== KITCHEN QUEUE ===" << endl;
    kitchen.displayQueue();
}

void RestaurantSystem::processNextOrder() {
    cout << "\n=== PROCESS NEXT ORDER ===" << endl;

    if (kitchen.isEmpty()) {
        cout << "No orders in the kitchen queue." << endl;
        return;
    }

    // Get the front order to display and potentially update
    Order* nextOrder = kitchen.getFront();
    if (nextOrder == nullptr) {
        cout << "No orders in the kitchen queue." << endl;
        return;
    }

    // Find the first pending order to process
    Order* current = nextOrder;
    Order* orderToProcess = nullptr;
    do {
        if (current->getStatus() == "pending") {
            orderToProcess = current;
            break;
        }
        current = current->getNext();
    } while (current != nextOrder);

    if (orderToProcess == nullptr) {
        cout << "No pending orders to process." << endl;
        return;
    }

    // Display the order to process with item details and status (Filtered for Kitchen)
    cout << "\n==============================================" << endl;
    cout << "           ORDER PROCESSING TICKET            " << endl;
    cout << "==============================================" << endl;
    cout << "Order ID: " << orderToProcess->getOrderID() << endl;
    cout << "Table: " << orderToProcess->getTableNo() << endl;
    cout << "==============================================" << endl;
    
    orderToProcess->displayPendingItems(); 

    int serveChoice;
    while (true) {
        cout << "\nEnter Item # to mark as SERVED (0 for ALL, -1 to Cancel Selection): ";
        if (cin >> serveChoice) {
             break;
        }
        cout << "Invalid input! Please enter a number." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (serveChoice == -1) {
        cout << "Processing cancelled." << endl;
        return;
    }

    if (serveChoice == 0) {
        // Serve ALL
        char confirm;
        cout << "Mark ALL items as SERVED? (Y/N): ";
        cin >> confirm;
        if (toupper(confirm) == 'Y') {
            orderToProcess->serveAllItems(); // Ensure all items are marked served
            orderToProcess->setStatus("served");
            kitchen.dequeueOrder();
            cout << "Order " << orderToProcess->getOrderID() << " fully processed/served." << endl;
        }
    } else {
        // Serve specific item by PENDING index (1, 2, 3...)
        if (orderToProcess->servePendingItem(serveChoice)) {
            // Check if all items are served
            if (orderToProcess->checkAllServed()) {
                orderToProcess->setStatus("served");
                kitchen.dequeueOrder();
                cout << "All items served! Order removed from kitchen queue." << endl;
            } else {
                cout << "Item served. Order remains in queue until all items are ready." << endl;
            }
        } else {
            cout << "Failed to serve item (Invalid choice)." << endl;
        }
    }
}

// Menu Display Functions
void RestaurantSystem::displayMainMenu() {
    cout << "\n=================================" << endl;
    cout << "    RESTAURANT FOOD ORDERING SYSTEM" << endl;
    cout << "=================================" << endl;
    cout << "1. Admin" << endl;
    cout << "2. Customer" << endl;
    cout << "0. Exit" << endl;
    cout << "=================================" << endl;
    cout << "Choice: ";
}

void RestaurantSystem::displayCustomerMenu() {
    cout << "\n==================================" << endl;
    cout << "        CUSTOMER MENU             " << endl;
    cout << "==================================" << endl;
    cout << "1. View Menu" << endl;
    cout << "2. Create New Order" << endl;
    cout << "3. View My Orders / Pay Bill" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "==================================" << endl;
    cout << "Enter your choice (0-3): ";
}

void RestaurantSystem::displayAdminMenu() {
    cout << "\n==================================" << endl;
    cout << "          ADMIN MENU             " << endl;
    cout << "==================================" << endl;
    cout << "1. View Kitchen Queue" << endl;
    cout << "2. Process Next Order" << endl;
    cout << "3. Cancel Order" << endl;
    cout << "4. Manage Menu Items" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "==================================" << endl;
    cout << "Enter your choice (0-4): ";
}

void RestaurantSystem::displayMenuManagement() {
    cout << "\n=================================" << endl;
    cout << "       MENU MANAGEMENT            " << endl;
    cout << "=================================" << endl;
    cout << "1. Add Menu Item" << endl;
    cout << "2. Remove Menu Item" << endl;
    cout << "3. Edit Menu Item" << endl;
    cout << "4. Search Menu Item" << endl;
    cout << "0. Back to Admin Menu" << endl;
    cout << "=================================" << endl;
    cout << "Enter your choice (0-4): ";
}

// Authentication
bool RestaurantSystem::authenticateAdmin() {
    string password;
    int attempts = 3;

    cout << "\n=== ADMIN LOGIN ===" << endl;

    while (attempts > 0) {
        cout << "Enter admin password (" << attempts << " attempts left): ";
        cin.ignore();
        getline(cin, password);

        if (password == "admin123") {
            cout << "Login successful!" << endl;
            return true;
        } else {
            attempts--;
            if (attempts > 0) {
                cout << "Invalid password! Please try again." << endl;
            } else {
                cout << "Maximum login attempts exceeded. Returning to main menu." << endl;
            }
        }
    }

    return false;
}

// Main Program Flow with Error Checking
void RestaurantSystem::run() {
    int choice;
    bool running = true;

    while (running) {
        displayMainMenu();

        // Get main menu choice with error checking
        while (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number (0-2): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1: // Admin
                if (authenticateAdmin()) {
                    int adminChoice;
                    bool inAdminMenu = true;

                    while (inAdminMenu) {
                        displayAdminMenu();

                        // Get admin menu choice with error checking
                        while (!(cin >> adminChoice)) {
                            cout << "Invalid input! Please enter a number (0-4): ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }

                                switch (adminChoice) {
                                    case 1:
                                        viewKitchenQueue();
                                        break;
                                    case 2:
                                        processNextOrder();
                                        break;
                                    case 3:
                                        cancelOrder();
                                        break;
                                    case 4:
                                        {
                                            int menuMgmtChoice;
                                            bool inMenuMgmt = true;

                                            while (inMenuMgmt) {
                                                displayMenuManagement();

                                                // Get menu management choice with error checking
                                                while (!(cin >> menuMgmtChoice)) {
                                                    cout << "Invalid input! Please enter a number (0-5): ";
                                                    cin.clear();
                                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                                }

                                                switch (menuMgmtChoice) {
                                                    case 1:
                                                        addMenuItem();
                                                        break;
                                                    case 2:
                                                        removeMenuItem();
                                                        break;
                                                    case 3:
                                                        editMenuItem();
                                                        break;
                                                    case 4:
                                                        searchMenuItem();
                                                        break;
                                                    case 0:
                                                        inMenuMgmt = false;
                                                        break;
                                                    default:
                                                        cout << "Invalid choice! Please enter a number between 0-4." << endl;
                                                }
                                            }
                                        }
                                        break;
                                    case 0:
                                        inAdminMenu = false;
                                        cout << "Returning to main menu..." << endl;
                                        break;
                                    default:
                                        cout << "Invalid choice! Please enter a number between 0-4." << endl;
                                }
                    }
                }
                break;

            case 2: // Customer (NO LOGIN REQUIRED)
                {
                    int customerChoice;
                    bool inCustomerMenu = true;
                    int tableNo;

                    cout << "\nWelcome Customer!" << endl;
                    
                    // Session Login
                    while (true) {
                        cout << "Please enter your Table Number to start (1-20): ";
                        if (cin >> tableNo && tableNo >= 1 && tableNo <= 20) {
                            break;
                        } else {
                            cout << "Invalid table number! Please enter 1-20." << endl;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                    }
                    
                    cout << "\n[Logged in as Table " << tableNo << "]" << endl;

                    while (inCustomerMenu) {
                        displayCustomerMenu();

                        // Get customer menu choice with error checking
                        while (!(cin >> customerChoice)) {
                            cout << "Invalid input! Please enter a number (0-3): ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }

                        switch (customerChoice) {
                            case 1:
                                {
                                    // 1. Display Menu First
                                    displayMenu();

                                    // 2. Ask for Sorting
                                    int sortChoice;
                                    while (true) {
                                        cout << "\nSort Menu? (1: Price, 2: Category, 0: No): ";
                                        if (cin >> sortChoice) {
                                            break;
                                        }
                                        cout << "Invalid input! Enter number." << endl;
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    }

                                    if (sortChoice == 1) {
                                        menu.displaySortedByPrice();
                                        // Do not call displayMenu() again
                                    } else if (sortChoice == 2) {
                                        menu.displaySortedByCategory();
                                        // Do not call displayMenu() again
                                    }
                                }
                                break;
                            case 2:
                                createOrder(tableNo);
                                break;
                            case 3:
                                viewMyOrders(tableNo);
                                break;
                            case 0:
                                inCustomerMenu = false;
                                cout << "Returning to main menu..." << endl;
                                break;
                            default:
                                cout << "Invalid choice! Please enter a number between 0-3." << endl;
                        }
                    }
                }
                break;

            case 0: // Exit
                cout << "\nThank you for using Restaurant Food Ordering System!" << endl;
                cout << "Saving data and exiting..." << endl;
                running = false;
                break;

            default:
                cout << "Invalid choice! Please enter a number between 0-2." << endl;
        }

        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
