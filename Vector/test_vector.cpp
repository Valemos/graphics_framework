
#include "source/Vector3.h"
#include <iostream>
#include <vector>

int main()
{
	Vector3 v1 = { 1, 2, 3 };
	Vector3 v2 = { 0, 0, 5 };
	Vector3 v3 = { 0, 0, 35 };

	std::cout << v1.normal().str() << std::endl;
	std::cout << v1.scalarMult(v2) << std::endl;
	std::cout << v2.distance(v3) << std::endl;
	std::cout << v3.distance(v2) << std::endl;
	
	return 0;
}