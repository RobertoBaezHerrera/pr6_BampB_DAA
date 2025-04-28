#include "../include/algorithm/BusquedaLocal.h"

BusquedaLocal::BusquedaLocal(const DatosMDP& datos) : AlgoritmoVoraz(datos) { }

std::vector<std::vector<double>> BusquedaLocal::CalcularElementosFueraDeS(const std::vector<std::vector<double>>& S) {
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
  return elem;
}

// Aqui solo podrá mejorar un elemento de la solucion
std::vector<std::vector<double>> BusquedaLocal::BLSwap(const std::vector<std::vector<double>>& S) {
  std::vector<std::vector<double>> elem = CalcularElementosFueraDeS(S);
  double z = CalcularZ(S);
  double z_mejor = z;
  std::vector<std::vector<double>> S_mejor = S;
  for (int i = 0; i < S.size(); ++i) {
    for (int j = 0; j < elem.size(); ++j) {
        if (S[i] == elem[j]) continue;
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

// Aqui podra mejorar varios elementos de la solucion, pero actualizara con la primera mejora posible smp
std::vector<std::vector<double>> BusquedaLocal::BLSwapIterativoFirstImprovement(const std::vector<std::vector<double>>& S) {
  std::vector<std::vector<double>> elem = CalcularElementosFueraDeS(S);
  double z_actual = CalcularZ(S);
  std::vector<std::vector<double>> S_actual = S;
  bool mejora = true;
  while (mejora) {
    mejora = false;
    for (int i = 0; i < S_actual.size(); ++i) {
      for (int j = 0; j < elem.size(); ++j) {
        if (S[i] == elem[j]) continue;
        // Intercambiamos el elemento i de S por el elemento j de elem
        std::vector<std::vector<double>> S_temp = S_actual;
        S_temp[i] = elem[j];
        // Calculamos la nueva z
        double z_temp = CalcularZ(S_temp);
        if (z_temp > z_actual) {
          z_actual = z_temp;
          S_actual = S_temp;
          mejora = true;
          std::cout << "Mejorando la solucion: " << z_actual << std::endl;
          break; // Salimos del bucle interno
        }
      }
      if (mejora) break; // Salimos del bucle externo
    }
  }
  return S_actual;
}

// Aqui podra mejorar varios elementos de la solucion, y actualiza con la mejor mejora global
std::vector<std::vector<double>> BusquedaLocal::BLSwapIterativoBestImprovement(const std::vector<std::vector<double>>& S) {
  std::vector<std::vector<double>> elem = CalcularElementosFueraDeS(S);
  double z_actual = CalcularZ(S);
  std::vector<std::vector<double>> S_actual = S;
  double z_mejor = z_actual;
  std::vector<std::vector<double>> S_mejor = S_actual;
  bool mejora = true;
  while (mejora) {
    mejora = false;
    for (int i = 0; i < S.size(); ++i) {
      for (int j = 0; j < elem.size(); ++j) {
        if (S[i] == elem[j]) continue;
        // Intercambiamos el elemento i de S por el elemento j de elem
        std::vector<std::vector<double>> S_temp = S_actual;
        S_temp[i] = elem[j];
        // Calculamos la nueva z
        double z_temp = CalcularZ(S_temp);
        if (z_temp > z_mejor) {
          z_mejor = z_temp;
          S_mejor = S_temp;
          mejora = true;
          std::cout << "Mejorando la solucion: " << z_actual << std::endl;
        }
      }
    }
    // Guardamos el mejor cambio global
    S_actual = S_mejor;
    z_actual = z_mejor;
  }
  return S_actual;
}