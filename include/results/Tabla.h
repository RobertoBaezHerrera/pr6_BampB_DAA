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
#include <fstream>
#include <iomanip>
#include <vector>

#include "../results/SolucionMDP.h"

class Tabla {
 public:
  Tabla(const std::string& fichero_salida, bool primera_vez);
  virtual void ImprimirCabecera() = 0;
  virtual void ImprimirResultados(SolucionMDP* s) = 0;

 protected:
  std::ofstream fichero_salida_;
};

class TablaVoraz : public Tabla {
 public:
  TablaVoraz(const std::string& fichero_salida, bool primera_vez = true);
  void ImprimirCabecera() override;
  void ImprimirResultados(SolucionMDP* s) override;
};

class TablaGRASP : public Tabla {
 public:
  TablaGRASP(const std::string& fichero_salida, bool primera_vez = false);
  void ImprimirCabecera() override;
  void ImprimirResultados(SolucionMDP* s) override;
};