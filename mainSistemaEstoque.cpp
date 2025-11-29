#include "Estoque.h"
#include "Relatorio.h"

using namespace std;

int main() {
    // = = declarações = = //
    Relatorio relLoja;
    Estoque loja(relLoja);
    
   
    // = = testes com valores = = //
    cout<<"Estoque inical: ";
    cout<<loja.tamanhoEstoque()<<endl;  //tamanho do estoque
    
    loja.adicionarProduto("Celular", 2000, 1);
    loja.adicionarProduto("Camisa Polo", 24.9, 10);
    loja.adicionarProduto("Camisa Regata", 24.9, 30);
    loja.adicionarProduto("Vinho");
    loja.adicionarProduto("Tablet", 2000, 5);
    loja.adicionarProduto("Mouse", 35.5, 100);
    loja.adicionarProduto("Notebook", 3000, 25);
    loja.adicionarProduto("Celular", 2000, 1);
    loja.adicionarProduto("Celular", 1500, 5);
    loja.adicionarProduto("Tablet", 3000,  5);
    
    loja.definirCategoria("Camisa Polo", "Vestuario");
    loja.definirCategoria("Mouse", "Informativa");
    loja.definirCategoria("Notebook", "Informativa");
    loja.definirCategoria("Celular", "Eletrônicos");
    loja.definirCategoria("Tablet", "Eletrônicos");
    
    cout<<"Estoque intermediario: ";
    cout<<loja.tamanhoEstoque()<<endl;  //tamanho do estoque
    
    loja.saidaEstoque("Celular");
    loja.saidaEstoque("Tablet");
    cout<<"Estoque intermediario: ";
    cout<<loja.tamanhoEstoque()<<endl;  //tamanho do estoque
    
    
    relLoja.exibirCategorias();
    relLoja.exibirCategorias();
    relLoja.imprimirProdutosPorCategoria();
    
    loja.consultarProduto("Celular");  //consulta pelo nome - apenas exibição
    
    relLoja.relatorioHistoricoEntradas();
    relLoja.relatorioHistoricoVendas();
    relLoja.calcularEstatisticas(loja);
    relLoja.exibirEstatisticasPorCategoria();
    relLoja.gerarInventarioCompleto(loja);
    

    return 0;
}