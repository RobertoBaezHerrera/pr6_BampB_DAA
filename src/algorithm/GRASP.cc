#include "algorithm/GRASP.h"

AlgoritmoGRASP::AlgoritmoGRASP(const DatosMDP& datos) : AlgoritmoVoraz(datos) { }

std::vector<int> AlgoritmoGRASP::CalcularElementosMasAlejados(const std::vector<std::vector<double>>& elem,
  const std::vector<double>& centro_gravedad, int LRC) const {
  std::vector<std::pair<double, int>> distancias_indices;

  if (elem.empty()) {
    std::cerr << "Error: El conjunto de elementos está vacío." << std::endl;
    return {};
  }

  if (LRC > elem.size()) {
    std::cerr << "Error: LRC no puede ser mayor que el número de elementos."  << std::endl;
    return {};
  }

  // Calcular todas las distancias al centro de gravedad y guardar índice
  for (std::size_t i = 0; i < elem.size(); ++i) {
    double distancia_actual = CalcularDistancia(elem[i], centro_gravedad);
    distancias_indices.push_back({distancia_actual, i});
  }

  // Ordenar de mayor a menor distancia
  std::sort(distancias_indices.begin(), distancias_indices.end(),
            std::greater<>());

  // Coger los LRC primeros índices
  std::vector<int> indices;
  for (int i = 0; i < LRC; ++i) {
    indices.push_back(distancias_indices[i].second);
  }

  return indices;
}

std::vector<std::vector<double>> AlgoritmoGRASP::EjecutarVorazAleatorio(int LRC) {
  std::vector<std::vector<double>> S = datos_.GetConjuntoS();
  std::vector<std::vector<double>> elem = S;
  S.clear();
  // Sc es el centro de gravedad inicial
  std::vector<double> centro_gravedad = CalcularCentroGravedad(elem);
  while (S.size() < datos_.GetM()) {
    // Calculamos el indice del elemento mas alejado del centro de gravedad
    std::vector<int> indices_max_distancia = CalcularElementosMasAlejados(elem, centro_gravedad, LRC);
    // Esto es lo que cambia en el algoritmo GRASP
    int id_aleatorio = rand() % indices_max_distancia.size();
    int id_max_distancia = indices_max_distancia[id_aleatorio];
    // El elemento mas alejado del centro de gravedad es el que se añade al conjunto
    S.push_back(elem[id_max_distancia]);
    elem.erase(elem.begin() + id_max_distancia);
    // Actualizar el centro de gravedad
    centro_gravedad = CalcularCentroGravedad(S);
  }
  return S;
}

std::vector<std::vector<double>> AlgoritmoGRASP::EjecutarGRASP(int LRC, int iteraciones) {
  std::cout << "\033[33mResolviendo con GRASP...\033[0m" << std::endl;
  std::vector<std::vector<double>> S = EjecutarVorazAleatorio(LRC);
  double z = CalcularZ(S);
  double z_mejor = z;
  auto S_mejor = S;
  int limite_iteraciones = 0;
  while (limite_iteraciones < iteraciones) {
    S = EjecutarVorazAleatorio(LRC);
    // Aplicar busqueda local
    BusquedaLocal busqueda_local(datos_);
    S = busqueda_local.BLSwap(S);
    z = CalcularZ(S);
    if (z > z_mejor) {
      z_mejor = z;
      S_mejor = S;
    }
    limite_iteraciones++;
  }
  return S_mejor;
}