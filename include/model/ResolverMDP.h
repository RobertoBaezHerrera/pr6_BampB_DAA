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
#include "../algorithm/RamificacionYPoda.h"

class ResolverMDP {
 public:
  ResolverMDP(const DatosMDP& datos);

  // Método para resolver el problema MDP
  void ResolverVoraz();
  // Método para resolver el problema MDP con Voraz y Busqueda Local
  void ResolverVorazConBusquedaLocal();
  // Método para resolver el problema MDP con GRASP
  void ResolverGRASP(int LRC, int iteraciones = 10);
  // Método para resolver el problema MDP con Ramificación y Poda
  void ResolverRamificacionYPoda(double cota_inferior, int m);

  // Getters
  SolucionMDP* GetSolucionVoraz() const { return solucion_voraz_; }
  SolucionMDP* GetSolucionGRASP() const { return solucion_grasp_; }
  SolucionMDP* GetSolucionRamificacionYPoda() const { return solucion_ramificacion_y_poda_; }

  // Método para liberar la memoria de las soluciones
  void LiberarMemoria();

 private:
  DatosMDP datos_;
  SolucionMDP* solucion_voraz_;
  SolucionMDP* solucion_grasp_;
  SolucionMDP* solucion_ramificacion_y_poda_;
};