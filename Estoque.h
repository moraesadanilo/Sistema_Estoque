#ifndef ESTOQUE_H
#define ESTOQUE_H
#include <vector>
#include <map>
#include <set>
#include <string>
#include <chrono>
#include "Produto.h"
#include "Estruturas.h"
class Relatorio; // Declaração Forward para evitar inclusão circular (Diga ao compilador: "Relatorio é um nome de classe") 
using namespace std;

/* susbstituido por arquivo .h
//Estrutura para item em movimentacao
struct itemMov {
        string nomeProduto;
        string categoria = "Nao registrada";
        int quantidade;
        double valorTotal;
        std::chrono::system_clock::time_point data;  
    };                 
*/
class Estoque{
private:
    //Relacionamento//
    Relatorio& relatorio;  //NÃO cria um objeto Relatorio, ele usa um que já existe.
    
    //VECTORES: 
    vector<Produto> estoque;            
    // Associação produto -> categoria.
    map<string, string> categoriaDoProduto;         // chave = nome do produto & valor = categoria.
    map<string, set<string>>produtosDaCategoria;    // chave = categoria  & valor = nome do produto
    
    itemMov montarRegistro(const Produto& item, int quantidade);
    
public:
    
    // Permite que outras classe leia os dados, mas não os modifique.
    const vector<Produto>& getEstoque() const;
 
    // Getter para o mapa de categorias (apenas leitura)
    const map<string, string>& getCategorias() const;                                            
    
    //construtor construtor que recebe o objeto Relatorio existente.
    Estoque(Relatorio& rel) : relatorio(rel) {}
    
    //= = adição de itens sem parametros - solicitado ao usuario = = //
    void adicionarProduto();

    // = = adição de itens com 3 parametros = = //
    void adicionarProduto(string nome, double valor_unit, int quantidade);
    // = = adição de itens com 2 parametros = = //
    void adicionarProduto(string nome, double valor_unit);
    // = = adição de itens com 1 parametros = = //
    void adicionarProduto(string nome);
    
// = = = = =  ATUALIZADORES = = = = = 
    //MAP: define a qual categoria o podutos fará parte
    void definirCategoria(const string& nomeProd, const string& categ);

    //consulta e exibição de produto pelo nome dentro do container vector
    void consultarProduto(string nome);
    
    // = = = = = SAIDAS  = = = = =
    void saidaEstoque(const string& nome);

    // Tamanho do estoque total
    int tamanhoEstoque();
};

#endif
