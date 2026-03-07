#pragma once
#include <fstream>
#include <string>
#include <vector>


#include "clsClient.h"
#include "clsString.h"

class clsClientRepository {
  static string _fileName;
  static string _delim;

  static clsClient _ConvertLineToClient(const string &line) {
    vector<string> linePartitions{clsString::Split(line, _delim)};

    return clsClient{clsClient::getUpdateMode(), linePartitions.at(0),
                     linePartitions.at(1),       linePartitions.at(2),
                     linePartitions.at(3),       linePartitions.at(4),
                     static_cast<short>(stoi(linePartitions.at(5))),  stof(linePartitions.at(6))};
  }

  static string _ConvertClientToLine(const clsClient &Client) {
    return Client.firstName + _delim + Client.lastName + _delim + Client.email +
           _delim + Client.phone + _delim + Client.accountNumber + _delim +
           to_string(Client.pinCode) + _delim + to_string(Client.balance);
  }

public:
  static bool append(const clsClient &Client) {
    ofstream oFile{_fileName, ios::app};
    if (oFile) {
      string line{_ConvertClientToLine(Client)};
      oFile << line << "\n";
      oFile.close();
      return true;
    }

    return false;
  }

  static vector<clsClient> loadAll() {
    ifstream iFile{_fileName, ios::in};
    vector<clsClient> Clients{};
    if (iFile) {
      string line{};
      while (getline(iFile, line)) {
        clsClient Client{_ConvertLineToClient(line)};
        Clients.push_back(Client);
      }
      iFile.close();
    }
    return Clients;
  }

  static bool saveAll(const vector<clsClient>& Clients) {
      ofstream oFile{ _fileName, ios::out };
      if (oFile) {
          for (clsClient Client : Clients) {
              oFile << _ConvertClientToLine(Client) << '\n';
          }
          oFile.close();
          return true;
      }
      return false;
  }

  static bool reSave(const clsClient& Client) {
      vector<clsClient> Clients{loadAll()};
      
        for (clsClient& C : Clients) {
            if (Client.accountNumber == C.accountNumber) {
                C = Client;
                return saveAll(Clients);
            }
        }
      return false;
  }
};
string clsClientRepository::_fileName = "Clients.txt";
string clsClientRepository::_delim = "#//#";
