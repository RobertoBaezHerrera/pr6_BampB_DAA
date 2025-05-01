/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Asignatura: Diseño y Análisis de Algoritmos
  * @author Roberto Báez Herrera, a Fayna Cruz Galván
  * Correo: alu0101497013@ull.edu.es, alu0101477497@ull.edu.es
  * @date 18/03/2025
  */

  #include <iostream>
  #include <string>
  #include <dirent.h>
  #include <algorithm>
  #include <limits>
  
  #include "../../include/io/LectorDeInstancias.h"
  
  LectorDeInstancias::LectorDeInstancias(std::string ruta_directorio, std::string fichero_salida) {
    ruta_directorio_ = ruta_directorio;
    fichero_salida_ = fichero_salida;
  }
  
void LectorDeInstancias::LeerNombresFicherosEntrada() {
    std::string cada_fichero;
    // Abrir el directorio y leer los nombres de los ficheros
    DIR* directorio = opendir(ruta_directorio_.c_str());
    struct dirent* archivo;
    if (directorio) {
        while ((archivo = readdir(directorio)) != NULL) {
            cada_fichero = archivo->d_name;
            // Excluir las entradas especiales "." y ".."
            if (cada_fichero != "." && cada_fichero != "..") {
                cada_fichero = ruta_directorio_ + "/" + cada_fichero;
                ficheros_entrada_.push_back(cada_fichero);
            }
        }
        closedir(directorio);
    }

    // Ordenar por orden natural (numérico) basado en el nuevo formato
    std::sort(ficheros_entrada_.begin(), ficheros_entrada_.end(), [](const std::string& a, const std::string& b) {
        auto extraer_numeros = [](const std::string& nombre) -> std::pair<int, int> {
            size_t pos = nombre.find("max_div_");
            if (pos == std::string::npos) return {std::numeric_limits<int>::max(), std::numeric_limits<int>::max()};
    
            pos += 8;  // Después de "max_div_"
            size_t guion1 = nombre.find('_', pos);
            if (guion1 == std::string::npos) return {std::numeric_limits<int>::max(), std::numeric_limits<int>::max()};
    
            int n = std::stoi(nombre.substr(pos, guion1 - pos));
    
            size_t pos2 = guion1 + 1;
            size_t punto = nombre.find('.', pos2); // Hasta antes de .txt
            if (punto == std::string::npos) punto = nombre.length();
            int k = std::stoi(nombre.substr(pos2, punto - pos2));
    
            return {n, k};
        };
    
        return extraer_numeros(a) < extraer_numeros(b);
    });
    
}