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

#include <cmath>
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

#include "../algorithm/Voraz.h"
#include "../model/DatosMDP.h"
#include "../algorithm/BusquedaLocal.h"

class AlgoritmoGRASP : public AlgoritmoVoraz {
 public:
  AlgoritmoGRASP(const DatosMDP& datos);
  std::vector<int> CalcularElementosMasAlejados(const std::vector<std::vector<double>>& elem, const std::vector<double>& centro_gravedad, int LRC) const;
  std::vector<std::vector<double>> EjecutarVorazAleatorio(int LRC);
  std::vector<std::vector<double>> EjecutarGRASP(int LRC, int iteraciones = 10);
};