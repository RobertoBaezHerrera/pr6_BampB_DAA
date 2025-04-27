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

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

class AlgoritmoVoraz {
 public:
  AlgoritmoVoraz(const DatosMDP& datos);
  std::vector<std::vector<double>> EjecutarVoraz();
  std::vector<double> CalcularCentroGravedad(const std::vector<std::vector<double>>& elem);
  double CalcularDistancia(const std::vector<double>& Si, const std::vector<double>& centro_gravedad) const;
  int CalcularElementoMasAlejado(const std::vector<std::vector<double>>& elem, const std::vector<double>& centro_gravedad) const;
  double CalcularZ(const std::vector<std::vector<double>>& S) const;

 protected:
  DatosMDP datos_;
};