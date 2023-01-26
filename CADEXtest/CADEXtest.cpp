#include <iostream>
#include <list>
#include <vector>
#include <iterator>
#include <algorithm>
#include <omp.h>
#include "Curves.h"


int main()
{
	// Random curves list with random params
	srand((unsigned)time(NULL));
	std::list<Curve*> Curves;
	std::cout << "Random Curves List:" << std::endl;
	for (size_t i = 0; i < 20; i++)
	{
		int rnd = rand()%100;
		switch (rnd%3)
		{
		case 0:
			Curves.push_back(new Circle(rnd+1));
			std::cout << i + 1 << ". Circle R: " << rnd + 1 << std::endl;
			break;
		case 1:
			Curves.push_back(new Ellipse(rnd+1, rnd%47+1));
			std::cout << i + 1 << ". Ellipse Rp: " << rnd + 1 << ", Ra: " << rnd % 47 + 1 << std::endl;
			break;
		case 2:
			Curves.push_back(new Helix(rnd+1, rnd%43));
			std::cout << i + 1 << ". Helix R: " << rnd + 1 << ", Step: " << rnd % 43 << std::endl;
			break;
		default:
			break;
		}
	}

	// Coords and derivatives calculation at t = PI/4
	std::list<Curve*>::iterator CurvesIter = Curves.begin();
	int Row = 1;
	std::cout << std::endl << "Coordinates and derivatives at PI/4:" << std::endl;
	for (CurvesIter; CurvesIter != Curves.end(); ++CurvesIter)
	{
		std::cout << Row << ". Coordinates at PI/4: " << (*CurvesIter)->GetCoords(PI / 4) << " | Derivative at PI/4: " << (*CurvesIter)->GetDerivative(PI/4) << std::endl;
		Row++;
	}

	// Second list, circles only
	std::vector<Circle*> Circles;
	for (CurvesIter = Curves.begin(); CurvesIter != Curves.end(); ++CurvesIter)
	{
		if (auto c = dynamic_cast<Circle*>(*CurvesIter))
		{
			Circles.push_back(c);
		}
	}

	// Circles Radiii Sum from second list
	int RadiusSum = 0;
	#pragma omp parallel for default(none) shared(Circles)
	for (int i = 0; i < Circles.size(); i++)
	{
		RadiusSum += Circles[i]->GetRadius();
	}
	std::cout << std::endl << "Circles Radiii Sum: " << RadiusSum << std::endl;


	// Second list sorted by radius
	std::sort(Circles.begin(), Circles.end(), [](Circle* a, Circle* b) -> bool {return a->GetRadius() < b->GetRadius(); });
	std::cout << std::endl << "Sorted circles list: " << std::endl;
	std::vector<Circle*>::iterator CirclesIter = Circles.begin();
	Row = 1;
	for (CirclesIter = Circles.begin(); CirclesIter != Circles.end(); ++CirclesIter)
	{
		std::cout << Row << ". Radius: " << (*CirclesIter)->GetRadius() << std::endl;
		Row++;
	}
	
}