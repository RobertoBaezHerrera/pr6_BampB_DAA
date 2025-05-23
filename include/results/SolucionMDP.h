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

#include "../model/DatosMDP.h"

class SolucionMDP {
 public:
  SolucionMDP() = default;
  SolucionMDP(const std::vector<std::vector<double>>& S, double z, double cpu,
              const std::string& fichero_entrada, int n, int k, int m, DatosMDP datos);
  
  // Getters
  std::vector<std::vector<double>> GetS() const;
  double GetZ() const;
  double GetCPU() const;
  std::string GetFicheroEntrada() const;
  int GetN() const;
  int GetK() const;
  int GetM() const;
  DatosMDP GetDatos() const;

 protected:
  std::vector<std::vector<double>> S_;
  double z_;
  double cpu_;
  std::string fichero_entrada_;
  int n_;
  int k_;
  int m_;
  DatosMDP datos_;
};

class SolucionVoraz : public SolucionMDP {
 public:
  SolucionVoraz() = default;
  SolucionVoraz(const std::vector<std::vector<double>>& S, double z, double cpu,
                const std::string& fichero_entrada, int n, int k, int m, DatosMDP datos) 
                : SolucionMDP(S, z, cpu, fichero_entrada, n, m, k, datos) { }
};

class SolucionGRASP : public SolucionMDP {
 public:
  SolucionGRASP() = default;
  SolucionGRASP(const std::vector<std::vector<double>>& S, double z, double cpu,
                const std::string& fichero_entrada, int n, int k, int m, DatosMDP datos, int iteraciones, int LRC);

  // Getters
  int GetIteraciones() const { return iteraciones_; }
  int GetLRC() const { return LRC_; }
 private:
  int iteraciones_;
  int LRC_;
};

class SolucionRamificacionYPoda : public SolucionMDP {
 public:
  SolucionRamificacionYPoda() = default;
  SolucionRamificacionYPoda(const std::vector<std::vector<double>>& S, double z, double cpu,
                            const std::string& fichero_entrada, int n, int k, int m, DatosMDP datos, int nodos_generados);

  // Getters
  int GetNodosGenerados() const { return nodos_generados_; }
 private:
  int nodos_generados_;
};