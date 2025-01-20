#pragma once
#include <map>

const char* getHost(std::map<std::string, std::string>& args);

std::map<std::string, std::string> parseCommandLineArguments(int argc, char* argv[]);

int getPort(std::map<std::string, std::string>& args);

int generateRandomId();