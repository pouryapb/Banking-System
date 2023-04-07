// Banking System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
using namespace std;

// defining static integers for better readability
#define LOGIN_STATE 0
#define MENU 1
#define NEW_USER 2
#define DELETE_USER 3
#define MODIFY_USER 4
#define SEARCH 5
#define MODIFY_BALANCE 6
#define TRANSACTION 7
#define BANK_BALANCE 8
#define CHANGE_PASSWORD 9

// the state of program
int state = LOGIN_STATE;

// database
vector<vector<string>> db;

void loadDb() {
    fstream file;
    file.open("./database.txt");

    string lastName, codeMelly, accountNumber, money, password;

    // reading file line by line
    while (file >> lastName >> codeMelly >> accountNumber >> money >> password) {

        vector<string> v;
        v.push_back(lastName);
        v.push_back(codeMelly);
        v.push_back(accountNumber);
        v.push_back(money);
        v.push_back(password);

        // putting arr in db
        db.push_back(v);
    }

    file.close();
}

void addToDb(string lastName, int codeMelly, int accountNumber, int money, string password) {
    if (!ifstream("./database.txt")) {
        ofstream("./database.txt");
    }

    // open the file with append flag
    fstream file;
    file.open("./database.txt", ios_base::app);

    file << "\n" << lastName << " " << codeMelly << " " << accountNumber << " " << money << " " << password;

    file.close();
    loadDb();
}

void editDb() {
    ofstream file;
    file.open("./database.txt");

    for (int i = 0; i < db.size(); i++) {
        vector<string> v = db.at(i);

        string line = "";
        for (int j = 0; j < v.size(); j++) {
            if (j != 0) {
                line = line.append(" ");
            }
            line = line.append(v.at(j));
        }
        
        if (i != 0) {
            file << "\n";
        }
        file << line;
    }

    file.close();
}

void login() {
    // getting login info from user
    string username, password;
    cout << "Enter Username:\n";
    cin >> username;
    cout << "Enter Password:\n";
    cin >> password;

    // checking user to grant access
    if (username == "admin" && password == "adm123") {
        state = MENU;
        system("cls");
    }
    else {
        // clear console and show message
        system("cls");
        cout << "Username or Password is incorrect!\n\n";
    }
}

void menu() {
    // show the menu
    cout << "Choose by entering a number:\n\n";
    cout << "1. New User\n";
    cout << "2. Delete User\n";
    cout << "3. Modify User\n";
    cout << "4. Search User\n";
    cout << "5. Modify User Balance\n";
    cout << "6. Transaction\n";
    cout << "7. View Bank Balance\n";
    cout << "8. Change User Password\n";
    cout << "\ninput: ";

    // getting input
    int choice;
    cin >> choice;

    // changing state
    switch (choice) {
    case 1:
        state = NEW_USER;
        system("cls");
        break;
    case 2:
        state = DELETE_USER;
        system("cls");
        break;
    case 3:
        state = MODIFY_USER;
        system("cls");
        break;
    case 4:
        state = SEARCH;
        system("cls");
        break;
    case 5:
        state = MODIFY_BALANCE;
        system("cls");
        break;
    case 6:
        state = TRANSACTION;
        system("cls");
        break;
    case 7:
        state = BANK_BALANCE;
        system("cls");
        break;
    case 8:
        state = CHANGE_PASSWORD;
        system("cls");
        break;
    default:
        system("cls");
        cout << "Invalid input\n\n";
        break;
    }
}

void newUser() {
    string lastName, password;
    int codeMelly, accountNumber, money;
    
    // gathering info
    cout << "Lastname: ";
    cin >> lastName;
    cout << "\nCode Melly: ";
    cin >> codeMelly;
    cout << "\nAccount Number: ";
    cin >> accountNumber;
    cout << "\nMoney: ";
    cin >> money;
    cout << "\nPassword: ";
    cin >> password;

    // TODO check for doublicates or other invalid info

    // make new account
    addToDb(lastName, codeMelly, accountNumber, money, password);
    system("cls");
    state = MENU;
}

void deleteUser() {
    
    string accountNumber;

    cout << "Insert Account Number to delete: ";
    cin >> accountNumber;

    for (int i = 0; i < db.size(); i++) {
        vector<string> user = db.at(i);

        if (user.at(2) == accountNumber) {
            db.erase(db.begin() + i);
            editDb();
            system("cls");
            cout << "User Deleted.\n\n";
            state = MENU;
            return;
        }
    }

    system("cls");
    cout << "User not Found.\n\n";
    state = MENU;
}

void modifyUser() {
    
    string name, number;
    cout << "Enter Account Number to modify: ";
    cin >> number;
    
    for (int i = 0; i < db.size(); i++) {
        vector<string> user = db.at(i);

        if (user.at(2) == number) {
            cout << "\nuser info:\nlastname: " << user.at(0) << "\ncode melly: " << user.at(1) << "\naccount number: " << user.at(2) << "\nballance: " << user.at(3) << "\npassword: " << user.at(4) << "\n\n";
            cout << "Enter new name: ";
            cin >> name;
            db.at(i).at(0) = name;
            editDb();
            cout << "Name changed\n\n";
            state = MENU;
            return;
        }
    }

    system("cls");
    cout << "User not Found.\n\n";
    state = MENU;
}

void search() {
    
    string input;
    cout << "Enter Complete name or code melly or account name: ";
    cin >> input;

    for (int i = 0; i < db.size(); i++) {
        vector<string> user = db.at(i);

        if (user.at(0) == input || user.at(1) == input || user.at(2) == input) {
            cout << "\nuser info:\nlastname: " << user.at(0) << "\ncode melly: " << user.at(1) << "\naccount number: " << user.at(2) << "\nballance: " << user.at(3) << "\npassword: " << user.at(4) << "\n\n";
            state = MENU;
            return;
        }
    }

    system("cls");
    cout << "User not Found.\n\n";
    state = MENU;
}

void modifyBalance() {
    string money, number;
    cout << "Enter Account Number to modify: ";
    cin >> number;

    for (int i = 0; i < db.size(); i++) {
        vector<string> user = db.at(i);

        if (user.at(2) == number) {
            cout << "\nuser info:\nlastname: " << user.at(0) << "\ncode melly: " << user.at(1) << "\naccount number: " << user.at(2) << "\nballance: " << user.at(3) << "\npassword: " << user.at(4) << "\n\n";
            cout << "Enter amount: "; // negative or positive
            cin >> money;
            int amount = stoi(money); // convert string to integer
            int newAmount = stoi(user.at(3)) + amount; // summing with previus amount
            db.at(i).at(3) = to_string(newAmount); // convert to string and save to db
            editDb();
            cout << "balance changed to " << newAmount << ".\n\n";
            state = MENU;
            return;
        }
    }

    system("cls");
    cout << "User not Found.\n\n";
    state = MENU;
}

void transaction() {
    string money, number;
    cout << "Enter Account Number To Pick Money from: ";
    cin >> number;

    int amount, sender;

    // search in acounts for sender
    for (int i = 0; i < db.size(); i++) {
        vector<string> user = db.at(i);

        if (user.at(2) == number) {
            cout << "\nuser info:\nlastname: " << user.at(0) << "\ncode melly: " << user.at(1) << "\naccount number: " << user.at(2) << "\nballance: " << user.at(3) << "\npassword: " << user.at(4) << "\n\n";
            cout << "Enter amount: ";
            cin >> money;
            amount = stoi(money); // convert string to integer
            sender = i; // save sender index
            break;
        }
        else if (i == db.size() - 1) {
            system("cls");
            cout << "User not Found.\n\n";
            state = MENU;
            return;
        }
    }

    cout << "Enter Account Number To Send Money to: ";
    cin >> number;

    // search in accounts for reciver
    for (int i = 0; i < db.size(); i++) {
        vector<string> user = db.at(i);

        if (user.at(2) == number) {
            cout << "\nuser info:\nlastname: " << user.at(0) << "\ncode melly: " << user.at(1) << "\naccount number: " << user.at(2) << "\nballance: " << user.at(3) << "\npassword: " << user.at(4) << "\n\n";
            db.at(sender).at(3) = to_string((stoi(db.at(sender).at(3)) - amount)); // converting sender money to integer and subtracting amount and changing it back to string
            db.at(i).at(3) = to_string((stoi(db.at(i).at(3)) + amount)); // converting reciver money to integer and adding amount and changing it back to string
            editDb();
            cout << "Transaction Complete!\n\n";
            state = MENU;
            return;
        }
        else if (i == db.size() - 1) {
            system("cls");
            cout << "User not Found.\n\n";
            state = MENU;
        }
    }
}

void bankBalance() {

    int sum = 0;
    for (int i = 0; i < db.size(); i++) {
        vector<string> user = db.at(i);

        sum += stoi(user.at(3));
    }

    system("cls");
    cout << "Bank Balance: " << sum << "\n\n";
    state = MENU;
}

void changePassword() {
    string password, number;
    cout << "Enter Account Number to modify password: ";
    cin >> number;

    for (int i = 0; i < db.size(); i++) {
        vector<string> user = db.at(i);

        if (user.at(2) == number) {
            cout << "\nuser info:\nlastname: " << user.at(0) << "\ncode melly: " << user.at(1) << "\naccount number: " << user.at(2) << "\nballance: " << user.at(3) << "\npassword: " << user.at(4) << "\n\n";
            cout << "Enter new password: ";
            cin >> password;
            db.at(i).at(4) = password;
            editDb();
            cout << "Name changed\n\n";
            state = MENU;
            return;
        }
    }

    system("cls");
    cout << "User not Found.\n\n";
    state = MENU;
}

int main() {
    loadDb();

    while (true) {
        switch (state) {
        case LOGIN_STATE:
            login();
            break;
        case MENU:
            menu();
            break;
        case NEW_USER:
            newUser();
            break;
        case DELETE_USER:
            deleteUser();
            break;
        case MODIFY_USER:
            modifyUser();
            break;
        case SEARCH:
            search();
            break;
        case MODIFY_BALANCE:
            modifyBalance();
            break;
        case TRANSACTION:
            transaction();
            break;
        case BANK_BALANCE:
            bankBalance();
            break;
        case CHANGE_PASSWORD:
            changePassword();
            break;
        }
    }
}
