#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <string>
#include <chrono>
using namespace std;

struct itemMov {
    string nomeProduto;
    string categoria = "Nao registrada";
    int quantidade;
    double valorTotal;
    std::chrono::system_clock::time_point data;  
};

#endif