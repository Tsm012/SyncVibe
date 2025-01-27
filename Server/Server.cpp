#include <Engine.h>
#include <Utilities.h>

#include <thread>
#include <map>

int main(int argc, char* argv[])
{
	std::map<std::string, std::string> args =
		parseCommandLineArguments(argc, argv);

	Engine().run();
	return 0;
}