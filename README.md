# Práctica 1 — Estructuras de Datos (ST0245)

Comparación de tiempos de ejecución entre algoritmos de ordenamiento: **QuickSort**, **HeapSort** y **Red-Black Tree**, sobre un dataset de 100,000 palabras aleatorias en inglés.

---

## Estructura del proyecto

```
practica1_EDA/
├── data/
│   ├── words_alpha.txt       # Fuente: 100k palabras en inglés (UTF-8)
│   └── dataset.txt           # Generado en runtime (no versionado)
├── src/
│   ├── main.cpp              # Orquestador: genera dataset, mide tiempos y compara
│   ├── quick_sort.h
│   ├── quick_sort.cpp        # QuickSort con pivote mediana de tres — O(n log n)
│   ├── heap_sort.h
│   ├── heap_sort.cpp         # HeapSort con Max-Heap — O(n log n)
│   ├── red_black_tree.h
│   ├── red_black_tree.cpp    # Red-Black Tree, inorder traversal — O(n log n)
│   └── dataset/
│       ├── create_random_dataset.h
│       └── create_random_dataset.cpp
├── build/                    # Binarios compilados (no versionado)
├── docs/
│   └── flowchart.md
├── BUGS.md
└── README.md
```

---

## Compilación

Requiere C++17 y g++. Ejecutar desde la raíz del proyecto:

```bash
g++ -std=c++17 -O2 \
  src/main.cpp \
  src/quick_sort.cpp \
  src/heap_sort.cpp \
  src/red_black_tree.cpp \
  src/dataset/create_random_dataset.cpp \
  -o build/proyecto
```

## Ejecución

```bash
./build/proyecto
```

Salida esperada (los tiempos varían por ejecución):
```
--- Tiempos de ejecucion ---
QuickSort:      57 ms
HeapSort:       106 ms
Red-Black Tree: 80 ms

--- Memoria estimada ---
QuickSort:      4.48 MB
HeapSort:       4.48 MB
Red-Black Tree: 7.53 MB

--- Verificacion (primeras 10 palabras) ---
QuickSort: a aahing aaliis aaronite ...
HeapSort:  a aahing aaliis aaronite ...
RBT:       a aahing aaliis aaronite ...
```

El archivo `data/dataset.txt` se genera automáticamente con las 100,000 palabras seleccionadas.

---

## Módulos

### `create_random_dataset`
Lee `data/words_alpha.txt`, baraja todas las palabras usando Fisher-Yates
(`std::shuffle` + `std::mt19937_64` + `std::seed_seq` de 256 bits de entropía),
selecciona las primeras 100,000 y las escribe en `data/dataset.txt`.

### `quick_sort`
QuickSort recursivo sobre `std::vector<std::string>`. Usa mediana de tres elementos
(primero, medio, último) como pivote para evitar el peor caso O(n²) con datos
casi ordenados. Ordenamiento in-place.

### `heap_sort`
Construye un Max-Heap con `build_max_heap()` en O(n), luego extrae el máximo
n veces con `heap_sort()` en O(n log n). Incluye `estimate_memory_mb()` para
estimar el consumo de memoria. Ordenamiento in-place.

### `red_black_tree`
Árbol Rojo-Negro con inserción balanceada. Se insertan las 100,000 palabras en 
el árbol y, posteriormente, el recorrido inorder devuelve las claves en orden lexicográfico. 
Cada nodo almacena la clave, el color y tres punteros: padre, hijo izquierdo e hijo derecho.

---

## Estado

| Módulo                | Estado       |
|-----------------------|--------------|
| Generador de dataset  | Implementado |
| QuickSort             | Implementado |
| HeapSort              | Implementado |
| Red-Black Tree        | Implementado |
| Medición de tiempos   | Implementado |
| Estimación de memoria | Implementado |

---

## Bugs

| ID      | Descripción                                           | Estado  |
|---------|-------------------------------------------------------|---------|
| BUG-001 | `words_alpha.txt` en UTF-16 LE causa lectura corrupta | Cerrado |
| BUG-002 | `estimate_memory_mb` declarada `void` en heap_sort.h  | Cerrado |
