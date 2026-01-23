#include "RestaurantSystem.h"
#include <iostream>

using namespace std;

int main() {
    // Display initial title
    cout << "==========================================" << endl;
    cout << "   RESTAURANT FOOD ORDERING SYSTEM        " << endl;
    cout << "==========================================" << endl;
    cout << "         Developed by Group 8" << endl;
    cout << "      TDS6213 Data Structures & Algorithms" << endl;
    cout << "==========================================" << endl;

    // Create and run the system
    RestaurantSystem system;
    system.run();

    return 0;
}
