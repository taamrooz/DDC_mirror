#pragma once
#include "SDL.h"

namespace Engine
{
	class rect2d
	{
	private:
		SDL_Rect* wrap_{};
	public:
		rect2d(int x, int y, int w, int h) noexcept : wrap_{ new SDL_Rect{x,y,w,h} } {}
		rect2d() noexcept : wrap_{ new SDL_Rect{0,0,0,0}} {}
		~rect2d() noexcept { delete wrap_; }
		constexpr int x() const noexcept { return wrap_->x; }
		constexpr void x(int x) noexcept { wrap_->x = x; }
		constexpr int y() const noexcept { return wrap_->y; }
		constexpr void y(int y) noexcept { wrap_->y = y; }
		constexpr int width() const noexcept { return wrap_->w; }
		constexpr void width(int width) noexcept { wrap_->w = width; }
		constexpr int height() const noexcept { return wrap_->h; }
		constexpr void height(int height) noexcept { wrap_->h = height; }
		constexpr SDL_Rect* unwrap() const noexcept { return wrap_; }
	};
}


