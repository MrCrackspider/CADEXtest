#include "pch.h"
#include "Curves.h"


// Curve
Curve::Curve() {}



// Point
Point3D::Point3D() : x(0), y(0), z(0) {}
Point3D::Point3D(double x, double y, double z) : x(x), y(y), z(z) {}
void Point3D::set(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
std::string Point3D::GetStr() const
{
	return std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z);
}



// Circle
Circle::Circle() : Radius(0) {}
Circle::Circle(double r) : Radius(r) {}
Point3D Circle::GetCoords(double t)
{

	return Point3D(Radius * cos(t), Radius * sin(t), 0);
}
Point3D Circle::GetDerivative(double t)
{
	return Point3D(Radius * sin(t) * (-1), Radius * cos(t), 0);
}
double Circle::GetRadius()
{
	return Radius;
}



// Ellipse
Ellipse::Ellipse() : RadiusP(0), RadiusA(0) {}
Ellipse::Ellipse(double Rp, double Ra) : RadiusP(Rp), RadiusA(Ra) {}
Point3D Ellipse::GetCoords(double t)
{
	return Point3D((RadiusP + RadiusA) / 2 * cos(t), sqrt(RadiusP * RadiusA) * sin(t), 0);
}
Point3D Ellipse::GetDerivative(double t)
{
	return Point3D((RadiusP + RadiusA) / 2 * sin(t) * (-1), sqrt(RadiusP * RadiusA) * cos(t), 0);
}



// Helix
Helix::Helix() : Radius(0), Step(0) {}
Helix::Helix(double radius, double step) : Radius(radius), Step(step) {}
double Helix::GetRadius()
{
	return Radius;
}
Point3D Helix::GetCoords(double t)
{
	return Point3D(Radius * cos(t), Radius * sin(t), t * Step / (2 * PI));
}
Point3D Helix::GetDerivative(double t)
{
	return Point3D(Radius * sin(t) * (-1), Radius * cos(t), Step / (2 * PI));
}

