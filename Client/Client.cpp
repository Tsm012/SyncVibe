#include <iostream>
#include <map>
#include <optional>
#include <string>
#include "Engine.h"
#include <Utilities.h>
#include "Client.h"


int main(int argc, char* argv[])
{
	std::map<std::string, std::string> args =
		parseCommandLineArguments(argc, argv);

	const char* host = getHost(args);
	int port = getPort(args);

	Engine(Engine::Client, host, port).run();

	return 0;
}
