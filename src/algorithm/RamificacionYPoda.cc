#include "../../include/algorithm/RamificacionYPoda.h"

RamificacionYPoda::RamificacionYPoda(const DatosMDP& datos) : datos_(datos) {
  m_ = datos.GetM();  // Tamaño solución a construir
}

std::vector<std::vector<double>> RamificacionYPoda::Ejecutar(const double cota_inferior) {
  std::vector<std::vector<double>> S_original = datos_.GetConjuntoS();
  std::vector<std::vector<double>> mejor_solucion;

  // Inicializamos la cola de prioridad con nodos iniciales (uno por cada
  // elemento posible inicial) Esta cola repreesnta el árbol de búsqueda y se
  // ordena por la cota superior de cada nodo 
  // La cota superior es la mejor estimación de la solución que podemos obtener a partir de ese nodo
  std::priority_queue<Nodo> cola;
  double cota_inf = cota_inferior;  // Usamos el resultado voraz como cota inferior inicial
  for (const auto& elem : S_original) {
    std::vector<std::vector<double>> parcial = {elem};
    std::vector<std::vector<double>> restantes;
    for (const auto& e : S_original) {
      if (e != elem) restantes.push_back(e);
    }
  
    // Al inicio se establece una cota inferior de referencia, y luego vamos
    // calculando cotas superiores, y cuando se encuentra una mejor cota
    // superior con una solución factible, se actualiza a esa la cota inferior
    double cota_sup = CalcularCotaSuperior(parcial, restantes);  // Cota superior inicial
    cola.emplace(parcial, restantes, cota_sup);
    ++nodos_generados_;
  }

  // El algoritmo acaba cuando no quedan ramas que explorar o se ha podado todo
  while (!cola.empty()) {
    Nodo nodo = cola.top();
    cola.pop();

    // PODA: si su cota superior es peor que la mejor solución, descartamos
    if (nodo.GetCotaSuperior() <= cota_inf) continue;

    // Si es solución completa
    if (nodo.GetSolucionParcial().size() == m_) {
      double valor = datos_.CalcularZ(nodo.GetSolucionParcial());
      if (valor > cota_inf) {
        // Actualizamos la cota inferior y la mejor solución
        cota_inf = valor;
        mejor_solucion = nodo.GetSolucionParcial();
      }
      continue;
    }

    // Expandimos el nodo
    std::vector<Nodo> hijos = Expandir(nodo);
    for (const Nodo& hijo : hijos) {
      if (hijo.GetCotaSuperior() > cota_inf) {
        cola.push(hijo);
        ++nodos_generados_;
      }
    }
  }
  
  return mejor_solucion;
}

std::vector<Nodo> RamificacionYPoda::Expandir(const Nodo& nodo) {
  std::vector<Nodo> hijos;
  for (int i = 0; i < nodo.GetCandidatosRestantes().size(); ++i) {
    std::vector<std::vector<double>> nueva_sol = nodo.GetSolucionParcial();
    nueva_sol.push_back(nodo.GetCandidatosRestantes()[i]);

    std::vector<std::vector<double>> nuevos_candidatos = nodo.GetCandidatosRestantes();
    nuevos_candidatos.erase(nuevos_candidatos.begin() + i);

    double cota_sup = CalcularCotaSuperior(nueva_sol, nuevos_candidatos);
    hijos.emplace_back(nueva_sol, nuevos_candidatos, cota_sup);
  }
  return hijos;
}

double RamificacionYPoda::CalcularCotaSuperior(
    const std::vector<std::vector<double>>& solucion_parcial,
    const std::vector<std::vector<double>>& candidatos_restantes) {
  // 1) Mapear a índices
  std::vector<int> parcial, restantes;
  const auto& S_original = datos_.GetConjuntoS();
  for (const auto& elem : solucion_parcial) {
    auto it = std::find(S_original.begin(), S_original.end(), elem);
    if (it != S_original.end()) {
      parcial.push_back(std::distance(S_original.begin(), it));
    }
  }
  for (const auto& elem : candidatos_restantes) {
    auto it = std::find(S_original.begin(), S_original.end(), elem);
    if (it != S_original.end()) {
      restantes.push_back(std::distance(S_original.begin(), it));
    }
  }

  // 2) Traer matriz de distancias
  const auto& matriz = datos_.GetMatrizDistancia();

  // 3) Dispersión actual: suma de pares en 'parcial'
  double dispersion_actual = 0.0;
  for (int i = 0; i < parcial.size(); ++i) {
    for (int j = i + 1; j < parcial.size(); ++j) {
      dispersion_actual += matriz[parcial[i]][parcial[j]];
    }
  }

  // 4) Si ya está completo, devolvemos su valor exacto
  if (parcial.size() == m_) {
    return dispersion_actual;
  }

  // 5) Contribución parcial-candidato
  int faltan = m_ - parcial.size();
  // Aportes parciales a candidatos
  std::vector<double> aportes_pc;
  aportes_pc.reserve(restantes.size());
  for (int c : restantes) {
    double suma = 0.0;
    for (int p : parcial) {
      suma += matriz[p][c];
    }
    aportes_pc.push_back(suma);
  }
  std::sort(aportes_pc.begin(), aportes_pc.end(), std::greater<>());
  double suma_pc = 0.0;
  for (int k = 0; k < faltan && k < aportes_pc.size(); ++k) {
    suma_pc += aportes_pc[k];
  }

  // 6) Contribución candidato-candidato
  //    Necesitamos los pares internos más grandes entre los 'restantes'
  std::vector<double> aportes_cc;
  for (int i = 0; i < restantes.size(); ++i) {
    for (int j = i + 1; j < restantes.size(); ++j) {
      aportes_cc.push_back(matriz[restantes[i]][restantes[j]]);
    }
  }
  std::sort(aportes_cc.begin(), aportes_cc.end(), std::greater<>());
  int pares_necesarios = faltan * (faltan - 1) / 2;
  double suma_cc = 0.0;
  for (int k = 0; k < pares_necesarios && k < aportes_cc.size(); ++k) {
    suma_cc += aportes_cc[k];
  }

  // 7) Cota superior = dispersión actual + futuras contribuciones
  double cota_sup = dispersion_actual + suma_pc + suma_cc;
  return cota_sup;
}
