#include "../headers_1/GR_Decomposer.h"
#include "../headers_1/LU_Decomposer.h"
#include <thread>
#include <chrono>
#define out(a) std::cout << a << ": \n";

int main()
{
	Matrix A(5, 5);
	A.MakeRandom(0);
	out("a");
	A.Display();
	LU_Decomposer LU_A(A);
	Matrix& L = (*LU_A.pL);
	Matrix& U = (*LU_A.pU);
	Matrix& P = (*LU_A.pP);
	Matrix& Q = (*LU_A.pQ);
	out("L");
	L.Display();
	out("U");
	U.Display();
	Matrix LU = L*U;
	out("LU");
	LU.Display();

	Matrix PAQ = P*A*Q;
	out("PAQ");
	PAQ.Display();

	std::this_thread::sleep_for(std::chrono::seconds(1));

	Matrix B(5,1);
	B.MakeRandom(0);
	out("B");
	B.Display();

	Matrix x = LU_A.EquationSolution(P*B);
	out("x");
	x.Display();

	Matrix Ax = A*x;
	out("Ax");
	Ax.Display();
	
}
