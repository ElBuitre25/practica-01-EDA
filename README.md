# Práctica 1 — Estructuras de Datos (ST0245)

Comparación de tiempos de ejecución entre algoritmos de ordenamiento: **QuickSort**, **HeapSort** y **AVL Tree**, sobre un dataset de 100,000 palabras aleatorias en inglés.

---

## Estructura del proyecto

```
practica1_EDA/
├── data/
│   ├── words_alpha.txt       # Fuente: ~100k palabras en inglés
│   └── dataset.txt           # Generado en runtime (no versionado)
├── src/
│   ├── main.cpp              # Orquestador: genera dataset y mide tiempos
│   ├── heap_sort.h           # Interfaz del módulo HeapSort
│   ├── heap_sort.cpp         # Implementación HeapSort — O(n log n)
│   └── dataset/
│       ├── create_random_dataset.h
│       └── create_random_dataset.cpp
├── build/                    # Binarios compilados (no versionado)
├── BUGS.md                   # Bugs conocidos pendientes de solución
└── README.md
```

---

## Compilación

Requiere C++17 y g++. Ejecutar desde la raíz del proyecto:

```bash
g++ -std=c++17 src/main.cpp src/dataset/create_random_dataset.cpp src/heap_sort.cpp -o build/proyecto
```

## Ejecución

```bash
./build/proyecto
```

Salida esperada:
```
QuickSort : X ms
HeapSort  : X ms
AVL       : X ms
```

El archivo `data/dataset.txt` se genera automáticamente con las 100,000 palabras seleccionadas.

---

## Módulos

### `create_random_dataset`
Lee `data/words_alpha.txt`, baraja todas las palabras usando Fisher-Yates
(`std::shuffle` + `std::mt19937_64` + `std::seed_seq` de 256 bits de entropía),
selecciona las primeras 100,000 y las escribe en `data/dataset.txt`.

### `main.cpp`
Llama al generador de dataset y mide con `std::chrono::high_resolution_clock`
el tiempo de cada algoritmo de ordenamiento. Los algoritmos están pendientes
de implementación.

### `heap_sort`
Implementa el algoritmo HeapSort sobre `std::vector<std::string>`.
Construye un Max-Heap con `build_max_heap()` en O(n), luego extrae
el máximo n veces con `heap_sort()` en O(n log n). Incluye
`estimate_memory_mb()` para estimar el consumo de memoria en MB.
No utiliza estructuras auxiliares — ordenamiento in-place O(1) espacial.

---

## Estado actual

| Módulo                | Estado          |
|-----------------------|-----------------|
| Generador de dataset  | Implementado    |
| Orquestador / medición| Implementado    |
| QuickSort             | Pendiente       |
| HeapSort              | Implementado    |
| AVL Tree              | Pendiente       |

---

## Bugs conocidos

Ver [`BUGS.md`](BUGS.md) para el detalle completo.

| ID      | Descripción                                              | Estado   |
|---------|----------------------------------------------------------|----------|
| BUG-001 | `words_alpha.txt` en UTF-16 LE causa lectura corrupta    | Abierto  |
| BUG-002 | `estimate_memory_mb` declarada `void` en `heap_sort.h`   | Cerrado  |
