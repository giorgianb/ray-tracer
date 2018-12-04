#ifndef __RAY_TRACER_VECTOR_INCLUDED
#define __RAY_TRACER_VECTOR_INCLUDED

#include <utility>

class Vector {
	private:
		double _x;
		double _y;
		double _z;
	public:
		Vector(const double x, const double y, const double z);

		double x() const;
		double y() const;
		double z() const;

		void x(const double x);
		void y(const double y);
		void z(const double z);

		Vector& operator+=(const Vector& v);
		Vector& operator-=(const Vector& v);
		Vector& operator*=(const double k);
		Vector& operator/=(const double k);
};

double operator*(const Vector& v1, const Vector& v2);
Vector operator*(const Vector& v, const double k);
Vector operator*(const double k, const Vector& v);
Vector operator/(const Vector& v, const double k);
Vector operator+(const Vector& v1, const Vector& v2);
Vector operator-(const Vector& v);
Vector operator-(const Vector& v1, const Vector& v2);
Vector operator%(const Vector& v1, const Vector& v2);

bool operator==(const Vector& v1, const Vector& v2);
bool operator!=(const Vector& v1, const Vector& v2);
bool operator<(const Vector& v1, const Vector& v2);
bool operator<=(const Vector& v1, const Vector& v2);
bool operator>(const Vector& v1, const Vector& v2);
bool operator>=(const Vector& v1, const Vector& v2);

double magnitude(const Vector& v);
Vector normalize(const Vector& v);

using MaybeVector = std::pair<bool, Vector>;
#endif
