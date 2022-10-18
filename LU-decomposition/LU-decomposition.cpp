#include <iostream>
#include "Matrix.h"
#include"LU_Decomposer.h"


int main()
{

	Matrix A(2, 3);
	A.MakeCustom();
	LU_Decomposer decomp(A);

	Matrix B(3, 1);
	B.MakeCustom();
	decomp.EquationSolution((*decomp.P) * B).Display();
	Matrix Ainv = decomp.GetInverted();
	Ainv.Display();

	Matrix E = A * Ainv;
	E.Display();

	E = Ainv * A;
	E.Display();
}
