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
  #include <chrono>
  
  #include "../include/utils/GestorArchivos.h"
  /*#include "../include/DatosVRPT.h"
  #include "../include/BusquedasLocales/ContextoBusquedaLocal.h"
  #include "../include/BusquedasLocales/ReInsercionIntra.h"
  #include "../include/BusquedasLocales/ReInsercionInter.h"
  #include "../include/BusquedasLocales/SwapIntra.h"
  #include "../include/BusquedasLocales/SwapInter.h"
  #include "../include/AlgoritmosConstructivos.h"
  #include "../include/GVNS.h"
  #include "../include/Tablas/TablaVoraz.h"
  #include "../include/Tablas/TablaGRASP.h"
  #include "../include/Tablas/TablaGVNS.h" */
  
  // Texto de ayuda
  const std::string kTextoAyuda = "Uso: pr5_VRPT <ruta_directorio> <fichero_salida.txt>\n\n"
      "Encuentra la ruta óptima de 3 formas diferentes: voraz, GRASP y GVNS.\n"
      "Obtiene los grafos de los ficheros de entrada que estánn el la ruta del directorio.\n"
      "Además, imprime los resultados en un fichero de salida.\n"
      "Opciones: \n"
      "  --help \t\t Muestra la ayuda. \n"
      "  <ruta_directorio> <fichero_salida.txt> \t ";
  
  // Según la entrada, muestra la ayuda y comprobar los parametros
  void Usage(int argc, char* argv[]) {
      if (argc == 2) {
        std::string parametro{argv[1]};
        if (parametro == "--help") {
          std::cout << kTextoAyuda << std::endl;
          exit(EXIT_SUCCESS);
        } else {
          std::cout << argv[0] << ": Error: Parámetro '" << parametro << "' no reconocido." << std::endl;
          std::cout << "Pruebe '" << argv[0] << " --help' para más información." << std::endl;
          exit(EXIT_SUCCESS);
        }
      } else if (argc != 4) {
        std::cout << argv[0] << ": Error: Numero de parámetros incorrectos." << std::endl;
        std::cout << "Pruebe '" << argv[0] << " --help' para más información." << std::endl;
        exit(EXIT_SUCCESS);
      }
  }
   
  
  // Ejecuta los algoritmos y los imprime en la tabla
  void EjecutarAlgorimtos(std::string fichero_entrada, double& promedio_vehiculos_recoleccion, double& promedio_vehiculos_transporte) {
    /* DatosVRPT datos(fichero_entrada);
    AlgoritmosConstructivos algoritmo(datos);
    algoritmo.CalcularRutasRecoleccionGreedy();
    algoritmo.CalcularRutasTransporte();
    
    // Calcular la ruta GRASP seleccionando la mejor ruta de x iteraciones
    std::vector<std::vector<std::string>> ruta_GRASP;
    std::vector<VehiculoRecoleccion> vehiculos_GRASP;
    std::cout << std::endl << std::endl;
    algoritmo.GRASP(3);
    ruta_GRASP = datos.GetRutasGRASP();
    vehiculos_GRASP = datos.GetCV_GRASP();
    datos.ImprimirRutas();
    std::cout << "Tiempo total de la ruta GRASP: " << datos.CalcularTiempoTotalRutasGRASP() << std::endl;
    promedio_vehiculos_recoleccion += datos.GetRutasCV().size();
    promedio_vehiculos_transporte += datos.GetRutasTV().size(); */
  }
  
  // Lee los ficheros de entrada y ejecuta los algoritmos
  void LeerFicheros(int argc, char* argv[]) {
    std::string ruta_directorio{argv[1]};
    std::string fichero_salida{argv[2]};
    GestorArchivos gestor{ruta_directorio, fichero_salida};
    gestor.LeerNombresFicherosEntrada();
    double promedio_vehiculos_recoleccion = 0, promedio_vehiculos_transporte = 0;
    int num_ficheros = 9;
    //TablaVoraz tabla_voraz("Cuadro 1: Algoritmo Voraz. Tabla de resultados");
    for (auto& fichero : gestor.GetFicherosEntrada()) {
      EjecutarAlgorimtos(fichero, promedio_vehiculos_recoleccion, promedio_vehiculos_transporte);
      //break;
    }
    std::cout << "Numero de ficheros definidos: " << num_ficheros << std::endl;
    promedio_vehiculos_recoleccion /= gestor.GetFicherosEntrada().size();
    promedio_vehiculos_transporte /= gestor.GetFicherosEntrada().size();
    std::cout << "Promedio de vehiculos de recoleccion: " << promedio_vehiculos_recoleccion << std::endl;
    std::cout << "Promedio de vehiculos de transporte: " << promedio_vehiculos_transporte << std::endl;
  
    return;
  }
  
  // Programa principal
  int main(int argc, char* argv[]) {
      Usage(argc, argv);
      // Inicilizar semilla aleatoria
      srand(time(nullptr));
      int opcion = std::stoi(argv[3]);
      switch (opcion) {
      case 3:
        LeerFicheros(argc, argv);
        break;
      default:
        break;
      }
      return 0;
  }