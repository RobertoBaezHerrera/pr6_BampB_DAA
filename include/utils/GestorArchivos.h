/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Diseño y Análisis de Algoritmos
  * @author Roberto Báez Herrera
  * Correo: alu0101497013@ull.edu.es, alu0101477497@ull.edu.es
  * @date 18/03/2025
  */

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

// Clase que obtiene los nombres de los ficheros de entrada dada una ruta
class GestorArchivos {
 public:
  GestorArchivos(std::string ruta_directorio, std::string fichero_salida);
  void EscribirTabla(/*CalcularTSP resultado*/);
  void LeerNombresFicherosEntrada();
  std::vector<std::string> GetFicherosEntrada() const { return ficheros_entrada_; }


  ~GestorArchivos() = default;
 private:
  std::vector<std::string> ficheros_entrada_;
  std::string fichero_salida_;
  std::string ruta_directorio_;
  int numero_ficheros_;
};