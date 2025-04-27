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

class ResolverMDP {
 public:
  ResolverMDP(const DatosMDP& datos) : datos_(datos) { };

  // Método para resolver el problema MDP
  void ResolverVoraz(int m);

 private:
  DatosMDP datos_;
};