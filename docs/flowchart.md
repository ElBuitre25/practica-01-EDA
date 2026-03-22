# Diagrama de flujo — Práctica 1 EDA

```mermaid
flowchart TD
    A((Inicio)) --> B["Crear dataset.txt"]

    B --> C["Abrir words_alpha.txt"]
    C --> C1{Archivo abierto?}
    C1 -- No --> ERR1["Error: no se pudo abrir\nRetornar vacío"]
    C1 -- Sí --> D["Leer líneas en vector\nstd::getline"]

    D -. "⚠ BUG-001: archivo en UTF-16 LE\ncausa lectura corrupta — ver BUGS.md" .-> D

    D --> VAL{"size >= 100 000?"}
    VAL -- No --> ERR2["Error: palabras insuficientes\nRetornar vacío"]
    VAL -- Sí --> E["Barajar con Fisher-Yates\nstd::shuffle + mt19937_64\nseed_seq 256 bits"]

    E --> F["Seleccionar primeros 100 000 elementos"]
    F --> G["Abrir data/dataset.txt"]
    G --> G1{Archivo abierto?}
    G1 -- No --> ERR3["Error: no se pudo guardar\nRetornar vacío"]
    G1 -- Sí --> H["Escribir 100 000 palabras\nen dataset.txt"]

    H --> MAIN["main.cpp"]

    MAIN --> T1["Medir QuickSort\nstd::chrono"]
    MAIN --> T2["Medir HeapSort\nstd::chrono"]
    MAIN --> T3["Medir AVL\nstd::chrono"]

    T1 -. pendiente .-> QS["quick_sort.cpp\nQuick Sort"]
    T3 -. pendiente .-> AV["avl_inorder.cpp\nAVL Inorder"]

    T2 --> HS_COPY["Copiar dataset\nhttps heap_dataset = dataset"]
    HS_COPY --> HS_BUILD["build_max_heap\nRecorre nodos no-hoja — O(n)"]
    HS_BUILD --> HS_HEAPIFY["heapify\nRepara subárbol raíz i — O(log n)"]
    HS_HEAPIFY --> HS_SORT["heap_sort\nExtrae máximo n veces — O(n log n)"]
    HS_SORT --> HS_MEM["estimate_memory_mb\nsizeof string × n — O(1) auxiliar"]
    HS_MEM -. "⚠ BUG-002: declarada void\nen lugar de double — ver BUGS.md" .-> HS_MEM
    HS_MEM --> HS_OUT["heap_sort.cpp\nImplementado"]

    T1 --> RES["Imprimir resultados\ncout: X ms por algoritmo"]
    HS_OUT --> RES
    T3 --> RES

    RES --> Z((Fin))
```
