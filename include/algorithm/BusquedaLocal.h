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

#include "../model/DatosMDP.h"
#include "../algorithm/Voraz.h"

class BusquedaLocal : public AlgoritmoVoraz {
 public:
  BusquedaLocal(const DatosMDP& datos);
  std::vector<std::vector<double>> BLSwap(const std::vector<std::vector<double>>& S);
};