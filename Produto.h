#ifndef PRODUTO_H
#define PRODUTO_H

#include <iostream>
#include <string>

using namespace std;

class Produto {
private:
    string nome;
    double valor_unit;  
    int saldo_estoque;
    
public:
//CONSTRUTORORES://
    Produto(string n, double u, int s);
    Produto(string n, double u);
    Produto(string n);
    Produto();
//ENTRADAS E MODIFICAÇÕES//
    void entrada(Produto &item, int qtd);
    void alteraPreco(Produto &item, double valor);
// SETTERS - para modificar com validação 
    void setNome(string n);
    void setValorUni(double u);
    void setSaldoEst(int s);
    
//SAIDAS E CONSULTAS//
    bool saida(Produto &item, int qtd);
    void exibirproduto()const;
    string getNome() const;
    double getValor_unit() const;
    int getSaldo_estoque() const;
    double calcularValorTotalItem() const;
    
};

#endif