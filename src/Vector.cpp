#include "Vector.h"
#include <cmath>
// TODO: Remove in debug
#include <iostream>
#include "Debug.h"

Vector::Vector(const double x, const double y, const double z): 
	_x {x}, 
	_y {y}, 
	_z {z} {
}

double Vector::x() const {
	return _x;
}

double Vector::y() const {
	return _y;
}

double Vector::z() const {
	return _z;
}

void Vector::x(const double x) {
	_x = x;
}

void Vector::y(const double y) {
	_y = y;
}

void Vector::z(const double z) {
	_z = z;
}

Vector& Vector::operator+=(const Vector& v) {
	_x += v.x();
	_y += v.y();
	_z += v.z();

	return *this;
}

Vector& Vector::operator-=(const Vector& v) {
	return *this += -v;
}

Vector& Vector::operator*=(const double k) {
	_x *= k;
	_y *= k;
	_z *= k;
	
	return *this;
}

Vector& Vector::operator/=(const double k) {
	_x /= k;
	_y /= k;
	_z /= k;

	return *this;
}

double operator*(const Vector& v1, const Vector& v2) {
	return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

Vector operator*(const Vector& v, const double k) {
	return {k*v.x(), k*v.y(), k*v.z()};
}

Vector operator*(const double k, const Vector& v) {
	return v * k;
}

Vector operator/(const Vector& v, const double k) {
	return 1/k * v;
}

Vector operator+(const Vector& v1, const Vector& v2) {
	return {v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z()};
}

Vector operator-(const Vector& v) {
	return {-v.x(), -v.y(), -v.z()};
}

Vector operator-(const Vector& v1, const Vector& v2) {
	return v1 + -v2;
}


// Cross Product, since % kind of looks like and x
Vector operator%(const Vector& v1, const Vector& v2) {
	const double s1 {v1.y()*v2.z() - v1.z()*v2.y()};
	const double s2 {v1.z()*v2.x() - v1.x()*v2.z()};
	const double s3 {v1.x()*v2.y() - v1.y()*v2.x()};

	return {s1, s2, s3};
}

bool operator==(const Vector& v1, const Vector& v2) {
	constexpr double ESP {1e-9};
	const Vector v {v1 - v2};

	return fabs(v.x()) <= ESP && fabs(v.y()) <= ESP && fabs(v.z()) <= ESP;

//	return v1.x() == v2.x() && v1.y() == v2.y() && v1.z() == v2.z();
}

bool operator!=(const Vector& v1, const Vector& v2) {
	return !(v1 == v2);
}

bool operator<(const Vector& v1, const Vector& v2) {
	// TODO: use a global ESP
	constexpr double ESP {1e-9};
	const Vector v {v1 - v2};

	const double diffs[3] {v.x(), v.y(), v.z()};
	for (const auto& d: diffs)
		if (fabs(d) >= ESP)
			return d < 0;

//	return v1.x() < v2.x()
//		|| (v1.x() == v2.x() && v1.y() < v2.y())
//		|| (v1.x() == v2.x() && v1.y() == v2.y() && v1.z() < v2.z());
}

bool operator<=(const Vector& v1, const Vector& v2) {
	return v1 < v2 || v1 == v2;
}

bool operator>(const Vector& v1, const Vector& v2) {
	return !(v1 <= v2);

}

bool operator>=(const Vector& v1, const Vector& v2) {
	return v1 > v2 || v1 == v2;

}

double magnitude(const Vector& v)  {
	return std::sqrt(v * v);
}

Vector normalize(const Vector& v) {
	return v / magnitude(v);
}
