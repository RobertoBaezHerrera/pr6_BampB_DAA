#include "../include/results/SolucionMDP.h"

SolucionMDP::SolucionMDP(const std::vector<std::vector<double>>& S, double z, double cpu,
               const std::string& fichero_entrada, int n, int k, int m)
    : S_(S), z_(z), cpu_(cpu), fichero_entrada_(fichero_entrada), n_(n), k_(k), m_(m) {
  // Constructor
}

// Getters
std::vector<std::vector<double>> SolucionMDP::GetS() const { return S_; }

double SolucionMDP::GetZ() const { return z_; }

double SolucionMDP::GetCPU() const { return cpu_; }

std::string SolucionMDP::GetFicheroEntrada() const { return fichero_entrada_; }

int SolucionMDP::GetN() const { return n_; }

int SolucionMDP::GetK() const { return k_; }

int SolucionMDP::GetM() const { return m_; }