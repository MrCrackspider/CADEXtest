#pragma once

#ifndef EXPORT
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
#endif

#include <ostream>
#include <string>

#define PI 3.14159

extern "C" class EXPORT Point3D
{
public:
	Point3D();
	Point3D(double x, double y, double z);
	void set(double x, double y, double z);
	std::string GetStr() const;
	// 
	friend std::ostream& operator<< (std::ostream& os, Point3D const& p)
	{
		os << p.GetStr();
		return os;
	}
private:
	double x, y, z;
};



class EXPORT Curve
{
public:
	Curve();
	virtual Point3D GetCoords(double t) = 0;
	virtual Point3D GetDerivative(double t) = 0;
};



class EXPORT Circle :
	public Curve
{
public:
	Circle();
	Circle(double r);
	Point3D GetCoords(double t);
	Point3D GetDerivative(double t) override;
	double GetRadius();

private:
	double Radius;

};



class EXPORT Ellipse :
	public Curve
{
public:
	Ellipse();
	Ellipse(double Rp, double Ra);
	Point3D GetCoords(double t);
	Point3D GetDerivative(double t) override;
private:
	double RadiusP, RadiusA;
};



class EXPORT Helix :
	public Curve
{
public:
	Helix();
	Helix(double radius, double step);
	double GetRadius();
	Point3D GetCoords(double t);
	Point3D GetDerivative(double t) override;

private:
	double Radius, Step;
};