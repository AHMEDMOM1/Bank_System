#include <iostream>

#include "clsClient.h"
#include "clsClientManager.h"
#include "clsClientScreen.h"

int main()
{

	clsClient Client{ clsClientManager::findClient("A101") };
	clsClientScreen::print(Client);
}
