#include <istream>
#include <ostream>
#include "vector2d.h"

std::istream& operator>>(std::istream& is, vector2d& p) {
	float x, y;
	if (is >> x && is >> y) {
		p.x(x);
		p.y(y);
	}
	return is;
}

std::ostream& operator<<(std::ostream& os, vector2d p) {
	os << p.x() << " " << p.y();
	return os;
}