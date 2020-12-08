#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "json.hpp"
using namespace std;
using namespace nlohmann;

class Database
{

public:
    json getDatabase() {
        return j;
    }

    json getCustomerList() {
        return j["customers"];
    }

    /*
    Displays current JSON object in console.
    Probably should not be done with large JSON objects.
    */
    void displayJSON() const {
        cout << j.dump(4) << endl;
    }

    /*
    Read "database.json" into current JSON object.
    */
    void readFile() {
        ifstream i("database.json");
        i >> j;
    }

    /*
    Write current JSON object into "database.json".
    */
    void writeFile() {
        ofstream o("database.json");
        o << setw(4) << j << endl;
    }

    //Need to add email and phone number eventually
    /*
    Add a customer into the database.

    They are automatically assigned an ID number based on the number of customers in the database.

    @param lastName The customer's last name.
    @param firstName The customer's first name.
    @param yyyy The customer's year of birth to 4 digits.
    @param mm The customer's month of birth to 2 digits.
    @param dd The customer's day of birth to 2 digits.
    */
    void addCustomer(string lastName, string firstName, int yyyy, int mm, int dd) {
        json newCustomer;
        json DOB;
        
        newCustomer["lastName"] = lastName;
        newCustomer["firstName"] = firstName;
        newCustomer["ID"] = j["customers"].size();

        DOB["yyyy"] = yyyy;
        DOB["mm"] = mm;
        DOB["dd"] = dd;

        newCustomer["DOB"] = DOB;
        j["customers"].push_back(newCustomer);
    }

    void deleteCustomer(int ID) {
        j["customers"][ID] = NULL;
    }

    void editCustomerInfo(int ID, string field, string newInfo) {
        j["customers"][ID][field] = newInfo;
    }

    void editCustomerDOB(int ID, int yyyy, int mm, int dd) {
        j["customers"][ID]["DOB"]["yyyy"] = yyyy;
        j["customers"][ID]["DOB"]["mm"] = mm;
        j["customers"][ID]["DOB"]["dd"] = dd;
    }

private:
    json j;

};

// This implementation needs to create a vector of potential correct answers and allow for clarification.
/*int searchName (string name) {
    //Search code. There's probably a better way to find the ID but this is how it is for now.
    int resultID = -1;
    for (auto customerList : j["customers"]) {
        int index = 0;
        for (auto customerName : customerList) {
            if (customerName == name) {
                cout << "true";
                resultID = index;
            }
            index++;
        }
    }

    return resultID;
}

void writeJSON(json object) {

    ofstream o("database.json");
    o << setw(4) << j << endl;

}*/

