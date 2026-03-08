#pragma once

#include <iomanip>

#include "clsClient.h"
#include "clsScreen.h"

class clsClientScreen : public clsScreen {
public:
  static void print(const clsClient &Client) {
    cout << "Client Card:" << endl;
    cout << setw(50) << setfill('-') << '-' << endl << setfill(' ');
    cout << "First Name: " << Client.getFirstName() << endl;
    cout << "Last Name: " << Client.getLastName() << endl;
    cout << "Full Name: " << Client.getFullName() << endl;
    cout << "Email: " << Client.getEmail() << endl;
    cout << "Phone Number: " << Client.getPhone() << endl;
    cout << "Account Number: " << Client.getAccountNumber() << endl;
    cout << "Pin Code: " << Client.getPinCode() << endl;
    cout << "Balance: " << Client.getBalance() << endl;
    cout << setw(50) << setfill('-') << '-' << endl << setfill(' ');
  }
};
