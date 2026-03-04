#pragma once
#include <vector>

#include "clsClient.h"
#include "clsClientRepository.h"

class clsClientManager {

  static clsClient _GetEmptyClient() {
    return clsClient(clsClient::getEmptyMode(), "", "", "", "", "", "", 0);
  }

public:
  static clsClient findClient(const string &account) {
    vector<clsClient> Clients{clsClientRepository::loadAll()};

    for (const clsClient &Client : Clients) {
      if (Client.accountNumber == account) {
        return Client;
      }
    }
    return _GetEmptyClient();
  }
};
