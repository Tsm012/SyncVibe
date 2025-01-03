#include "Network.h"
#include <enet.h>
#include <stdio.h>

int main()
{
	if (enet_initialize() != 0)
	{
		printf("An error occurred while initializing ENet.\n");
		return 1;
	}

	enet_deinitialize();
	std::cout << "Hello World!" << std::endl;
	return 0;
}