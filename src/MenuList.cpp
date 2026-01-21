#include "MenuList.h"
#include <iomanip>

MenuList::MenuList() : head(nullptr) {}

MenuList::~MenuList() {
    FoodItem* current = head;
    while (current != nullptr) {
        FoodItem* temp = current;
        current = current->getNext();
        delete temp;
    }
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
    cout << "Food item added: " << f->getName() << endl;
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
            current->setFoodInfo(id, newName, newPrice, newCat);
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
        cout << "Menu is empty." << endl;
        return;
    }
    cout << "\n--- MENU ---" << endl;
    FoodItem* current = head;
    while (current != nullptr) {
        current->displayItem();
        current = current->getNext();
    }
    cout << "------------" << endl;
}

void MenuList::sortMenuByPrice() {
    if (head == nullptr || head->getNext() == nullptr) return;

    bool swapped;
    do {
        swapped = false;
        FoodItem* current = head;
        while (current->getNext() != nullptr) {
            if (current->getPrice() > current->getNext()->getPrice()) {
                // Swap values instead of nodes
                int id = current->getFoodId();
                string name = current->getName();
                string cat = current->getCategory();
                double price = current->getPrice();

                current->setFoodInfo(
                    current->getNext()->getFoodId(),
                    current->getNext()->getName(),
                    current->getNext()->getPrice(),
                    current->getNext()->getCategory()
                );

                current->getNext()->setFoodInfo(id, name, price, cat);

                swapped = true;
            }
            current = current->getNext();
        }
    } while (swapped);

    cout << "Menu sorted by price successfully." << endl;
}
