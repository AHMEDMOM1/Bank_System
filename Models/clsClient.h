#pragma once

#include "clsPerson.h"

class clsClient : public clsPerson {

  string _AccountNumber;
  short _PinCode;
  float _Balance;

  enum enMode { Empty, Update } _Mode{};

public:
  clsClient(enMode Mode, const string &FirstName, const string &LastName,
            const string &Email, const string &Phone,
            const string &AccountNumber, const short &PinCode,
            float AccountBalance)
      : clsPerson(FirstName, LastName, Email, Phone) {
    _Mode = Mode;
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

  bool isEmpty() const { return _Mode == enMode::Empty; }

  static enMode getEmptyMode() { return enMode::Empty; }
  static enMode getUpdateMode() { return enMode::Update; }

  __declspec(property(get = getAccountNumber)) string accountNumber;
  __declspec(property(get = getPinCode, put = setPinCode)) short pinCode;
  __declspec(property(get = getBalance, put = setBalance)) float balance;
};