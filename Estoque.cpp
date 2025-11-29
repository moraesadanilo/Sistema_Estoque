#include <vector>
#include <map>
#include <set>
#include <string>
#include <chrono>
#include "Produto.h"
#include "Estoque.h"
#include "Relatorio.h"
using namespace std;

    itemMov Estoque::montarRegistro(const Produto& item, int quantidade) {
        itemMov registro;
            registro.nomeProduto = item.getNome();
            registro.quantidade = quantidade;
            registro.valorTotal = item.getValor_unit() * quantidade;
            registro.data = std::chrono::system_clock::now();

            // Busca a categoria usando o mapa interno da Estoque (categoriaDoProduto)
            auto it = categoriaDoProduto.find(item.getNome());
            if (it != categoriaDoProduto.end()) {
                registro.categoria = it->second;
            } else {
                registro.categoria = "Nao Registrada"; // Ou use o valor padrão do struct
            }

        return registro;
    }
    
    //= = = = ACESSO = = = = 
    // Permite que outras classe leia os dados, mas não os modifique.
    const vector<Produto>& Estoque::getEstoque() const {
        return estoque;
    }                                                                  //ok
    // Getter para o mapa de categorias (apenas leitura)
    const map<string, string>& Estoque::getCategorias() const {
        return categoriaDoProduto;
    }                                                           //ok
    
    ////////// = = = CONSTRUTORES = = = //////////  

    //construtor construtor que recebe o objeto Relatorio existente.
    Estoque::Estoque(Relatorio& rel) : relatorio(rel) {}
    
    //= = adição de itens sem parametros - solicitado ao usuario = = //
    void Estoque::adicionarProduto(){
        string nome;
        //string categ;
        double valor_unit; //preço
        int quantidade;
        
        cout << "Nome do produto: ";
        getline(cin, nome);
        cout << "Valor unitario (R$): ";
        cin >> valor_unit;
        cout << "Quantidade: ";
        cin >> quantidade;

        estoque.push_back( Produto(nome, valor_unit, quantidade));
        //relatorio.registrarEntrada(const itemMov& ent);
        
    }

    //consulta e exibição de produto pelo nome dentro do container vector
    void Estoque::consultarProduto(string nome){
        int cont = 0;
        for (const auto& item : estoque) {
            if(item.getNome() == nome){
                item.exibirproduto();
                cont++;
            }
        }
        if(cont==0) cout<<"Produto nao encontrado";
    }
    
    // Tamanho do estoque total
    int Estoque::tamanhoEstoque(){
        return estoque.size();    
    }
    
// = = = = =  ATUALIZADORES = = = = = 
    //MAP: define a qual categoria o podutos fará parte
    void Estoque::definirCategoria(const string& nomeProd, const string& categ){
        categoriaDoProduto[nomeProd]=categ;                     // chave = nome do produto & valor = categoria.
        produtosDaCategoria[categ].insert(nomeProd);            // valor = categoria alimentando o SET de categorias unicas.
        relatorio.adicionarCategoria(categ);                    // envia pro Relatorio a categoria alimentando o SET de categorias unicas.
        relatorio.adicionarProd_Categoria(nomeProd, categ);
        
    } 

/////////// = = = = = = MOVIMENTO DE MATERIAIS = = = = = 
    
    // Entrada de itens por função
    void Estoque::saidaEstoque(const string& nome) {
            bool encontrado = false;
        
        // Encontra o produto no vetor 'estoque'
        for (auto& item : estoque) {
            if (item.getNome() == nome) {
                encontrado = true;
                cout << "Quantidade de "<< nome <<" a ser vendida (saida): ";
                int n;
                cin >> n;   //  <<<=============   ver logica para ser 1 por padrão     
                
                //  valida se há saldo suficiente para saída na classe Produto
                bool venda_realizada = item.saida(item, n); 
                
                    if (venda_realizada) {
                        // Monta e registra no histórico de venda que fica na classe Relatorio
                        itemMov venda = montarRegistro(item, n);
                        relatorio.registrarVenda(venda); 
                        
                        std::cout << "Venda realizada e registrada com sucesso!" << std::endl;
                    break;
                    }
            }
        }
            
        if (!encontrado) {
            cout << "Produto nao encontrado." << std::endl;
        }
    }
    // = = adição de itens com 3 parametros = = //
    void Estoque::adicionarProduto(string nome, double valor_unit, int quantidade){
        estoque.push_back( Produto(nome, valor_unit, quantidade)); 
        relatorio.registrarEntrada(estoque.back());
    }
    // = = adição de itens com 2 parametros = = //
    void Estoque::adicionarProduto(string nome, double valor_unit){
        estoque.push_back( Produto(nome, valor_unit)); 
        relatorio.registrarEntrada(estoque.back());
    }
    // = = adição de itens com 1 parametros = = //
    void Estoque::adicionarProduto(string nome){
        estoque.push_back( Produto(nome));
        relatorio.registrarEntrada(estoque.back());
    }



//=============>>  revisar como e implementar  depois//
/*
// adiciona item a estoque exixtente por função
void Estoque::entradaEstoque(const std::string& nome) {
    bool encontrado = false;
    
    // 1. Encontra o produto no vetor 'estoque'
    for (auto& item : estoque) {
        if (item.getNome() == nome) {
            encontrado = true;
            std::cout << "Quantidade a ser adicionada (entrada): ";
            int n;
            std::cin >> n;

            // 2. Chama o método de entrada da classe Produto
            item.entrada(item, n);
            
            // 3. Monta e registra o histórico de entrada no Relatorio
            itemMov entrada = montarRegistro(item, n, "Entrada");
            relatorio.registrarEntrada(entrada); 
            
            std::cout << "Entrada registrada com sucesso!" << std::endl;
            break;
        }
    }
    if (!encontrado) {
        std::cout << "Produto nao encontrado." << std::endl;
    }
}
*/


/*    
***    //Exibe item movimentado 
***   void exibirItemEst(const Movimentacao& v){
***   cout<<"Item: "<<v.nomeProduto<<" | Qtd: "<<v.quantidade<< " | Valor total: R$ "<<v.valorTotal<<endl;
    }
*/