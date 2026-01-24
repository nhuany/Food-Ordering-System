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



void MenuList::displaySortedByPrice() const {
    if (head == nullptr) {
        cout << "Menu is empty." << endl;
        return;
    }

    // 1. Count nodes
    int count = 0;
    FoodItem* current = head;
    while (current != nullptr) {
        count++;
        current = current->getNext();
    }

    // 2. Create dynamic array of pointers
    FoodItem** items = new FoodItem*[count];
    current = head;
    for (int i = 0; i < count; i++) {
        items[i] = current;
        current = current->getNext();
    }

    // 3. Bubble Sort by Price
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (items[j]->getPrice() > items[j + 1]->getPrice()) {
                FoodItem* temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }

    // 4. Display
    cout << "\n==================================================================" << endl;
    cout << "                    MENU LIST (Sorted by Price)                   " << endl;
    cout << "==================================================================" << endl;
    cout << left << setw(8) << "ID"
         << setw(25) << "ITEM NAME"
         << setw(15) << "CATEGORY"
         << setw(10) << "PRICE" << endl;
    cout << "==================================================================" << endl;
    for (int i = 0; i < count; i++) {
        items[i]->displayItemLine();
    }
    cout << "==================================================================" << endl;

    // 5. Cleanup
    delete[] items;
}

void MenuList::displaySortedByCategory() const {
    if (head == nullptr) {
        cout << "Menu is empty." << endl;
        return;
    }

    // 1. Count nodes
    int count = 0;
    FoodItem* current = head;
    while (current != nullptr) {
        count++;
        current = current->getNext();
    }

    // 2. Create dynamic array of pointers
    FoodItem** items = new FoodItem*[count];
    current = head;
    for (int i = 0; i < count; i++) {
        items[i] = current;
        current = current->getNext();
    }

    // 3. Bubble Sort by Category
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (items[j]->getCategory() > items[j + 1]->getCategory()) {
                FoodItem* temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }

    // 4. Display
    cout << "\n==================================================================" << endl;
    cout << "                  MENU LIST (Sorted by Category)                  " << endl;
    cout << "==================================================================" << endl;
    cout << left << setw(8) << "ID"
         << setw(25) << "ITEM NAME"
         << setw(15) << "CATEGORY"
         << setw(10) << "PRICE" << endl;
    cout << "==================================================================" << endl;
    for (int i = 0; i < count; i++) {
        items[i]->displayItemLine();
    }
    cout << "==================================================================" << endl;

    // 5. Cleanup
    delete[] items;
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