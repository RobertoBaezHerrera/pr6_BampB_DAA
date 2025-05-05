#include "../../include/model/Nodo.h"

Nodo::Nodo(const std::vector<std::vector<double>>& parcial, const std::vector<std::vector<double>>& restantes, double c_sup) 
    : solucion_parcial(parcial), candidatos_restantes(restantes), cota_superior(c_sup) { }

// Getters
std::vector<std::vector<double>> Nodo::GetSolucionParcial() const {
    return solucion_parcial;
}

std::vector<std::vector<double>> Nodo::GetCandidatosRestantes() const {
    return candidatos_restantes;
}

double Nodo::GetCotaSuperior() const {
    return cota_superior;
}

/* double Nodo::GetCotaInferior() const {
    return cota_inferior;
} */

// Orden inverso para priority_queue (de menor a mayor)
bool Nodo::operator<(const Nodo& other) const {
    return cota_superior > other.cota_superior;
}