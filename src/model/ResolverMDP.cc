#include "../include/model/ResolverMDP.h"

ResolverMDP::ResolverMDP(const DatosMDP& datos) : datos_(datos) { }

void ResolverMDP::ResolverVoraz() {
  std::cout << "\033[35mResolviendo con Voraz...\033[0m" << std::endl;
  AlgoritmoVoraz voraz(datos_);
  // Medir tiempo de CPU
  double inicio = clock();
  std::vector<std::vector<double>> S = voraz.EjecutarVoraz();
  double fin = clock();
  double cpu = (fin - inicio) / CLOCKS_PER_SEC;
  double z = voraz.CalcularZ(S);
  solucion_voraz_ = new SolucionVoraz(S, z, cpu, datos_.GetFicheroEntrada(), datos_.GetNumElementosN(), datos_.GetM(), datos_.GetDimensionK(), datos_);
}

void ResolverMDP::ResolverVorazConBusquedaLocal() {
  std::cout << "\033[35mResolviendo con Voraz y Busqueda Local...\033[0m" << std::endl;
  AlgoritmoVoraz voraz(datos_);
  // Medir tiempo de CPU
  double inicio = clock();
  std::vector<std::vector<double>> S = voraz.EjecutarVoraz();
  BusquedaLocal busqueda_local(datos_);
  S = busqueda_local.BLSwapIterativoBestImprovement(S);
  double fin = clock();
  double cpu = (fin - inicio) / CLOCKS_PER_SEC;
  double z = voraz.CalcularZ(S);
  solucion_voraz_ = new SolucionVoraz(S, z, cpu, datos_.GetFicheroEntrada(), datos_.GetNumElementosN(), datos_.GetM(), datos_.GetDimensionK(), datos_);
}

void ResolverMDP::ResolverGRASP(int LRC, int iteraciones) {
  //std::cout << "\033[33mResolviendo el problema MDP con GRASP...\033[0m" << std::endl;
  AlgoritmoGRASP grasp(datos_);
  // Medir tiempo de CPU
  double inicio = clock();
  std::vector<std::vector<double>> S = grasp.EjecutarGRASP(LRC, iteraciones);
  double fin = clock();
  double cpu = (fin - inicio) / CLOCKS_PER_SEC;
  double z = grasp.CalcularZ(S);
  solucion_grasp_ = new SolucionGRASP(S, z, cpu, datos_.GetFicheroEntrada(), datos_.GetNumElementosN(), datos_.GetDimensionK(), datos_.GetM(), datos_, iteraciones, LRC);
}

void ResolverMDP::ResolverRamificacionYPoda(double cota_inferior, int m) {
  std::cout << "\033[35mResolviendo con Ramificación y Poda...\033[0m" << std::endl;
  /* RamificacionYPoda ramificacion(datos_);
  std::cout << "Cota inferior: " << cota_inferior << std::endl;
  std::cout << "m_: " << m << std::endl;
  datos_.SetM(m);
  std::vector<std::vector<double>> S = ramificacion.Ejecutar(cota_inferior); */
  //double z = datos_.CalcularZ(S);
  //solucion_ramificacion_y_poda_ = new SolucionRamificacionYPoda(S, z, 0.0, datos_.GetFicheroEntrada(), datos_.GetNumElementosN(), datos_.GetDimensionK(), datos_.GetM(), datos_, ramificacion.GetNodosGenerados());
}

void ResolverMDP::LiberarMemoria() {
  if (solucion_voraz_ != nullptr) {
    delete solucion_voraz_;
  }
  if (solucion_grasp_ != nullptr) {
    delete solucion_grasp_;
  }
  if (solucion_ramificacion_y_poda_ != nullptr) {
    delete solucion_ramificacion_y_poda_;
  }
}