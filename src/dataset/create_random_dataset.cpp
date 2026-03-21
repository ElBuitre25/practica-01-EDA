#include "create_random_dataset.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <random>
#include <algorithm>

std::vector<std::string> create_random_dataset(std::string input_file){
    //Vector dinamico donde se almacenaran las palabras del file.txt
    std::vector<std::string> file_vector={};
    //Reservamos espacio para almacenar la linea del txt leida
    std::string line;
    //Elemento entropico obtenido del sistema operativo
    std::random_device rd;
    //Nuevo vector que guardara 100mil palabras
    std::vector<std::string> new_file_vector;
    //Leemos el archivo file
    std::ifstream file(input_file);
    if(!file.is_open()){
        std::cerr << "Error: NO se pudo abrir el archivo" << std::endl;
        return {};
    }
    while(std::getline(file, line)){
        file_vector.push_back(line);
    }
    //Toma 8 valores entropicos y genera una semilla mas compleja
    std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    //Generamos el motor de aleatoriedad
    std::mt19937_64 gen(ss);
    //Realizamos el shuffle
    std::shuffle(file_vector.begin(), file_vector.end(), gen);
    //Verificamos que el archivo tenga al menos 100mil palabras
    if(file_vector.size() < 100000){
        std::cerr << "Error: el archivo tiene menos de 100000 palabras (" << file_vector.size() << ")" << std::endl;
        return {};
    }
    //Obtenemos los primeros 100mil elementos
    new_file_vector.assign(file_vector.begin(), file_vector.begin()+100000);
    std::ofstream dataset("data/dataset.txt");
    //Verificamos si el archivo se pudo abrir
    if(!dataset.is_open()){
        std::cerr << "Error: no se pudo abrir el archivo" << std::endl;
        return {};
    }
    //Llenamos dataset.txt con las palabras aleatorias
    for(size_t i = 0; i < 100000; i++){
        dataset << new_file_vector[i] << "\n";
    }
    return new_file_vector;
}
