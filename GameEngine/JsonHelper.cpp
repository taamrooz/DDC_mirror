#include "JsonHelper.h"
#include <fstream>
#include <iostream>
#include <iomanip>

/*
 * https://github.com/nlohmann/json
 * documentation on how to use the JSON object returned by this function
 */

json& Engine::get_json()
{
	auto i = new json();
	return *i;
}

void Engine::write_to_file(json& j, std::string path)
{
	std::ofstream out(path + ".json");
	out << std::setw(4) << j << std::endl;
}

void Engine::read_from_file(json& j, std::string path)
{
	std::ifstream in(path + ".json");
	in >> j;
}
