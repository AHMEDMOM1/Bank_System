#pragma once
#include <vector>

#include "IClientRepository.h"
#include "clsClient.h"


class clsClientManager {

  IClientRepository &_repository;

  clsClient _GetEmptyClient() { return clsClient("", "", "", "", "", 0, 0); }

public:
  clsClientManager(IClientRepository &repo) : _repository(repo) {}

  clsClient initNewAccount(const string &account) {
    return clsClient("", "", "", "", account, 0, 0);
  }

  clsClient findClient(const string &account) {
    vector<clsClient> Clients{_repository.loadAll()};

    for (const clsClient &Client : Clients) {
      if (Client.getAccountNumber() == account) {
        return Client;
      }
    }
    return _GetEmptyClient();
  }

  bool addClient(const clsClient &Client) { return _repository.append(Client); }

  bool updateClient(const clsClient &Client) {
    return _repository.reSave(Client);
  }
};
