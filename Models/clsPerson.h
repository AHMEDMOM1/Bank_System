#pragma once
#include <iostream>

using namespace std;

class clsPerson {
  string _firstName{};
  string _lastName{};
  string _email{};
  string _phone{};

public:
  clsPerson(const string &firstName, const string &lastName,
            const string &email, const string &phone) {
    _firstName = firstName;
    _lastName = lastName;
    _email = email;
    _phone = phone;
  }
  clsPerson() = default;

  void setFirstName(const string &firstName) { _firstName = firstName; }
  string getFirstName() const { return _firstName; }

  void setLastName(const string &lastName) { _lastName = lastName; }
  string getLastName() const { return _lastName; }

  string getFullName() const { return _firstName + " " + _lastName; }

  void setEmail(const string &email) { _email = email; }
  string getEmail() const { return _email; }

  void setPhone(const string &phone) { _phone = phone; }
  string getPhone() const { return _phone; }

  __declspec(property(get = getFirstName, put = setFirstName)) string firstName;
  __declspec(property(get = getLastName, put = setLastName)) string lastName;
  __declspec(property(get = getFullName)) string fullName;
  __declspec(property(get = getEmail, put = setEmail)) string email;
  __declspec(property(get = getPhone, put = setPhone)) string phone;
};
