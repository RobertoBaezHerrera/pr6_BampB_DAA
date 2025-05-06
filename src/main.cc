/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Grado en Ingeniería Informática
 * Asignatura: Diseño y Análisis de Algoritmos
 * @author Roberto Báez Herrera
 * Correo: alu0101497013@ull.edu.es, alu0101477497@ull.edu.es
 * @date 06/05/2025
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

bool primera_ejecucion = true;

// Texto de ayuda
const std::string kTextoAyuda =
    "Uso: pr6_VRPT <ruta_directorio> <fichero_salida.txt>\n\n"
    "Encuentra la máxima diversidad entre vecrores de varias formas diferentes: "
    "utilizando voraz, GRASP y ramificación y poda.\n"
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

/* void ImprimirTablas(ResolverMDP resolver, std::string fichero_salida) {
  // Imprimir TablaVoraz
  Tabla* tabla = new TablaVoraz(fichero_salida, primera_ejecucion);
  tabla->ImprimirCabecera();
  tabla->ImprimirResultados(resolver.GetSolucionVoraz());

  // Imprimir TablaGRASP
  tabla = new TablaGRASP(fichero_salida, false);
  tabla->ImprimirCabecera();
  tabla->ImprimirResultados(resolver.GetSolucionGRASP());
} */

void EjecutarVoraz(const std::string& fichero_entrada, Tabla* tabla, bool busqueda_local = false) {
  for (int m = 2; m <= 5; ++m) {
    // Crear objeto DatosMDP
    DatosMDP datos(fichero_entrada);
    datos.SetM(m);
    ResolverMDP resolver(datos);
    if (busqueda_local) {
      resolver.ResolverVorazConBusquedaLocal();
    } else {
      resolver.ResolverVoraz();
    }
    tabla->ImprimirResultados(resolver.GetSolucionVoraz());
    //resolver.LiberarMemoria();
  }
  tabla->ImprimirLineaSeparadora();
  /* // Impresion de S por voraz
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
  std::cout << "----------------------------------------" << std::endl; */
}

void EjecutarGRASP(const std::string& fichero_entrada, Tabla* tabla) {
  for (int m = 2; m <= 5; ++m) {
    for (int iter = 1; iter <= 2; ++iter) {
      for (int LRC = 2; LRC <= 3; ++LRC) {
        // Crear objeto DatosMDP
        DatosMDP datos(fichero_entrada);
        datos.SetM(m);
        ResolverMDP resolver(datos);
        int iteraciones = 10;
        resolver.ResolverGRASP(LRC, iteraciones * iter);
        tabla->ImprimirResultados(resolver.GetSolucionGRASP());
        //resolver.LiberarMemoria();
      }
    }
  }
  tabla->ImprimirLineaSeparadora();
}

void EjecutarRamificacionYPodaVoraz(const std::string& fichero_entrada, Tabla* tabla) {
  std::cout << "Ejecutando Ramificacion y Poda Voraz..." << std::endl;
  for (int m = 2; m <= 5; ++m) {
    // Crear objeto DatosMDP
    DatosMDP datos(fichero_entrada);
    datos.SetM(m);
    ResolverMDP resolver(datos);
    resolver.ResolverVoraz();
    double resultado = resolver.GetSolucionVoraz()->GetZ();
    RamificacionYPoda ramificacion(datos);
    // Medir tiempo de CPU
    double inicio = clock();
    std::vector<std::vector<double>> S = ramificacion.Ejecutar(resultado);
    double fin = clock();
    double cpu = (fin - inicio) / CLOCKS_PER_SEC;
    if (S.empty()) S = resolver.GetSolucionVoraz()->GetS();
    double z = datos.CalcularZ(S);
    SolucionMDP* s = new SolucionRamificacionYPoda(S, z, cpu, datos.GetFicheroEntrada(), datos.GetNumElementosN(),
        datos.GetDimensionK(), datos.GetM(), datos, ramificacion.GetNodosGenerados());
    tabla->ImprimirResultados(s);
    //resolver.LiberarMemoria();
  }
  tabla->ImprimirLineaSeparadora();
}

void EjecutarRamificacionYPodaGRASP(const std::string& fichero_entrada, Tabla* tabla) {
  std::cout << "Ejecutando Ramificacion y Poda GRASP..." << std::endl;
  for (int m = 2; m <= 5; ++m) {
    for (int iter = 1; iter <= 2; ++iter) {
      for (int LRC = 2; LRC <= 3; ++LRC) {
        // Crear objeto DatosMDP
        DatosMDP datos(fichero_entrada);
        datos.SetM(m);
        ResolverMDP resolver(datos);
        int iteraciones = 10;
        resolver.ResolverGRASP(LRC, iteraciones * iter);
        double resultado = resolver.GetSolucionGRASP()->GetZ();
        RamificacionYPoda ramificacion(datos);
        // Medir tiempo de CPU
        double inicio = clock();
        std::vector<std::vector<double>> S = ramificacion.Ejecutar(resultado);
        double fin = clock();
        double cpu = (fin - inicio) / CLOCKS_PER_SEC;
        if (S.empty()) S = resolver.GetSolucionGRASP()->GetS();
        double z = datos.CalcularZ(S);
        SolucionMDP* s = new SolucionRamificacionYPoda(S, z, cpu, datos.GetFicheroEntrada(), datos.GetNumElementosN(),
            datos.GetDimensionK(), datos.GetM(), datos, ramificacion.GetNodosGenerados());
        tabla->ImprimirResultados(s);

        //resolver.LiberarMemoria();
      }
    }
  }
  tabla->ImprimirLineaSeparadora();
}

// Lee los ficheros de entrada y ejecuta los algoritmos
void LeerFicheros(int argc, char* argv[], int opcion) {
  std::string ruta_directorio{argv[1]};
  std::string fichero_salida{argv[2]};
  LectorDeInstancias gestor{ruta_directorio, fichero_salida};
  gestor.LeerNombresFicherosEntrada();
  int num_ficheros = gestor.GetFicherosEntrada().size();
  Tabla* tabla = nullptr;
  if (opcion == 1 || opcion == 2) {
    tabla = new TablaVoraz(fichero_salida);
  } else if (opcion == 3) {
    tabla = new TablaGRASP(fichero_salida);
  } else if (opcion == 4 || opcion == 5) {
    tabla = new TablaRamificacionYPoda(fichero_salida);
  }
  bool busqueda_local;
  // Si la opción es 2, se activa la búsqueda local para el algoritmo Voraz
  opcion == 2 ? busqueda_local = true : busqueda_local = false;
  tabla->ImprimirCabecera();
  for (auto& fichero_entrada : gestor.GetFicherosEntrada()) {
    std::cout << "\033[1;33mEjecutando el fichero: " << fichero_entrada << "\033[0m" << std::endl;
    if (opcion == 1 || opcion == 2) {
      EjecutarVoraz(fichero_entrada, tabla, busqueda_local);
    } else if (opcion == 3) {
      EjecutarGRASP(fichero_entrada, tabla);
    } else if (opcion == 4) {
      EjecutarRamificacionYPodaVoraz(fichero_entrada, tabla);
    } else if (opcion == 5) {
      EjecutarRamificacionYPodaGRASP(fichero_entrada, tabla);
    } else {
      std::cout << "Opción no válida." << std::endl;
    }
    //break;
  }
  std::cout << "Numero de ficheros definidos: " << num_ficheros << std::endl;
  delete tabla;
  return;
}

int MenuOpciones() {
  int opcion = 0;
  std::cout << "Seleccione una opción: " << std::endl;
  std::cout << "1. Resolver mediante VORAZ" << std::endl;
  std::cout << "2. Resolver mediante VORAZ y Busqueda Local" << std::endl;
  std::cout << "3. Resolver mediante GRASP" << std::endl;
  std::cout << "4. Resolver mediante Ramificacion y Poda con la cota inferior del Voraz" << std::endl;
  std::cout << "5. Resolver mediante Ramificacion y Poda con la cota inferior del GRASP" << std::endl;
  std::cout << "0. Salir" << std::endl;
  std::cin >> opcion;
  return opcion;
}

void EjecutarPrograma(int opcion, int argc, char* argv[]) {
  switch (opcion) {
    case 0:
      std::cout << "Saliendo del programa...." << std::endl;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
      LeerFicheros(argc, argv, opcion);
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