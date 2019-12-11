#pragma once
#include <cmath>
#include <iosfwd>
#include <algorithm>

template <typename Scalar> class basic_vector2d {
public:
	constexpr basic_vector2d() noexcept = default;
	constexpr basic_vector2d(Scalar x, Scalar y) noexcept : x_{ x }, y_{ y } {}
	constexpr Scalar x() const noexcept { return x_; }
	constexpr void x(Scalar newX) noexcept { x_ = newX; }
	constexpr Scalar y() const noexcept { return y_; }
	constexpr void y(Scalar newY) noexcept { y_ = newY; }

	constexpr bool operator==(basic_vector2d other) const noexcept {
		return x_ == other.x_ && y_ == other.y_;
	}

	constexpr bool operator!=(basic_vector2d other) const noexcept {
		return x_ != other.x_ || y_ != other.y_;
	}

	constexpr basic_vector2d& operator+=(basic_vector2d other) noexcept {
		x_ += other.x_;
		y_ += other.y_;
		return *this;
	}

	constexpr basic_vector2d& operator-=(basic_vector2d other) noexcept {
		x_ -= other.x_;
		y_ -= other.y_;
		return *this;
	}

	constexpr basic_vector2d& operator*=(Scalar s) noexcept {
		x_ *= s;
		y_ *= s;
		return *this;
	}

	constexpr basic_vector2d& operator/=(Scalar s) noexcept {
		x_ /= s;
		y_ /= s;
		return *this;
	}

private:
	Scalar x_{};
	Scalar y_{};
};

using vector2d = basic_vector2d<float>;
using ivector2d = basic_vector2d<int>;

template <typename Scalar>
std::istream& operator>>(std::istream& is, basic_vector2d<Scalar>& p) {
	Scalar x, y;
	if (is >> x && is >> y) {
		p.x(x);
		p.y(y);
	}
	return is;
}

template <typename Scalar>
std::ostream& operator<<(std::ostream& os, basic_vector2d<Scalar> p) {
	os << p.x() << " " << p.y();
	return os;
}

template <typename Scalar>
constexpr basic_vector2d<Scalar> perp(basic_vector2d<Scalar> v) {
	return { -v.y(), v.x() };
}

template <typename Scalar>
constexpr basic_vector2d<Scalar> operator-(basic_vector2d<Scalar> a,
	basic_vector2d<Scalar> b) {
	return { a.x() - b.x(), a.y() - b.y() };
}

template <typename Scalar>
constexpr basic_vector2d<Scalar> operator+(basic_vector2d<Scalar> a,
	basic_vector2d<Scalar> b) {
	return { a.x() + b.x(), a.y() + b.y() };
}

template <typename Scalar>
constexpr basic_vector2d<Scalar> operator*(basic_vector2d<Scalar> v, float s) {
	return v *= s;
}

template <typename Scalar>
constexpr basic_vector2d<Scalar> operator*(float s, basic_vector2d<Scalar> v) {
	return operator*(v, s);
}

template <typename Scalar>
constexpr basic_vector2d<Scalar> operator/(basic_vector2d<Scalar> v, float s) {
	return v /= s;
}

template <typename Scalar>
constexpr basic_vector2d<Scalar> operator/(float s, basic_vector2d<Scalar> v) {
	return operator/(v, s);
}

template <typename Scalar>
constexpr float dot(basic_vector2d<Scalar> a, basic_vector2d<Scalar> b) {
	return a.x() * b.x() + a.y() * b.y();
}

template <typename Scalar> constexpr auto norm2(basic_vector2d<Scalar> p) {
	return dot(p, p);
}

template <typename Scalar> constexpr auto norm(basic_vector2d<Scalar> p) {
	return std::sqrt(dot(p, p));
}

template <typename Scalar> constexpr double length(basic_vector2d<Scalar> v) {
	return std::sqrt(std::pow(v.x(), 2) + std::pow(v.y(), 2));
}

template <typename Scalar>
constexpr basic_vector2d<Scalar> normalize(basic_vector2d<Scalar> p) {
	auto ls = norm(p);
	return { p.x() / ls, p.y() / ls };
}

template <typename Scalar>
constexpr auto distance(basic_vector2d<Scalar> from,
	basic_vector2d<Scalar> to) {
	return norm(from - to);
}

template <typename Scalar>
constexpr auto distance2(basic_vector2d<Scalar> from,
	basic_vector2d<Scalar> to) {
	return norm2(from - to);
}
template <typename Scalar>
basic_vector2d<Scalar> rotate(basic_vector2d<Scalar> v, float radians) {
	auto s = sin(radians);
	auto c = cos(radians);
	return { c * v.x() - s * v.y(), s * v.x() + c * v.y() };
}

template <typename Scalar>
constexpr bool onLine(basic_vector2d<Scalar> p1, basic_vector2d<Scalar> p2, basic_vector2d<Scalar> p) {
	if (p.x() <= std::max(p1.x(), p2.x()) && p.x() <= std::min(p1.x(), p2.x()) &&
		(p.y() <= std::max(p1.y(), p2.y()) && p.y() <= std::min(p1.y(), p2.y())))
		return true;

	return false;
}

template <typename Scalar>
constexpr int direction(basic_vector2d<Scalar> a, basic_vector2d<Scalar> b, basic_vector2d<Scalar> c)
{
	int val = (b.y() - a.y()) * (c.x() - b.x()) - (b.x() - a.x()) * (c.y() - b.y());
	if (val == 0)
		return 0;     //colinear
	else if (val < 0)
		return 2;    //anti-clockwise direction
	return 1;    //clockwise direction
}

template <typename Scalar>
constexpr bool intersects(basic_vector2d<Scalar> a1, basic_vector2d<Scalar> a2, basic_vector2d<Scalar> b1, basic_vector2d<Scalar> b2)
{
	int dir1 = direction(a1, a2, b1);
	int dir2 = direction(a1, a2, b2);
	int dir3 = direction(b1, b2, a1);
	int dir4 = direction(b1, b2, a2);

	if (dir1 != dir2 && dir3 != dir4)
		return true; //they are intersecting

	if (dir1 == 0 && onLine(a1, a2, b1)) //when p2 of line2 are on the line1
		return true;

	if (dir2 == 0 && onLine(a1, a2, b2)) //when p1 of line2 are on the line1
		return true;

	if (dir3 == 0 && onLine(b1, b2, a1)) //when p2 of line1 are on the line2
		return true;

	if (dir4 == 0 && onLine(b1, b2, a2)) //when p1 of line1 are on the line2
		return true;

	return false;
}