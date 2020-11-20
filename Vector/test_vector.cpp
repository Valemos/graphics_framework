
#include "source/Vector3.h"
#include <iostream>
#include <vector>

int main()
{
	Vector3 v1 = { 1, 2, 3 };
	Vector3 v2 = { 0, 0, 5 };
	Vector3 v3 = { 0, 0, 35 };
	Vector3 v4 = { 1, 0 };
	

	std::cout << v1.Normal().Str() << std::endl;
	std::cout << v1.Dot(v2) << std::endl;
	std::cout << v2.Distance(v3) << std::endl;
	std::cout << v3.Distance(v2) << std::endl;
	std::cout << v4.Rotate(0, 0, 3.141592 * 0.5).Str() << std::endl;
	std::cout << v4.Rotate(0, 0, 3.141592 ).Str() << std::endl;
	std::cout << v4.Rotate(0, 0, 3.141592 * 1.5).Str() << std::endl;

	
	return 0;
}