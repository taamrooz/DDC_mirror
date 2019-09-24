#pragma once
#include "Component.h"

struct velocity_component : component
{
	velocity_component() = default;
	velocity_component(double dx, double dy) : dx{ dx }, dy{ dy } {}
	double dx{};
	double dy{};
};
