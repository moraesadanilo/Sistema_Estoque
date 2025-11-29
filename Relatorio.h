#ifndef RELATORIO_H
#define RELATORIO_H
#include <string>
#include <vector>
#include <map>
#include <set>
#include "Produto.h"
#include "Estruturas.h"

using namespace std;

class Estoque;  // ← CORREÇÃO: forward declaration, remove include circular

class Relatorio{
private:
   
    double valorTotalEstoque=0;
    int itensTotalEstoque=0;
    
    vector<itemMov> vendas_Historico;       //vector para armazenar o registro de vendas
    vector<itemMov> entradas_Historico;     //vector para armazenar o registro de vendas
    set<string> categoriasUnicas;           // SET: Categorias disponíveis                                          //ok
    map<string, string> categoriadProduto;         // chave = nome do produto & valor = categoria.                  //ok
    map<string, set<string>> produtosDaCategoria;  //receber uma referência ao map sem copiar.
    map<string, int> produtos_por_categoria;       // MAP: Quantidade total de produtos em cada categoria   contagem//ok
    map<string, int> unid_por_categoria;           //Total de unidades de prod da categotia                        //ok
    map<string, double> valorTotal_Categoria;       //soma do valor em estoque por categoria                        //ok
    
    
public:
    
    //Atualiza inventário do que tem categoria definida
    void calcularEstatisticas(const Estoque& loja);
    
    // Cacula valor total do inventário (por produto).
    void calcularValorTotalEstoque(const vector<Produto>& dadosEstoque);
    
    // Cacula valor total do inventário (por produto).
    void calcularItensTotalEstoque(const vector<Produto>& dadosEstoque);
    
// = = = = = ENTRADAS DE DADOS (métodos de manipulação) = = = = =

    // Registra entrada ao historico - registro minimo
    void registrarEntrada(const Produto& ent);

    // Adiciona valores de categorias ao respectivo container.
    void adicionarCategoria(const string& nome);
    
    //Adiciona valores de produtos ao respectivo container de categorias.
    void adicionarProd_Categoria(const string& nomeProduto, const string& categoria);
    
// = = = = = SAIDAS DE DADOS (métodos de manipulação) = = = = =
    
    //Busca valor total (encapsulado privado) 
    double getvalorTotalInventario();
    
    //Busca total de itens em estoque (encapsulado privado)
    int getitensTotalInventario();
    
    //Registra venda ao historico 
    void registrarVenda(const itemMov& v);
    
// = = = = = IMPRESSOES EM TELA = = = = = //
    
    //item ja cadastrado
    void itensJaCadastrados(const Estoque& analisado);
    
    //Exibe inventário completo ====>>> (sem saldos zerados)
    void gerarInventarioCompleto(const Estoque& analisado);    
    
    //Exibe todas as entradas registradas
    void relatorioHistoricoEntradas() const;
    
    //Exibe venda em tela
    void exibirItem(const itemMov& v) const;
    
    //Exibe todas as vendas registradas
    void relatorioHistoricoVendas() const;
    
    // Lista e imprime as categorias do sistema
    void exibirCategorias();
    
    // Lista e imprime em tela os itens de cada categoria do sistema
    void imprimirProdutosPorCategoria() const;
    
    void exibirEstatisticasPorCategoria() const;
    
};

#endif
