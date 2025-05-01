#include "../include/results/Tabla.h"

const std::string kSeparador = "____________________________________________________________________________________________________________________________________________";

Tabla::Tabla(const std::string& fichero_salida, bool primera_vez) {
  if (primera_vez) {
    // Abrir en modo de sobrescritura para borrar el contenido existente
    fichero_salida_.open(fichero_salida, std::ios::out);
  } else {
    // Abrir en modo de adición para no borrar el contenido existente
    fichero_salida_.open(fichero_salida, std::ios::out | std::ios::app);
  }

  if (!fichero_salida_.is_open()) {
    std::cerr << "Error: No se puede abrir el fichero " << fichero_salida << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Tabla::ImprimirLineaSeparadora() {
    fichero_salida_ << kSeparador << std::endl;
}

TablaVoraz::TablaVoraz(const std::string& fichero_salida, bool primera_vez) : Tabla(fichero_salida, primera_vez) { }

void TablaVoraz::ImprimirCabecera() {
    fichero_salida_ << std::left;  // Alinear a la izquierda
    fichero_salida_ << "TABLA DE RESULTADOS DEL ALGORITMO VORAZ" << std::endl;
    fichero_salida_ << kSeparador << std::endl;
    fichero_salida_ << std::setw(25) << "Problema";
    fichero_salida_ << std::setw(10) << "n";
    fichero_salida_ << std::setw(10) << "K";
    fichero_salida_ << std::setw(10) << "m";
    fichero_salida_ << std::setw(15) << std::fixed << std::setprecision(2) << "z";
    fichero_salida_ << std::setw(25) << "S";
    fichero_salida_ << std::setw(25) << "CPU" << std::endl; 
    fichero_salida_ << kSeparador << std::endl;
}

void TablaVoraz::ImprimirResultados(SolucionMDP* s) {
    // Imprimir los resultados en el fichero de salida
    std::string fichero_entrada = s->GetFicheroEntrada();
    fichero_entrada = fichero_entrada.substr(fichero_entrada.find_last_of("/") + 1);

    // Calcular los indices de los elementos en el conjunto S
    std::string indices = "";
    DatosMDP datos = s->GetDatos();
    std::vector<std::vector<double>> S_original = datos.GetConjuntoS();
    std::vector<std::vector<double>> S = s->GetS();
    for (const auto& elem : S) {
      auto it = std::find(S_original.begin(), S_original.end(), elem);
      if (it != S_original.end()) {
        int index = std::distance(S_original.begin(), it);
        indices += std::to_string(index) + " ";
      }
    }

    // Establecer un ancho fijo para cada columna
    fichero_salida_ << std::left;  // Alinear a la izquierda
    fichero_salida_ << std::setw(25) << fichero_entrada;
    fichero_salida_ << std::setw(10) << s->GetN();
    fichero_salida_ << std::setw(10) << s->GetK();
    fichero_salida_ << std::setw(10) << s->GetM();
    fichero_salida_ << std::setw(15) << s->GetZ();
    fichero_salida_ << std::setw(25) << indices;
    fichero_salida_ << std::setw(25) << s->GetCPU() << std::endl;
}

TablaGRASP::TablaGRASP(const std::string& fichero_salida, bool primera_vez) : Tabla(fichero_salida, primera_vez) { }

void TablaGRASP::ImprimirCabecera() {
    fichero_salida_ << std::left;  // Alinear a la izquierda
    fichero_salida_ << "TABLA DE RESULTADOS DEL ALGORITMO GRASP" << std::endl;
    fichero_salida_ << kSeparador << std::endl;
    fichero_salida_ << std::setw(25) << "Problema";
    fichero_salida_ << std::setw(10) << "n";
    fichero_salida_ << std::setw(10) << "K";
    fichero_salida_ << std::setw(10) << "m";
    fichero_salida_ << std::setw(15) << "Iter";
    fichero_salida_ << std::setw(10) << "|LRC|";
    fichero_salida_ << std::setw(15) << std::fixed << std::setprecision(2) << "z";
    fichero_salida_ << std::setw(25) << "S";
    fichero_salida_ << std::setw(25) << "CPU" << std::endl; 
    fichero_salida_ << kSeparador << std::endl;
}

void TablaGRASP::ImprimirResultados(SolucionMDP* s) {
    // Imprimir los resultados en el fichero de salida
    std::string fichero_entrada = s->GetFicheroEntrada();
    fichero_entrada = fichero_entrada.substr(fichero_entrada.find_last_of("/") + 1);

    // Calcular los indices de los elementos en el conjunto S
    std::string indices = "";
    DatosMDP datos = s->GetDatos();
    std::vector<std::vector<double>> S_original = datos.GetConjuntoS();
    std::vector<std::vector<double>> S = s->GetS();
    for (const auto& elem : S) {
      auto it = std::find(S_original.begin(), S_original.end(), elem);
      if (it != S_original.end()) {
        int index = std::distance(S_original.begin(), it);
        indices += std::to_string(index) + " ";
      }
    }

    // Establecer un ancho fijo para cada columna
    fichero_salida_ << std::left;  // Alinear a la izquierda
    fichero_salida_ << std::setw(25) << fichero_entrada;
    fichero_salida_ << std::setw(10) << s->GetN();
    fichero_salida_ << std::setw(10) << s->GetK();
    fichero_salida_ << std::setw(10) << s->GetM();
    fichero_salida_ << std::setw(15) << static_cast<SolucionGRASP*>(s)->GetIteraciones();
    fichero_salida_ << std::setw(10) << static_cast<SolucionGRASP*>(s)->GetLRC();
    fichero_salida_ << std::setw(15) << s->GetZ();
    fichero_salida_ << std::setw(25) << indices;
    fichero_salida_ << std::setw(25) << s->GetCPU() << std::endl;
}