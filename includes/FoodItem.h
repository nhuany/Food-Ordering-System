#ifndef FOODITEM_H
#define FOODITEM_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class FoodItem {
private:
    int FoodID;
    string FoodName;
    string FoodCat;
    double FoodPrice;
    
    // Pointer for MenuList (since it's described as a Node)
    FoodItem* next; 

public:
    FoodItem() : FoodID(0), FoodName(""), FoodCat(""), FoodPrice(0.0), next(nullptr) {}

    FoodItem(int id, string name, string cat, double price) 
        : FoodID(id), FoodName(name), FoodCat(cat), FoodPrice(price), next(nullptr) {}

    void setFoodInfo(int id, string name, double price, string category) {
        FoodID = id;
        FoodName = name;
        FoodPrice = price;
        FoodCat = category;
    }

    int getFoodId() const { return FoodID; }
    string getName() const { return FoodName; }
    double getPrice() const { return FoodPrice; }
    string getCategory() const { return FoodCat; }
    
    FoodItem* getNext() const { return next; }
    void setNext(FoodItem* n) { next = n; }

    void displayItem() const {
        cout << "ID: " << FoodID 
             << " | Name: " << FoodName 
             << " | Category: " << FoodCat 
             << " | Price: $" << fixed << setprecision(2) << FoodPrice << endl;
    }
};

#endif
