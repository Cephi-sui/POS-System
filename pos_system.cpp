// POSSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <iomanip>
#include <curses.h>
#include "json.hpp"
#include "database.h"
using namespace std;
using namespace nlohmann;

void start();
void mainMenu(bool with_clear);
void returnToMenu();
void searchCustomers();
void manageCustomers();
void viewAppointments();
void manageAppointments();

Database d;

/*void clear() {
    cout << string(100, '\n');
}*/

inline int convertInputToInt(string user_input) {
    return stoi(user_input, nullptr);
}

void generateTest() {
    d.addCustomer("Justice", "Jess", 2002, 07, 25);
    d.addCustomer("Frazier", "Tom", 1970, 02, 11);
    d.addCustomer("Smith", "Bill", 1998, 04, 12);
    d.addCustomer("Bond", "James", 1859, 12, 20);
    d.addCustomer("Frazier", "Tom", 1980, 02, 11);
    d.addCustomer("Jonathan", "James", 1996, 003, 07);
}

int main() {

	initscr();
	mvprintw(2, 2, "test");
	int x, y;
	getmaxyx(stdscr, y, x);
	char stry[3];
	char strx[3];
	itoa(y, stry, 10);
	itoa(x, strx, 10);
	move(0, 0);
	mvprintw(10,10,stry);
	mvprintw(1, 0, strx);
	move(10, 10);
	getch();
	endwin();
    //start();

}

void start() {
    //d.readFile(); //Uncomment this when time for actual use instead of testing
    generateTest();

    mainMenu(true);
}

void mainMenu(bool with_clear) {
    if (with_clear) {
        clear();
    }
    cout << "Welcome to my POS System!\n\n";

    cout << "What would you like to do?" << endl;
    cout << "--------------------------" << endl;
    cout << "1. Search customers" << endl << "2. Manage customers" << endl << "3. View appointments" << endl << "4. Manage appointments" << endl << "5. Quit" << endl << endl;
    string user_input;
    cin >> user_input;

    switch (convertInputToInt(user_input)) {
    case 1:
        searchCustomers();
        break;
    case 2:
        manageCustomers();
        break;
    case 3:
        viewAppointments();
        break;
    case 4:
        manageAppointments();
        break;
    case 5:
        exit(EXIT_SUCCESS);
        break;
    default:
        clear();
        cout << "You didn't input a number between 1 and 5!" << endl << endl;
        mainMenu(false);
    }
}

void returnToMenu() {
    cout << "1. Return to Main Menu" << endl << endl;
    string user_input;
    cin >> user_input;

    if (convertInputToInt(user_input) == 1) {
        mainMenu(true);
    }
    else {
        cout << endl << "That's not the number 1!" << endl;
        returnToMenu();
    }
}

void searchCustomers() {
    clear();
    cout << "Type the first name, last name, number, or email to search (ONLY ONE OF THESE. DON'T TYPE A FULL NAME)" << endl << endl;
    string user_input;
    cin >> user_input;
    cout << endl << endl;

    json ID, firstName, lastName, year, month, day, phone, email;
    //json customerList = d.getDatabase()["customers"];
    for (auto i : d.getCustomerList()) { //Goes through each customer in the list
        for (auto k = i.begin(); k != i.end(); ++k) { //Goes through all information for each customer
            if (k.value() == user_input) { //Confirms that the customers has information that matches the search term
                for (auto l = i.begin(); l != i.end(); l++) { //Goes through the customer information again to get store all the information to display
                    if (l.key() == "ID") {
                        ID = l.value();
                    }
                    else if (l.key() == "firstName") {
                        firstName = l.value();
                    }
                    else if (l.key() == "lastName") {
                        lastName = l.value();
                    }
                    else if (l.key() == "phone") {
                        phone = l.value();
                    }
                    else if (l.key() == "email") {
                        email = l.value();
                    }
                }
                for (auto l = i["DOB"].begin(); l != i["DOB"].end(); ++l) { //Goes through date of birth separately. Not quite sure how this manages to work but hey it works.
                    if (l.key() == "dd") {
                        day = l.value();
                    }
                    else if (l.key() == "mm") {
                        month = l.value();
                    }
                    else if (l.key() == "yyyy") {
                        year = l.value();
                    }
                }
                cout << ID << " | " << lastName << ", " << firstName << " | " << year << "/" << (month < 10 ? "0" : "") << month << "/" << (day < 10 ? "0" : "") << day << " | " << phone << " | " << email << endl;
                break;
            }
        }
    }

    cout << endl;
}

void manageCustomers() {
}

void viewAppointments() {

}
void manageAppointments() {

}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
