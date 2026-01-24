#ifndef MENULIST_H
#define MENULIST_H

#include <iostream>
#include <string>
#include <vector>
#include "FoodItem.h"

using namespace std;

class MenuList {
private:
    FoodItem* head;

public:
    MenuList();
    ~MenuList();


    void addFoodItem(FoodItem* f);
    void deleteFoodItem(int id);
    void editFoodItem(int id, string newName, string newCat, double newPrice);
    FoodItem* searchFoodByName(string name) const;
    FoodItem* getFoodByID(int id) const;
    void displayMenu() const;
    void displaySortedByPrice() const;
    void displaySortedByCategory() const;
    bool isEmpty() const;
    void saveToFile(const string& filename) const;
};

#endif
