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

#include "../model/DatosMDP.h"

class AlgoritmoVoraz {
 public:
  AlgoritmoVoraz(const DatosMDP& datos);
  void Ejecutar();
  void ImprimirResultados() const;

 private:
  double CalcularDiversidad(const std::vector<int>& solucion) const;
  void ImprimirSolucion(const std::vector<int>& solucion) const;

  DatosMDP datos_;
  std::vector<int> mejor_solucion_;
  double mejor_diversidad_ = -1.0;
};