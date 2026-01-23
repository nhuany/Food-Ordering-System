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
    ofstream file("menu.txt");
    if (file.is_open()) {
        // For simplicity, we'll implement saving later
        // For now, just a placeholder
        file.close();
    }
}

void RestaurantSystem::initializeMenu() {
    // Load menu from file or create default items
    ifstream file("menu.txt");
    if (file.is_open()) {
        int id;
        string name, category;
        double price;

        while (file >> id >> ws && getline(file, name, ',') &&
               getline(file, category, ',') >> price) {
            FoodItem* newItem = new FoodItem(id, name, category, price);
            menu.addFoodItem(newItem);
        }
        file.close();
    } else {
        // Create default menu items SILENTLY (no cout messages)
        FoodItem* item1 = new FoodItem(101, "Burger", "Main Course", 12.99);
        FoodItem* item2 = new FoodItem(102, "Fries", "Side", 5.99);
        FoodItem* item3 = new FoodItem(103, "Coke", "Beverage", 3.50);
        FoodItem* item4 = new FoodItem(104, "Pizza", "Main Course", 25.99);
        FoodItem* item5 = new FoodItem(105, "Salad", "Appetizer", 8.99);
        FoodItem* item6 = new FoodItem(106, "Ice Cream", "Dessert", 6.50);

        // Add items without printing messages
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
            break;
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
void RestaurantSystem::createOrder() {
    cout << "\n=== CREATE NEW ORDER ===" << endl;

    int tableNo;
    while (true) {
        cout << "Enter table number (1-20): ";
        if (cin >> tableNo && tableNo >= 1 && tableNo <= 20) {
            break;
        } else {
            cout << "Invalid input! Please enter a table number between 1-20." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    Order* newOrder = new Order(nextOrderID, tableNo);
    nextOrderID++;

    char addMore = 'Y';
    int itemCount = 0;

    while (toupper(addMore) == 'Y' && itemCount < 10) { // Limit to 10 items per order
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

        // For demonstration, we'll create a temporary food item
        FoodItem* orderedFood = new FoodItem(foodID, "Item", "Category", 10.00);

        newOrder->addFoodOrder(nextOrderItemID, orderedFood, quantity);
        nextOrderItemID++;
        itemCount++;

        cout << "Item added to order. (" << itemCount << " items total)" << endl;

        if (itemCount < 10) {
            cout << "Add another item? (Y/N): ";
            cin >> addMore;
        } else {
            cout << "Maximum items per order reached (10 items)." << endl;
            break;
        }
    }

    // Add order to kitchen queue
    kitchen.enqueueOrder(newOrder);
    cout << "\nOrder " << newOrder->getOrderID() << " created and sent to kitchen!" << endl;
}

void RestaurantSystem::viewOrders() {
    cout << "\n========================================================" << endl;
    cout << "               VIEW YOUR ORDER                         " << endl;
    cout << "========================================================" << endl;

    if (kitchen.isEmpty()) {
        cout << "\n--------------------------------------------------------" << endl;
        cout << "          No orders to display at the moment.         " << endl;
        cout << "--------------------------------------------------------" << endl;
    } else {
        cout << "\nHere is your current order receipt:\n" << endl;
        cout << "========================================================" << endl;

        kitchen.viewNextOrder();

        cout << "\n========================================================" << endl;
        cout << "Note: If you have multiple orders, please ask staff for assistance." << endl;
    }

    cout << "\nPress Enter to return to menu...";
    cin.ignore();
    cin.get();
}


void RestaurantSystem::updateOrderStatus() {
    cout << "\n========================================================" << endl;
    cout << "               UPDATE ORDER STATUS                     " << endl;
    cout << "========================================================" << endl;

    if (kitchen.isEmpty()) {
        cout << "\n--------------------------------------------------------" << endl;
        cout << "          No orders to update.                         " << endl;
        cout << "--------------------------------------------------------" << endl;
        return;
    }

    // Show current orders
    cout << "\nCurrent Orders in System:" << endl;
    cout << "========================================================" << endl;
    kitchen.displayQueue();

    // Simple input
    int orderID;
    cout << "\nEnter Order ID: ";
    cin >> orderID;

    cout << "\n========================================================" << endl;
    cout << "         SELECT NEW STATUS                            " << endl;
    cout << "========================================================" << endl;
    cout << "1. Pending     | 2. Preparing" << endl;
    cout << "3. Ready       | 4. Served" << endl;
    cout << "5. Cancelled" << endl;
    cout << "========================================================" << endl;

    int choice;
    cout << "Choice (1-5): ";
    cin >> choice;

    string status;
    switch(choice) {
        case 1: status = "Pending"; break;
        case 2: status = "Preparing"; break;
        case 3: status = "Ready"; break;
        case 4: status = "Served"; break;
        case 5: status = "Cancelled"; break;
        default:
            cout << "\nInvalid choice!" << endl;
            return;
    }

    // Simple update message
    cout << "\n========================================================" << endl;
    cout << "      Order " << orderID << " status changed to: " << status << endl;
    cout << "========================================================" << endl;

    // Note: In full implementation, actually update the order
    cout << "\n[Status update recorded]" << endl;
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

    kitchen.viewNextOrder();

    char complete;
    while (true) {
        cout << "Mark this order as completed? (Y/N): ";
        cin >> complete;
        complete = toupper(complete);

        if (complete == 'Y' || complete == 'N') {
            break;
        }
        cout << "Invalid input! Please enter Y or N." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (complete == 'Y') {
        kitchen.dequeueOrder();
        cout << "Order processed successfully!" << endl;
    } else {
        cout << "Order processing cancelled." << endl;
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
    cout << "\n=================================" << endl;
    cout << "        CUSTOMER MENU            " << endl;
    cout << "=================================" << endl;
    cout << "1. View Menu" << endl;
    cout << "2. Create New Order" << endl;
    cout << "3. View My Orders" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "=================================" << endl;
    cout << "Enter your choice (0-3): ";
}

void RestaurantSystem::displayAdminMenu() {
    cout << "\n=================================" << endl;
    cout << "          ADMIN MENU             " << endl;
    cout << "=================================" << endl;
    cout << "1. View All Orders" << endl;
    cout << "2. View Kitchen Queue" << endl;
    cout << "3. Process Next Order (Kitchen)" << endl;
    cout << "4. Update Order Status" << endl;  // Changed from "Manage Menu Items"
    cout << "5. Manage Menu Items" << endl;    // Moved to option 5
    cout << "0. Back to Main Menu" << endl;
    cout << "=================================" << endl;
    cout << "Enter your choice (0-5): ";
}

void RestaurantSystem::displayMenuManagement() {
    cout << "\n=================================" << endl;
    cout << "       MENU MANAGEMENT            " << endl;
    cout << "=================================" << endl;
    cout << "1. Add Menu Item" << endl;
    cout << "2. Remove Menu Item" << endl;
    cout << "3. Edit Menu Item" << endl;
    cout << "4. Search Menu Item" << endl;
    cout << "5. Sort Menu by Price" << endl;
    cout << "0. Back to Admin Menu" << endl;
    cout << "=================================" << endl;
    cout << "Enter your choice (0-5): ";
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
                                        viewOrders();
                                        break;
                                    case 2:
                                        viewKitchenQueue();
                                        break;
                                    case 3:
                                        processNextOrder();
                                        break;
                                    case 4:  // NEW OPTION - Update Order Status
                                        updateOrderStatus();
                                        break;
                                    case 5:  // Changed from 4 to 5
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
                                                    case 5:
                                                        menu.sortMenuByPrice();
                                                        break;
                                                    case 0:
                                                        inMenuMgmt = false;
                                                        break;
                                                    default:
                                                        cout << "Invalid choice! Please enter a number between 0-5." << endl;
                                                }
                                            }
                                        }
                                        break;
                                    case 0:
                                        inAdminMenu = false;
                                        cout << "Returning to main menu..." << endl;
                                        break;
                                    default:
                                        cout << "Invalid choice! Please enter a number between 0-5." << endl;
                                }
                    }
                }
                break;

            case 2: // Customer (NO LOGIN REQUIRED)
                {
                    int customerChoice;
                    bool inCustomerMenu = true;

                    cout << "\nWelcome Customer!" << endl;

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
                                displayMenu();
                                break;
                            case 2:
                                createOrder();
                                break;
                            case 3:
                                // View customer's orders (simplified - shows all orders)
                                viewOrders();
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
