#pragma once
#include "Component.h"
enum class DropTypes {
	Flask_Blue
};
struct ChestComponent : Component {
	ChestComponent(DropTypes contains) : contains{ contains } {}
		DropTypes contains;
};