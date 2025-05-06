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

#include <queue>
#include <vector>
#include <algorithm>

#include "../model/DatosMDP.h"
#include "../model/Nodo.h"

class RamificacionYPoda {
 public:
  RamificacionYPoda(const DatosMDP& datos);
  std::vector<std::vector<double>> Ejecutar(const double resultado_voraz);

  // Getters
  int GetNodosGenerados() const { return nodos_generados_; }

  double CalcularCotaInferior(const std::vector<std::vector<double>>& solucion_parcial);
  double CalcularCotaSuperior(const std::vector<std::vector<double>>& solucion_parcial,
      const std::vector<std::vector<double>>& candidatos_restantes);
  std::vector<Nodo> Expandir(const Nodo& nodo);

 private:
  const DatosMDP& datos_;
  int m_;  // Tamaño solución objetivo
  int nodos_generados_ = 0;  // Contador de nodos generados
};
