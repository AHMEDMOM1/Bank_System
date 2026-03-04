#pragma once

#include <iomanip>

#include "clsClient.h"
#include "clsScreen.h"

class clsClientScreen : public clsScreen {
public:
  static void print(const clsClient &Client) {
    cout << "Client Card:" << endl;
    cout << setw(50) << setfill('-') << '-' << endl << setfill(' ');
    cout << "First Name: " << Client.firstName << endl;
    cout << "Last Name: " << Client.lastName << endl;
    cout << "Full Name: " << Client.fullName << endl;
    cout << "Email: " << Client.email << endl;
    cout << "Phone Number: " << Client.phone << endl;
    cout << "Account Number: " << Client.accountNumber << endl;
    cout << "Pin Code: " << Client.pinCode << endl;
    cout << "Balance: " << Client.balance << endl;
    cout << setw(50) << setfill('-') << '-' << endl << setfill(' ');
  }
};
