#include "../include/results/Tabla.h"

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
    fichero_salida_ << "_________________________________________________________________________________________________" << std::endl;
}

TablaVoraz::TablaVoraz(const std::string& fichero_salida, bool primera_vez) : Tabla(fichero_salida, primera_vez) { }

void TablaVoraz::ImprimirCabecera() {
    fichero_salida_ << std::left;  // Alinear a la izquierda
    fichero_salida_ << "TABLA DE RESULTADOS DEL ALGORITMO VORAZ" << std::endl;
    fichero_salida_ << "_________________________________________________________________________________________________" << std::endl;
    fichero_salida_ << std::setw(25) << "Problema";
    fichero_salida_ << std::setw(10) << "n";
    fichero_salida_ << std::setw(10) << "K";
    fichero_salida_ << std::setw(10) << "m";
    fichero_salida_ << std::setw(15) << "z";
    fichero_salida_ << std::setw(10) << "S";
    fichero_salida_ << std::setw(25) << "CPU" << std::endl; 
    fichero_salida_ << "_________________________________________________________________________________________________" << std::endl;
}

void TablaVoraz::ImprimirResultados(SolucionMDP* s) {
    // Imprimir los resultados en el fichero de salida
    std::string fichero_entrada = s->GetFicheroEntrada();
    fichero_entrada = fichero_entrada.substr(fichero_entrada.find_last_of("/") + 1);

    // Establecer un ancho fijo para cada columna
    fichero_salida_ << std::left;  // Alinear a la izquierda
    fichero_salida_ << std::setw(25) << fichero_entrada;
    fichero_salida_ << std::setw(10) << s->GetN();
    fichero_salida_ << std::setw(10) << s->GetK();
    fichero_salida_ << std::setw(10) << s->GetM();
    fichero_salida_ << std::setw(15) << s->GetZ();
    fichero_salida_ << std::setw(10) << s->GetS().size();
    fichero_salida_ << std::setw(25) << s->GetCPU() << std::endl;
}

TablaGRASP::TablaGRASP(const std::string& fichero_salida, bool primera_vez) : Tabla(fichero_salida, primera_vez) { }

void TablaGRASP::ImprimirCabecera() {
    fichero_salida_ << std::left;  // Alinear a la izquierda
    fichero_salida_ << "\n\n\nTTABLA DE RESULTADOS DEL ALGORITMO GRASP" << std::endl;
    fichero_salida_ << "_________________________________________________________________________________________________" << std::endl;
    fichero_salida_ << std::setw(25) << "Problema";
    fichero_salida_ << std::setw(10) << "n";
    fichero_salida_ << std::setw(10) << "K";
    fichero_salida_ << std::setw(10) << "m";
    fichero_salida_ << std::setw(15) << "Iter";
    fichero_salida_ << std::setw(10) << "|LRC|";
    fichero_salida_ << std::setw(15) << "z";
    fichero_salida_ << std::setw(10) << "S";
    fichero_salida_ << std::setw(25) << "CPU" << std::endl; 
    fichero_salida_ << "_________________________________________________________________________________________________" << std::endl;
}

void TablaGRASP::ImprimirResultados(SolucionMDP* s) {
    // Imprimir los resultados en el fichero de salida
    std::string fichero_entrada = s->GetFicheroEntrada();
    fichero_entrada = fichero_entrada.substr(fichero_entrada.find_last_of("/") + 1);

    // Establecer un ancho fijo para cada columna
    fichero_salida_ << std::left;  // Alinear a la izquierda
    fichero_salida_ << std::setw(25) << fichero_entrada;
    fichero_salida_ << std::setw(10) << s->GetN();
    fichero_salida_ << std::setw(10) << s->GetK();
    fichero_salida_ << std::setw(10) << s->GetM();
    fichero_salida_ << std::setw(15) << static_cast<SolucionGRASP*>(s)->GetIteraciones();
    fichero_salida_ << std::setw(10) << static_cast<SolucionGRASP*>(s)->GetLRC();
    fichero_salida_ << std::setw(15) << s->GetZ();
    fichero_salida_ << std::setw(10) << s->GetS().size();
    fichero_salida_ << std::setw(25) << s->GetCPU() << std::endl;
}