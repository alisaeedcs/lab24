// comsc-210 | Ali Saeed \ Lab 23
// ide used; vs code

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

//function prototypes
int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

int main() {
    srand(time(0));

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    //list
    list<Goat> trip;

    //loop that runs the main_menu() function until quit is chosen
    int choice = 0;
    cout << "\t*** GOAT MANAGER 3001 ***\n";
    while (choice != 4) {
        choice = main_menu();
        cout << endl;
        cout << endl;
        if (choice == 1) {
            //add goat
            add_goat(trip, names, colors);
        }
        else if (choice == 2) {
            //delete goat
            delete_goat(trip);
        }
        else if (choice == 3) {
            //list goats
            display_trip(trip);
        }
        else if (choice == 4) {
            //quit so just put nothing ehre
        }
        else {
            cout << "Invalid choice \n";
        }
        cout << endl;
    }
    //first run attempt resulted in lots of errors with the auto type specifier have to update my coderuner
    //actually can ust try other thing to run it
    //running now thru extension modifications but it doesnt delete (maybe my conditions i put into one of the functions)
    //working correctly!
    //still getting the warnings with the auto type C++11 extension but it should be because of my c++ version

    return 0;
}

//main menu function output and takes in the choice
int main_menu() {
    cout << "\t[1] Add a goat\n";
    cout << "\t[2] Delete a goat\n";
    cout << "\t[3] List goats\n";
    cout << "\t[4] Quit\n";
    cout << "\tChoice --> ";
    int choice;
    cin >> choice;
    return choice;
}

//add goat to list
void add_goat(list<Goat> &trip, string names[], string colors[]) {
    string name, color;
    int age;
    name = names[rand() % SZ_NAMES];
    color = colors[rand() % SZ_COLORS];
    age = rand() % MAX_AGE;

    Goat addedGoat(name, age, color);
    trip.push_back(addedGoat);
    cout << "\tGoat added, Name: " << name << ", Age: " << age << ", Color: " << color << "\n";
}

//display the trip so that we can see all elements in list for deleting (use select with this and then use delete with the select)
void display_trip(list<Goat> trip) {
    if (trip.empty()) {
        cout << "List empty.";
        return;
    }
    int i = 1;
    //looked into video notes for tjhis function
    for (auto it = trip.begin(); it!= trip.end(); ++it) {
        cout << "\t\t[" << i << "] " << it->get_name() << " (" << it->get_age() << ", " << it->get_color() << ")\n";
        i++;
    }
}

//select number of goat for now to be used to delete
int select_goat(list<Goat> trip) {
    //make sure it has at east one element
    if (trip.empty()) {
        cout << "List empty.";
        return -1;
    }
    //access display function to let you choose
    display_trip(trip);

    int choice;
    //get user input for choice
    cout << "\tEnter the number of the goat you want to perform this action on: ";
    cin >> choice;

    return choice - 1; 
}

//make sure its valid then go iterate and delete it
void delete_goat(list<Goat> &trip) {
    auto it = trip.begin();
    int choice = select_goat(trip);

    //make sure selection not out of bounds
    if (choice < 0 || choice > trip.size()) {
        cout << "Invalid sleection";
        return;
    }

    //go to the specific element in list
    for (int i = 0; i < choice; i++) {
        it++;
    }
    //erase it at that position
    trip.erase(it);
}

