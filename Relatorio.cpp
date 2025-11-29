#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "Produto.h"
#include "Estoque.h"
#include "Relatorio.h"

using namespace std;
   
    //Atualiza inventário do que tem categoria definida
    void Relatorio::calcularEstatisticas(const Estoque& loja){   // Baseado em categorias 
    // Limpa os MAPs antes de recalcular
        produtos_por_categoria.clear();
        valorTotal_Categoria.clear();

    // Obtém os dados de Estoque
        const vector<Produto>& dadosEstoque = loja.getEstoque();            //recebe estoque bruto de Estoque
        const map<string, string>& dadosCategorias = loja.getCategorias();    //recebe map com as categ fornecidas por Estoque
    // Atualizada produtos vinculados a categorias
        for (const auto& produto : dadosEstoque) {
        
        // Encontra a categoria do produto usando seu nome (Produto::getNome()) como chave
        auto it = dadosCategorias.find(produto.getNome());  

            if (it != dadosCategorias.end()) {          //Verifica se o elemento foi encontrado ou não, end() para indicar não existir/o fim.
            // Se a categoria for encontrada:
            const string& categoria = it->second;   //extrai valor(string) do map : map<chave,valor>;
            // Calcula o valor total deste produto
            double valorProduto = produto.getValor_unit() * produto.getSaldo_estoque();
            // Atualiza o map de contagem de quantos produtos tem na categoria (carteira de produtos)
            produtos_por_categoria[categoria]++;                                                        
            //Atualiza o saldo de itens em cada categoria (unidades)
            unid_por_categoria[categoria] += produto.getSaldo_estoque();                                      
            // Atualiza o map de valor total (adiciona o valor)
            valorTotal_Categoria[categoria] += valorProduto;
            }
        }
        // Chama função separada para calcular valor total do 
        
        
        calcularValorTotalEstoque(dadosEstoque);
        calcularItensTotalEstoque(dadosEstoque);
    }
    
    // Cacula valor total do inventário (por produto).
    void Relatorio::calcularValorTotalEstoque(const vector<Produto>& dadosEstoque){
        valorTotalEstoque = 0.0; // zera antes de somar
        
        for (const auto& item : dadosEstoque) {
            double valorItem = item.getValor_unit() * item.getSaldo_estoque();
            valorTotalEstoque += valorItem;
        }
    }
    
    // Cacula valor total do inventário (por produto).
    void Relatorio::calcularItensTotalEstoque(const vector<Produto>& dadosEstoque){
        itensTotalEstoque = 0; // zera antes de somar
        
        for (const auto& item : dadosEstoque) {
            itensTotalEstoque += item.getSaldo_estoque();
        }
    }
    
// = = = = = ENTRADAS DE DADOS (métodos de manipulação) = = = = =

    // Registra entrada ao historico - registro minimo
    void Relatorio::registrarEntrada(const Produto& ent) {   //recebe venda realizada
            // registro minimo 
        double valorProduto_totEntrad = ent.getValor_unit() * ent.getSaldo_estoque();

        //produtos_por_categoria[categoria]++;
        //unid_por_categoria[categoria] += p.getSaldo_estoque();
        //valorTotal_Categoria[categoria] += valorProduto;
        valorTotalEstoque += valorProduto_totEntrad;
        itensTotalEstoque += ent.getSaldo_estoque();
        
        //Criação do registro que ira para o relatorio
        itemMov entd;
        entd.nomeProduto = ent.getNome();
        entd.quantidade = ent.getSaldo_estoque(); // ver Se você deseja registrar apenas a QUANTIDADE QUE ENTROU, 
        entd.valorTotal = valorProduto_totEntrad;
        entd.data = std::chrono::system_clock::now();  //falta teste 
        
        entradas_Historico.push_back(entd);      //add a entrada recebida ao vector
        
  
        
        
        
        
        
        
        
        
// ===>>>    atualizar para registrar data-hora e usar estrutura padrao
        
    }

    // Adiciona valores de categorias ao respectivo container.
    void Relatorio::adicionarCategoria(const string& nome) {
        categoriasUnicas.insert(nome);
    }
    
    //Adiciona valores de produtos ao respectivo container de categorias.
    void Relatorio::adicionarProd_Categoria(const string& nomeProduto, const string& categoria){
        produtosDaCategoria[categoria].insert(nomeProduto);
    }
    
    
// = = = = = SAIDAS DE DADOS (métodos de manipulação) = = = = =
    
    //Busca valor total (encapsulado privado) 
    double Relatorio::getvalorTotalInventario(){
        return valorTotalEstoque;
    };
    
    //Busca total de itens em estoque (encapsulado privado)
    int Relatorio::getitensTotalInventario(){
        return itensTotalEstoque;
    };
    
    //Registra venda ao historico 
    void Relatorio::registrarVenda(const itemMov& v) {   //recebe venda realizada
        vendas_Historico.push_back(v);      //add a venda recebida ao vector
    }
    

// = = = = = IMPRESSOES EM TELA = = = = = //
    
    //item ja cadastrado
    void Relatorio::itensJaCadastrados(const Estoque& analisado){
        // Acessa os dados privados de Estoque através do método público
        const vector<Produto>& dadosEstoque = analisado.getEstoque();
        
        for (const auto& item : dadosEstoque) {
                // Lógica para gerar o relatório com os dados do produto
                item.exibirproduto();
            }
    }
    
    //Exibe inventário completo ====>>> (sem saldos zerados)
    void Relatorio::gerarInventarioCompleto(const Estoque& analisado) {
        // Acessa os dados privados de Estoque através do método público
        const vector<Produto>& dadosEstoque = analisado.getEstoque();
        
        cout << "\n= = = = = = INVENTARIO POR ITEM - TODOS OS PRODUTOS (sem saldos zerados) = = = = = " << endl;
        for (const auto& item : dadosEstoque) { 
            if(item.getSaldo_estoque()>0){
                item.exibirproduto(); 
                cout<<" | Valor Total: "<< item.calcularValorTotalItem()<<endl;
            }
    } 
        cout << "\n- - - - - - - - - - - - - - - " << endl;
        cout<<"Total de itens em estoque: "<< getitensTotalInventario()<<endl;
        cout<<"Valor Total do Inventario (R$): "<< getvalorTotalInventario()<<endl;
        cout << "\n====================" << endl;
    }     
    
    //Exibe todas as entradas registradas
    void Relatorio::relatorioHistoricoEntradas() const {
        cout << "\n======= HISTÓRICO DE ENTRADAS =======" << endl;
        for (const auto& registro : entradas_Historico)       //percorre todos os registros do vector
            exibirItem(registro);                          //exibe os registros do vector em tela
        cout << "====================================" << endl;
    }
    
    //Exibe venda em tela
    void Relatorio::exibirItem(const itemMov& v) const {    //recebe e exibe em tela uma venda
        cout << "Item: " << v.nomeProduto
             << " | Qtd: " << v.quantidade
             << " | Total: R$ " << v.valorTotal
             << endl;
    }
    
    //Exibe todas as vendas registradas
    void Relatorio::relatorioHistoricoVendas() const {
        cout << "\n======= HISTÓRICO DE VENDAS =======" << endl;
        for (const auto& registro : vendas_Historico)       //percorre todos os registros do vector
            exibirItem(registro);                          //exibe os registros do vector em tela
        cout << "====================================" << endl;
    }
    
    // Lista e imprime as categorias do sistema
    void Relatorio::exibirCategorias(){
        cout << "\n======= CATEGORIAS DOS PRODUTOS =======" << endl;
        for (const string& elemento : categoriasUnicas){
        cout << "- " << elemento << endl;
        }
        cout << "====================================" << endl;
    }
    
    // Lista e imprime em tela os itens de cada categoria do sistema
    void Relatorio::imprimirProdutosPorCategoria() const {
    cout << "\n======= PRODUTOS DAS CATEGORIAS =======" << endl;
        for (const auto& par : produtosDaCategoria) {
            const auto& categoria = par.first;      //categoria = chave
            const auto& produtos = par.second;      //produto (nome) = valor
            
            cout << "# Categoria: " << categoria << "\n";
            for (const auto& item : produtos) {
                std::cout << "  - " << item << "\n";
            }
            cout << "\n";
        }
        cout << "====================================" << endl;
    }
    
    void Relatorio::exibirEstatisticasPorCategoria() const {
    cout << "\n=== RELATÓRIO DE ESTATÍSTICAS POR CATEGORIA ===" << std::endl;
    
    // Iteramos sobre o mapa de contagem de produtos (carteira).
    // Assumimos que as chaves (categorias) são as mesmas nos três mapas.
    for (const auto& par : produtos_por_categoria) {
        const string& categoria = par.first;
        int contagem_produtos = par.second; // Quantidade de tipos de produtos (ex: 5 tipos)

        // Buscamos os valores correspondentes nos outros mapas:
        // Nota: O método .at() é usado para acessar o valor, pois já sabemos que a chave existe
        // se ela veio do loop de produtos_por_categoria.
        int unidades_totais = unid_por_categoria.at(categoria);
        double valor_total = valorTotal_Categoria.at(categoria);

        cout << "\n # CATEGORIA: " << categoria << std::endl;
        
        cout << std::fixed << std::setprecision(2); // Formatação para valores monetários

        cout << "  - Tipos de produtos : " << contagem_produtos << std::endl;
        cout << "  - Unidades em estoque (Total): " << unidades_totais << std::endl;
        cout << "  - Valor total em estoque (R$): " << valor_total << std::endl;
    }
    
    cout << "==========================================" << std::endl;
    }