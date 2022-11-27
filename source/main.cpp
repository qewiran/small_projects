#include "LU_Decomposer.h"
#include "GR_Decomposer.h"
#include <thread>
#include <chrono>
#define out(a) std::cout << a << ": \n";

int main()
{
	Matrix A(1000, 1000);
	A.MakeRandom(0);

	LU_Decomposer LU_A(A);
	std::cout<<"done";
}
