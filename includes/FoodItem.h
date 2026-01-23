#ifndef FOODITEM_H
#define FOODITEM_H

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class FoodItem {
private:
    int foodID;
    string foodName;
    string foodCategory;
    double foodPrice;
    FoodItem* next;//

public:
    // Default constructor
    FoodItem() {
        foodID = 0;
        foodName = "";
        foodCategory = "";
        foodPrice = 0.0;
        next = nullptr;//
    }

    // Parameterized constructor
    FoodItem(int id, string name, string category, double price) {
        foodID = id;
        foodName = name;
        foodCategory = category;
        foodPrice = price;
        next = nullptr;//
    }

    // Store dish details
    void setFoodInfo(int id, string name, string category, double price) {
        foodID = id;
        foodName = name;
        foodCategory = category;
        foodPrice = price;

    }

    // Get
    int getFoodId() const { return foodID; }
    string getName() const { return foodName; }
    string getCategory() const { return foodCategory; }
    double getPrice() const { return foodPrice; }
    FoodItem* getNext() const { return next; }//
    void setNext(FoodItem* n) { next = n; }//

    // Display food info
    void displayItem() const {
        cout << "Food ID: " << foodID << endl;
        cout << "Food Name: " << foodName << endl;
        cout << "Category: " << foodCategory << endl;
        cout << "Price: RM " << fixed << setprecision(2) << foodPrice << endl;
    }
};

#endif
