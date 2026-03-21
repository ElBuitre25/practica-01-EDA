# Generador de Dataset Aleatorio

Módulo encargado de producir el dataset de entrada para los algoritmos de ordenamiento.
Implementado en `src/dataset/create_random_dataset.cpp`.

---

## Firma de la función

```cpp
std::vector<std::string> create_random_dataset(std::string input_file);
```

Recibe la ruta al archivo fuente, devuelve un `std::vector<std::string>` con
las 100,000 palabras seleccionadas.

---

## Flujo interno

### 1. Lectura del archivo fuente

```cpp
std::ifstream file(input_file);
while (std::getline(file, line))
    file_vector.push_back(line);
```

Lee `data/words_alpha.txt` línea por línea y almacena cada palabra en
`file_vector`. Si el archivo no se puede abrir, retorna un vector vacío.

> **BUG-001:** `words_alpha.txt` está actualmente en UTF-16 LE, lo que produce
> lectura corrupta. Ver [BUGS.md](../BUGS.md).

---

### 2. Validación de tamaño

```cpp
if (file_vector.size() < 100000) {
    std::cerr << "Error: el archivo tiene menos de 100000 palabras" << std::endl;
    return {};
}
```

Garantiza que hay suficientes palabras antes de proceder. Sin esta guarda,
el `assign` posterior causaría **undefined behavior**.

---

### 3. Generación de entropía y semilla

```cpp
std::random_device rd;
std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
std::mt19937_64 gen(ss);
```

| Componente | Descripción |
|------------|-------------|
| `std::random_device` | Fuente de entropía del sistema operativo (`/dev/urandom` en Linux) |
| `std::seed_seq` | Combina 8 valores de 32 bits → semilla de **256 bits** de entropía |
| `std::mt19937_64` | Motor Mersenne Twister de 64 bits; periodo de 2^19937 − 1 |

Usar `seed_seq` con múltiples valores de `random_device` evita semillas
débiles y garantiza que cada ejecución produzca un orden diferente.

---

### 4. Barajado — Fisher-Yates

```cpp
std::shuffle(file_vector.begin(), file_vector.end(), gen);
```

`std::shuffle` implementa el algoritmo **Fisher-Yates moderno** (Knuth):

```
para i desde n-1 hasta 1:
    j = número aleatorio uniforme en [0, i]
    intercambiar(arr[i], arr[j])
```

- Complejidad: **O(n)**
- Garantiza que todas las **n!** permutaciones son equiprobables
- Sin sesgo estadístico gracias a `mt19937_64`

---

### 5. Selección y escritura

```cpp
new_file_vector.assign(file_vector.begin(), file_vector.begin() + 100000);

std::ofstream dataset("data/dataset.txt");
for (size_t i = 0; i < 100000; i++)
    dataset << new_file_vector[i] << "\n";
```

Toma los primeros 100,000 elementos del vector ya barajado y los escribe en
`data/dataset.txt`, uno por línea.

---

## Propiedades del dataset generado

| Propiedad | Valor |
|-----------|-------|
| Tamaño | 100,000 palabras |
| Fuente | `data/words_alpha.txt` |
| Salida | `data/dataset.txt` |
| Distribución | Uniforme (sin repetición dentro del archivo fuente) |
| Reproducibilidad | No — semilla aleatoria en cada ejecución |

---

## Bugs conocidos

| ID | Descripción | Estado |
|----|-------------|--------|
| BUG-001 | `words_alpha.txt` en UTF-16 LE causa lectura corrupta | Abierto |

Ver [BUGS.md](../BUGS.md) para soluciones propuestas.
