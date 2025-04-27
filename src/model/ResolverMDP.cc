#include "../include/model/ResolverMDP.h"

void ResolverMDP::ResolverVoraz(int m) {
  std::cout << "\033[33mResolviendo el problema MDP...\033[0m" << std::endl;
  AlgoritmoVoraz voraz(datos_);
  std::vector<std::vector<double>> S = voraz.EjecutarVoraz(m);
  double z = voraz.CalcularZ(S);
  std::cout << "Z: " << z << std::endl;
}