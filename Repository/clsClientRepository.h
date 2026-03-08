#pragma once
#include <fstream>
#include <string>
#include <vector>

#include "IClientRepository.h"
#include "clsClient.h"
#include "clsString.h"

class clsClientRepository : public IClientRepository {
  string _fileName;
  string _delim;

  clsClient _ConvertLineToClient(const string &line) {
    vector<string> linePartitions{clsString::Split(line, _delim)};

    return clsClient{linePartitions.at(0),
                     linePartitions.at(1),
                     linePartitions.at(2),
                     linePartitions.at(3),
                     linePartitions.at(4),
                     static_cast<short>(stoi(linePartitions.at(5))),
                     stof(linePartitions.at(6))};
  }

  string _ConvertClientToLine(const clsClient &Client) {
    return Client.getFirstName() + _delim + Client.getLastName() + _delim +
           Client.getEmail() + _delim + Client.getPhone() + _delim +
           Client.getAccountNumber() + _delim + to_string(Client.getPinCode()) +
           _delim + to_string(Client.getBalance());
  }

public:
  clsClientRepository(const string &fileName, const string &delim = "#//#")
      : _fileName(fileName), _delim(delim) {}

  bool append(const clsClient &Client) override {
    ofstream oFile{_fileName, ios::app};
    if (oFile) {
      string line{_ConvertClientToLine(Client)};
      oFile << line << "\n";
      oFile.close();
      return true;
    }

    return false;
  }

  vector<clsClient> loadAll() override {
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

  bool saveAll(const vector<clsClient> &Clients) override {
    ofstream oFile{_fileName, ios::out};
    if (oFile) {
      for (const clsClient &Client : Clients) {
        oFile << _ConvertClientToLine(Client) << '\n';
      }
      oFile.close();
      return true;
    }
    return false;
  }

  bool reSave(const clsClient &Client) override {
    vector<clsClient> Clients{loadAll()};

    for (clsClient &C : Clients) {
      if (Client.getAccountNumber() == C.getAccountNumber()) {
        C = Client;
        return saveAll(Clients);
      }
    }
    return false;
  }
};
