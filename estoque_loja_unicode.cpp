#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <chrono>
using namespace std;
struct itemMov {
        string nomeProduto;
        string categoria = "Nao registrada";
        int quantidade;
        double valorTotal;
        std::chrono::system_clock::time_point data;  
    };                 //Estrutura para item em movimentacao
// ############ ASSINATURAS ##########
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
    
    //Classe filha, ex celular -> Fab/marca - modelo - etc
    //Classe filha, ex vestuario -> Fab/marca - modelo - tamanho
};
///////////////////////////
// 1. Declaração Forward
class Relatorio; // Diga ao compilador: "Relatorio é um nome de classe"
//////////////////////////////////////////////////////////////
class Estoque{
private:
    //Relacionamento//
    Relatorio& relatorio;         // referência ao objeto Relatorio                                 //ok
    //NÃO cria um objeto Relatorio, ele usa um que já existe.
    
    //VECTORES: 
    vector<Produto> estoque;            //estoque completo - privado                                //ok
    // Associação produto -> categoria.
    map<string, string> categoriaDoProduto;         // chave = nome do produto & valor = categoria. //ok
    map<string, set<string>>produtosDaCategoria;    // chave = categoria  & valor = nome do produto
    
    itemMov montarRegistro(const Produto& item, int quantidade) {
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
    

public:
    //= = = = ACESSO = = = = 
    // Permite que outras classe leia os dados, mas não os modifique.
    const vector<Produto>& getEstoque() const {
        return estoque;
    }                                                                  //ok
    // Getter para o mapa de categorias (apenas leitura)
    const map<string, string>& getCategorias() const {
        return categoriaDoProduto;
    }                                                           //ok
    
    ////////// = = = CONSTRUTORES = = = //////////  
    //link para class Relatório
    
    //construtor construtor que recebe o objeto Relatorio existente.
    Estoque(Relatorio& rel) : relatorio(rel) {}
    //= = adição de itens sem parametros - solicitado ao usuario = = //
    void adicionarProduto(){
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
    void consultarProduto(string nome){
        int cont = 0;
        for (const auto& item : estoque) {
            if(item.getNome() == nome){
                item.exibirproduto();
                cont++;
            }
        }
        if(cont==0) cout<<"Produto nao encontrado";
    }
    
    // = = = = = SAIDAS  = = = = =
    void saidaEstoque(const string& nome);
/*    
***    //Exibe item movimentado 
***   void exibirItemEst(const Movimentacao& v){
***   cout<<"Item: "<<v.nomeProduto<<" | Qtd: "<<v.quantidade<< " | Valor total: R$ "<<v.valorTotal<<endl;
    }
*/
    // Tamanho do estoque total
    int tamanhoEstoque(){
        return estoque.size();    
    }
};
/////////////////////////////////////////////////////////////
class Relatorio{
private:
   
    double valorTotalEstoque;
    int itensTotalEstoque;
    
    
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
    void calcularEstatisticas(const Estoque& loja){   // Baseado em categorias 
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
    void calcularValorTotalEstoque(const vector<Produto>& dadosEstoque){
        valorTotalEstoque = 0.0; // zera antes de somar
        
        for (const auto& item : dadosEstoque) {
            double valorItem = item.getValor_unit() * item.getSaldo_estoque();
            valorTotalEstoque += valorItem;
        }
    }
    
    // Cacula valor total do inventário (por produto).
    void calcularItensTotalEstoque(const vector<Produto>& dadosEstoque){
        itensTotalEstoque = 0; // zera antes de somar
        
        for (const auto& item : dadosEstoque) {
            itensTotalEstoque += item.getSaldo_estoque();
        }
    }
    
// = = = = = ENTRADAS DE DADOS (métodos de manipulação) = = = = =

    // Registra entrada ao historico - registro minimo
    void registrarEntrada(const Produto& ent) {   //recebe venda realizada
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
    void adicionarCategoria(const string& nome) {
        categoriasUnicas.insert(nome);
    }
    
    //Adiciona valores de produtos ao respectivo container de categorias.
    void adicionarProd_Categoria(const string& nomeProduto, const string& categoria){
        produtosDaCategoria[categoria].insert(nomeProduto);
    }
    
    
// = = = = = SAIDAS DE DADOS (métodos de manipulação) = = = = =
    
    //Busca valor total (encapsulado privado) 
    double getvalorTotalInventario(){
        return valorTotalEstoque;
    };
    
    //Busca total de itens em estoque (encapsulado privado)
    int getitensTotalInventario(){
        return itensTotalEstoque;
    };
    
    //Registra venda ao historico 
    void registrarVenda(const itemMov& v) {   //recebe venda realizada
        vendas_Historico.push_back(v);      //add a venda recebida ao vector
    }
    

// = = = = = IMPRESSOES EM TELA = = = = = //
    
    //item ja cadastrado
    void itensJaCadastrados(const Estoque& analisado){
        // Acessa os dados privados de Estoque através do método público
        const vector<Produto>& dadosEstoque = analisado.getEstoque();
        
        for (const auto& item : dadosEstoque) {
                // Lógica para gerar o relatório com os dados do produto
                item.exibirproduto();
            }
    }
    
    //Exibe inventário completo ====>>> (sem saldos zerados)
    void gerarInventarioCompleto(const Estoque& analisado) {
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
    void relatorioHistoricoEntradas() const {
        cout << "\n======= HISTÓRICO DE ENTRADAS =======" << endl;
        for (const auto& registro : entradas_Historico)       //percorre todos os registros do vector
            exibirItem(registro);                          //exibe os registros do vector em tela
        cout << "====================================" << endl;
    }
    
    //Exibe venda em tela
    void exibirItem(const itemMov& v) const {    //recebe e exibe em tela uma venda
        cout << "Item: " << v.nomeProduto
             << " | Qtd: " << v.quantidade
             << " | Total: R$ " << v.valorTotal
             << endl;
    }
    
    //Exibe todas as vendas registradas
    void relatorioHistoricoVendas() const {
        cout << "\n======= HISTÓRICO DE VENDAS =======" << endl;
        for (const auto& registro : vendas_Historico)       //percorre todos os registros do vector
            exibirItem(registro);                          //exibe os registros do vector em tela
        cout << "====================================" << endl;
    }
    
    // Lista e imprime as categorias do sistema
    void exibirCategorias(){
        cout << "\n======= CATEGORIAS DOS PRODUTOS =======" << endl;
        for (const string& elemento : categoriasUnicas){
        cout << "- " << elemento << endl;
        }
        cout << "====================================" << endl;
    }
    
    // Lista e imprime em tela os itens de cada categoria do sistema
    void imprimirProdutosPorCategoria() const {
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
    
    void exibirEstatisticasPorCategoria() const {
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
    
};

////////////////////////////////////////////////////////////


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

// ############ IMPLEMENTAÇÕES ##########
//CONSTRUTOR://
//genericos
//Produto::Produto(string n, double u, int s) : nome(n), valor_unit(u), saldo_estoque(s){}
Produto::Produto(string n, double u) : nome(n), valor_unit(u), saldo_estoque(0){}
Produto::Produto(string n) : nome(n), valor_unit(0), saldo_estoque(0){} 
// construtor padrão, inicializa com valores neutros
Produto::Produto() {
        setNome("");
        setValorUni(0.0);
        setSaldoEst(0);
}
//com validação
Produto::Produto(string n, double u, int s){ 
    setNome(n);      
    setValorUni(u);     
    setSaldoEst(s);    
} 

//ENTRADAS E MODIFICAÇÕES//
void Produto::entrada(Produto &item, int qtd){
        if(qtd>0){
            item.saldo_estoque+=qtd;
            cout<<"Entrada realizada com sucesso. Novo estoque: "<<item.getSaldo_estoque()<<endl;
        }else{
            cout<<"Valor invalido!"<<endl;
        }
};
void Produto::alteraPreco(Produto &item, double valor){
    if(valor>=0 && valor!=item.valor_unit){
        item.valor_unit=valor;
        cout<<"Preço alterado com sucesso. Novo preço: "<<item.getValor_unit()<<endl;
    }else{
        cout<<"Valor invalido!"<<endl;
        //valor igual anterior
    }
            
};
// SETTERS - para modificar com validação 
void Produto::setNome(string n){ 
    if (n.length() > 0) { 
        nome = n; 
    }else { 
    cout << "Erro: Nome não pode ser vazio!" << endl; 
        nome = "Sem nome"; 
    } 
};
void Produto::setValorUni(double u){
    if (u > 0 ) { 
            valor_unit = u;
        } 
    else { 
    cout << "Erro: Valor inválido! Mantendo valor anterior." <<endl;} 
};     
void Produto::setSaldoEst(int s){
    if (s > 0 ) { 
         saldo_estoque = s;
        } else { 
            cout << "Erro: Valor inválido! Mantendo valor anterior." <<endl;
        }
};

//SAIDAS E CONSULTAS//
    bool Produto::saida(Produto &item, int qtd){
            if(qtd<=0){
                cout<<"ERRO! Valor invalido."<<endl;
                return false;
            } else if(saldo_estoque>=qtd){
              item.saldo_estoque-=qtd;
              return true;
              //cout<<"Solicitacao atendida;
            }else{
                cout<<"Saldo insuficiente no estoque!"<<endl;
                return false;
            }
    };
    
    //Calcular valor total de cada item 
    double Produto::calcularValorTotalItem() const{
        return valor_unit * saldo_estoque;
    }
    
    // Exibe informações do produto
    void Produto::exibirproduto()const{
            cout<<"Item: "<<nome<< " | Valor unitario: "<<valor_unit<< " | Estoque atual: "<<saldo_estoque<<endl;
    };
    string Produto::getNome() const{
        return nome;
    };
    /*string Produto::getcategoria() const{
            return categoria;
    };*/
    double Produto::getValor_unit() const{
            return valor_unit;
    };
    int Produto::getSaldo_estoque() const{
            return saldo_estoque;
    };
    
///////////////////////////////////// CLASSE ESTOQUE //////////////////////////

// = = = = =  ATUALIZADORES = = = = = 
    //MAP: define a qual categoria o podutos fará parte
    void Estoque::definirCategoria(const string& nomeProd, const string& categ){
        categoriaDoProduto[nomeProd]=categ;                     // chave = nome do produto & valor = categoria.
        produtosDaCategoria[categ].insert(nomeProd);            // valor = categoria alimentando o SET de categorias unicas.
        relatorio.adicionarCategoria(categ);                    // envia pro Relatorio a categoria alimentando o SET de categorias unicas.
        relatorio.adicionarProd_Categoria(nomeProd, categ);
        
    } 

// = = = = = = MOVIMENTO DE MATERIAIS = = = = = 
// Entrada de itens por função
void Estoque::saidaEstoque(const string& nome) {
        bool encontrado = false;
    
    // Encontra o produto no vetor 'estoque'
    for (auto& item : estoque) {
        if (item.getNome() == nome) {
            encontrado = true;
            cout << "Quantidade de "<< nome <<" a ser vendida (saida): ";
            int n;
/*====>*/   cin >> n;   //ver logica para ser 1 por padrão 
            
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



//===>>  revisar depois//
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

