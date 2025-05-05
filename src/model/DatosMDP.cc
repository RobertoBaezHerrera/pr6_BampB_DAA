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
  fichero_entrada_ = fichero_entrada;
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

  // Matriz de distancias
  matriz_de_distancias_.resize(num_elementos_n_, std::vector<double>(num_elementos_n_));
  for (int i = 0; i < num_elementos_n_; ++i) {
    for (int j = i + 1; j < num_elementos_n_; ++j) {
        matriz_de_distancias_[i][j] = CalcularDistancia(conjunto_S_[i], conjunto_S_[j]);
        matriz_de_distancias_[j][i] = matriz_de_distancias_[i][j];
        // Actualizar la distancia máxima
        if (matriz_de_distancias_[i][j] > distancia_maxima_) {
          distancia_maxima_ = matriz_de_distancias_[i][j];
        }
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

int DatosMDP::GetTamanoConjuntoS() const {
  return conjunto_S_.size();
}

std::vector<std::vector<double>> DatosMDP::GetMatrizDistancia() const {
  return matriz_de_distancias_;
}

double DatosMDP::GetElementoMatrizDistancia(int i, int j) const {
  if (i < 0 || i >= num_elementos_n_ || j < 0 || j >= num_elementos_n_) {
    std::cerr << "Error: Índice fuera de rango en la matriz de distancias." << std::endl;
    return -1.0; // Valor de error
  }
  return matriz_de_distancias_[i][j];
}

void DatosMDP::AnadirElementoAConjuntoS(const std::vector<double>& elemento) {
  conjunto_S_.push_back(elemento);
}

double DatosMDP::CalcularDistancia(const std::vector<double>& Si, const std::vector<double>& centro_gravedad) const {
  double distancia = 0.0;
  for (int i = 0; i < Si.size(); ++i) {
    distancia += (Si[i] - centro_gravedad[i]) * (Si[i] - centro_gravedad[i]);
  }
  return sqrt(distancia);
}

std::string DatosMDP::GetFicheroEntrada() const {
  return fichero_entrada_;
}

double DatosMDP::GetDistanciaMaxima() const {
  return distancia_maxima_;
}




void DatosMDP::SetM(int m) {
  m_ = m;
}

void DatosMDP::VaciarConjuntoS() {
  conjunto_S_.clear();
  conjunto_S_.resize(num_elementos_n_);
}

double DatosMDP::CalcularZ(const std::vector<std::vector<double>>& S) const {
  double z = 0.0;
  for (int i = 0; i < S.size(); ++i) {
    for (int j = i + 1; j < S.size(); ++j) {
      z += CalcularDistancia(S[i], S[j]);
    }
  }
  return z;
}