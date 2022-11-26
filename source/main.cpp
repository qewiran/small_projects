#include "LU_Decomposer.h"
#include "GR_Decomposer.h"
#include <thread>
#include <chrono>
#define out(a) std::cout << a << ": \n";

int main()
{
	out("A");
	Matrix A(5, 5);
	A.MakeRandom(1);
	A.Display();
	// auto t1 = std::chrono::high_resolution_clock::now();
	LU_Decomposer LU_A(A);
	// auto t2 = std::chrono::high_resolution_clock::now();
	// std::cout << "LU took: "
	//           << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
	//           << " milliseconds\n";
	std::this_thread::sleep_for(std::chrono::seconds(1));
	Matrix B(5,1);
	B.MakeRandom(1);
	out("B");
	B.Display();
	Matrix x = LU_A.EquationSolution((*LU_A.pP)*B);
	out("x");
	x.Display();
	out("Ax");
	Matrix Ax = A*x;
	
	Ax.Display();
	// t1 = std::chrono::high_resolution_clock::now();
	//GR_Decomposer GR_A(A);
	// t2 = std::chrono::high_resolution_clock::now();
	// std::cout << "QR took: "
	//           << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
	//           << " milliseconds\n";
	// Matrix &G = (*GR_A.pG);
	// Matrix GR = (*GR_A.pG) * (*GR_A.pR);
	// out("GR");
	// GR.Display();
	// out("G");
	// G.Display();

	// LU_Decomposer LU_G(G);

	// Matrix Ginv = LU_G.GetInverted();
	// out("G^(-1)");
	// Ginv.Display();
	// out("G^(-1)*G");
	// Matrix I = Ginv * G;
	// I.Display();
	// out("G*G^(-1)");
	// I = G * Ginv;
	// I.Display();
}
