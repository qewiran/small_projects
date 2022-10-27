#include "Matrix.h"
#include "LU_Decomposer.h"
#include <thread>

int main()
{
	std::cout << "A: \n";
	Matrix A(5, 5);
	A.MakeRandom(0);

	LU_Decomposer decomp(&A);
	std::cout << "L: \n";
	(*decomp.L).Display();
	std::cout << "U: \n";
	(*decomp.U).Display();
	std::cout << "LU: \n";
	Matrix LU = (*decomp.L) * (*decomp.U);
	LU.Display();
	std::cout << "PAQ: \n";
	Matrix PAQ = (*decomp.P) * A;
	PAQ = PAQ * (*decomp.Q);
	PAQ.Display();

	std::this_thread::sleep_for(std::chrono::seconds(1));
	Matrix B(5, 1);
	std::cout << "B: \n";
	B.MakeRandom(0);

	B.Display();
	std::cout << "solution: \n";
	Matrix x = decomp.EquationSolution((*decomp.P) * B);
	x.Display();
	Matrix Ax = A * x;
	std::cout << "Ax \n";
	Ax.Display();

	std::cout << "A^(-1) \n";
	Matrix Ainv = decomp.GetInverted();
	Ainv.Display();

	std::cout << "A^(-1)*A: \n";
	Matrix I = Ainv * A;
	I.Display();
	std::cout << "A*A^(-1): \n";
	I = A * Ainv;
	I.Display();
}
