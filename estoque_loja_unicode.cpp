#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
using namespace std;

class Produto {
private:
    string nome;
    string categoria;
    double preco;  //valor initario
    int saldo_estoque;
    //int id;      //como se auto gerar?
    
public:
//CONSTRUTOR://
    Produto(string n, double p, string c, int s){
        nome=n;
        preco=p;
        saldo_estoque=s;
        categoria=c;
    };
    Produto(string n, double p){
        nome=n;
        preco=p;
        categoria="";
        saldo_estoque= 0;
    };
    Produto(string n){
        nome=n;
        categoria="";
        preco=0;
        saldo_estoque= 0;
    };
//ENTRADAS E MODIFICAÇÕES//
    void entrada(Produto &item, int qtd){
        if(qtd>0){
            item.saldo_estoque+=qtd;
            cout<<"Entrada realizada com sucesso. Novo estoque: "<<item.getsaldo_estoque()<<endl;
        }else{
            cout<<"Valor invalido!"<<endl;
        }
    };
    void alterapreco(Produto &item, double valor){
        if(valor>=0 && valor!=item.preco){
            item.preco=valor;
            cout<<"Preço alterado com sucesso. Novo preço: "<<item.getpreco()<<endl;
        }else{
            cout<<"Valor invalido!"<<endl;
            //valor igual anterior
        }
            
    };
    // SETTERS - para modificar com validação 
    void setNome(string n){ 
        if (n.length() > 0) { 
            nome = n; 
        }else { 
        cout << "Erro: Nome não pode ser vazio!" << endl; 
            nome = "Sem nome"; 
        } 
    }
    
    //SAIDAS E CONSULTAS//
        void saida(Produto &item, int qtd){
            if(saldo_estoque>qtd){
              item.saldo_estoque-=qtd;
              cout<<"Entrada realizada com sucesso. Novo estoque: "<<item.getsaldo_estoque()<<endl;
            }else{
                cout<<"Valor invalido!"<<endl;
            }
        };
        void exibirproduto()const{
            cout<<"Item: "<<nome<< " | Preco: "<<preco<< " | Estoque atual: "<<saldo_estoque<<endl;
        };
        
        string getnome(){
            return nome;
        }
        string getcategoria() const{
            return categoria;
        }
        double getpreco() const{
            return preco;
        }
        int getsaldo_estoque() const{
            return saldo_estoque;
        }

};

    //Departamento - linha
    //marca modelo ano
    //Classe filha, ex celular -> Fab/marca - modelo - etc
    //Classe filha, ex vestuario -> Fab/marca - modelo - tamanho

int main() {
    vector<Produto> estoque;

    cout<<"Estoque inical: ";
    cout<<estoque.size()<<endl;  //tamanho do estoque
    //cout<<estoque.empty()<<endl; //estoque está vazio?
    
    estoque.push_back(Produto("Celular", 2000, "Eletronicos", 1));
    estoque.push_back(Produto("Camisa", 24.9));
    estoque.push_back(Produto("Vinho"));
    estoque.push_back(Produto("Tablet", 2000, "Eletronicos", 5));
    estoque.push_back(Produto("Mouse", 35.5, "Informatica", 100));
    estoque.push_back(Produto("Notebook", 3000, "Informatica", 25));


    cout<<"Estoque final: ";
    cout<<estoque.size()<<endl;  //tamanho do estoque
    //<<estoque.empty()<<endl; //estoque está vazio?

    // SET: Categorias disponíveis
    set<string> categorias;
    categorias.insert("Telefonia");
    categorias.insert("Vestuario");
    categorias.insert("Perfumaria");
    categorias.insert("Bebidas");

    

    // 3. MAP: contagem de produtos por categoria
    map<string, int> produtos_por_categoria;          // produto por categoria 
    for (const Produto& item : estoque) {         //na classe Produto, vector estoque
        produtos_por_categoria[item.getcategoria()]++; 
    } 
    
    // 3. MAP:  valor total em estoque por categoria
    map<string, double> valorTotal_categoria;       
    for (const Produto& item : estoque) {         
        
        valorTotal_categoria[item.getcategoria()]+= item.getpreco() *item.getsaldo_estoque(); 
    } 

    
    cout << "\n--- PRODUTO POR CATEGORIA (map) ---" << endl; 
    for (const auto& par : produtos_por_categoria) { 
    cout << par.first << ": " << par.second << " produto(s)" << endl; 
    } 

    cout << "\n--- VALOR TOTAL DA CATEGORIA (map) ---" << endl;
    for (const auto& par : valorTotal_categoria) { 
    cout << par.first << ": R$ " << par.second << " em produto(s)" << endl; 
    } 


    cout << "\n=== ESTATISTICAS ===" << endl;
    cout << "\n--- TODOS OS PRODUTOS (vector) ---" << endl; 
    for (const Produto& item : estoque) { 
        item.exibirproduto();
        //cout<<endl;
    } 

    return 0;
}
