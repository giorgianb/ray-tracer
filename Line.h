#ifndef __RAY_TRACER_LINE_INCLUDED
#define __RAY_TRACER_LINE_INCLUDED
class Line {
	private:
		Vector _direction;
		Vector _offset;
	public:
		Line(const Vector& direction, const Vector& offset);
		Vector direction() const;
		Vector offset() const;
};

Vector evaluate(const Line& l, const double& s);
Vector normal(const Line& l, const Vector& v);

#endif
