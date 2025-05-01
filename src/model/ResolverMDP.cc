#include "../include/model/ResolverMDP.h"

ResolverMDP::ResolverMDP(const DatosMDP& datos) : datos_(datos) { }

void ResolverMDP::ResolverVoraz() {
  std::cout << "\033[35mResolviendo con Voraz...\033[0m" << std::endl;
  AlgoritmoVoraz voraz(datos_);
  std::vector<std::vector<double>> S = voraz.EjecutarVoraz();
  double z = voraz.CalcularZ(S);
  solucion_voraz_ = new SolucionVoraz(S, z, 0.0, datos_.GetFicheroEntrada(), datos_.GetNumElementosN(), datos_.GetM(), datos_.GetDimensionK(), datos_);
}

void ResolverMDP::ResolverVorazConBusquedaLocal() {
  std::cout << "\033[35mResolviendo con Voraz y Busqueda Local...\033[0m" << std::endl;
  AlgoritmoVoraz voraz(datos_);
  std::vector<std::vector<double>> S = voraz.EjecutarVoraz();
  BusquedaLocal busqueda_local(datos_);
  S = busqueda_local.BLSwapIterativoBestImprovement(S);
  double z = voraz.CalcularZ(S);
  solucion_voraz_ = new SolucionVoraz(S, z, 0.0, datos_.GetFicheroEntrada(), datos_.GetNumElementosN(), datos_.GetM(), datos_.GetDimensionK(), datos_);
}

void ResolverMDP::ResolverGRASP(int LRC, int iteraciones) {
  //std::cout << "\033[33mResolviendo el problema MDP con GRASP...\033[0m" << std::endl;
  AlgoritmoGRASP grasp(datos_);
  std::vector<std::vector<double>> S = grasp.EjecutarGRASP(LRC, iteraciones);
  double z = grasp.CalcularZ(S);
  solucion_grasp_ = new SolucionGRASP(S, z, 0.0, datos_.GetFicheroEntrada(), datos_.GetNumElementosN(), datos_.GetDimensionK(), datos_.GetM(), datos_, iteraciones, LRC);
}