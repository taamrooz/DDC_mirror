#pragma once
#include "json.hpp"
#include <string>

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif
using json = nlohmann::json;
namespace Engine {
	ENGINE_API json& get_json();
	/*
	* \brief writes contents from this object to a json file
	* @param path path to file including filename, excluding extension
	*/
	ENGINE_API void write_to_file(json& j, std::string path);
	/*
	* \brief reads contents from a json file and loads them into this object
	* @param path path to file including filename, excluding extension
	*/
	ENGINE_API void read_from_file(json& j, std::string path);
}