#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <conio.h> // _getch

using namespace std;

// Constants for file names and delimiters
const string DELIMITER = "#//#";
const string CLIENT_FILE_NAME = "Bank.txt";
const string USER_FILE_NAME = "users.txt";

// Enum for main menu options
enum MainMenuOption { Add = 1, View, Find, Delete, Update, Transaction, Manage, LogOut };
using ManageUserMenuOption = MainMenuOption ; // Fixed naming convention

// Enum for transaction menu options
enum TransactionMenuOption { Deposit = 1, Withdraw, TotalBalance };

// Enum for client menu options
enum ClientMenuOption { QuickWithdraw = 1, NormalWithdraw, ClientDeposit, ShowBalance, ClientLogOut };

// Enum for member types
enum Members { Client = 1, User };

// Structure to hold user information
struct UserInfo {
	string user_name{};
	string user_password{};  // Fixed spelling
	short total_access{};
};

// Structure to hold client data
struct ClientData {
	string account_number;
	unsigned short pin_code;
	string name;
	string phone_number;
	float balance;
};

// Gets a valid positive float from user input
float getValidPositiveNumber(const char* message) {
	float number{};
	cout << message;
	while (!(cin >> number) || number < 1) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Enter a valid positive number: ";
	}
	return number;
}

// Gets user approval with Y/N response
bool getUserApproval(const char* message) {
	char answer;
	cout << message;
	while (cin >> answer && !(toupper(answer) == 'Y' || toupper(answer) == 'N')) {
		cin.ignore(INT_MAX, '\n');
		cout << "Enter Y/N: ";
	}
	return toupper(answer) == 'Y';
}

// Converts client data structure to string format for file storage
string serializeClientData(const ClientData& client) {
	string client_data_str{};
	client_data_str = client.account_number + DELIMITER;
	client_data_str += to_string(client.pin_code) + DELIMITER;
	client_data_str += client.name + DELIMITER;
	client_data_str += client.phone_number + DELIMITER;
	client_data_str += to_string(client.balance);
	return client_data_str;
}

// Displays an error message
void displayErrorMessage(const char* message) {
	cout << "\n\n" << message << "\n\n";
}

// Splits a string record into individual fields using delimiter
vector<string> parseRecordData(string record_info) {
	vector<string> parsed_data;
	string word;
	int pos;
	while ((pos = record_info.find(DELIMITER)) != string::npos) {
		word = record_info.substr(0, pos);
		if (!word.empty()) parsed_data.push_back(word);
		record_info.erase(0, pos + DELIMITER.length());
	}
	if (!record_info.empty()) parsed_data.push_back(record_info);
	return parsed_data;
}

// Prints client data in a formatted way
void printClientData(vector<string>& client) {
	cout << "\n\n";
	cout << setw(30) << setfill('-') << '-' << endl;
	cout << "Account Number: " << client.at(0) << endl;
	cout << "Pin Code: " << client.at(1) << endl;
	cout << "Name: " << client.at(2) << endl;
	cout << "Phone Number: " << client.at(3) << endl;
	cout << "Balance: " << client.at(4) << endl;
	cout << setw(30) << setfill('-') << '-' << "\n\n";
}

// Gets a string input from the user
string getStringInput(const char* message) {
	string input;
	cout << message;
	getline(cin >> ws, input);
	return input;
}

// Loads data from a file into a vector of strings
vector<string> loadDataFromFile(const string& file_name) {
	ifstream input_file(file_name, ios::in);
	vector<string> data{};
	if (input_file) {
		string line;
		while (getline(input_file, line)) {
			data.push_back(line);
		}
	}
	return data;
}

// Searches for a client by account number and returns the index
short findValidAccount(vector<string>& file_data,const string& account_number) {
	for (int i{}; i < file_data.size(); i++) {
		vector <string> parsed_data = parseRecordData(file_data.at(i));
		if (parsed_data.front() == account_number) return i;
	}
	return -1;
}

// Converts a single file line to ClientData structure
ClientData convertLineToClientData(const string& file_data) {
	ClientData client{};
	vector<string> client_fields = parseRecordData(file_data);
	client = { client_fields.at(0) ,(unsigned short)stoi(client_fields.at(1)),
	client_fields.at(2), client_fields.at(3), stof(client_fields.at(4)) };
	return client;
}

// Counts the number of lines in a file
int countFileLines(const string& file_name) {
	ifstream input_file(file_name, ios::in);
	int line_count = 0;
	if (input_file) {
		string line;
		while (getline(input_file, line)) line_count++;
	}
	return line_count;
}

// Creates a separator line with a character
string createSeparatorLine(char character, int count) {
	return string(count, character);
}

// Gets a valid account number from user
string getValidAccountNumber(vector<string>& file_data) {
	string account_number;
	short required_account{};

	while (true) {
		account_number = getStringInput("Record Account: ");
		required_account = findValidAccount(file_data, account_number);
		if (required_account != string::npos) {
			break;
		}
		displayErrorMessage("Account Not Found!!");
	}

	return file_data.at(required_account);
}

// Prints a header with a message and spacing
void printHeader(const char* message, short number_letter = 1) {
	cout << setw(35) << setfill('-') << '-' << endl;
	cout << createSeparatorLine(' ', number_letter) << message << endl;
	cout << setw(35) << setfill('-') << '-' << "\n\n";
}

// Displays Client data by account number
void displayClientData() {
	printHeader("Find Client Screen", 8);
	vector<string> clients_data = loadDataFromFile(CLIENT_FILE_NAME);

	string client_str{ getValidAccountNumber(clients_data) };
	vector<string>parsed_data_client{ parseRecordData(client_str) };

	printClientData(parsed_data_client);
}

// Saves record data to the file
void saveRecordDataToFile(const string& file_name,const string& record_data_str) {
	ofstream output_file(file_name, ios::app);
	if (output_file) output_file << record_data_str << endl;
}

// Clears all contents of a file
void deleteFileContents(const string& file_name) {
	ofstream output_file(file_name, ios::out | ios::trunc);
}

// Stores all client data from file into a vector of ClientData structures
vector<ClientData> storeClientDataInVector() {
	vector<string> clients_data = loadDataFromFile(CLIENT_FILE_NAME);

	vector<ClientData> clients{};
	for (int i{}; i < clients_data.size(); i++) {
		clients.push_back(convertLineToClientData(clients_data.at(i)));
	}

	return clients;
}

// Deletes a client account from the system
void deleteClientAccount() {
	printHeader("Delete Client Screen", 8);

	vector<string> clients_data = loadDataFromFile(CLIENT_FILE_NAME);
	string client_str{ getValidAccountNumber(clients_data) };
	vector<string>parsed_data{ parseRecordData(client_str) };
	printClientData(parsed_data);

	short required_account{ findValidAccount(clients_data, parsed_data.front()) };
	vector<ClientData>clients{ storeClientDataInVector() };

	if (getUserApproval("Are You Sure You Want Delete?: ")) {
		clients.erase(clients.begin() + required_account);
		deleteFileContents(CLIENT_FILE_NAME);

		for (auto& client : clients) {
			string client_str{ serializeClientData(client) };
			saveRecordDataToFile(CLIENT_FILE_NAME, client_str);
		}
	}
}

// Edits client data with user input
void editClientData(ClientData& client) {
	client.pin_code = getValidPositiveNumber("Enter Pin Code: ");

	cin.ignore(INT_MAX, '\n');
	client.name = getStringInput("Enter Name: ");

	client.phone_number = getStringInput("Enter Phone: ");

	client.balance = getValidPositiveNumber("Enter Account Balance: ");
}

// Updates client data in the system
void updateClientData() {
	printHeader("Update Client Info Screen", 6);

	vector<string> clients_data = loadDataFromFile(CLIENT_FILE_NAME);
	string client_str{ getValidAccountNumber(clients_data) };
	vector<string>parsed_data{ parseRecordData(client_str) };
	printClientData(parsed_data);

	short required_account{ findValidAccount(clients_data, parsed_data.front()) };

	vector<ClientData> clients{ storeClientDataInVector() };

	if (getUserApproval("Are You Sure You Want Update?: ")) {
		editClientData(clients.at(required_account));
		deleteFileContents(CLIENT_FILE_NAME);

		for (auto& client : clients) {
			string client_str{ serializeClientData(client) };
			saveRecordDataToFile(CLIENT_FILE_NAME, client_str);
		}
	}
}

// Displays all client records from the file
void displayAllClientRecords(ifstream& input_file) {
	string line;

	short i = 1;
	while (getline(input_file, line)) {
		vector<string> parsed_data = parseRecordData(line);
		cout << "| " << setw(20) << left << to_string(i) + '.' + parsed_data.at(0);
		cout << "| " << setw(15) << left << parsed_data.at(1);
		cout << "| " << setw(30) << left << parsed_data.at(2);
		cout << "| " << setw(15) << left << parsed_data.at(3);
		cout << "| " << setw(29) << left << parsed_data.at(4) << '|' << endl;
		i++;
	}
}

// Prints the header for the client list
void printClientListHeader() {
	int client_count = countFileLines(CLIENT_FILE_NAME);
	cout << createSeparatorLine('\t', 6) << "Client List (" << client_count << ") Client(s). \n\n";
	cout << setw(120) << setfill('-') << '-' << setfill(' ') << endl;
	cout << "| " << setw(20) << left << " Account Number";
	cout << "| " << setw(15) << left << " Pin Code";
	cout << "| " << setw(30) << left << " Client Name";
	cout << "| " << setw(15) << left << " Phone";
	cout << "| " << setw(29) << left << " Balance" << '|' << endl;
	cout << setw(120) << setfill('-') << '-' << setfill(' ') << endl;
}

// Displays the list of all clients
void displayClientList() {
	ifstream input_file(CLIENT_FILE_NAME, ios::in);
	if (input_file) {
		printClientListHeader();
		displayAllClientRecords(input_file);
		cout << setw(120) << setfill('-') << '-' << "\n";
	}
}

// Enters a new unique account number
string enterNewAccountNumber(vector<string>& file_data) {
	string account_number{};

	while (true) {
		account_number = getStringInput("Record Account: ");
		short pos = findValidAccount(file_data, account_number);
		if (pos == -1) {
			break;
		}
		displayErrorMessage("This account already exists!!");
	}
	return account_number;
}

// Adds multiple new clients to the system
void addNewClients() {
	short number_of_clients = getValidPositiveNumber("\nHow many clients do you want to add: ");
	static int client_counter = 1;

	vector<string> clients_data = loadDataFromFile(CLIENT_FILE_NAME);
	for (int i = 0; i < number_of_clients; i++) {
		ClientData new_client{};
		cout << "\nPerson." << (client_counter++) << ' ';

		new_client.account_number = enterNewAccountNumber(clients_data);
		new_client.pin_code = getValidPositiveNumber("Enter Pin Code: ");

		cin.ignore(INT_MAX, '\n');
		new_client.name = getStringInput("Enter Name: ");

		new_client.phone_number = getStringInput("Enter Phone: ");

		new_client.balance = getValidPositiveNumber("Enter Account Balance: ");
		string client{ serializeClientData(new_client) };
		saveRecordDataToFile(CLIENT_FILE_NAME, client);
	}
	while (getUserApproval("Do You Need To Append More Clients? ")) return addNewClients();
}

// Adds a new client via the interface
void addNewClient() {
	printHeader("Add New Clients Screen", 7);
	addNewClients();
}

// Displays the main menu options
void displayMainMenu() {
	cout << setw(35) << setfill('=') << '=' << setfill(' ') << "\n\n";
	cout << createSeparatorLine(' ', 11) << "User Main Menu" << "\n\n";
	cout << setw(35) << setfill('=') << '=' << setfill(' ') << "\n";
	cout << " [1]. Add New Client" << endl;
	cout << " [2]. View Client List" << endl;
	cout << " [3]. Find Data Of Client" << endl;
	cout << " [4]. Delete Client" << endl;
	cout << " [5]. Update Client's Data" << endl;
	cout << " [6]. Transaction" << endl;
	cout << " [7]. Manage Users" << endl;
	cout << " [8]. Login Out" << endl;
	cout << " [9]. Exit" << endl;
	cout << setw(35) << setfill('=') << '=' << setfill(' ') << "\n\n";
}

// Gets the user's main menu choice
short getMainMenuChoice() {
	short choice = getValidPositiveNumber("Choice: ");
	return choice;
}

// Handles deposit operation
void deposit() {
	printHeader("Deposit Screen", 11);

	vector<string> clients_data = loadDataFromFile(CLIENT_FILE_NAME);

	string client_str{ getValidAccountNumber(clients_data) };
	vector<string>parsed_data{ parseRecordData(client_str) };
	printClientData(parsed_data);

	short required_account{ findValidAccount(clients_data, parsed_data.front()) };
	vector<ClientData>clients = storeClientDataInVector();

	if (getUserApproval("Are You Sure You Want Deposit?: ")) {
		float amount{ getValidPositiveNumber("Enter Value You need: ") };
		clients.at(required_account).balance += amount;
		deleteFileContents(CLIENT_FILE_NAME);
		for (size_t i = 0; i < clients.size(); i++) {
			string client{ serializeClientData(clients.at(i)) };
			saveRecordDataToFile(CLIENT_FILE_NAME, client);
		}
	}
}

// Handles withdraw operation
void withdraw() {
	printHeader("Withdraw Screen", 10);

	vector<string> clients_data = loadDataFromFile(CLIENT_FILE_NAME);

	string client_str{ getValidAccountNumber(clients_data) };
	vector<string>parsed_data{ parseRecordData(client_str) };
	printClientData(parsed_data);

	short required_account{ findValidAccount(clients_data, parsed_data.front()) };
	vector<ClientData>clients = storeClientDataInVector();

	if (getUserApproval("Are You Sure You Want Withdraw?: ")) {
		float amount{};
		do {
			amount = getValidPositiveNumber("Withdraw an amount not exceeding the balance: ");
		} while (amount > clients.at(required_account).balance);
		clients.at(required_account).balance -= amount;
		deleteFileContents(CLIENT_FILE_NAME);
		for (size_t i = 0; i < clients.size(); i++) {
			string client{ serializeClientData(clients.at(i)) };
			saveRecordDataToFile(CLIENT_FILE_NAME, client);
		}
	}
}

// Displays the transaction menu
void displayTransactionMenu() {
	cout << setw(40) << setfill('=') << '=' << setfill(' ') << "\n";
	cout << createSeparatorLine(' ', 9) << "Transaction Menu Screen" << "\n";
	cout << setw(40) << setfill('=') << '=' << setfill(' ') << "\n";
	cout << " [1]. Deposit" << endl;
	cout << " [2]. Withdraw" << endl;
	cout << " [3]. Total Balance" << endl;
	cout << " [4]. Exit" << endl;
	cout << setw(40) << setfill('=') << '=' << setfill(' ') << "\n";
}

// Gets the user's transaction choice
short getTransactionChoice() {
	short choice = getValidPositiveNumber("Choose One: ");
	return choice;
}

// Prints header for total balance display
void printTotalBalanceHeader() {
	int client_count = countFileLines(CLIENT_FILE_NAME);
	cout << createSeparatorLine('\t', 6) << "Client List (" << client_count << ") Client(s). \n\n";
	cout << setw(120) << setfill('-') << '-' << setfill(' ') << endl;
	cout << "| " << setw(30) << left << " Account Number";
	cout << "| " << setw(44) << left << " Client Name";
	cout << "| " << setw(39) << left << " Balance" << '|' << endl;
	cout << setw(120) << setfill('-') << '-' << setfill(' ') << endl;
}

// Displays client balances body section
void displayClientBalancesBody() {
	string line;
	ifstream input_file(CLIENT_FILE_NAME, ios::in);
	for (short i = 1; getline(input_file, line); i++) {
		vector<string> parsed_data = parseRecordData(line);
		cout << "| " << setw(30) << left << to_string(i) + '.' + parsed_data.at(0);
		cout << "| " << setw(44) << left << parsed_data.at(2);
		cout << "| " << setw(39) << left << parsed_data.at(4) << '|' << endl;
	}
}

// Calculates total balance of all clients
float calculateTotalBalance() {
	float total = 0;
	vector<ClientData>clients = storeClientDataInVector();

	for (size_t i = 0; i < clients.size(); i++) total += clients.at(i).balance;
	return total;
}

// Prints the total balance
void printTotalBalance() {
	float total = calculateTotalBalance();
	cout << setw(64) << ' ' << "Total Balance = " << total << endl;
}

// Displays total balances of all clients
void displayTotalBalances() {
	printTotalBalanceHeader();
	displayClientBalancesBody();
}

// Converts file data to UserInfo vector
vector<UserInfo> convertToUserVector(vector<string>& file_data) {
	vector<UserInfo> users{};
	for (int i{}; i < file_data.size(); i++) {
		vector<string>parsed_data{ parseRecordData(file_data.at(i)) };
		users.push_back({ parsed_data.at(0), parsed_data.at(1),(short)stoi(parsed_data.at(2)) });
	}
	return users;
}

// Converts string data to UserInfo struct
UserInfo convertToUserStruct(string& user_data) {
	UserInfo user{};
	vector<string>parsed_data{ parseRecordData(user_data) };
	user = { parsed_data.at(0), parsed_data.at(1),(short)stoi(parsed_data.at(2)) };
	return user;
}

// Gets user account from file data
UserInfo getUserAccount() {
	vector<string> users_data{ loadDataFromFile(USER_FILE_NAME) };
	string user_string{ getValidAccountNumber(users_data) };
	return convertToUserStruct(user_string);
}

// Validates user password input
string getCorrectPassword(UserInfo user) {
	string password{};
	while (true) {
		password = getStringInput("Enter password: ");
		if (password == user.user_password) {
			break;
		}
		displayErrorMessage("Incorrect Password!!");
	}
	return password;
}

// Handles user login process
UserInfo userLogin() {
	printHeader("Login Page", 13);
	UserInfo user{};

	// read user name
	user = getUserAccount();

	// read user password
	user.user_password = getCorrectPassword(user);

	return user;
}

// Handles transaction operations
void handleTransactions() {
	do {
		system("cls");
		displayTransactionMenu();
		TransactionMenuOption choice = static_cast<TransactionMenuOption>(getTransactionChoice());
		switch (choice) {
		case TransactionMenuOption::Deposit:
			system("cls");
			deposit();
			break;
		case TransactionMenuOption::Withdraw:
			system("cls");
			withdraw();
			break;
		case TransactionMenuOption::TotalBalance:
			system("cls");
			displayTotalBalances();
			cout << setw(120) << setfill('-') << '-' << setfill(' ') << endl;
			printTotalBalance();
			break;
		default:
			return;
		}
		cout << "\n\n";
		cout << setw(50) << setfill('+') << '+' << endl;
		cout << "Press any character to return to menu: " << endl;
		cout << setw(50) << setfill('+') << '+' << endl;
	} while (_getch());
}

// Displays the manage users menu
void displayManageMenu() {
	cout << setw(35) << setfill('=') << '=' << setfill(' ') << "\n";
	cout << createSeparatorLine(' ', 6) << "---Manage Users Menu---" << "\n";
	cout << setw(35) << setfill('=') << '=' << setfill(' ') << "\n";
	cout << " [1]. Add New User" << endl;
	cout << " [2]. View User List" << endl;
	cout << " [3]. Find Data Of User" << endl;
	cout << " [4]. Delete User" << endl;
	cout << " [5]. Update User's Data" << endl;
	cout << " [6]. Main Menu" << endl;
	cout << setw(35) << setfill('=') << '=' << setfill(' ') << "\n\n";
}

// Gets access permissions for a new user
short getAccessForUser() {
	short access_total{};

	if (getUserApproval("Do You Want To Give Full Access: "))
		return-1;

	cout << "Do you want to give access to : \n";

	if (getUserApproval("Add Client: "))
		access_total |= 0x01;

	if (getUserApproval("Show Client: "))
		access_total |= 0x02;

	if (getUserApproval("Find Client: "))
		access_total |= 0x04;

	if (getUserApproval("Delete Client: "))
		access_total |= 0x08;

	if (getUserApproval("Update Client: "))
		access_total |= 0x10;

	if (getUserApproval("Transactions: "))
		access_total |= 0x20;

	if (getUserApproval("Manage Users: "))
		access_total |= 0x40;

	return access_total;
}

// Converts UserInfo struct to string format for file storage
string serializeUserToStr(UserInfo& user) {
	user.user_name += DELIMITER;
	user.user_password += DELIMITER;
	return user.user_name + user.user_password + to_string(user.total_access);
}

// Adds a new user to the system
void addUser() {
	UserInfo user{};
	printHeader("Add New User", 14);
	vector<string> users_data{ loadDataFromFile(USER_FILE_NAME) };
	do {
		user.user_name = enterNewAccountNumber(users_data);

		user.user_password = getStringInput("Enter Password: ");

		user.total_access = getAccessForUser();

		string userStr{ serializeUserToStr(user) };
		saveRecordDataToFile(USER_FILE_NAME, userStr);

		cout << "User Added Successfully,";
	} while (getUserApproval("Do you want add more: "));
}

// Prints header for user list display
void printUserListHeader() {
	int user_count = countFileLines(USER_FILE_NAME);
	cout << createSeparatorLine('\t', 6) << "User List (" << user_count << ") User(s). \n\n";
	cout << setw(120) << setfill('-') << '-' << setfill(' ') << endl;
	cout << "| " << setw(40) << left << " User Name";
	cout << "| " << setw(60) << left << " Password";
	cout << "| " << setw(13) << left << " Access" << '|' << endl;
	cout << setw(120) << setfill('-') << '-' << setfill(' ') << endl;
}

// Displays all users records from file
void displayAllUsersRecords(ifstream& input_file) {
	string line;
	for (short i = 1; getline(input_file, line); i++) {
		vector<string> parsed_data = parseRecordData(line);
		cout << "| " << setw(40) << left << to_string(i) + '.' + parsed_data.at(0);
		cout << "| " << setw(60) << left << parsed_data.at(1);
		cout << "| " << setw(13) << left << parsed_data.at(2) << '|' << endl;
	}
}

// Displays the list of all users
void displayUserList() {
	ifstream input_file{ USER_FILE_NAME, ios::in };
	if (input_file) {
		printUserListHeader();
		displayAllUsersRecords(input_file);
		cout << setw(120) << setfill('-') << '-' << "\n";
	}
}

// Prints user data in formatted way
void printUserData(vector<string>& user) {
	cout << "\n\n";
	cout << setw(40) << setfill('-') << '-' << endl;
	cout << "User Name: " << user.front() << endl;
	cout << "Password: " << user.at(1) << endl;
	cout << "Access: " << user.back() << endl;
	cout << setw(40) << setfill('-') << '-' << endl;
	cout << setfill(' '); // for give back the stream letter again
	cout << "\n\n";
}

// Displays User data by username
void displayUserData() {
	printHeader("Find User Screen", 9);

	vector<string> users_data{ loadDataFromFile(USER_FILE_NAME) };

	string user_str{ getValidAccountNumber(users_data) };

	vector<string>parsed_data_client{ parseRecordData(user_str) };

	printUserData(parsed_data_client);
}

// Checks if user is admin
bool checkIsAdmin(UserInfo user) {
	return user.user_name == "Admin";
}

// Deletes a user from the system
void deleteUser() {
	printHeader("Delete User Screen", 8);

	vector<string> users_data{ loadDataFromFile(USER_FILE_NAME) };

	string user_str{ getValidAccountNumber(users_data) };
	vector<string>parsed_data{ parseRecordData(user_str) };

	vector<UserInfo> users{ convertToUserVector(users_data) };
	short required_account{ findValidAccount(users_data, parsed_data.front()) };

	if (checkIsAdmin(users.at(required_account))) {
		displayErrorMessage("You cannot delete Admin!!");
		return;
	}
	printUserData(parsed_data);

	if (getUserApproval("Are You Sure You Want Delete?: ")) {
		users.erase(users.begin() + required_account);
		deleteFileContents(USER_FILE_NAME);

		for (size_t i = 0; i < users.size(); i++) {
			string user{ serializeUserToStr(users.at(i)) };
			saveRecordDataToFile(USER_FILE_NAME, user);
		}
	}
}

// Edits user data with new input
UserInfo editUserData(UserInfo& user) {
	user.user_password = getStringInput("Enter Password: ");
	user.total_access = getAccessForUser();
	return user;
}

// Updates user data in the system
void updateUserData() {
	printHeader("Update User Info Screen", 6);

	vector<string> users_data{ loadDataFromFile(USER_FILE_NAME) };

	string user_str{ getValidAccountNumber(users_data) };

	vector<string>parsed_data{ parseRecordData(user_str) };

	short required_account{ findValidAccount(users_data, parsed_data.front()) };

	vector<UserInfo> users{ convertToUserVector(users_data) };

	if (checkIsAdmin(users.at(required_account))) {
		displayErrorMessage("You cannot update Admin!!");
		return;
	}
	printUserData(parsed_data);

	if (getUserApproval("Are You Sure You Want Update?: ")) {
		users.at(required_account) = editUserData(users.at(required_account));
		deleteFileContents(USER_FILE_NAME);
		for (size_t i = 0; i < users.size(); i++) {
			string user{ serializeUserToStr(users.at(i)) };
			saveRecordDataToFile(USER_FILE_NAME, user);
		}
	}
}

// Manages user operations menu
void userManageList() {
	do {
		system("cls");
		displayManageMenu();
		ManageUserMenuOption choice = static_cast<ManageUserMenuOption>(getMainMenuChoice());
		switch (choice) {
		case ManageUserMenuOption::Add:
			system("cls");
			addUser();
			break;
		case ManageUserMenuOption::View:
			system("cls");
			displayUserList();
			break;
		case ManageUserMenuOption::Find:
			system("cls");
			displayUserData();
			break;
		case ManageUserMenuOption::Delete:
			system("cls");
			deleteUser();
			break;
		case ManageUserMenuOption::Update:
			system("cls");
			updateUserData();
			break;
		default:
			return;
		}
		cout << "\n\n";
		cout << setw(50) << setfill('+') << '+' << endl;
		cout << "Press any character to return to manage menu: " << endl;
		cout << setw(50) << setfill('+') << '+' << endl;
	} while (_getch());
}

// Checks if user has access to specific menu option
bool checkIfHasAccess(short total_access, MainMenuOption choice) {
	if (total_access == -1 || choice >= MainMenuOption::LogOut) return true;

	for (short i{ 0x40 }; i >= pow(2, choice - 1); i /= 2) {
		if (total_access == 0) return false;
		if (total_access >= i) total_access -= i;
	}
	return total_access == 0;
}

// Runs the main banking system for users
void userList(const UserInfo& user) {
	do {
		system("cls");
		displayMainMenu();
		MainMenuOption choice = static_cast<MainMenuOption>(getMainMenuChoice());
		if (!checkIfHasAccess(user.total_access, choice)) {
			cout << "You don't have access for this choice!!";
			continue;
		}
		switch (choice) {
		case MainMenuOption::Add:
			system("cls");
			addNewClient();
			break;
		case MainMenuOption::View:
			system("cls");
			displayClientList();
			break;
		case MainMenuOption::Find:
			system("cls");
			displayClientData();
			break;
		case MainMenuOption::Delete:
			system("cls");
			deleteClientAccount();
			break;
		case MainMenuOption::Update:
			system("cls");
			updateClientData();
			break;
		case MainMenuOption::Transaction:
			handleTransactions();
			break;
		case MainMenuOption::Manage:
			system("cls");
			userManageList();
			return userList(user);
		case MainMenuOption::LogOut:
			system("cls");
			return userList(userLogin());
		default:
			return;
		}
		cout << "\n\n";
		cout << setw(50) << setfill('+') << '+' << endl;
		cout << "Press any character to return to menu: " << endl;
		cout << setw(50) << setfill('+') << '+' << endl;
	} while (_getch());
}

// Prints the login page interface
void printLoginPage() {
	cout << createSeparatorLine(' ', 24) << setw(30) << setfill('=') << '='          << createSeparatorLine(' ', 10) << setw(30) << '='     << setfill(' ') << endl;
	cout << createSeparatorLine(' ', 24) << "||"     << createSeparatorLine(' ', 11) << "Client" << createSeparatorLine(' ', 9)  << "||"    << createSeparatorLine(' ', 10) << "||"
		 << createSeparatorLine(' ', 12) << "User"   << createSeparatorLine(' ', 10) << "||"     << endl;
	cout << createSeparatorLine(' ', 24) << setw(30) << setfill('=')                 << '='      << createSeparatorLine(' ', 10) << setw(30) << '=' << setfill(' ') << "\n\n";
	cout << createSeparatorLine(' ', 13) << setw(90) << setfill('-')                 << '-'      << setfill(' ') << endl;
	cout << createSeparatorLine(' ', 13);
}

// Prints the client ATM menu
void printClientATMMenu(string name_client) {
	cout << setw(35) << setfill('=') << '=' << setfill(' ') << "\n";
	cout << createSeparatorLine(' ', 8 - name_client.size()/2) << name_client << " Welcome to Our Bank" << "\n";
	cout << setw(35) << setfill('=') << '=' << setfill(' ') << "\n";
	cout << " [1]. Quick Withdraw" << endl;
	cout << " [2]. Normal Withdraw" << endl;
	cout << " [3]. Deposit" << endl;
	cout << " [4]. Check Balance" << endl;
	cout << " [5]. LogOut" << endl;
	cout << " [6]. Exit" << endl;
	cout << setw(35) << setfill('=') << '=' << setfill(' ') << "\n\n";
}

// Prints quick withdraw money options
void printQuickWithdrawMenu() {
	cout << setw(35) << setfill('=') << '=' << setfill(' ') << "\n";
	cout << createSeparatorLine(' ', 8) << "Quick Withdraw Screen" << "\n";
	cout << setw(35) << setfill('=') << '=' << setfill(' ') << "\n";
	cout << "[1].20$" << setw(20) << right << "[2].50$" << endl;
	cout << "[3].100$" << setw(20) << right << "[4].200$" << endl;
	cout << "[5].400$" << setw(20) << right << "[6].800$" << endl;
	cout << "[7].1600$" << setw(20) << right << "[8].4000$" << endl;
	cout << setw(35) << setfill('=') << '=' << setfill(' ');
}

// Handles client login process
ClientData clientLogin() {
	printHeader("Login Page", 13);
	ClientData clientData{};
	vector<string> clients_data = loadDataFromFile(CLIENT_FILE_NAME);

	while (true) {
		string account_number{ getStringInput("Account Number: ") };
		short pinCode = getValidPositiveNumber("Pin Code: ");

		short index{ findValidAccount(clients_data, account_number) };

		if (index == -1) {
			displayErrorMessage("Account Number / Pin Code Incorrect!!");
			continue;
		}
		clientData = convertLineToClientData(clients_data.at(index));
		if (clientData.pin_code != pinCode) {
			displayErrorMessage("Account Number / Pin Code Incorrect!!");
			continue;
		}
		break;
	}

	return clientData;
}

//Returns a valid number that is a multiple of five for withdrawal
void getNumThatMultOfFive(int& requestedMoney) {

	while (requestedMoney % 5 != 0) {
		requestedMoney = getValidPositiveNumber("Enter an amount multiple of 5's: ");
	}

	return;
}

// Returns valid balance for withdrawal
float getValidBalanceForWithdraw(int requestedMoney, float& balance) {
	do {
		requestedMoney = getValidPositiveNumber("Withdraw an amount not exceeding the balance: ");
		getNumThatMultOfFive(requestedMoney);
	} while (requestedMoney > balance);

	return requestedMoney;
}

// Handles quick withdraw functionality
void quickWithdraw(ClientData& client) {
	do {
		system("cls");
		printQuickWithdrawMenu();
		printf("\nYour Total Balance Now is: %.2f\n\n", client.balance);
		short choice = getValidPositiveNumber("Choice one: ");

		float amounts[] = { 0, 20, 50, 100, 200, 400, 800, 1600, 4000 };

		if (choice >= 1 && choice <= 8) {
			if (amounts[choice] <= client.balance) {
				client.balance -= amounts[choice];
				printf("\nSuccessful, Your Balance Now Is: %.2f\n", client.balance);
			}
			else {
				displayErrorMessage("Insufficient balance!");
			}
		}
		else {
			displayErrorMessage("Choice from[1] ->[8]!!");
		}
	} while (getUserApproval("Do You Need Withdraw More?"));
}

// Handles normal withdraw functionality
void normalWithdraw(ClientData& client) {
	float withdrawAmount{};
	printHeader("Withdraw Screen", 10);
	printf("Your Total Balance is: %.2f\n\n", client.balance);
	client.balance -= getValidBalanceForWithdraw(withdrawAmount, client.balance);
	printf("Successful, Your Balance Now Is: %.2f\n", client.balance);
}

// Handles client deposit functionality
void clientDeposit(ClientData& client) {

	printHeader("Deposit Menu Screen", 9);
	printf("Your Total Balance Now Is: %.2f\n\n", client.balance);

	int depositAmount = getValidPositiveNumber("Enter the amount: ");
	getNumThatMultOfFive(depositAmount);

	client.balance += depositAmount;

	printf("Successful, Your Balance Now Is: %.2f", client.balance);
}

// Shows client balance
void showBalance(ClientData& client) {
	printHeader("Total Balance Screen", 8);
	printf("Your Balance is: %.2f", client.balance);
}

// Saves updated client data back to file
void resaveClientData(ClientData& client) {
	vector<string> clients_data = loadDataFromFile(CLIENT_FILE_NAME);
	short index = findValidAccount(clients_data, client.account_number);

	clients_data.erase(clients_data.begin() + index);
	string client_str{ serializeClientData(client) };

	clients_data.insert(clients_data.begin() + index, client_str);

	deleteFileContents(CLIENT_FILE_NAME);
	for (int i{}; i < clients_data.size(); i++) {
		saveRecordDataToFile(CLIENT_FILE_NAME, clients_data.at(i));
	}
}

// Manages client operations menu
void clientList(ClientData client) {
	do {
		system("cls");
		printClientATMMenu(client.name);
		ClientMenuOption choice{ (ClientMenuOption)getValidPositiveNumber("Choice one: ") };
		switch (choice)
		{
		case QuickWithdraw:
			system("cls");
			quickWithdraw(client);
			break;
		case NormalWithdraw:
			system("cls");
			normalWithdraw(client);
			break;
		case ClientDeposit:
			system("cls");
			clientDeposit(client);
			break;
		case ShowBalance:
			system("cls");
			showBalance(client);
			break;
		case ClientLogOut:
			system("cls");
			resaveClientData(client);
			return clientList(clientLogin());
		default:
			return resaveClientData(client);
		}
		cout << "\n\n";
		cout << setw(50) << setfill('+') << '+' << endl;
		cout << "Press any character to return to menu: " << endl;
		cout << setw(50) << setfill('+') << '+' << endl;
	} while (_getch());
}

// Prints exit message
void printEndMessage() {
	system("cls");
	cout << setw(30) << setfill('+') << '+' << setfill(' ') << endl;
	cout << setw(20) << right << "Good Bye!!" << endl;
	cout << setw(30) << setfill('+') << '+' << setfill(' ') << endl;
}

// Handles main login page functionality
void loginPage() {
	short choice{};
	do {
		system("cls");
		printLoginPage();
		do {
			choice = getValidPositiveNumber("Choice [1]<-->[2]: ");
		} while (choice > 2 || choice < 1);

		switch (choice)
		{
		case Members::Client:
			system("cls");
			clientList(clientLogin());
			break;
		case Members::User:
			system("cls");
			userList(userLogin());
			break;
		}
	} while (getUserApproval("Do you need to go to login again?"));

	printEndMessage();
}

#include <format>

int main() {
	loginPage();

	
	return 0;
}
