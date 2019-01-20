#ifndef __RAY_TRACER_VECTOR_INCLUDED
#define __RAY_TRACER_VECTOR_INCLUDED

#include <optional>
#include <cmath>

class Vector {
	private:
		double _x;
		double _y;
		double _z;
	public:
		constexpr Vector(const double x, const double y, const double z) noexcept;

		constexpr double x() const noexcept;
		constexpr double y() const noexcept;
		constexpr double z() const noexcept;

		constexpr void x(const double x) noexcept;
		constexpr void y(const double y) noexcept;
		constexpr void z(const double z) noexcept;

		constexpr Vector& operator+=(const Vector& v) noexcept;
		constexpr Vector& operator-=(const Vector& v) noexcept;
		constexpr Vector& operator*=(const double k) noexcept;
		constexpr Vector& operator/=(const double k) noexcept;
};

constexpr double operator*(const Vector& v1, const Vector& v2) noexcept;
constexpr Vector operator*(const Vector& v, const double k) noexcept;
constexpr Vector operator*(const double k, const Vector& v) noexcept;
constexpr Vector operator/(const Vector& v, const double k) noexcept;
constexpr Vector operator+(const Vector& v1, const Vector& v2) noexcept;
constexpr Vector operator-(const Vector& v) noexcept;
constexpr Vector operator-(const Vector& v1, const Vector& v2) noexcept;
constexpr Vector operator%(const Vector& v1, const Vector& v2) noexcept;

constexpr bool operator==(const Vector& v1, const Vector& v2) noexcept;
constexpr bool operator!=(const Vector& v1, const Vector& v2) noexcept;
constexpr bool operator<(const Vector& v1, const Vector& v2) noexcept;
constexpr bool operator<=(const Vector& v1, const Vector& v2) noexcept;
constexpr bool operator>(const Vector& v1, const Vector& v2) noexcept;
constexpr bool operator>=(const Vector& v1, const Vector& v2) noexcept;

constexpr double magnitude(const Vector& v) noexcept;
constexpr Vector normalize(const Vector& v) noexcept;

using MaybeVector = std::optional<Vector>;

constexpr Vector::Vector(const double x, const double y, const double z) noexcept: 
	_x {x}, 
	_y {y}, 
	_z {z} {
}

constexpr double Vector::x() const noexcept {
	return _x;
}

constexpr double Vector::y() const noexcept {
	return _y;
}

constexpr double Vector::z() const noexcept {
	return _z;
}

constexpr void Vector::x(const double x) noexcept {
	_x = x;
}

constexpr void Vector::y(const double y) noexcept {
	_y = y;
}

constexpr void Vector::z(const double z) noexcept {
	_z = z;
}

constexpr Vector& Vector::operator+=(const Vector& v) noexcept {
	_x += v.x();
	_y += v.y();
	_z += v.z();

	return *this;
}

constexpr Vector& Vector::operator-=(const Vector& v) noexcept {
	return *this += -v;
}

constexpr Vector& Vector::operator*=(const double k) noexcept {
	_x *= k;
	_y *= k;
	_z *= k;
	
	return *this;
}

constexpr Vector& Vector::operator/=(const double k) noexcept {
	_x /= k;
	_y /= k;
	_z /= k;

	return *this;
}

constexpr double operator*(const Vector& v1, const Vector& v2) noexcept {
	return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

constexpr Vector operator*(const Vector& v, const double k) noexcept {
	return {k*v.x(), k*v.y(), k*v.z()};
}

constexpr Vector operator*(const double k, const Vector& v) noexcept {
	return v * k;
}

constexpr Vector operator/(const Vector& v, const double k) noexcept {
	return 1/k * v;
}

constexpr Vector operator+(const Vector& v1, const Vector& v2) noexcept {
	return {v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z()};
}

constexpr Vector operator-(const Vector& v) noexcept {
	return {-v.x(), -v.y(), -v.z()};
}

constexpr Vector operator-(const Vector& v1, const Vector& v2) noexcept {
	return v1 + -v2;
}


// Cross Product, since % kind of looks like and x
constexpr Vector operator%(const Vector& v1, const Vector& v2) noexcept {
	const double s1 {v1.y()*v2.z() - v1.z()*v2.y()};
	const double s2 {v1.z()*v2.x() - v1.x()*v2.z()};
	const double s3 {v1.x()*v2.y() - v1.y()*v2.x()};

	return {s1, s2, s3};
}

constexpr bool operator==(const Vector& v1, const Vector& v2) noexcept {
	const double ESP {1e-9};
	const Vector v {v1 - v2};

	return fabs(v.x()) <= ESP && fabs(v.y()) <= ESP && fabs(v.z()) <= ESP;

//	return v1.x() == v2.x() && v1.y() == v2.y() && v1.z() == v2.z();
}

constexpr bool operator!=(const Vector& v1, const Vector& v2) noexcept {
	return !(v1 == v2);
}

constexpr bool operator<(const Vector& v1, const Vector& v2) noexcept {
	// TODO: use a global ESP
	const double ESP {1e-9};
	const Vector v {v1 - v2};

	const double diffs[3] {v.x(), v.y(), v.z()};
	for (const auto& d: diffs)
		if (fabs(d) >= ESP)
			return d < 0;

	return false;
}

constexpr bool operator<=(const Vector& v1, const Vector& v2) noexcept {
	return v1 < v2 || v1 == v2;
}

constexpr bool operator>(const Vector& v1, const Vector& v2) noexcept {
	return !(v1 <= v2);

}

constexpr bool operator>=(const Vector& v1, const Vector& v2) noexcept {
	return v1 > v2 || v1 == v2;

}

constexpr double magnitude(const Vector& v)  noexcept {
	return std::sqrt(v * v);
}

constexpr Vector normalize(const Vector& v) noexcept {
	return v / magnitude(v);
}
#endif
