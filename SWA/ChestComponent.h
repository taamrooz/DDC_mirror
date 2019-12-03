#pragma once
#include "Component.h"
enum class DropTypes {
	Flask_Blue
};
struct ChestComponent : Component {
	ChestComponent(string_code contains) : contains{ contains } {}
		string_code contains;

		void ToJson(json& j, int id) override
		{
			j[id]["ChestComponent"]["contains"] = contains;
		}
};