/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos
 * @author Roberto Báez Herrera
 * Correo: alu0101497013@ull.edu.es, alu0101477497@ull.edu.es
 * @date 29/04/2025
 */

#include <iostream>
#include <string>
#include <vector>

#include "../include/io/LectorDeInstancias.h"
#include "../include/model/DatosMDP.h"
#include "../include/algorithm/Voraz.h"

// Texto de ayuda
const std::string kTextoAyuda =
    "Uso: pr6_VRPT <ruta_directorio> <fichero_salida.txt>\n\n"
    "Encuentra la máxima diversidad entre vecrores de 2 formas diferentes: "
    "voraz y GRASP.\n"
    "Obtiene los vectores de los ficheros de entrada que están el la ruta del "
    "directorio.\n"
    "Además, imprime los resultados en un fichero de salida.\n"
    "Opciones: \n"
    "  --help \t\t Muestra la ayuda. \n"
    "  <ruta_directorio> <fichero_salida.txt>\t ";

// Según la entrada, muestra la ayuda y comprobar los parametros
void Usage(int argc, char* argv[]) {
  if (argc == 2) {
    std::string parametro{argv[1]};
    if (parametro == "--help") {
      std::cout << kTextoAyuda << std::endl;
      exit(EXIT_SUCCESS);
    } else {
      std::cout << argv[0] << ": Error: Parámetro '" << parametro
                << "' no reconocido." << std::endl;
      std::cout << "Pruebe '" << argv[0] << " --help' para más información."
                << std::endl;
      exit(EXIT_SUCCESS);
    }
  } else if (argc != 3) {
    std::cout << argv[0] << ": Error: Numero de parámetros incorrectos."
              << std::endl;
    std::cout << "Pruebe '" << argv[0] << " --help' para más información."
              << std::endl;
    exit(EXIT_SUCCESS);
  }
}

// Ejecuta la instancia
void EjecutarInstancia(const std::string& fichero) {
  // Crear objeto DatosMDP
  DatosMDP datos(fichero);
  AlgoritmoVoraz voraz(datos);
  std::vector<std::vector<double>> S = voraz.EjecutarVoraz(3);

  // Crear objeto AlgoritmoVoraz
  /* AlgoritmoVoraz algoritmo_voraz(datos);
  // Ejecutar el algoritmo voraz
  algoritmo_voraz.Ejecutar();
  // Crear objeto AlgoritmoGRASP
  AlgoritmoGRASP algoritmo_grasp(datos);
  // Ejecutar el algoritmo GRASP
  algoritmo_grasp.Ejecutar(); */
}

// Lee los ficheros de entrada y ejecuta los algoritmos
void LeerFicheros(int argc, char* argv[]) {
  std::string ruta_directorio{argv[1]};
  std::string fichero_salida{argv[2]};
  LectorDeInstancias gestor{ruta_directorio, fichero_salida};
  gestor.LeerNombresFicherosEntrada();
  int num_ficheros = gestor.GetFicherosEntrada().size();
  // TablaVoraz tabla_voraz("Cuadro 1: Algoritmo Voraz. Tabla de resultados");
  for (auto& fichero : gestor.GetFicherosEntrada()) {
    EjecutarInstancia(fichero);
    break;
  }
  std::cout << "Numero de ficheros definidos: " << num_ficheros << std::endl;
  return;
}

int MenuOpciones() {
  int opcion = 0;
  std::cout << "Seleccione una opción: " << std::endl;
  std::cout << "1. Leer ficheros de entrada" << std::endl;
  std::cout << "0. Salir" << std::endl;
  std::cin >> opcion;
  return opcion;
}

void EjecutarPrograma(int opcion, int argc, char* argv[]) {
  switch (opcion) {
    case 0:
      std::cout << "Saliendo del programa...." << std::endl;
    case 1:
      LeerFicheros(argc, argv);
      break;
    default:
      std::cout << argv[0] << ": Error: Opción '" << argv[3]
                << "' no reconocida." << std::endl;
      std::cout << "Pruebe '" << argv[0] << " --help' para más información." << std::endl;
      break;
  }
}

// Programa principal
int main(int argc, char* argv[]) {
  Usage(argc, argv);
  // Inicilizar semilla aleatoria
  srand(time(nullptr));
  int opcion = MenuOpciones();
  EjecutarPrograma(opcion, argc, argv);
  std::cout << "\033[1;32m-----------------------------FIN DEL PROGRAMA-----------------------------\033[0m" << std::endl;
  return 0;
}