#pragma once
#include "JsonHelper.h"

class Component
{
public:
	virtual void ToJson(json &j, int id);
	virtual ~Component() {};
};

