#include "../include/algorithm/Voraz.h"

AlgoritmoVoraz::AlgoritmoVoraz(const DatosMDP& datos) : datos_(datos) { }

std::vector<double> AlgoritmoVoraz::CalcularCentroGravedad(const std::vector<std::vector<double>>& elem) {
  int dimension_K = datos_.GetDimensionK();
  std::vector<double> centro_gravedad(dimension_K, 0.0);

  if (elem.empty()) {
    std::cerr << "Error: El conjunto de elementos está vacío." << std::endl;
    return centro_gravedad;
  }
  for (int i = 0; i < elem.size(); ++i) {
    for (int j = 0; j < elem[i].size(); ++j) {
      centro_gravedad[j] += elem[i][j];
    }
  }
  for (int j = 0; j < dimension_K; ++j) {
    centro_gravedad[j] /= elem.size();
  }
  // Mostrar el centro de gravedad
    std::cout << "Centro de gravedad: ";
    for (const auto& valor : centro_gravedad) {
        std::cout << valor << " ";
    }
    std::cout << std::endl;
    return centro_gravedad;
}

double AlgoritmoVoraz::CalcularDistancia(const std::vector<double>& Si, const std::vector<double>& centro_gravedad) const {
  double distancia = 0.0;
  for (int i = 0; i < Si.size(); ++i) {
    distancia += (Si[i] - centro_gravedad[i]) * (Si[i] - centro_gravedad[i]);
  }
  return sqrt(distancia);
}

int AlgoritmoVoraz::CalcularElementoMasAlejado(const std::vector<std::vector<double>>& elem, const std::vector<double>& centro_gravedad) const {
  double max_distancia = -1.0;
  int id_max_distancia = -1;
  if (elem.empty()) {
    std::cerr << "Error: El conjunto de elementos está vacío." << std::endl;
    return id_max_distancia;
  }
  for (int i = 0; i < elem.size(); ++i) {
    double distancia_actual = CalcularDistancia(elem[i], centro_gravedad);
    if (distancia_actual > max_distancia) {
      max_distancia = distancia_actual;
      id_max_distancia = i;  // Suponiendo que el primer elemento es el ID
    }
  }
  return id_max_distancia;
}

std::vector<std::vector<double>> AlgoritmoVoraz::EjecutarVoraz(int m) {
  std::vector<std::vector<double>> S = datos_.GetConjuntoS();
  std::vector<std::vector<double>> elem = S;
  S.clear();
  // Sc es el centro de gravedad inicial
  std::vector<double> centro_gravedad = CalcularCentroGravedad(elem);
  while (S.size() < m) {
    // Calculamos el indice del elemento mas alejado del centro de gravedad
    int id_max_distancia = CalcularElementoMasAlejado(elem, centro_gravedad);
    // El elemento mas alejado del centro de gravedad es el que se añade al conjunto
    S.push_back(elem[id_max_distancia]);
    elem.erase(elem.begin() + id_max_distancia);
    // Actualizar el centro de gravedad
    centro_gravedad = CalcularCentroGravedad(S);
  }
  // Imprimir el conjunto S
    std::cout << "\033[1;33mConjunto S: \033[0m\n";
    for (const auto& elemento : S) {
        for (const auto& valor : elemento) {
            std::cout << valor << " ";
        }
        std::cout << std::endl;
    }
  // Imprimir el conjunto de elementos restantes
  return S;
}