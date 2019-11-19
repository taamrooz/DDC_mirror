#pragma once
#include "Component.h"
enum class DropTypes {
	Flask_Blue
};
struct ChestComponent : Component {
	ChestComponent(string_code contains) : contains{ contains } {}
		string_code contains;
};