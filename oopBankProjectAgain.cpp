#include <iostream>

#include "clsClientManager.h"
#include "clsAddClientScreen.h"
#include "clsClientRepository.h"


int main() {
  clsClientRepository repository("Clients.txt");
  clsClientManager manager(repository);
  clsAddClientScreen addScreen(manager);
  addScreen.AddScreen();


}
