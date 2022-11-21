#include "LU_Decomposer.h"
#include "GR_Decomposer.h"
#include <thread>
#include <chrono>
#define out(a) std::cout << a << ": \n";

int main()
{
  Row a(10);
  for (int i = 0; i < 10; i++)
    a[i] = i;
  double k = 2;
  Row b = a * k;
  a.Display();
  b.Display();
  auto c = a + b;
  c.Display();
  // out("A");
  // Matrix A(10, 10);
  // A.MakeRandom(0);
  // A.Display();

  // LU_Decomposer LU_A(A);

  // Matrix B(4,1);
  // B.MakeRandom(1);

  // GR_Decomposer GR_A(A);
  // Matrix& G = (*GR_A.pG);
  // Matrix GR = (*GR_A.pG)*(*GR_A.pR);
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
