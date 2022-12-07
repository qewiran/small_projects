#include "../headers/GR_Decomposer.h"
#include "../headers/LU_Decomposer.h"
#include "../headers/Iteration_Method.h"
#include <thread>
#include <ratio>
#include <chrono>
#define OUT(a) std::cout << a << ": \n";
#define CLK() std::chrono::high_resolution_clock::now();
#define CLK_OUT(t2, t1) std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " ms\n";

int main()
{
	Matrix A(5, 5);
	//A.MakeCustom();
	A.MakeRandom(0);
	A.Display();
	Matrix B(5, 1);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	//B.MakeCustom();
	B.MakeRandom(0);
	B.Display();
	LU_Decomposer LU_A(A);
	Matrix x1 = LU_A.EquationSolution(B);
	std::cout << "x1:\n";
	x1.Display();
	std::cout << "ax1:\n";
	Matrix ax1 = A * x1;
	ax1.Display();
	Iteration_Method solution(A, B);
	std::cout << "x2:\n";
	Matrix x2 = solution.JacobiSolution();
	x2.Display();
	std::cout << "ax2:\n";
	Matrix ax2 = (*solution.pInitialMatrix) * x2;
	ax2.Display();

	Matrix x3 = solution.SeidelSolution();
	x3.Display();
	std::cout << "ax3:\n";
	Matrix ax3 = (*solution.pInitialMatrix) * x3;
	ax3.Display();
}
