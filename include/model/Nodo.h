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
 #include <string>
 #include <vector>
 #include <cmath>

class Nodo {
 public:
  Nodo(const std::vector<std::vector<double>>& parcial,
       const std::vector<std::vector<double>>& restantes, double c_sup);
  // Constructor de copia
  Nodo(const Nodo& nodo) = default;

  //Getters
  std::vector<std::vector<double>> GetSolucionParcial() const;
  std::vector<std::vector<double>> GetCandidatosRestantes() const;
  double GetCotaSuperior() const;
  //double GetCotaInferior() const;

  // Orden inverso para priority_queue (máximo en la parte superior)
  bool operator<(const Nodo& other) const;

 private:
 std::vector<std::vector<double>> solucion_parcial;  // elementos ya elegidos
 std::vector<std::vector<double>> candidatos_restantes;  // candidatos que faltan por probar
 double cota_superior;
 //double cota_inferior;
};
