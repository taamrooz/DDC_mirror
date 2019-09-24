#pragma once
struct position_component : component
{
	position_component() = default;
	position_component(int x, int y) : x{ x }, y{ y } {}
	int x{};
	int y{};
};

