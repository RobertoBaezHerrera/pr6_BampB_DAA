
# Proyecto de Optimización Combinatoria — Máxima Diversidad

Este proyecto implementa y compara diferentes algoritmos para resolver el **Problema de la Máxima Diversidad**, utilizando múltiples enfoques de optimización heurística y exacta.

## Descripción del problema

Dado un conjunto de \( n \) elementos descritos por vectores en un espacio \( \mathbb{R}^k \), se desea seleccionar un subconjunto de tamaño \( m \) tal que se **maximice la dispersión total** entre sus elementos, medida como la suma de distancias euclídeas entre todos los pares del subconjunto.

## Algoritmos implementados

### 1. Voraz (Greedy)
- Construcción paso a paso del subconjunto.
- Selecciona en cada iteración el elemento que maximiza la dispersión incremental.
- Muy rápido, pero no garantiza solución óptima.

### 2. Búsqueda Local
- Parte de una solución inicial (voraz).
- Explora vecinos mediante intercambios de elementos.
- Se detiene en un óptimo local.

### 3. GRASP (Greedy Randomized Adaptive Search Procedure)
- Fase de construcción aleatorizada basada en una lista restringida de candidatos (LRC).
- Mejora posterior con búsqueda local.
- Se repite varias veces y guarda la mejor solución.

### 4. Ramificación y Poda (Branch & Bound)
- Explora el espacio de soluciones de forma exacta.
- Usa **cotas superiores** para podar nodos no prometedores.
- Se utilizan dos estrategias de ramificación:
  - Expansión del **mejor nodo**.
  - Expansión del **segundo mejor nodo**.
- Cotas inferiores obtenidas del **algoritmo voraz** o **GRASP**.

## Estructura del proyecto

```
include/
├── DatosMDP.h
├── AlgoritmoVoraz.h
├── BusquedaLocal.h
├── GRASP.h
└── RamificacionYPoda.h
src/
├── main.cpp
├── DatosMDP.cpp
├── AlgoritmoVoraz.cpp
├── BusquedaLocal.cpp
├── GRASP.cpp
└── RamificacionYPoda.cpp
Instances/
└── max_div_*.txt    # Instancias del problema
Resultados/
└── tablas_output.txt
README.md
```

## Resultados experimentales

Se han realizado pruebas con múltiples instancias y tamaños (n=15, 20, 30) y dimensiones (k=2, 3). Los algoritmos fueron evaluados en cuanto a:

- Calidad de la solución (valor de la función objetivo \( z \))
- Tiempo de CPU
- Nodos generados (en Branch & Bound)
- Estabilidad y consistencia de los resultados

Las tablas completas y las **conclusiones comparativas** se encuentran en la memoria PDF del proyecto.

## Requisitos y compilación

### Requisitos
- C++17 o superior
- Compilador compatible (g++, clang++)
- CMake (opcional)

### Compilación manual
```
g++ -std=c++17 -O2 src/*.cpp -o mdp_solver
```

### Ejecución
```
./mdp_solver Instances/max_div_20_2.txt
```

## Memoria

El proyecto incluye una memoria explicativa en PDF que describe:

- Los algoritmos diseñados
- Decisiones de implementación
- Comparativas entre métodos
- Conclusiones extraídas de los experimentos

## Autor

**Nombre:** Roberto Báez Herrera  
**Universidad:** Universidad de La Laguna  
**Curso:** Diseño y Análisis de Algoritmos
**Fecha:** Mayo 2025
