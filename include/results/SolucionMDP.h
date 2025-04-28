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
#include <vector>

class SolucionMDP {
 public:
  SolucionMDP() = default;
  SolucionMDP(const std::vector<std::vector<double>>& S, double z, double cpu,
              const std::string& fichero_entrada, int n, int k, int m);
  
  // Getters
  std::vector<std::vector<double>> GetS() const;
  double GetZ() const;
  double GetCPU() const;
  std::string GetFicheroEntrada() const;
  int GetN() const;
  int GetK() const;
  int GetM() const;

 protected:
  std::vector<std::vector<double>> S_;
  double z_;
  double cpu_;
  std::string fichero_entrada_;
  int n_;
  int k_;
  int m_;
};

class SolucionVoraz : public SolucionMDP {
 public:
  SolucionVoraz() = default;
  SolucionVoraz(const std::vector<std::vector<double>>& S, double z, double cpu,
                const std::string& fichero_entrada, int n, int k, int m) 
                : SolucionMDP(S, z, cpu, fichero_entrada, n, m, k) { }
};

class SolucionGRASP : public SolucionMDP {
 public:
  SolucionGRASP() = default;
  SolucionGRASP(const std::vector<std::vector<double>>& S, double z, double cpu,
                const std::string& fichero_entrada, int n, int k, int m, int iteraciones, int LRC);

  // Getters
  int GetIteraciones() const { return iteraciones_; }
  int GetLRC() const { return LRC_; }
 private:
  int iteraciones_;
  int LRC_;
};