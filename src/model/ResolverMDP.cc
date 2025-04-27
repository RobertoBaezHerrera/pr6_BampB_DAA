#include "../include/model/ResolverMDP.h"

ResolverMDP::ResolverMDP(const DatosMDP& datos) : datos_(datos) { }

void ResolverMDP::ResolverVoraz() {
  std::cout << "\033[33mResolviendo el problema MDP...\033[0m" << std::endl;
  AlgoritmoVoraz voraz(datos_);
  std::vector<std::vector<double>> S = voraz.EjecutarVoraz();
  double z = voraz.CalcularZ(S);
  solucion_voraz_ = new SolucionVoraz(S, z, 0.0, datos_.GetFicheroEntrada(), datos_.GetNumElementosN(), datos_.GetM(), datos_.GetDimensionK());
}