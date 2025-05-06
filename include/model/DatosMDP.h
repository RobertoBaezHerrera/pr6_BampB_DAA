/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos
 * @author Roberto Báez Herrera
 * Correo: alu0101497013@ull.edu.es, alu0101477497@ull.edu.es
 * @date 06/05/2025
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// Clase DatosMDP que almacena los datos de la instancia
class DatosMDP {
 public:
  DatosMDP(const std::string& fichero_entrada);

  // Getters
  int GetNumElementosN() const;
  int GetDimensionK() const;
  std::vector<std::vector<double>> GetConjuntoS() const;
  int GetM() const;
  int GetTamanoConjuntoS() const;
  std::string GetFicheroEntrada() const;
  std::vector<std::vector<double>> GetMatrizDistancia() const;
  double GetElementoMatrizDistancia(int i, int j) const;
  double GetDistanciaMaxima() const;

  // Setters
  void SetM(int m);
  void VaciarConjuntoS();

  void AnadirElementoAConjuntoS(const std::vector<double>& elemento);
  double CalcularDistancia(const std::vector<double>& Si, const std::vector<double>& centro_gravedad) const;
  double CalcularZ(const std::vector<std::vector<double>>& solucion) const;

 private:
  int num_elementos_n_;
  int dimension_K_;
  std::vector<std::vector<double>> conjunto_S_;
  int m_ = 0;
  std::string fichero_entrada_;
  std::vector<std::vector<double>> matriz_de_distancias_;
  double distancia_maxima_ = 0.0;
};