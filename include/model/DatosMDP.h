/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos
 * @author Roberto Báez Herrera
 * Correo: alu0101497013@ull.edu.es, alu0101477497@ull.edu.es
 * @date 29/04/2025
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>

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

  // Setters
  void SetM(int m);
  void VaciarConjuntoS();

  void AnadirElementoAConjuntoS(const std::vector<double>& elemento);

 private:
  int num_elementos_n_;
  int dimension_K_;
  std::vector<std::vector<double>> conjunto_S_;
  int m_ = 0;
};