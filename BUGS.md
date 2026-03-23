# Bug Report

## BUG-001: words_alpha.txt está codificado en UTF-16 LE — lectura corrupta con std::ifstream

### Síntoma
Las palabras escritas en `data/dataset.txt` contenían caracteres corruptos/ilegibles
(ej. línea 69989 mostraba glifos CJK y basura binaria en lugar de una palabra en inglés).

### Causa raíz
`data/words_alpha.txt` estaba codificado en **UTF-16 Little-Endian con CRLF**
(comenzaba con BOM `FF FE`), no en UTF-8.

`std::ifstream` abre el archivo en modo ASCII por defecto. Al leerlo con
`std::getline`, cada carácter ASCII quedaba representado como dos bytes (`letra\x00`)
y cada fin de línea como cuatro bytes (`\x0d\x00\x0a\x00`). El resultado era que
cada entrada del vector contenía bytes nulos intercalados y `\x0d\x00` al final.

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

### Solución aplicada
Se convirtió el archivo a UTF-8 sin BOM usando `iconv`:
```bash
iconv -f UTF-16LE -t UTF-8 data/words_alpha.txt -o data/words_alpha.txt
sed -i 's/\r//' data/words_alpha.txt
sed -i '1s/^\xef\xbb\xbf//' data/words_alpha.txt
```
No requirió cambios en el código C++.

### Estado
Corregido ✓

---

## BUG-002: estimate_memory_mb declarada como void en heap_sort.h

### Síntoma
El compilador lanzaba dos errores en cadena:
- `cannot overload functions distinguished by return type alone` en heap_sort.cpp
- `no operator "<<" matches these operands` en main.cpp

### Causa raíz
En `src/heap_sort.h`, la función `estimate_memory_mb` fue declarada
con tipo de retorno `void` en lugar de `double`:
```cpp
void estimate_memory_mb(const std::vector<std::string>& arr);
```

### Solución aplicada
Corregir el tipo de retorno en la declaración del header:
```cpp
double estimate_memory_mb(const std::vector<std::string>& arr);
```

### Estado
Corregido ✓
