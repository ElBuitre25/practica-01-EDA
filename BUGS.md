# Bug Report

## BUG-001: words_alpha.txt está codificado en UTF-16 LE — lectura corrupta con std::ifstream

### Síntoma
Las palabras escritas en `data/dataset.txt` contienen caracteres corruptos/ilegibles
(ej. línea 69989 muestra glifos CJK y basura binaria en lugar de una palabra en inglés).

### Causa raíz
`data/words_alpha.txt` está codificado en **UTF-16 Little-Endian con CRLF**
(comienza con BOM `FF FE`), no en UTF-8.

`std::ifstream` abre el archivo en modo binario/ASCII por defecto. Al leerlo con
`std::getline`, cada carácter ASCII queda representado como dos bytes (`letra\x00`)
y cada fin de línea como cuatro bytes (`\x0d\x00\x0a\x00`). El resultado es que
cada entrada del vector contiene:
- un `\x00` inicial sobrante del delimitador previo
- los bytes intercalados de UTF-16 (ej. `h\x00e\x00l\x00l\x00o\x00`)
- un `\x0d\x00` (CR en UTF-16) al final en lugar de nada

Estos strings corruptos son los que se barajan, se seleccionan y se escriben
en `data/dataset.txt`, produciendo la salida ilegible observada.

### Evidencia
```
$ file data/words_alpha.txt
data/words_alpha.txt: Unicode text, UTF-16, little-endian text, with CRLF line terminators

$ hexdump -C data/words_alpha.txt | head -3
00000000  ff fe 6c 00 61 00 75 00  67 00 68 00 65 00 64 00  |..l.a.u.g.h.e.d.|
00000010  0d 00 0a 00 ...
```

### Archivo afectado
`src/dataset/create_random_dataset.cpp` — función `create_random_dataset()`

### Soluciones posibles (a decidir por el equipo)

**Opción A — Convertir el archivo fuente a UTF-8:**
```bash
iconv -f UTF-16LE -t UTF-8 data/words_alpha.txt -o data/words_alpha_utf8.txt
```
Sin cambios en el código C++. Es la opción más simple.

**Opción B — Leer UTF-16 en C++ con `std::wifstream` + locale:**
```cpp
std::wifstream file(input_file);
file.imbue(std::locale(file.getloc(),
    new std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>));
```
Requiere cambiar el tipo de `file_vector` a `std::vector<std::wstring>` y
adaptar el resto del pipeline (shuffle, ofstream, sort).

**Opción C — Limpiar los bytes nulos y `\r` al leer (workaround):**
Tras cada `getline`, eliminar `\x00` y `\r` del string. Funciona pero es frágil.

### Recomendación
Opción A: convertir `words_alpha.txt` a UTF-8 antes de commitear el archivo
corregido. No requiere cambios en el código C++.

## BUG-002: estimate_memory_mb declarada como void en heap_sort.h

### Síntoma
El compilador lanza dos errores en cadena:
- `cannot overload functions distinguished by return type alone` en heap_sort.cpp
- `no operator "<<" matches these operands` en main.cpp 

### Causa raíz
En `src/heap_sort.h`, la función `estimate_memory_mb` fue declarada
con tipo de retorno `void` en lugar de `double`:
```cpp
// Declaración incorrecta
void estimate_memory_mb(const std::vector<std::string>& arr);
```

Esto genera un conflicto porque en `heap_sort.cpp` la definición
retorna `double`, y en `main.cpp` el resultado se pasa al operador `<<`
que no acepta `void`.

### Archivo afectado
`src/heap_sort.h` — declaración de `estimate_memory_mb()`

### Solución aplicada
Corregir el tipo de retorno en la declaración del header:
```cpp
// Declaración correcta
double estimate_memory_mb(const std::vector<std::string>& arr);
```

### Estado
Corregido ✓