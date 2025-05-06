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

#include "../model/DatosMDP.h"
#include "../algorithm/Voraz.h"

class BusquedaLocal : public AlgoritmoVoraz {
 public:
  BusquedaLocal(const DatosMDP& datos);
  std::vector<std::vector<double>> CalcularElementosFueraDeS(const std::vector<std::vector<double>>& S);
  std::vector<std::vector<double>> BLSwap(const std::vector<std::vector<double>>& S);
  std::vector<std::vector<double>> BLSwapIterativoFirstImprovement(const std::vector<std::vector<double>>& S);
    std::vector<std::vector<double>> BLSwapIterativoBestImprovement(const std::vector<std::vector<double>>& S);
};