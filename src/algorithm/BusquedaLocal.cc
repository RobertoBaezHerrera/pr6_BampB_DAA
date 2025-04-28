#include "../include/algorithm/BusquedaLocal.h"

BusquedaLocal::BusquedaLocal(const DatosMDP& datos) : AlgoritmoVoraz(datos) { }

std::vector<std::vector<double>> BusquedaLocal::BLSwap(const std::vector<std::vector<double>>& S) {
  std::vector<std::vector<double>> S_original = datos_.GetConjuntoS();
  // Elementos que no estan en la solucion
  std::vector<std::vector<double>> elem;
  for (int i = 0; i < S_original.size(); ++i) {
    bool encontrado = false;
    for (int j = 0; j < S.size(); ++j) {
      if (S_original[i] == S[j]) {
        encontrado = true;
        break;
      }
    }
    if (!encontrado) {
      elem.push_back(S_original[i]);
    }
  }
  double z = CalcularZ(S);
  double z_mejor = z;
  std::vector<std::vector<double>> S_mejor = S;
  for (int i = 0; i < S.size(); ++i) {
    for (int j = 0; j < elem.size(); ++j) {
      // Intercambiamos el elemento i de S por el elemento j de elem
      std::vector<std::vector<double>> S_temp = S;
      S_temp[i] = elem[j];
      // Calculamos la nueva z
      double z_temp = CalcularZ(S_temp);
      if (z_temp > z_mejor) {
        z_mejor = z_temp;
        S_mejor = S_temp;
        std::cout << "Mejorando la solucion: " << z_mejor << std::endl;
      }                     // DUDA SOBRE SI ACTUALIZAR SOBRE LA MARCHA LA S    
    }
  }

  
  return S_mejor;
}

