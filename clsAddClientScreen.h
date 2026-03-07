#pragma once

#include <iostream>

#include "clsScreen.h"
#include "clsClient.h"
#include "clsClientManager.h"
#include "clsInputValidate.h"
#include "clsClientRepository.h"
using namespace std;

class clsAddClientScreen : clsScreen
{
	static string _getNotExistAccount() {
		string account{};
		do {
			cout << "Enter New (Not Exist) Account Number: ";
			cin >> account;
		} while (!clsClientManager::findClient(account).isEmpty());

		return account;
	}
	static void _fillClient(clsClient& Client) {
		Client.firstName = clsInputValidate::ReadString("First Name: ");
		Client.lastName = clsInputValidate::ReadString("Last Name: ");
		Client.email = clsInputValidate::ReadString("Email: ");
		Client.phone = clsInputValidate::ReadString("Phone: ");
		Client.pinCode = static_cast<short>(clsInputValidate::ReadIntNumber("Pin Code: "));
		Client.balance = clsInputValidate::ReadDblNumber("Balance: ");
	}

public:
	static void AddScreen() {
		string account{ _getNotExistAccount() };
		clsClient Client{};
		_fillClient(Client);

		clsClientRepository::append(Client);
	}
	
};

