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
#include "../results/SolucionMDP.h"
#include "../algorithm/GRASP.h"

class ResolverMDP {
 public:
  ResolverMDP(const DatosMDP& datos);

  // Método para resolver el problema MDP
  void ResolverVoraz();
  // Método para resolver el problema MDP con Voraz y Busqueda Local
  void ResolverVorazConBusquedaLocal();
  // Método para resolver el problema MDP con GRASP
  void ResolverGRASP(int LRC, int iteraciones = 10);

  // Getters
  SolucionMDP* GetSolucionVoraz() const { return solucion_voraz_; }
  SolucionMDP* GetSolucionGRASP() const { return solucion_grasp_; }

 private:
  DatosMDP datos_;
  SolucionMDP* solucion_voraz_;
  SolucionGRASP* solucion_grasp_;
};