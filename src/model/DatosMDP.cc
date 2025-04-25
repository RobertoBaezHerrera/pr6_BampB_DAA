/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos
 * @author Roberto Báez Herrera
 * Correo: alu0101497013@ull.edu.es, alu0101477497@ull.edu.es
 * @date 29/04/2025
 */

#include "../include/model/DatosMDP.h"

#include <fstream>
#include <iostream>

DatosMDP::DatosMDP(const std::string& fichero_entrada) {
  std::ifstream fichero(fichero_entrada);
  if (!fichero.is_open()) {
    std::cerr << "Error: No se puede abrir el fichero " << fichero_entrada << std::endl;
    exit(EXIT_FAILURE);
  }
  fichero >> num_elementos_n_;
  fichero >> dimension_K_;
  conjunto_S_.resize(num_elementos_n_);
  for (int i = 0; i < num_elementos_n_; ++i) {
    for (int j = 0; j < dimension_K_; ++j) {
    double entero, decimal;
    char separator;
    fichero >> entero >> separator >> decimal;
    conjunto_S_[i].push_back(entero + 0.01 * decimal);
    }
  }
}

// Getters
std::vector<std::vector<double>> DatosMDP::GetConjuntoS() const {
  return conjunto_S_;
}

int DatosMDP::GetNumElementosN() const {
  return num_elementos_n_;
}

int DatosMDP::GetDimensionK() const {
  return dimension_K_;
}

int DatosMDP::GetM() const {
  return m_;
}