#pragma once

#include "clsPerson.h"

class clsClient : public clsPerson {

  string _AccountNumber{};
  short _PinCode{};
  float _Balance{};

public:
  clsClient(const string &FirstName, const string &LastName,
            const string &Email, const string &Phone,
            const string &AccountNumber, const short &PinCode,
            float AccountBalance)
      : clsPerson(FirstName, LastName, Email, Phone) {
    _AccountNumber = AccountNumber;
    _PinCode = PinCode;
    _Balance = AccountBalance;
  }
  clsClient() = default;

  string getAccountNumber() const { return _AccountNumber; }

  void setPinCode(const short &pinCode) { _PinCode = pinCode; }
  short getPinCode() const { return _PinCode; }

  void setBalance(const float &balance) { _Balance = balance; }
  float getBalance() const { return _Balance; }

  bool isEmpty() const { return _AccountNumber.empty(); }
};