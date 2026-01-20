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

public:
    // Default constructor
    FoodItem() {
        foodID = 0;
        foodName = "";
        foodCategory = "";
        foodPrice = 0.0;
    }

    // Parameterized constructor
    FoodItem(int id, string name, double price, string category) {
        foodID = id;
        foodName = name;
        foodPrice = price;
        foodCategory = category;
    }

    // Store dish details
    void setFoodInfo(int id, string name, double price, string category) {
        foodID = id;
        foodName = name;
        foodPrice = price;
        foodCategory = category;
    }

    // Get
    int getFoodId() const { return foodID; }
    string getName() const { return foodName; }
    double getPrice() const { return foodPrice; }
    string getCategory() const { return foodCategory; }

    // Display food info
    void displayItem() const {
        cout << "Food ID: " << foodID << endl;
        cout << "Food Name: " << foodName << endl;
        cout << "Category: " << foodCategory << endl;
        cout << "Price: RM " << fixed << setprecision(2) << foodPrice << endl;
    }
};
