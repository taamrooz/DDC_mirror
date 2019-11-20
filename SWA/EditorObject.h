#pragma once
#include <string>
#include <memory>

class EditorObject
{
public:
	std::string name;
	std::string file_path;
	std::shared_ptr<Texture> image = nullptr;
	int x = 0;
	int y = 0;
	int width = 48;
	int height = 48;
	bool empty = false;
};

