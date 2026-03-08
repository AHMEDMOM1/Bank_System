#pragma once
#include "clsClient.h"
#include <vector>


class IClientRepository {
public:
  virtual ~IClientRepository() = default;

  virtual bool append(const clsClient &Client) = 0;
  virtual std::vector<clsClient> loadAll() = 0;
  virtual bool saveAll(const std::vector<clsClient> &Clients) = 0;
  virtual bool reSave(const clsClient &Client) = 0;
};
