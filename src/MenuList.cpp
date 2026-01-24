#include "MenuList.h"
#include <iomanip>
#include <fstream>

MenuList::MenuList() : head(nullptr) {}

MenuList::~MenuList() {
    FoodItem* current = head;
    while (current != nullptr) {
        FoodItem* temp = current;
        current = current->getNext();
        delete temp;
    }
}

bool MenuList::isEmpty() const {
    return head == nullptr;
}

void MenuList::addFoodItem(FoodItem* f) {
    if (!f) return;
    if (head == nullptr) {
        head = f;
    } else {
        FoodItem* current = head;
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }
        current->setNext(f);
    }
}

void MenuList::deleteFoodItem(int id) {
    if (head == nullptr) return;

    if (head->getFoodId() == id) {
        FoodItem* temp = head;
        head = head->getNext();
        delete temp;
        cout << "Food item deleted successfully." << endl;
        return;
    }

    FoodItem* current = head;
    while (current->getNext() != nullptr && current->getNext()->getFoodId() != id) {
        current = current->getNext();
    }

    if (current->getNext() != nullptr) {
        FoodItem* temp = current->getNext();
        current->setNext(temp->getNext());
        delete temp;
        cout << "Food item deleted successfully." << endl;
    } else {
        cout << "Food item not found." << endl;
    }
}

void MenuList::editFoodItem(int id, string newName, string newCat, double newPrice) {
    FoodItem* current = head;
    while (current != nullptr) {
        if (current->getFoodId() == id) {
            // Only update if new value is not empty
            if (!newName.empty()) {
                // Update the name
                current->setFoodInfo(id, newName, current->getCategory(), current->getPrice());
            }
            if (!newCat.empty()) {
                // Update the category
                current->setFoodInfo(id, current->getName(), newCat, current->getPrice());
            }
            if (newPrice >= 0) { // -1 means keep current price
                // Update the price
                current->setFoodInfo(id, current->getName(), current->getCategory(), newPrice);
            }
            cout << "Food item updated successfully." << endl;
            return;
        }
        current = current->getNext();
    }
    cout << "Food item not found." << endl;
}

FoodItem* MenuList::searchFoodByName(string name) const {
    FoodItem* current = head;
    while (current != nullptr) {
        if (current->getName() == name) {
            current->displayItem();
            return current;
        }
        current = current->getNext();
    }
    cout << "Food item not found." << endl;
    return nullptr;
}

void MenuList::displayMenu() const {
    if (head == nullptr) {
        cout << "\n========================================" << endl;
        cout << "           MENU IS EMPTY               " << endl;
        cout << "========================================" << endl;
        return;
    }

    cout << "\n==================================================================" << endl;
    cout << "                           MENU LIST                               " << endl;
    cout << "==================================================================" << endl;
    cout << left << setw(8) << "ID"
         << setw(25) << "ITEM NAME"
         << setw(15) << "CATEGORY"
         << setw(10) << "PRICE" << endl;
    cout << "==================================================================" << endl;

    FoodItem* current = head;
    while (current != nullptr) {
        cout << left << setw(8) << current->getFoodId()
             << setw(25) << current->getName()
             << setw(15) << current->getCategory()
             << "RM " << fixed << setprecision(2) << current->getPrice() << endl;

        if (current->getNext() != nullptr) {
            cout << "------------------------------------------------------------------" << endl;
        }

        current = current->getNext();
    }

    cout << "==================================================================" << endl;
}

#include <algorithm>
#include <vector>

void MenuList::displaySortedByPrice() const {
    if (head == nullptr) {
        cout << "Menu is empty." << endl;
        return;
    }

    // Capture pointers in a vector
    vector<FoodItem*> items;
    FoodItem* current = head;
    while (current != nullptr) {
        items.push_back(current);
        current = current->getNext();
    }

    // Sort the vector using a lambda
    sort(items.begin(), items.end(), [](FoodItem* a, FoodItem* b) {
        return a->getPrice() < b->getPrice();
    });

    // Display
    cout << "\n==================================================================" << endl;
    cout << "                    MENU LIST (Sorted by Price)                   " << endl;
    cout << "==================================================================" << endl;
    cout << left << setw(8) << "ID"
         << setw(25) << "ITEM NAME"
         << setw(15) << "CATEGORY"
         << setw(10) << "PRICE" << endl;
    cout << "==================================================================" << endl;

    for (size_t i = 0; i < items.size(); ++i) {
        FoodItem* item = items[i];
        cout << left << setw(8) << item->getFoodId()
             << setw(25) << item->getName()
             << setw(15) << item->getCategory()
             << "RM " << fixed << setprecision(2) << item->getPrice() << endl;
             
        if (i < items.size() - 1) {
             cout << "------------------------------------------------------------------" << endl;
        }
    }
    cout << "==================================================================" << endl;
}

void MenuList::displaySortedByCategory() const {
    if (head == nullptr) {
        cout << "Menu is empty." << endl;
        return;
    }

    // Capture pointers in a vector
    vector<FoodItem*> items;
    FoodItem* current = head;
    while (current != nullptr) {
        items.push_back(current);
        current = current->getNext();
    }

    // Sort the vector
    sort(items.begin(), items.end(), [](FoodItem* a, FoodItem* b) {
        return a->getCategory() < b->getCategory();
    });

    // Display
    cout << "\n==================================================================" << endl;
    cout << "                   MENU LIST (Sorted by Category)                 " << endl;
    cout << "==================================================================" << endl;
    cout << left << setw(8) << "ID"
         << setw(25) << "ITEM NAME"
         << setw(15) << "CATEGORY"
         << setw(10) << "PRICE" << endl;
    cout << "==================================================================" << endl;

    for (size_t i = 0; i < items.size(); ++i) {
        FoodItem* item = items[i];
        cout << left << setw(8) << item->getFoodId()
             << setw(25) << item->getName()
             << setw(15) << item->getCategory()
             << "RM " << fixed << setprecision(2) << item->getPrice() << endl;

        if (i < items.size() - 1) {
             cout << "------------------------------------------------------------------" << endl;
        }
    }
    cout << "==================================================================" << endl;
}

void MenuList::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file for saving." << endl;
        return;
    }

    FoodItem* current = head;
    while (current != nullptr) {
        // Format: ID,Name,Category,Price
        file << current->getFoodId() << ","
             << current->getName() << ","
             << current->getCategory() << ","
             << current->getPrice();
             
        if (current->getNext() != nullptr) {
            file << endl;
        }
        current = current->getNext();
    }
    file.close();
    cout << "Menu data saved successfully." << endl;
}

FoodItem* MenuList::getFoodByID(int id) const {
    FoodItem* current = head;
    while (current != nullptr) {
        if (current->getFoodId() == id) {
            return current;
        }
        current = current->getNext();
    }
    return nullptr;
}