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
        // Extraer el número de la instancia basado en el nuevo formato
        auto get_number = [](const std::string& filename) -> int {
            size_t pos = filename.find("max_div_");
            if (pos == std::string::npos) {
                // Si no se encuentra "max_div_", devolver un número alto para que quede al final
                return std::numeric_limits<int>::max();
            }
            pos += 8; // Avanzar 8 caracteres después de "max_div_"
            size_t end = filename.find('_', pos); // Buscar el siguiente guion bajo '_'
            if (end == std::string::npos) {
                // Si no se encuentra el guion bajo, devolver un número alto
                return std::numeric_limits<int>::max();
            }
            return std::stoi(filename.substr(pos, end - pos));
        };

        return get_number(a) < get_number(b);
    });
}