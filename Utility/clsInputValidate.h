#pragma once
#include <algorithm>
#include <iostream>
#include <string>

#include "clsDate.h"

class clsInputValidate {

public:
    static bool IsNumberBetween(short Number, short From, short To) {
        if (Number >= From && Number <= To)
            return true;
        else
            return false;
    }

    static bool IsNumberBetween(int Number, int From, int To) {
        if (Number >= From && Number <= To)
            return true;
        else
            return false;
    }

    static bool IsNumberBetween(float Number, float From, float To) {
        if (Number >= From && Number <= To)
            return true;
        else
            return false;
    }

    static bool IsNumberBetween(double Number, double From, double To) {
        if (Number >= From && Number <= To)
            return true;
        else
            return false;
    }

    static bool IsDateBetween(clsDate Date, clsDate From, clsDate To) {
        // Date>=From && Date<=To
        if ((clsDate::IsDate1AfterDate2(Date, From) ||
            clsDate::IsDate1EqualDate2(Date, From)) &&
            (clsDate::IsDate1BeforeDate2(Date, To) ||
                clsDate::IsDate1EqualDate2(Date, To))) {
            return true;
        }

        // Date>=To && Date<=From
        if ((clsDate::IsDate1AfterDate2(Date, To) ||
            clsDate::IsDate1EqualDate2(Date, To)) &&
            (clsDate::IsDate1BeforeDate2(Date, From) ||
                clsDate::IsDate1EqualDate2(Date, From))) {
            return true;
        }

        return false;
    }

    static int
        ReadIntNumber(string massage = "", string ErrorMessage = "Invalid Number, Enter again\n") {
        int Number;
        cout << massage;
        while (!(cin >> Number)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return Number;
    }

    static int ReadIntNumberBetween(
        int From, int To,
        string ErrorMessage = "Number is not within range, Enter again:\n") {
        int Number = ReadIntNumber();

        while (!IsNumberBetween(Number, From, To)) {
            cout << ErrorMessage;
            Number = ReadIntNumber();
        }
        return Number;
    }

    static double
        ReadDblNumber(string massage = "", string ErrorMessage = "Invalid Number, Enter again\n") {
        double Number;
        cout << massage;
        while (!(cin >> Number)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return Number;
    }

    static string ReadString(string massage = "") {
        string str{};
        cout << massage;
        getline(cin >> ws, str);
        return str;
    }

    static string
        readValidAnswer(string errorMasage = "Invalid input (y/yes n/no)!") {
        string input{};

        while ((cin >> input) &&
            !(input == "y" || input == "yes" || input == "n" || input == "no")) {
            cout << errorMasage << endl;

            transform(input.begin(), input.end(), input.begin(),
                [](char c) { return static_cast<char>(std::tolower(c)); });
        }

        return input;
    }

    static double ReadDblNumberBetween(
        double From, double To,
        string ErrorMessage = "Number is not within range, Enter again:\n") {
        double Number = ReadDblNumber();

        while (!IsNumberBetween(Number, From, To)) {
            cout << ErrorMessage;
            Number = ReadDblNumber();
        }
        return Number;
    }

    static bool IsValideDate(clsDate Date) { return clsDate::IsValidDate(Date); }
};
