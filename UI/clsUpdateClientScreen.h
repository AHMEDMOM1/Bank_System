#pragma once
#include <iostream>
#include <string>

#include "clsScreen.h"
#include "clsClient.h"
#include "clsInputValidate.h"
#include "clsClientManager.h"
#include "clsClientScreen.h"

using namespace std;


class clsUpdateClientScreen : protected clsScreen
{
	static clsClient _getExistingAccount() {
		clsClient Client{};
		do {
			string account{};
			cout << "Enter Existing Account: ";
			getline(cin, account);
			Client = clsClientManager::findClient(account);
		} while (Client.isEmpty());
		return Client;
	}
	static void _ReInput(clsClient& Client) {
		
		Client.firstName = clsInputValidate::ReadString("First Name: ");

		Client.lastName = clsInputValidate::ReadString("Last Name: ");
		
		Client.email = clsInputValidate::ReadString("Email: ");

		Client.phone = clsInputValidate::ReadString("Phone: ");
		
		Client.pinCode = static_cast<short>(clsInputValidate::ReadIntNumber("Pin Code: "));

		Client.balance = clsInputValidate::ReadDblNumber("Balance: ");

	}

public:
	static bool updateScreen() {
		clsClient Client{ _getExistingAccount() };
		clsClientScreen::print(Client);
		_ReInput(Client);
		return clsClientRepository::reSave(Client);
	}
};

