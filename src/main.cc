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
#include "../include/model/ResolverMDP.h"
#include "../include/results/Tabla.h"
#include "../include/algorithm/GRASP.h"

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

void ImprimirTablas(ResolverMDP resolver, std::string fichero_salida) {
  // Crear objeto TablaVoraz
  Tabla* tabla = new TablaVoraz(fichero_salida, true);
  // Imprimir cabecera
  tabla->ImprimirCabecera();
  // Imprimir resultados
  tabla->ImprimirResultados(resolver.GetSolucionVoraz());

  // Crear objeto TablaGRASP
  tabla = new TablaGRASP(fichero_salida, false);
  // Imprimir cabecera
  tabla->ImprimirCabecera();
  // Imprimir resultados
  tabla->ImprimirResultados(resolver.GetSolucionGRASP());

}

// Ejecuta la instancia
void EjecutarInstancia(const std::string& fichero_entrada, std::string fichero_salida) {
  // Crear objeto DatosMDP
  DatosMDP datos(fichero_entrada);
  datos.SetM(3);
  ResolverMDP resolver(datos);
  resolver.ResolverVoraz();
  SolucionMDP* s = resolver.GetSolucionVoraz();
  std::cout << "Conjunto S: " << std::endl;
  for (const auto& elem : s->GetS()) {
    std::cout << "[ ";
    for (const auto& val : elem) {
      std::cout << val << " ";
    }
    std::cout << "]" << std::endl;
  }
  std::cout << "Z: " << s->GetZ() << std::endl;
  std::cout << "----------------------------------------" << std::endl;

  // GRASP
  resolver.ResolverGRASP(1, 1);
  SolucionMDP* s_grasp = resolver.GetSolucionGRASP();
  std::cout << "Conjunto S GRASP: " << std::endl;
  for (const auto& elem : s_grasp->GetS()) {
    std::cout << "[ ";
    for (const auto& val : elem) {
      std::cout << val << " ";
    }
    std::cout << "]" << std::endl;
  }
  std::cout << "Z: " << s_grasp->GetZ() << std::endl;
  std::cout << "----------------------------------------" << std::endl;

  ImprimirTablas(resolver, fichero_salida);

}

// Lee los ficheros de entrada y ejecuta los algoritmos
void LeerFicheros(int argc, char* argv[]) {
  std::string ruta_directorio{argv[1]};
  std::string fichero_salida{argv[2]};
  LectorDeInstancias gestor{ruta_directorio, fichero_salida};
  gestor.LeerNombresFicherosEntrada();
  int num_ficheros = gestor.GetFicherosEntrada().size();
  // TablaVoraz tabla_voraz("Cuadro 1: Algoritmo Voraz. Tabla de resultados");
  for (auto& fichero_entrada : gestor.GetFicherosEntrada()) {
    std::cout << "Ejecutando el fichero: " << fichero_entrada << std::endl;
    EjecutarInstancia(fichero_entrada, fichero_salida);
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