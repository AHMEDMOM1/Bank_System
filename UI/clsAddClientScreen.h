#pragma once

#include "clsClient.h"
#include "clsClientManager.h"
#include "clsClientScreen.h"
#include "clsInputValidate.h"
#include "clsScreen.h"


class clsAddClientScreen : protected clsScreen {
  clsClientManager &_manager;

  std::string _getNotExistAccount() {
    std::string account{};
    do {
      cout << "Enter New (Not Exist) Account Number: ";
      cin >> account;
    } while (!_manager.findClient(account).isEmpty());

    return account;
  }

  static void _fillClient(clsClient &Client) {
    Client.setFirstName(clsInputValidate::ReadString("First Name: "));
    Client.setLastName(clsInputValidate::ReadString("Last Name: "));
    Client.setEmail(clsInputValidate::ReadString("Email: "));
    Client.setPhone(clsInputValidate::ReadString("Phone: "));
    Client.setPinCode(
        static_cast<short>(clsInputValidate::ReadIntNumber("Pin Code: ")));
    Client.setBalance(clsInputValidate::ReadDblNumber("Balance: "));
  }

public:
  clsAddClientScreen(clsClientManager &manager) : _manager(manager) {}

  void AddScreen() {
    std::string account{_getNotExistAccount()};
    clsClient Client{_manager.initNewAccount(account)};
    _fillClient(Client);
    _manager.addClient(Client);
    clsClientScreen::print(Client);
  }
};
